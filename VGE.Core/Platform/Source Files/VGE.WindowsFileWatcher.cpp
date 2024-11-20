#include "../Header Files/VGE.WindowsFileWatcher.h"
#include <filesystem>

namespace VGE {

WindowsFileWatcher::WindowsFileWatcher(const std::string& path, bool recursive, FileChangeCallback callback)
    : m_path(path)
    , m_recursive(recursive)
    , m_callback(callback)
    , m_directoryHandle(INVALID_HANDLE_VALUE)
    , m_stopEvent(INVALID_HANDLE_VALUE)
    , m_running(false) {

    // Create stop event
    m_stopEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
    if (m_stopEvent == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("Failed to create stop event");
    }

    // Open directory for monitoring
    m_directoryHandle = CreateFileA(
        path.c_str(),
        FILE_LIST_DIRECTORY,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        nullptr,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
        nullptr
    );

    if (m_directoryHandle == INVALID_HANDLE_VALUE) {
        CloseHandle(m_stopEvent);
        throw std::runtime_error("Failed to open directory for monitoring");
    }
}

WindowsFileWatcher::~WindowsFileWatcher() {
    stop();

    if (m_directoryHandle != INVALID_HANDLE_VALUE) {
        CloseHandle(m_directoryHandle);
    }

    if (m_stopEvent != INVALID_HANDLE_VALUE) {
        CloseHandle(m_stopEvent);
    }
}

void WindowsFileWatcher::start() {
    if (m_running) return;

    m_running = true;
    m_watchThread = std::thread(&WindowsFileWatcher::watchThread, this);
}

void WindowsFileWatcher::stop() {
    if (!m_running) return;

    m_running = false;
    SetEvent(m_stopEvent);

    if (m_watchThread.joinable()) {
        m_watchThread.join();
    }
}

bool WindowsFileWatcher::isRunning() const {
    return m_running;
}

const std::string& WindowsFileWatcher::getWatchPath() const {
    return m_path;
}

void WindowsFileWatcher::watchThread() {
    std::vector<BYTE> buffer(BUFFER_SIZE);
    OVERLAPPED overlapped = {};
    overlapped.hEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);

    if (overlapped.hEvent == INVALID_HANDLE_VALUE) {
        m_running = false;
        return;
    }

    while (m_running) {
        DWORD bytesReturned = 0;
        ResetEvent(overlapped.hEvent);

        // Start async read
        bool success = ReadDirectoryChangesW(
            m_directoryHandle,
            buffer.data(),
            static_cast<DWORD>(buffer.size()),
            m_recursive,
            FILE_NOTIFY_CHANGE_FILE_NAME |
            FILE_NOTIFY_CHANGE_DIR_NAME |
            FILE_NOTIFY_CHANGE_ATTRIBUTES |
            FILE_NOTIFY_CHANGE_SIZE |
            FILE_NOTIFY_CHANGE_LAST_WRITE |
            FILE_NOTIFY_CHANGE_CREATION,
            &bytesReturned,
            &overlapped,
            nullptr
        );

        if (!success && GetLastError() != ERROR_IO_PENDING) {
            break;
        }

        // Wait for either file change or stop event
        HANDLE handles[] = { overlapped.hEvent, m_stopEvent };
        DWORD waitResult = WaitForMultipleObjects(2, handles, FALSE, INFINITE);

        if (waitResult == WAIT_OBJECT_0) {
            // File change event
            if (GetOverlappedResult(m_directoryHandle, &overlapped, &bytesReturned, FALSE)) {
                processNotification(buffer.data());
            }
        }
        else if (waitResult == WAIT_OBJECT_0 + 1) {
            // Stop event
            CancelIoEx(m_directoryHandle, &overlapped);
            break;
        }
        else {
            // Error
            break;
        }
    }

    CloseHandle(overlapped.hEvent);
    m_running = false;
}

void WindowsFileWatcher::processNotification(const BYTE* buffer) {
    auto info = reinterpret_cast<const FILE_NOTIFY_INFORMATION*>(buffer);

    while (true) {
        std::wstring filename(info->FileName, info->FileNameLength / sizeof(WCHAR));
        
        // Convert wide string to UTF-8
        int size = WideCharToMultiByte(CP_UTF8, 0, filename.c_str(), -1, nullptr, 0, nullptr, nullptr);
        std::string utf8Filename(size, 0);
        WideCharToMultiByte(CP_UTF8, 0, filename.c_str(), -1, &utf8Filename[0], size, nullptr, nullptr);

        // Create file change event
        FileChangeEvent event;
        event.path = std::filesystem::path(m_path) / utf8Filename;
        event.type = translateAction(info->Action);
        event.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();

        // Handle rename events
        if (info->Action == FILE_ACTION_RENAMED_OLD_NAME) {
            if (info->NextEntryOffset) {
                auto nextInfo = reinterpret_cast<const FILE_NOTIFY_INFORMATION*>(
                    reinterpret_cast<const BYTE*>(info) + info->NextEntryOffset
                );
                if (nextInfo->Action == FILE_ACTION_RENAMED_NEW_NAME) {
                    std::wstring newFilename(nextInfo->FileName, nextInfo->FileNameLength / sizeof(WCHAR));
                    size = WideCharToMultiByte(CP_UTF8, 0, newFilename.c_str(), -1, nullptr, 0, nullptr, nullptr);
                    std::string newUtf8Filename(size, 0);
                    WideCharToMultiByte(CP_UTF8, 0, newFilename.c_str(), -1, &newUtf8Filename[0], size, nullptr, nullptr);
                    event.oldPath = event.path;
                    event.path = std::filesystem::path(m_path) / newUtf8Filename;
                }
            }
        }

        // Invoke callback
        if (m_callback) {
            m_callback(event);
        }

        // Move to next entry if any
        if (info->NextEntryOffset == 0) {
            break;
        }

        info = reinterpret_cast<const FILE_NOTIFY_INFORMATION*>(
            reinterpret_cast<const BYTE*>(info) + info->NextEntryOffset
        );
    }
}

FileChangeType WindowsFileWatcher::translateAction(DWORD action) const {
    switch (action) {
        case FILE_ACTION_ADDED:
            return FileChangeType::CREATED;
        case FILE_ACTION_REMOVED:
            return FileChangeType::DELETED;
        case FILE_ACTION_MODIFIED:
            return FileChangeType::MODIFIED;
        case FILE_ACTION_RENAMED_OLD_NAME:
        case FILE_ACTION_RENAMED_NEW_NAME:
            return FileChangeType::RENAMED;
        default:
            return FileChangeType::MODIFIED;
    }
}

} // namespace VGE

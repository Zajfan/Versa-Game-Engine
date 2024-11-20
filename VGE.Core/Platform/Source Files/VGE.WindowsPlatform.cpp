#include "../Header Files/VGE.WindowsPlatform.h"
#include "VGE.WindowsWindow.h"
#include "VGE.WindowsFileWatcher.h"
#include <stdexcept>
#include <vector>
#include <string>
#include <Windows.h>
#include <unordered_map>

namespace VGE {

WindowsPlatform::WindowsPlatform() : m_initialized(false) {
}

WindowsPlatform::~WindowsPlatform() {
    shutdown();
}

bool WindowsPlatform::initialize() {
    if (m_initialized) return true;
    // Initialization code specific to Windows
    m_initialized = true;
    return m_initialized;
}

void WindowsPlatform::shutdown() {
    if (!m_initialized) return;
    // Cleanup code specific to Windows
    m_initialized = false;
}

std::unique_ptr<Window> WindowsPlatform::createWindow(const std::string& title, int width, int height) {
    return std::make_unique<WindowsWindow>(title, width, height);
}

void WindowsPlatform::pollEvents() {
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        // Consider using a more efficient event dispatch mechanism
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    // Potential optimization: reduce polling frequency or use a more efficient mechanism
}

bool WindowsPlatform::fileExists(const std::string& path) const {
    static std::unordered_map<std::string, bool> fileCache;
    auto it = fileCache.find(path);
    if (it != fileCache.end()) {
        return it->second;
    }
    DWORD attrib = GetFileAttributesA(path.c_str());
    bool exists = (attrib != INVALID_FILE_ATTRIBUTES && !(attrib & FILE_ATTRIBUTE_DIRECTORY));
    fileCache[path] = exists;
    return exists;
}

bool WindowsPlatform::createDirectory(const std::string& path) {
    if (fileExists(path)) return true;
    return CreateDirectoryA(path.c_str(), nullptr) || GetLastError() == ERROR_ALREADY_EXISTS;
}

bool WindowsPlatform::removeDirectory(const std::string& path) {
    return RemoveDirectoryA(path.c_str()) != 0;
}

bool WindowsPlatform::copyFile(const std::string& source, const std::string& dest) {
    return CopyFileA(source.c_str(), dest.c_str(), FALSE) != 0;
}

bool WindowsPlatform::moveFile(const std::string& source, const std::string& dest) {
    return MoveFileA(source.c_str(), dest.c_str()) != 0;
}

bool WindowsPlatform::deleteFile(const std::string& path) {
    return DeleteFileA(path.c_str()) != 0;
}

uint64_t WindowsPlatform::getFileSize(const std::string& path) const {
    WIN32_FILE_ATTRIBUTE_DATA fileInfo;
    if (GetFileAttributesExA(path.c_str(), GetFileExInfoStandard, &fileInfo)) {
        LARGE_INTEGER size;
        size.HighPart = fileInfo.nFileSizeHigh;
        size.LowPart = fileInfo.nFileSizeLow;
        return size.QuadPart;
    }
    return 0;
}

uint64_t WindowsPlatform::getFileModificationTime(const std::string& path) const {
    WIN32_FILE_ATTRIBUTE_DATA fileInfo;
    if (GetFileAttributesExA(path.c_str(), GetFileExInfoStandard, &fileInfo)) {
        FILETIME ft = fileInfo.ftLastWriteTime;
        ULARGE_INTEGER ull;
        ull.LowPart = ft.dwLowDateTime;
        ull.HighPart = ft.dwHighDateTime;
        return ull.QuadPart;
    }
    return 0;
}

std::vector<std::string> WindowsPlatform::listDirectory(const std::string& path) const {
    std::vector<std::string> fileList;
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA((path + "\\*").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        return fileList;
    }

    do {
        const std::string fileOrDir = findFileData.cFileName;
        if (fileOrDir != "." && fileOrDir != "..") {
            fileList.push_back(fileOrDir);
        }
    } while (FindNextFileA(hFind, &findFileData) != 0);

    FindClose(hFind);
    return fileList;
}

std::string WindowsPlatform::getAbsolutePath(const std::string& path) const {
    char fullPath[MAX_PATH];
    if (GetFullPathNameA(path.c_str(), MAX_PATH, fullPath, nullptr)) {
        return std::string(fullPath);
    }
    return std::string();
}

std::string WindowsPlatform::getCurrentDirectory() const {
    char buffer[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, buffer);
    return std::string(buffer);
}

bool WindowsPlatform::setCurrentDirectory(const std::string& path) {
    return SetCurrentDirectoryA(path.c_str()) != 0;
}

std::unique_ptr<FileWatcher> WindowsPlatform::createFileWatcher(const std::string& path, bool recursive, FileChangeCallback callback) {
    return std::make_unique<WindowsFileWatcher>(path, recursive, callback);
}

ProcessHandle WindowsPlatform::createProcess(const std::string& program, const std::vector<std::string>& args) {
    // Implementation for process creation
    return nullptr;
}

bool WindowsPlatform::terminateProcess(ProcessHandle handle) {
    // Implementation for process termination
    return false;
}

int WindowsPlatform::getProcessExitCode(ProcessHandle handle) {
    // Implementation for retrieving process exit code
    return -1;
}

bool WindowsPlatform::isProcessRunning(ProcessHandle handle) const {
    // Implementation to check if the process is running
    return false;
}

ThreadHandle WindowsPlatform::createThread(std::function<void()> function) {
    // Use a thread pool to manage threads efficiently
    return nullptr;
}

void WindowsPlatform::joinThread(ThreadHandle handle) {
    // Implement thread pooling to manage threads efficiently
}

void WindowsPlatform::detachThread(ThreadHandle handle) {
    // Implement thread pooling to manage threads efficiently
}

void WindowsPlatform::sleepThread(uint32_t milliseconds) {
    Sleep(milliseconds);
}

size_t WindowsPlatform::getThreadId() {
    return GetCurrentThreadId();
}

MutexHandle WindowsPlatform::createMutex() {
    // Use smart pointers for better resource management
    return nullptr;
}

void WindowsPlatform::destroyMutex(MutexHandle handle) {
    // Use smart pointers for better resource management
}

void WindowsPlatform::lockMutex(MutexHandle handle) {
    // Use smart pointers for better resource management
}

bool WindowsPlatform::tryLockMutex(MutexHandle handle) {
    // Use smart pointers for better resource management
    return false;
}

void WindowsPlatform::unlockMutex(MutexHandle handle) {
    // Use smart pointers for better resource management
}

EventHandle WindowsPlatform::createEvent(bool manualReset) {
    // Implementation for event creation
    return nullptr;
}

void WindowsPlatform::destroyEvent(EventHandle handle) {
    // Implementation to destroy an event
}

void WindowsPlatform::setEvent(EventHandle handle) {
    // Implementation to set an event
}

void WindowsPlatform::resetEvent(EventHandle handle) {
    // Implementation to reset an event
}

bool WindowsPlatform::waitForEvent(EventHandle handle, uint32_t timeout) {
    // Implementation to wait for an event
    return false;
}

std::string WindowsPlatform::getPlatformName() const {
    return "Windows";
}

std::string WindowsPlatform::getComputerName() const {
    char buffer[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(buffer);
    if (GetComputerNameA(buffer, &size)) {
        return std::string(buffer);
    }
    return std::string();
}

std::string WindowsPlatform::getUserName() const {
    char buffer[UNLEN + 1];
    DWORD size = sizeof(buffer);
    if (GetUserNameA(buffer, &size)) {
        return std::string(buffer);
    }
    return std::string();
}

uint32_t WindowsPlatform::getProcessorCount() const {
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    return sysInfo.dwNumberOfProcessors;
}

uint64_t WindowsPlatform::getTotalPhysicalMemory() const {
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    if (GlobalMemoryStatusEx(&statex)) {
        return statex.ullTotalPhys;
    }
    return 0;
}

uint64_t WindowsPlatform::getAvailablePhysicalMemory() const {
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    if (GlobalMemoryStatusEx(&statex)) {
        return statex.ullAvailPhys;
    }
    return 0;
}

std::string WindowsPlatform::getEnvironmentVariable(const std::string& name) const {
    char buffer[32767];
    DWORD size = GetEnvironmentVariableA(name.c_str(), buffer, sizeof(buffer));
    if (size > 0 && size < sizeof(buffer)) {
        return std::string(buffer, size);
    }
    return std::string();
}

bool WindowsPlatform::setEnvironmentVariable(const std::string& name, const std::string& value) {
    return SetEnvironmentVariableA(name.c_str(), value.c_str()) != 0;
}

uint64_t WindowsPlatform::getSystemTime() const {
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    ULARGE_INTEGER ull;
    ull.LowPart = ft.dwLowDateTime;
    ull.HighPart = ft.dwHighDateTime;
    return ull.QuadPart;
}

uint64_t WindowsPlatform::getHighResolutionTime() const {
    LARGE_INTEGER frequency, counter;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&counter);
    return (counter.QuadPart * 1000000) / frequency.QuadPart;
}

uint64_t WindowsPlatform::getHighResolutionFrequency() const {
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    return frequency.QuadPart;
}

bool WindowsPlatform::setClipboardText(const std::string& text) {
    if (!OpenClipboard(nullptr)) return false;
    EmptyClipboard();
    HGLOBAL hGlob = GlobalAlloc(GMEM_FIXED, text.size() + 1);
    if (!hGlob) {
        CloseClipboard();
        return false;
    }
    memcpy(hGlob, text.c_str(), text.size() + 1);
    SetClipboardData(CF_TEXT, hGlob);
    CloseClipboard();
    return true;
}

std::string WindowsPlatform::getClipboardText() const {
    if (!OpenClipboard(nullptr)) return std::string();
    HANDLE hData = GetClipboardData(CF_TEXT);
    if (!hData) {
        CloseClipboard();
        return std::string();
    }
    char* pszText = static_cast<char*>(GlobalLock(hData));
    if (!pszText) {
        CloseClipboard();
        return std::string();
    }
    std::string text(pszText);
    GlobalUnlock(hData);
    CloseClipboard();
    return text;
}

void* WindowsPlatform::loadLibrary(const std::string& path) {
    return LoadLibraryA(path.c_str());
}

void WindowsPlatform::unloadLibrary(void* handle) {
    if (handle) {
        FreeLibrary(static_cast<HMODULE>(handle));
    }
}

void* WindowsPlatform::getFunctionAddress(void* handle, const std::string& name) {
    if (handle) {
        return GetProcAddress(static_cast<HMODULE>(handle), name.c_str());
    }
    return nullptr;
}

std::string WindowsPlatform::getLastErrorMessage() const {
    DWORD errorMessageID = ::GetLastError();
    if (errorMessageID == 0) return std::string();

    LPSTR messageBuffer = nullptr;
    size_t size = FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&messageBuffer, 0, nullptr);
    std::string message(messageBuffer, size);
    LocalFree(messageBuffer);
    return message;
}

void WindowsPlatform::debugBreak() {
    __debugbreak();
}

void WindowsPlatform::outputDebugString(const std::string& text) {
    OutputDebugStringA(text.c_str());
}

std::string WindowsPlatform::getStackTrace() {
    // Implementation for retrieving stack trace
    return std::string();
}

std::wstring WindowsPlatform::utf8ToWide(const std::string& str) const {
    int sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    std::wstring wstr(sizeNeeded, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], sizeNeeded);
    return wstr;
}

std::string WindowsPlatform::wideToUtf8(const std::wstring& wstr) const {
    int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    std::string str(sizeNeeded, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], sizeNeeded, nullptr, nullptr);
    return str;
}

std::string WindowsPlatform::getLastErrorString() const {
    DWORD errorMessageID = ::GetLastError();
    if (errorMessageID == 0) return std::string();

    LPSTR messageBuffer = nullptr;
    size_t size = FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&messageBuffer, 0, nullptr);
    std::string message(messageBuffer, size);
    LocalFree(messageBuffer);
    return message;
}

} // namespace VGE

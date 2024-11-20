#pragma once

#include "../../Core/Header Files/VGE.Platform.h"
#include <Windows.h>
#include <thread>
#include <atomic>

namespace VGE {

class WindowsFileWatcher : public FileWatcher {
public:
    WindowsFileWatcher(const std::string& path, bool recursive, FileChangeCallback callback);
    ~WindowsFileWatcher() override;

    void start() override;
    void stop() override;
    bool isRunning() const override;
    const std::string& getWatchPath() const override;

private:
    void watchThread();
    void processNotification(const BYTE* buffer);
    FileChangeType translateAction(DWORD action) const;

    std::string m_path;
    bool m_recursive;
    FileChangeCallback m_callback;
    HANDLE m_directoryHandle;
    HANDLE m_stopEvent;
    std::thread m_watchThread;
    std::atomic<bool> m_running;
    static constexpr size_t BUFFER_SIZE = 32768;  // 32 KB buffer for notifications
};

} // namespace VGE

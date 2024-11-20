#pragma once

#include "../../Core/Header Files/VGE.Platform.h"
#include <Windows.h>

namespace VGE {

class WindowsWindow;
class WindowsFileWatcher;

class WindowsPlatform : public IPlatform {
public:
    WindowsPlatform();
    ~WindowsPlatform();

    // IPlatform implementation
    bool initialize() override;
    void shutdown() override;

    // Window management
    std::unique_ptr<Window> createWindow(const std::string& title, int width, int height) override;
    void pollEvents() override;

    // File system operations
    bool fileExists(const std::string& path) const override;
    bool createDirectory(const std::string& path) override;
    bool removeDirectory(const std::string& path) override;
    bool copyFile(const std::string& source, const std::string& dest) override;
    bool moveFile(const std::string& source, const std::string& dest) override;
    bool deleteFile(const std::string& path) override;
    uint64_t getFileSize(const std::string& path) const override;
    uint64_t getFileModificationTime(const std::string& path) const override;
    std::vector<std::string> listDirectory(const std::string& path) const override;
    std::string getAbsolutePath(const std::string& path) const override;
    std::string getCurrentDirectory() const override;
    bool setCurrentDirectory(const std::string& path) override;

    // File watching
    std::unique_ptr<FileWatcher> createFileWatcher(
        const std::string& path,
        bool recursive,
        FileChangeCallback callback) override;

    // Process management
    ProcessHandle createProcess(
        const std::string& program,
        const std::vector<std::string>& args) override;
    bool terminateProcess(ProcessHandle handle) override;
    int getProcessExitCode(ProcessHandle handle) override;
    bool isProcessRunning(ProcessHandle handle) const override;

    // Thread management
    ThreadHandle createThread(std::function<void()> function) override;
    void joinThread(ThreadHandle handle) override;
    void detachThread(ThreadHandle handle) override;
    void sleepThread(uint32_t milliseconds) override;
    size_t getThreadId() override;

    // Synchronization primitives
    MutexHandle createMutex() override;
    void destroyMutex(MutexHandle handle) override;
    void lockMutex(MutexHandle handle) override;
    bool tryLockMutex(MutexHandle handle) override;
    void unlockMutex(MutexHandle handle) override;

    EventHandle createEvent(bool manualReset = false) override;
    void destroyEvent(EventHandle handle) override;
    void setEvent(EventHandle handle) override;
    void resetEvent(EventHandle handle) override;
    bool waitForEvent(EventHandle handle, uint32_t timeout = UINT32_MAX) override;

    // System information
    std::string getPlatformName() const override;
    std::string getComputerName() const override;
    std::string getUserName() const override;
    uint32_t getProcessorCount() const override;
    uint64_t getTotalPhysicalMemory() const override;
    uint64_t getAvailablePhysicalMemory() const override;
    std::string getEnvironmentVariable(const std::string& name) const override;
    bool setEnvironmentVariable(const std::string& name, const std::string& value) override;

    // Time functions
    uint64_t getSystemTime() const override;
    uint64_t getHighResolutionTime() const override;
    uint64_t getHighResolutionFrequency() const override;

    // Clipboard operations
    bool setClipboardText(const std::string& text) override;
    std::string getClipboardText() const override;

    // DLL management
    void* loadLibrary(const std::string& path) override;
    void unloadLibrary(void* handle) override;
    void* getFunctionAddress(void* handle, const std::string& name) override;
    std::string getLastErrorMessage() const override;

    // Debug helpers
    void debugBreak() override;
    void outputDebugString(const std::string& text) override;
    std::string getStackTrace() override;

private:
    std::wstring utf8ToWide(const std::string& str) const;
    std::string wideToUtf8(const std::wstring& wstr) const;
    std::string getLastErrorString() const;

    HINSTANCE m_instance;
    bool m_initialized;
};

} // namespace VGE

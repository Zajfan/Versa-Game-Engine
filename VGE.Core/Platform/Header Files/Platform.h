#pragma once

#include "VGE.Core.h"
#include <string>
#include <vector>
#include <memory>
#include <functional>

namespace VGE {

// Forward declarations
class Window;
class FileWatcher;

// Platform-independent types
using FileHandle = void*;
using ThreadHandle = void*;
using ProcessHandle = void*;
using MutexHandle = void*;
using EventHandle = void*;

// File change event types
enum class FileChangeType {
    CREATED,
    MODIFIED,
    DELETED,
    RENAMED
};

// File change event data
struct FileChangeEvent {
    std::string path;
    FileChangeType type;
    std::string oldPath;  // Used for rename events
    uint64_t timestamp;
};

// File watcher callback
using FileChangeCallback = std::function<void(const FileChangeEvent&)>;

// Platform interface
class IPlatform {
public:
    virtual ~IPlatform() = default;

    // Initialization and shutdown
    virtual bool initialize() = 0;
    virtual void shutdown() = 0;

    // Window management
    virtual std::unique_ptr<Window> createWindow(const std::string& title, int width, int height) = 0;
    virtual void pollEvents() = 0;

    // File system operations
    virtual bool fileExists(const std::string& path) const = 0;
    virtual bool createDirectory(const std::string& path) = 0;
    virtual bool removeDirectory(const std::string& path) = 0;
    virtual bool copyFile(const std::string& source, const std::string& dest) = 0;
    virtual bool moveFile(const std::string& source, const std::string& dest) = 0;
    virtual bool deleteFile(const std::string& path) = 0;
    virtual uint64_t getFileSize(const std::string& path) const = 0;
    virtual uint64_t getFileModificationTime(const std::string& path) const = 0;
    virtual std::vector<std::string> listDirectory(const std::string& path) const = 0;
    virtual std::string getAbsolutePath(const std::string& path) const = 0;
    virtual std::string getCurrentDirectory() const = 0;
    virtual bool setCurrentDirectory(const std::string& path) = 0;

    // File watching
    virtual std::unique_ptr<FileWatcher> createFileWatcher(
        const std::string& path,
        bool recursive,
        FileChangeCallback callback) = 0;

    // Process management
    virtual ProcessHandle createProcess(
        const std::string& program,
        const std::vector<std::string>& args) = 0;
    virtual bool terminateProcess(ProcessHandle handle) = 0;
    virtual int getProcessExitCode(ProcessHandle handle) = 0;
    virtual bool isProcessRunning(ProcessHandle handle) const = 0;

    // Thread management
    virtual ThreadHandle createThread(std::function<void()> function) = 0;
    virtual void joinThread(ThreadHandle handle) = 0;
    virtual void detachThread(ThreadHandle handle) = 0;
    virtual void sleepThread(uint32_t milliseconds) = 0;
    virtual size_t getThreadId() = 0;

    // Synchronization primitives
    virtual MutexHandle createMutex() = 0;
    virtual void destroyMutex(MutexHandle handle) = 0;
    virtual void lockMutex(MutexHandle handle) = 0;
    virtual bool tryLockMutex(MutexHandle handle) = 0;
    virtual void unlockMutex(MutexHandle handle) = 0;

    virtual EventHandle createEvent(bool manualReset = false) = 0;
    virtual void destroyEvent(EventHandle handle) = 0;
    virtual void setEvent(EventHandle handle) = 0;
    virtual void resetEvent(EventHandle handle) = 0;
    virtual bool waitForEvent(EventHandle handle, uint32_t timeout = UINT32_MAX) = 0;

    // System information
    virtual std::string getPlatformName() const = 0;
    virtual std::string getComputerName() const = 0;
    virtual std::string getUserName() const = 0;
    virtual uint32_t getProcessorCount() const = 0;
    virtual uint64_t getTotalPhysicalMemory() const = 0;
    virtual uint64_t getAvailablePhysicalMemory() const = 0;
    virtual std::string getEnvironmentVariable(const std::string& name) const = 0;
    virtual bool setEnvironmentVariable(const std::string& name, const std::string& value) = 0;

    // Time functions
    virtual uint64_t getSystemTime() const = 0; // Returns time in milliseconds since epoch
    virtual uint64_t getHighResolutionTime() const = 0; // Returns time in nanoseconds
    virtual uint64_t getHighResolutionFrequency() const = 0;

    // Clipboard operations
    virtual bool setClipboardText(const std::string& text) = 0;
    virtual std::string getClipboardText() const = 0;

    // DLL management
    virtual void* loadLibrary(const std::string& path) = 0;
    virtual void unloadLibrary(void* handle) = 0;
    virtual void* getFunctionAddress(void* handle, const std::string& name) = 0;
    virtual std::string getLastErrorMessage() const = 0;

    // Debug helpers
    virtual void debugBreak() = 0;
    virtual void outputDebugString(const std::string& text) = 0;
    virtual std::string getStackTrace() = 0;
};

// Window interface
class Window {
public:
    virtual ~Window() = default;

    virtual void show() = 0;
    virtual void hide() = 0;
    virtual void close() = 0;
    virtual void minimize() = 0;
    virtual void maximize() = 0;
    virtual void restore() = 0;

    virtual void setTitle(const std::string& title) = 0;
    virtual void setSize(int width, int height) = 0;
    virtual void setPosition(int x, int y) = 0;
    virtual void setFullscreen(bool fullscreen) = 0;
    virtual void setVSync(bool enabled) = 0;

    virtual bool isVisible() const = 0;
    virtual bool isFocused() const = 0;
    virtual bool isMinimized() const = 0;
    virtual bool isMaximized() const = 0;
    virtual bool isFullscreen() const = 0;

    virtual void* getNativeHandle() const = 0;
    virtual void* getNativeDisplay() const = 0;

    virtual void swapBuffers() = 0;
};

// File watcher interface
class FileWatcher {
public:
    virtual ~FileWatcher() = default;

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual bool isRunning() const = 0;
    virtual const std::string& getWatchPath() const = 0;
};

// Platform factory
class PlatformFactory {
public:
    static std::unique_ptr<IPlatform> createPlatform();
};

} // namespace VGE

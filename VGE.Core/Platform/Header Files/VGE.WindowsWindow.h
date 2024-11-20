#pragma once

#include "../../Core/Header Files/VGE.Platform.h"
#include <Windows.h>
#include <string>

namespace VGE {

class WindowsWindow : public Window {
public:
    WindowsWindow(const std::string& title, int width, int height);
    ~WindowsWindow() override;

    // Window interface implementation
    void show() override;
    void hide() override;
    void close() override;
    bool shouldClose() const override;
    void setTitle(const std::string& title) override;
    void setSize(int width, int height) override;
    void setPosition(int x, int y) override;
    void getSize(int& width, int& height) const override;
    void getPosition(int& x, int& y) const override;
    void* getNativeHandle() const override;
    void processEvents() override;

    // Windows-specific methods
    HWND getWindowHandle() const { return m_hwnd; }
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:
    bool registerWindowClass();
    bool createWindow(const std::string& title, int width, int height);
    void cleanup();

    HWND m_hwnd;
    HINSTANCE m_hinstance;
    bool m_shouldClose;
    static const wchar_t* WINDOW_CLASS_NAME;
    static bool s_windowClassRegistered;
};

} // namespace VGE

#include "../Header Files/VGE.WindowsWindow.h"
#include <stdexcept>

namespace VGE {

const wchar_t* WindowsWindow::WINDOW_CLASS_NAME = L"VGE_WindowClass";
bool WindowsWindow::s_windowClassRegistered = false;

WindowsWindow::WindowsWindow(const std::string& title, int width, int height)
    : m_hwnd(nullptr)
    , m_hinstance(GetModuleHandle(nullptr))
    , m_shouldClose(false) {
    
    if (!registerWindowClass()) {
        throw std::runtime_error("Failed to register window class");
    }

    if (!createWindow(title, width, height)) {
        throw std::runtime_error("Failed to create window");
    }
}

WindowsWindow::~WindowsWindow() {
    cleanup();
}

bool WindowsWindow::registerWindowClass() {
    if (s_windowClassRegistered) {
        return true;
    }

    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;  
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = m_hinstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);  
    wc.lpszClassName = WINDOW_CLASS_NAME;
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);  
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);  

    if (!RegisterClassExW(&wc)) {
        return false;
    }

    s_windowClassRegistered = true;
    return true;
}

bool WindowsWindow::createWindow(const std::string& title, int width, int height) {
    // Convert title to wide string
    int titleSize = MultiByteToWideChar(CP_UTF8, 0, title.c_str(), -1, nullptr, 0);
    std::wstring wideTitle(titleSize, 0);
    MultiByteToWideChar(CP_UTF8, 0, title.c_str(), -1, &wideTitle[0], titleSize);

    // Calculate window size including borders
    RECT rect = { 0, 0, width, height };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

    m_hwnd = CreateWindowExW(
        0,                              // Optional window styles
        WINDOW_CLASS_NAME,              // Window class
        wideTitle.c_str(),             // Window text
        WS_OVERLAPPEDWINDOW,           // Window style
        CW_USEDEFAULT,                 // X
        CW_USEDEFAULT,                 // Y
        rect.right - rect.left,        // Width
        rect.bottom - rect.top,        // Height
        nullptr,                       // Parent window    
        nullptr,                       // Menu
        m_hinstance,                   // Instance handle
        this                          // Additional application data
    );

    return (m_hwnd != nullptr);
}

void WindowsWindow::cleanup() {
    if (m_hwnd) {
        DestroyWindow(m_hwnd);
        m_hwnd = nullptr;
    }
}

void WindowsWindow::show() {
    ShowWindow(m_hwnd, SW_SHOW);
    UpdateWindow(m_hwnd);
}

void WindowsWindow::hide() {
    ShowWindow(m_hwnd, SW_HIDE);
}

void WindowsWindow::close() {
    m_shouldClose = true;
    PostMessage(m_hwnd, WM_CLOSE, 0, 0);
}

bool WindowsWindow::shouldClose() const {
    return m_shouldClose;
}

void WindowsWindow::setTitle(const std::string& title) {
    // Convert title to wide string
    int titleSize = MultiByteToWideChar(CP_UTF8, 0, title.c_str(), -1, nullptr, 0);
    std::wstring wideTitle(titleSize, 0);
    MultiByteToWideChar(CP_UTF8, 0, title.c_str(), -1, &wideTitle[0], titleSize);

    SetWindowTextW(m_hwnd, wideTitle.c_str());
}

void WindowsWindow::setSize(int width, int height) {
    RECT rect = { 0, 0, width, height };
    AdjustWindowRect(&rect, GetWindowLong(m_hwnd, GWL_STYLE), FALSE);
    SetWindowPos(m_hwnd, nullptr, 0, 0, 
        rect.right - rect.left, rect.bottom - rect.top,
        SWP_NOMOVE | SWP_NOZORDER);
}

void WindowsWindow::setPosition(int x, int y) {
    SetWindowPos(m_hwnd, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void WindowsWindow::getSize(int& width, int& height) const {
    RECT rect;
    GetClientRect(m_hwnd, &rect);
    width = rect.right - rect.left;
    height = rect.bottom - rect.top;
}

void WindowsWindow::getPosition(int& x, int& y) const {
    RECT rect;
    GetWindowRect(m_hwnd, &rect);
    x = rect.left;
    y = rect.top;
}

void* WindowsWindow::getNativeHandle() const {
    return m_hwnd;
}

void WindowsWindow::processEvents() {
    MSG msg = {};
    while (PeekMessage(&msg, m_hwnd, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK WindowsWindow::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    WindowsWindow* window = nullptr;

    if (msg == WM_NCCREATE) {
        auto createStruct = reinterpret_cast<CREATESTRUCT*>(lparam);
        window = static_cast<WindowsWindow*>(createStruct->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
    } else {
        window = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    switch (msg) {
        case WM_CLOSE:
            if (window) {
                window->m_shouldClose = true;
            }
            DestroyWindow(hwnd);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_SIZE:
            if (window) {
                RECT rect;
                GetClientRect(hwnd, &rect);
                // TODO: Add window resize callback here when implemented
            }
            return 0;

        case WM_KEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP:
            if (window) {
                // TODO: Add keyboard input handling when input system is implemented
            }
            break;

        case WM_MOUSEMOVE:
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
        case WM_MOUSEWHEEL:
            if (window) {
                // TODO: Add mouse input handling when input system is implemented
            }
            break;
    }

    return DefWindowProc(hwnd, msg, wparam, lparam);
}

} // namespace VGE

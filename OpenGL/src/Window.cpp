#include "Window.h"

Window::Window()
{
    window = glfwCreateWindow(width, height, "", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
    {
        Window* thisWindow = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
        for (auto& callback : thisWindow->resizeCallbacks)
            callback(*thisWindow, width, height);
    });
}

Window::~Window()
{
    glfwDestroyWindow(window);
}

void Window::SetSize(int width, int height)
{
    glfwSetWindowSize(window, width, height);
    this->width = width;
    this->height = height;
}

int Window::GetWidth()
{
    glfwGetWindowSize(window, &width, &height);
    return width;
}

int Window::GetSize()
{
    glfwGetWindowSize(window, &width, &height);
    return height;
}

bool Window::IsClosing()
{
    return glfwWindowShouldClose(window);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}


void Window::AddSizeChangedCallBack(const std::function<void(const Window&, int, int)>& callback)
{
    resizeCallbacks.push_back(callback);
}

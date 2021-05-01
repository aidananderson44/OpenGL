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

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
    {
        Window* thisWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        if (!thisWindow->showingCursor)
        {
            for (auto& callback : thisWindow->mouseMoveCallbacks)
                callback(*thisWindow, xPos - thisWindow->mouseXPos, yPos - thisWindow->mouseYPos);
            thisWindow->mouseXPos = xPos;
            thisWindow->mouseYPos = yPos;
        }
    });

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        Window* thisWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            thisWindow->SetCursorVisible(true);
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
    {
        Window* thisWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS )
            thisWindow->SetCursorVisible(false);
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

void Window::SetCursorVisible(bool isVisible)
{
    if (!isVisible)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        glfwGetCursorPos(window, &mouseXPos, &mouseYPos);
    }
    else
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
        mouseXPos = -1, mouseYPos = -1;
    }
    showingCursor = isVisible;
}


void Window::AddSizeChangedCallBack(const std::function<void(const Window&, int, int)>& callback)
{
    resizeCallbacks.push_back(callback);
}

void Window::AddMouseMoveCallBack(const std::function<void(const Window&, double, double)>& callback)
{
    mouseMoveCallbacks.push_back(callback);
}

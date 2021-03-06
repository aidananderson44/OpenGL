#include "Window.h"
#include <iostream>
Window::Window()
    :lastTime(glfwGetTime())
{
    if (!glfwInit())
    {
        std::cout << "Error initializing glfw!" << std::endl;
    }
    window = glfwCreateWindow(width, height, "", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
    {
        Window* thisWindow = static_cast<Window *>(glfwGetWindowUserPointer(window));
        for (auto& callback : thisWindow->resizeCallbacks)
            callback(*thisWindow, width, height);
    });

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
    {
        Window* thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (!thisWindow->showingCursor)
        {
            for (auto& callback : thisWindow->mouseMoveCallbacks)
                callback(*thisWindow, (int)(xPos - thisWindow->mouseXPos), (int)(yPos - thisWindow->mouseYPos));
            thisWindow->mouseXPos = xPos;
            thisWindow->mouseYPos = yPos;
        }
    });

    glfwSetKeyCallback(window, [](GLFWwindow* window, int glfwKey, int scancode, int glfwAction, int mods)
    {
        Window* thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (glfwKey == GLFW_KEY_ESCAPE && glfwAction == GLFW_RELEASE)
            thisWindow->SetCursorVisible(true);
        else if (glfwKey == GLFW_KEY_ENTER && glfwAction == GLFW_RELEASE)
            thisWindow->SetCursorVisible(false);
        Key key;
        switch (glfwKey)
        {
        case GLFW_KEY_W:
        case GLFW_KEY_UP:
            key = Key::Forward;
            break;
        case GLFW_KEY_S:
        case GLFW_KEY_DOWN:
            key = Key::Backward;
            break;
        case GLFW_KEY_A:
        case GLFW_KEY_LEFT:
            key = Key::StrafeLeft;
            break;
        case GLFW_KEY_D:
        case GLFW_KEY_RIGHT:
            key = Key::StrafeRight;
            break;
        case GLFW_KEY_SPACE:
            key = Key::FlyUp;
            break;
        case GLFW_KEY_LEFT_CONTROL:
            key = Key::FlyDown;
            break;
        default:
            key = Key::None;
            break;
        }
        Action action;
        switch (glfwAction)
        {
        case GLFW_PRESS:
            action = Action::Press;
            break;
        case GLFW_RELEASE:
            action = Action::Release;
            break;
        case GLFW_REPEAT:
            action = Action::Repeat;
            break;
        default:
            action = Action::None;
            break;
        }

        if (key != Key::None && action != Action::None)
        {
            for (auto& callback : thisWindow->keyPressCallbacks)
                callback(*thisWindow, key, action);
        }

    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
    {
      //  Window* thisWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
       // if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS )
        //    thisWindow->SetCursorVisible(false);
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

int Window::GetWidth() const
{
    glfwGetWindowSize(window, &width, &height);
    return width;
}

int Window::GetHeight() const
{
    glfwGetWindowSize(window, &width, &height);
    return height;
}

bool Window::IsClosing() const
{
    return glfwWindowShouldClose(window);
}

void Window::Refresh() const
{
    lastTime = glfwGetTime();
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

void Window::AddKeyPressCallBack(const std::function<void(const Window&, Key key, Action action)>& callback)
{
    keyPressCallbacks.push_back(callback);
}

double Window::DeltaTime()
{
    return (glfwGetTime() - lastTime) * 1000;
}

float Window::UIScale() const
{
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    float xscale, yscale;
    glfwGetMonitorContentScale(primary, &xscale, &yscale);
    return xscale;
}

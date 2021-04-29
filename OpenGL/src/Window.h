#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <memory>
#include <vector>
class Window
{
public:
	Window();
	~Window();
	GLFWwindow* GetWindow() { return window; }
	void SetSize(int width, int height);
	int GetWidth();
	int GetSize();
	bool IsClosing();
	void SwapBuffers();

	void AddSizeChangedCallBack(const std::function<void(const Window&, int, int)> &callback);

private:
	GLFWwindow *window;
	std::vector<std::function<void(const Window&, int, int)>> resizeCallbacks;
	int width = 640, height = 480;
};


#pragma once
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
	void SetCursorVisible(bool isVisible);


	void AddSizeChangedCallBack(const std::function<void(const Window&, int, int)> &callback);
	void AddMouseMoveCallBack(const std::function<void(const Window&, double, double)>& callback);


private:
	GLFWwindow *window;
	std::vector<std::function<void(const Window&, int, int)>> resizeCallbacks;
	std::vector<std::function<void(const Window&, int, int)>> mouseMoveCallbacks;
	int width = 640, height = 480;
	double mouseXPos = -1;
	double mouseYPos = -1;
	bool showingCursor = true;
};


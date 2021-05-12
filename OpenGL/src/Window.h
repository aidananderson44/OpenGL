#pragma once
#include <GLFW/glfw3.h>
#include <functional>
#include <memory>
#include <vector>
class Window
{
public:
	enum class Key
	{
		Forward,
		Backward,
		StrafeLeft,
		StrafeRight,
		FlyUp,
		FlyDown,
		None
	};

	enum class Action
	{
		Press = 0,
		Release = 1,
		Repeat,
		None
	};

	Window();
	~Window();
	GLFWwindow* GetWindow() { return window; }
	void SetSize(int width, int height);
	int GetWidth() const;
	int GetHeight() const;
	bool IsClosing() const;
	void Refresh() const;
	void SetCursorVisible(bool isVisible);


	void AddSizeChangedCallBack(const std::function<void(const Window&, int, int)> &callback);
	void AddMouseMoveCallBack(const std::function<void(const Window&, double, double)>& callback);
	void AddKeyPressCallBack(const std::function<void(const Window&, Key key, Action action)>& callback);
	double DeltaTime();

	float UIScale() const;



private:
	GLFWwindow *window;
	std::vector<std::function<void(const Window&, int, int)>> resizeCallbacks;
	std::vector<std::function<void(const Window&, int, int)>> mouseMoveCallbacks;
	std::vector<std::function<void(const Window&, Key, Action)>> keyPressCallbacks;
	mutable int width = 640, height = 480;
	double mouseXPos = -1;
	double mouseYPos = -1;
	bool showingCursor = true;
	mutable double lastTime;
};


#pragma once
#include "tests/Test.h"
#include "Window.h"
#include "gl/Renderer.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class Engine
{
public:
	Engine();
	~Engine();
	template<typename T>
	void Run();
private:
	Window window;
	Renderer renderer;
};

template<typename T>
inline void Engine::Run()
{
    T test;
    test.OnSizeChange(window.GetWidth(), window.GetHeight());
    window.AddSizeChangedCallBack([&test, this](const Window&, int width, int height)
    {
        test.OnSizeChange(width, height);
        this->renderer.SetSize(width, height);
    });

    window.AddMouseMoveCallBack([&test](const Window&, double xDiff, double yDiff)
    {
        test.OnMouseMove(xDiff, yDiff);
    });

    window.AddKeyPressCallBack([&test](const Window&, Window::Key key, Window::Action action)
    {
        test.OnKeyChange(key, action);
    });


    float SCALE = window.UIScale();
    ImFontConfig cfg;
    cfg.SizePixels = 13 * SCALE;
    ImGui::GetIO().Fonts->AddFontDefault(&cfg)->FontSize *= SCALE;
   
    /* Loop until the user closes the window */
    while (!window.IsClosing())
    {
        renderer.Clear();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        test.OnUpdate((float)window.DeltaTime());
        test.OnRender(renderer);
        test.OnImGUIRender();

        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        window.Refresh();
    }    
}

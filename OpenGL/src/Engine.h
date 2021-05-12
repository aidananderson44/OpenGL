#pragma once
#include "tests/Test.h"
#include "materials/Quad.h"
#include "Window.h"
#include "gl/Renderer.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "gl/DepthTexture.h"

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
    float resolutionScale = 0.5f;
    Renderer offScreenRenderer = Renderer::GetOffScreenRenderer((int)(renderer.GetWidth() * resolutionScale), (int)(renderer.GetHeight() * resolutionScale));
    
    window.AddSizeChangedCallBack([&test, &offScreenRenderer, &resolutionScale, this](const Window&, int width, int height)
    {
        test.OnSizeChange(width, height);
        this->renderer.SetSize(width, height);
        offScreenRenderer.SetSize((int)(width * resolutionScale), (int)(height * resolutionScale));
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
    
    Quad quad;
    quad.SetShaderFromPath("res/shaders/basicMaterial.shader");
    bool Depth = false;
    

    /* Loop until the user closes the window */
    while (!window.IsClosing())
    {
      //  offScreenRenderer.SetSize((int)(renderer.GetWidth() * resolutionScale), (int)(renderer.GetHeight() * resolutionScale));
        renderer.Clear();
        
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        test.OnUpdate((float)window.DeltaTime());


        test.OnRender(renderer);
     /*   offScreenRenderer.BindFrameBuffer();

        if(Depth)
            quad.AddTexture("Texture", (offScreenRenderer.GetFrameBuffer()->GetDepthTexture()));
        else
            quad.AddTexture("Texture", (offScreenRenderer.GetFrameBuffer()->GetColorTexture()));
        
        renderer.Draw(quad);
        
        renderer.BindFrameBuffer();*/
        test.OnImGUIRender();
        
      //  ImGui::SliderFloat("ResolutionScale", &resolutionScale, 0.01f, 2.0f, "%.3f", 32);
      //  ImGui::Checkbox("Use Depth Buffer", &Depth);
        ImGui::End();

        ImGui::Render();
        
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        window.Refresh();
    }    
}

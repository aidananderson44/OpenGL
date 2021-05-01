#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "gl/Renderer.h"
#include "Window.h"

#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"
#include "tests/TestTexture2DWithMaterial.h"
#include "tests/Test3DMaterial.h"
#include "tests/Test3DPerspective.h"
#include "tests/Test3DPerspectiveWithCamera.h"
int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSwapInterval(1);
    Window window;
    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    glEnable(GL_DEPTH_TEST);
    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        Renderer renderer;
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window.GetWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 330");
        ImGui::StyleColorsDark();

        test::Test* currentTest = nullptr;
        window.AddSizeChangedCallBack([&currentTest](const Window&, int width, int height)
        {
            if (currentTest != nullptr)
                currentTest->SetAspectRatio((float)width / (float)height);
            glViewport(0, 0, width, height);
        });

        window.AddMouseMoveCallBack([&currentTest](const Window&, double xDiff, double yDiff)
        {
            currentTest->MouseMove(xDiff, yDiff);
        });

        test::TestMenu* testMenu = new test::TestMenu(currentTest);
        currentTest = testMenu;
        testMenu->RegisterTest<test::TestClearColor>("Clear Color");
        testMenu->RegisterTest<test::TestTexture2D>("2D Texture");
        testMenu->RegisterTest<test::TestTexture2DWithMaterial>("2D texture With Material");
        testMenu->RegisterTest<test::Test3DMaterial>("3D Material");
        testMenu->RegisterTest<test::Test3DPerspective>("3D Perspective");
        testMenu->RegisterTest<test::Test3DPerspectiveWithCamera>("3D Perspective with camera");

        /* Loop until the user closes the window */
        while (!window.IsClosing())
        {
            /* Render here */
            GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
            renderer.Clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            if (currentTest)
            {
                currentTest->OnUpdate(0);
                currentTest->OnRender();
                ImGui::Begin("Test");
                if (currentTest != testMenu && ImGui::Button("<-"))
                {
                    delete currentTest;
                    currentTest = testMenu;
                }
                currentTest->OnImGUIRender();
                ImGui::End();
            }
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            window.SwapBuffers();
        }
        if (currentTest != testMenu)
            delete testMenu;
        delete currentTest;
    }
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
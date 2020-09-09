#include <fstream>
#include <string>
#include <sstream>

#include <GL/glew.h>
#include "DebugManager.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Camera.h"
#include "Actor.h"

#include <GLFW/glfw3.h>

#include "Test.h"
#include "TestClearColor.h"
#include "TestTexture.h"
#include "TestCube.h"
#include "TestProjection.h"
#include "TestVertexShader.h"
#include "TestLighting.h"
#include "TestScene.h"



#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


template<class T> test::Test* create()
{
    return new T();
}

test::Test* currentTest = nullptr;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    currentTest->OnKeyPress(key, action);
    //if(action == GLFW_PRESS)    GLDebugOut("Key", key);
}


int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    glfwSetKeyCallback(window, key_callback);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;


    const char* glsl_version = "#version 130";

    std::cout << glGetString(GL_VERSION) << std::endl;
    {

        Renderer renderer;


        // Setup Dear ImGui context
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        // Setup Tests
        //test::Test* currentTest = nullptr;
        test::TestMenu* testMenu = new test::TestMenu(currentTest);
        currentTest = testMenu;

        testMenu->RegisterTest<test::TestClearColor>("Clear Color");
        testMenu->RegisterTest<test::TestTexture>("Texture 2D");
        testMenu->RegisterTest<test::TestCube>("Cube 3D");
        testMenu->RegisterTest<test::TestProjection>("Projection 3D");
        testMenu->RegisterTest<test::TestVertexShader>("Vertex Shader");
        testMenu->RegisterTest<test::TestLighting>("Basic Lighting");
        testMenu->RegisterTest<test::TestScene>("Basic Scene");
        //testMenu->RegisterTest<test::TestNoise>("Noise");



        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {

            /* Render here */
            renderer.Clear();

            GLCALL(glClear(GL_COLOR_BUFFER_BIT));
            glfwPollEvents();

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            if(currentTest)
            {
                currentTest->OnUpdate(0.0f);
                currentTest->OnRender();
                ImGui::Begin("Tests");
                if (currentTest != testMenu && ImGui::Button("<-"))
                {
                    //delete currentTest;
                    currentTest = testMenu;
                }
                if (ImGui::Button("[x]"))
                    glfwSetWindowShouldClose(window, GLFW_TRUE);
                currentTest->OnImGuiRender();
                ImGui::End();
            }
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);
            /* Poll for and process events */
            glfwPollEvents();

        }
        delete currentTest;
        if (currentTest != testMenu)
            delete testMenu;
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}

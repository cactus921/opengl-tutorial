#include <fstream>
#include <string>
#include <sstream>

#include <GL/glew.h>
#include "DebugManager.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include "Test.h"
#include "TestClearColor.h"
#include "TestTexture.h"
#include "TestCube.h"

#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


template<class T> test::Test* create()
{
    return new T();
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

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;


    const char* glsl_version = "#version 130";

    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        /*
        float positions[] = {
            -0.5f, -0.5f, 0.0f, 0.0f,
             0.5f, -0.5f, 1.0f, 0.0f,
             0.5f,  0.5f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 1.0f
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 2);
        layout.Push(GL_FLOAT, 2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        Shader shader("res/Basic.shader");
        shader.Bind();

        Texture texture("res/batman-logo-1.png");
        texture.Bind(0);
        shader.SetUniform1i("u_Texture", 0);
        */


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
        test::Test* currentTest = nullptr;
        test::TestMenu* testMenu = new test::TestMenu(currentTest);
        currentTest = testMenu;

        testMenu->RegisterTest<test::TestClearColor>("Clear Color");
        testMenu->RegisterTest<test::TestTexture>("Texture 2D");
        testMenu->RegisterTest<test::TestCube>("Cube 3D");

        /*
        glm::vec3 translationA(0.0f, 0.0f, 0.0f);
        glm::vec3 translationB(0.0f, 0.0f, 0.0f);
        float r = 0.0f;
        float increment = 0.01f;
        */

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
                    delete currentTest;
                    currentTest = testMenu;
                }
                if (ImGui::Button("[x]"))
                    glfwSetWindowShouldClose(window, GLFW_TRUE);
                currentTest->OnImGuiRender();
                ImGui::End();
            }

            /*
            shader.Bind();
            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
                glm::mat4 mvp = proj * view * model;
                shader.SetUniformMat4f("u_MVP", mvp);
                renderer.Draw(va, ib, shader);
            }

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
                glm::mat4 mvp = proj * view * model;
                shader.SetUniformMat4f("u_MVP", mvp);
                renderer.Draw(va, ib, shader);
            }

            //shader.SetUniformMat4f("u_MVP", mvp);
            //renderer.Draw(va, ib, shader);

            if (r > 1.0f || r < 0.0f)
                increment = -increment;
            r += increment;

            {
                ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
                ImGui::SliderFloat3("translationA", &translationA.x, -1.0f, 1.0f);
                ImGui::SliderFloat3("translationB", &translationB.x, -1.0f, 1.0f);
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            }
            */
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

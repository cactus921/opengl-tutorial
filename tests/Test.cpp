#include "Test.h"



#include <GL/glew.h>
#include "imgui.h"



namespace test{
    TestMenu::TestMenu(Test*& currentTestPointer)
        : m_CurrentTest (currentTestPointer)
    {
        //ctor

    }

    TestMenu::~TestMenu()
    {
        //dtor
    }

    void TestMenu::OnRender()
    {
        GLCALL(glClearColor(0.5f, 0.7f, 1.0f, 1.0f));
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));
    }

    void TestMenu::OnImGuiRender()
    {
        for(auto& test : m_Tests)
        {
            if(ImGui::Button(test.first.c_str()))
            {
                GLDebugOut("Pressed", test.first.c_str());
                m_CurrentTest = test.second();

            }
        }
    }

}


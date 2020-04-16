#ifndef TEST_H
#define TEST_H

#include <vector>
#include <functional>
#include "DebugManager.h"


namespace test {

    class Test
    {
        public:
            Test() {}
            virtual ~Test() {}

            virtual void OnUpdate(float deltaTime) {}
            virtual void OnRender() {}
            virtual void OnImGuiRender() {}
            virtual void OnDestruct() {}

    };

    class TestMenu : public Test
    {
        public:
            TestMenu(Test*& currentTestPointer);
            ~TestMenu();

            void OnRender();
            void OnImGuiRender();


            template<typename T>
            void RegisterTest(const std::string& name)
            {
                GLDebugOut("Registering Test", name);
                m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
            }

        private:
            Test*& m_CurrentTest;
            std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
    };

}

#endif // TEST_H

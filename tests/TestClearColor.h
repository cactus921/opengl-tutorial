#ifndef TESTCLEARCOLOR_H
#define TESTCLEARCOLOR_H

#include "Test.h"

namespace test {

    class TestClearColor : public Test
    {
        public:
            TestClearColor();
            ~TestClearColor();

            void OnUpdate(float deltaTime);
            void OnRender();
            void OnImGuiRender();
            void OnDestruct();

        private:
            float m_ClearColor[4];

    };


}

#endif // TESTCLEARCOLOR_H

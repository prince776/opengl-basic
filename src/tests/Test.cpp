#include "Test.h"
#include "imgui/imgui.h"
#include "Renderer.h"

namespace test {

	TestMenu::TestMenu(Test *&currentTestPointer)
		: currentTest(currentTestPointer)
	{
		
	}
	
	void TestMenu::onRender()
	{
		GLCALL(glClearColor(0, 0, 0, 1));
	}
	
	void TestMenu::onImGuiRender()
	{
		for (auto &test : tests)
		{
			if (ImGui::Button(test.first.c_str()))
			{
				currentTest = test.second();
			}
		}	
	}

}
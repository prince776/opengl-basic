#include "TestClearColor.h"
#include "Renderer.h"
#include "imgui/imgui.h"

namespace test {

	TestClearColor::TestClearColor()
		: clearColor{ 0.2f, 0.3f, 0.8f, 1.0f }
	{

	}

	TestClearColor::~TestClearColor()
	{

	}
	
	void TestClearColor::onUpdate(float deltaTime)
	{
		
	}
	
	void TestClearColor::onRender()
	{
		GLCALL(glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]));
		GLCALL(glClear(GL_COLOR_BUFFER_BIT));
	}
	
	void TestClearColor::onImGuiRender()
	{
		ImGui::ColorEdit4("Clear Color", &clearColor[0]);
	}

}

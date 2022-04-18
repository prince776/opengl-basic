#pragma once

#include <vector>
#include <functional>
#include <string>
#include <iostream>

namespace test {

	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual void onUpdate(float deltaTime) {}
		virtual void onRender() {}
		virtual void onImGuiRender() {}
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test *&currentTestPointer);

		void onRender() override;
		void onImGuiRender() override;
		template<typename T>
		void registerTest(const std::string &name)
		{
			std::cout << "Registering test: " << name << "\n";
		tests.push_back(std::make_pair(name, []() { return new T(); }));
		}
	private:
		Test *&currentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> tests;
	};

}

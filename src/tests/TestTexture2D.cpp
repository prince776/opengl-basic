#include "TestTexture2D.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexBufferLayout.h"
#include "imgui/imgui.h"

extern int width, height;

namespace test {

	TestTexture2D::TestTexture2D()
		: translationA(200, 200, 0), translationB(400, 200, 0),
			proj(glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f)),
			view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
	{
		float positions[] = {
			-50, -50, 0, 0,
			50, -50, 1, 0,
			50, 50, 1, 1,
			-50, 50, 0, 1
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0,
		};

		vao = std::make_unique<VertexArray>();
		vbo = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.push<float>(2);
		layout.push<float>(2);
		vao->addBuffer(*vbo, layout);
		ibo = std::make_unique<IndexBuffer>(indices, 6);
		
		texture = std::make_unique<Texture>("res/textures/test.png");
		shader = std::make_unique<Shader>("res/shaders/basic.glsl");
		shader->bind();

		shader->setUniform1i("u_Texture", 0);

		vao->unBind();
		vbo->unBind();
		ibo->unBind();
		shader->unBind();
	}
	
	TestTexture2D::~TestTexture2D()
	{
		
	}
	
	void TestTexture2D::onUpdate(float deltaTime)
	{
		
	}
	
	void TestTexture2D::onRender()
	{
		GLCALL(glClearColor(0, 0, 0, 1));
		GLCALL(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;
		shader->bind();
		texture->bind();
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
			glm::mat4 mvp = proj * view * model;
			shader->setUniformMat4f("u_MVP", mvp);
			renderer.draw(*vao, *ibo, *shader);
		}
		
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
			glm::mat4 mvp = proj * view * model;
			shader->setUniformMat4f("u_MVP", mvp);
			renderer.draw(*vao, *ibo, *shader);
		}
	}
	
	void TestTexture2D::onImGuiRender()
	{
		ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 400);
		ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 400);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}

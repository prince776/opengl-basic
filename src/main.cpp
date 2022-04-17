#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

int main(void)
{
	GLFWwindow *window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	constexpr int width = 640, height = 480;

	/* Create a windowed mode window and its OpenGL context */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	std::cout << glGetString(GL_VERSION) << std::endl;
	
	GLCALL(glEnable(GL_BLEND));
	GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	{
		float positions[] = {
			100, 100, 0, 0,
			200, 100, 1, 0,
			200, 200, 1, 1,
			100, 200, 0, 1
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0,
		};

		// Vertex array
		VertexArray vao;

		// Vertex buffer
		VertexBuffer vbo(positions, 4 * 4 * sizeof(float));
	
		VertexBufferLayout layout;
		layout.push<float>(2);
		layout.push<float>(2);
		
		vao.addBuffer(vbo, layout);
		// Index buffer
		IndexBuffer ibo(indices, 6);

		glm::mat4 proj = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));


		// Shader
		Shader shader("res/shaders/basic.glsl");

		// Texture
		Texture texture("res/textures/test.png");
		texture.bind();

		shader.bind();
		shader.setUniform1i("u_Texture", 0);

		vao.unBind();
		vbo.unBind();
		ibo.unBind();
		shader.unBind();

		Renderer renderer;

		// ImGui
		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui::StyleColorsDark();

		glm::vec3 translation(200, 200, 0);

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			renderer.clear();
			ImGui_ImplGlfwGL3_NewFrame();

			glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
			glm::mat4 mvp = proj * view * model;

			shader.bind();
			shader.setUniformMat4f("u_MVP", mvp);
			renderer.draw(vao, ibo, shader);

			// ImGui
			{
				ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 400);
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}


			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}
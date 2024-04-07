#include <iostream>
#include <vector>
#include <cmath>
#include "OpenGLCore/Renderer.h"
#include "OpenGLCore/VertexBuffer.h"
#include "OpenGLCore/IndexBuffer.h"
#include "OpenGLCore/VertexArray.h"
#include "OpenGLCore/Shader.h"
#include "OpenGLCore/VertexBufferLayout.h"
#include "OpenGLCore/Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Modal.h"

const float PI = 3.14159265359f;

#define GLEW_STATIC

void SetAnimationVector(float& time, std::vector<GLfloat>& animation, std::vector<GLfloat>& positions, const float& scale, const float& modeshape)
{
	float elongationFactor = 0.0f;

	for (size_t i = 0; i < animation.size(); i++)
	{
		elongationFactor += scale *  cos(PI * time) * modeshape;
		animation[i] = elongationFactor * sin(PI * time);
	}

	for(size_t i = 0; i < 9; i++)
	{
		if(( 8 * ( i + 2 ) + 1 ) < positions.size())
		{
			positions[( 8 * ( i + 2 ) - 3 )] += animation[i];
			positions[( 8 * ( i + 2 ) - 1 )] += animation[i];
			positions[( 8 * ( i + 2 ) + 1 )] += animation[i];
			positions[( 8 * ( i + 2 ) + 3 )] += animation[i];
		}
		else
		{
			positions[77] += animation[7];
			positions[79] += animation[7];
		}
	}
}

int main(int, char**) {

    GLFWwindow* window;

    if (!glfwInit())
        return -1;
    
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	float x = 600.0f;
	float y = 450.0f;

    window = glfwCreateWindow(static_cast<int>(x), static_cast<int>(y), "Single DoF System", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

	glfwSwapInterval(1); // Frame rate

    if(glewInit() != GLEW_OK)
    std::cout << "Error!" << std::endl;

	{
		std::vector<GLfloat> animation(9);
		std::vector<GLfloat> positions = 
		{
			x / 2 - 50.0f, y / 2 - 100.0f,
			x / 2 + 55.0f, y / 2 - 100.0f,
			x / 2 + 55.0f, y / 2 - 95.0f,
			x / 2 - 50.0f, y / 2 - 95.0f,
			
			x / 2, y / 2 - 95.0f,
			x / 2 + 5.0f, y / 2 - 95.0f,
			x / 2 + 5.0f, y / 2 - 80.0f,
			x / 2, y / 2 - 80.0f,

			x / 2, y / 2 - 80.0f,
			x / 2 + 5.0f, y / 2 - 80.0f,
			x / 2 + 19.0f, y / 2 - 70.0f,
			x / 2 + 14.0f, y / 2 - 70.0f,

			x / 2 + 14.0f, y / 2 - 70.0f,
			x / 2 + 19.0f, y / 2 - 70.0f,
			x / 2 + 5.0f, y / 2 - 56.0f,
			x / 2.0f, y / 2 - 56.0f,

			x / 2.0f, y / 2 - 56.0f,
			x / 2 + 5.0f, y / 2 - 56.0f,
			x / 2 + 19.0f, y / 2 - 42.0f,
			x / 2 + 14.0f, y / 2 - 42.0f,

			x / 2 + 14.0f, y / 2 - 42.0f,
			x / 2 + 19.0f, y / 2 - 42.0f,
			x / 2 + 5.0f, y / 2 - 28.0f,
			x / 2, y / 2 - 28.0f,

			x / 2.0f, y / 2 - 28.0f,
			x / 2 + 5.0f, y / 2 - 28.0f,
			x / 2 + 19.0f, y / 2 - 14.0f,
			x / 2 + 14.0f, y / 2 - 14.0f,

			x / 2 + 14.0f, y / 2 - 14.0f,
			x / 2 + 19.0f, y / 2 - 14.0f,
			x / 2 + 5.0f, y / 2,
			x / 2, y / 2,

			x / 2, y / 2,
			x / 2 + 5.0f, y / 2,
			x / 2 + 5.0f, y / 2 + 15.0f,
			x / 2, y / 2 + 15.0f,

			x / 2 - 50.0f, y / 2 + 15.0f,
			x / 2 + 55.0f, y / 2 + 15.0f,
			x / 2 + 55.0f, y / 2 + 55.0f,
			x / 2 - 50.0f, y / 2 + 55.0f
		};
		
		std::vector<GLuint> indices = 
		{
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4,
			8, 9, 10, 10, 11, 8,
			12, 13, 14, 14, 15, 12,
			16, 17, 18, 18, 19, 16,
			20, 21, 22, 22, 23, 20,
			24, 25, 26, 26, 27, 24,
			28, 29, 30, 30, 31, 28,
			32, 33, 34, 34, 35, 32,
			36, 37, 38, 38, 39, 36
		};
		
		VertexArray va;
		VertexBuffer vb(&positions[0], positions.size());

		VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(&indices[0], indices.size());

		glm::mat4 proj = glm::ortho(0.0f, x, 0.0f, y, -1.0f, 1.0f);

		Shader shader("../../assets/shaders/Basic.shader.txt");
		shader.Bind();
		shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
		shader.SetUniformMat4f("u_MVP", proj);

		va.Unbind();
		vb.Unbind();
		ib.Unbind();
		shader.Unbind();

		Renderer renderer;

		Modal singledof;
		std::vector<float> mass = {10.0f};
		std::vector<float> springconstant = {1000.0f};
		
		singledof.GenerateMassMatrix(mass);
		singledof.GenerateStiffnessMatrix(springconstant);
		singledof.Run();

		std::cout << "Mode of Single DoF System: " << singledof.GetNatralFreq()[0] << " Hz." << std::endl;
		float modeshape = static_cast<float>(singledof.GetModeShapes()[0]);
		float scale = 1.0f;

		while (!glfwWindowShouldClose(window))
		{
			renderer.Clear();

			float time = static_cast<float>(glfwGetTime());
			SetAnimationVector(time, animation, positions, scale, modeshape);

			vb.UpdateData(&positions[0], 0, positions.size());

			shader.Bind();
			shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
			shader.SetUniformMat4f("u_MVP", proj);
			renderer.Draw(va, ib, shader);

			GLCall(glfwSwapBuffers(window));
			GLCall(glfwPollEvents());
		}
	}
    glfwTerminate();
}
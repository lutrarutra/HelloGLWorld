#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <SDL2\SDL.h>
#include <string>
#include <fstream>
#include "shader.h"
#include "transform.h"
#include "camera.h"
#include "mesh.h"

#undef main

#define WIDTH 1024
#define HEIGHT 800

#pragma region stuff

SDL_Window* m_window;
SDL_GLContext m_context;
void Cleanup();
std::string title = "Hello SDL2 window!";
bool isRunning;
void loopEvents(SDL_Event event);
void setGLAttributes();
void init();
GLuint vertexbuffer;
GLuint vao;
GLuint vbo;
GLuint m_program;

#pragma endregion



int main()
{
	isRunning = true;

	init();

	Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0)),
		Vertex(glm::vec3(0, 0.5, 0)),
		Vertex(glm::vec3(0.5, -0.5, 0)), 
	};
	
	//Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 0), glm::vec3(0, 0, -1))

	unsigned int indices[] = { 1,2,3 };
	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	Shader shader("./res/basicShader");
	Transform transform;
	Camera camera(glm::vec3(0, 0, -3), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);

	float counter = 0.0f;

	while (isRunning)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
			loopEvents(event);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(vao);


		mesh.Draw();

		shader.Bind();
		shader.Update(transform, camera);
		SDL_GL_SwapWindow(m_window);
		counter += 0.0005f;

	}
	
	Cleanup();

	return 0;
}

void Cleanup()
{
	// Delete our OpengL context
	SDL_GL_DeleteContext(m_context);

	// Destroy our window
	SDL_DestroyWindow(m_window);

	// Shutdown SDL 2
	SDL_Quit();
}

void init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	m_context = SDL_GL_CreateContext(m_window);

	setGLAttributes();

	glewExperimental = GL_TRUE;
	glEnable(GL_MULTISAMPLE);

	glewInit();

	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);

	SDL_GL_SwapWindow(m_window);
}

void setGLAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);
}

void loopEvents(SDL_Event e)
{
	if (e.type == SDL_QUIT)
		isRunning = false;
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			isRunning = false;
			break;
		case SDLK_r:
			// Cover with red and update
			glClearColor(1.0, 0.0, 0.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT);
			SDL_GL_SwapWindow(m_window);
			break;
		case SDLK_g:
			// Cover with green and update
			glClearColor(0.0, 1.0, 0.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT);
			SDL_GL_SwapWindow(m_window);
			break;
		case SDLK_b:
			// Cover with blue and update
			glClearColor(0.0, 0.0, 1.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT);
			SDL_GL_SwapWindow(m_window);
			break;
		default:
			break;
		}
	}
}




#include <iostream>
#include <SDL2\SDL.h>
#include <string>
#include "shader.h"
#include "transform.h"
#include "camera.h"
#include "mesh.h"
#include "texture.h"
#include "display.h"
#include <math.h>


#define WIDTH 1024
#define HEIGHT 800

#pragma region stuff

void Cleanup();
bool isRunning;
void loopEvents(SDL_Event event);

#pragma endregion



int main(int argc, char** argv)
{
	isRunning = true;
	Display display("Hello GL Word!", (int)WIDTH, (int)HEIGHT);

	Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(-0.5, -0.5)),
		Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0, 0.5)),
		Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(0.5, -0.5)),
	};

	unsigned int indices[] = { 0, 1, 2 };

	//Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));

	Mesh mesh2("./res/monkey3.obj");
	Shader shader("./res/basicShader");
	Texture texture("./res/groundBrick.jpg");
	Camera camera(glm::vec3(0, 0, -6), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
	Transform transform;

	float counter = 0.0f;
	SDL_Event event;

	while (isRunning)
	{
		
		//Listen for events
		while (SDL_PollEvent(&event))
			loopEvents(event);

		//Clear window aka. turn page and re-draw everything
		display.Clear();

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);
		
		//Here move your stuff shown on display
		//transform.GetPos().x = sinCounter;
		//transform.GetPos().z = cosCounter;
		transform.GetRot().x = counter;
		transform.GetRot().y = counter + (float)M_PI;
		//transform.GetScale().x = abs(sinCounter);
		//transform.GetScale().y = abs(sinCounter);
		transform.GetRot().z = counter;

		//Update swap etc...
		shader.Bind();
		texture.Bind(0);
		shader.Update(transform, camera);
		mesh2.Draw();
		//mesh.Draw();

		//Delay for not full CPU&GPU usage
		display.Swap();
		
		counter += 0.0025f;
		SDL_Delay(1);

	}

	//After exiting loop clean up things
	Cleanup();

	return 0;
}

void Cleanup()
{
	// Shutdown SDL 2
	SDL_Quit();
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
		default:
			break;
		}
	}
}




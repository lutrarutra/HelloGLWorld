#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <SDL2\SDL.h>
#include <glm\glm.hpp>


class Display
{

public:
	Display(std::string title, int width, int height);
	
	void Clear(float r, float g, float b, float a);
	void Clear();
	void Swap();

	~Display();

private:
	void operator=(const Display& display) {}
	Display(const Display& display) {}
	SDL_Window* m_window;
	SDL_GLContext m_context;
};

#endif // DISPLAY_H
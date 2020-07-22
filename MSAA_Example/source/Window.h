#pragma once

#include <SDL.h>
#include <GL/glew.h>
#include <memory>

//enum for setting the position of the window
enum class WINDOWPOS : unsigned int {
	CENTERED = SDL_WINDOWPOS_CENTERED, 
	UNDEFINED = SDL_WINDOWPOS_UNDEFINED
};

class Window {
public:
	
	Window(const char* Title = "Aliasing vs MSAA", 
		 WINDOWPOS posX = WINDOWPOS::CENTERED,  WINDOWPOS posY = WINDOWPOS::CENTERED,
		unsigned int width = 1280, unsigned int height = 720);
	
	//main loop
	void Run();
	
private:
	//initialize SDL
	void InitSDL();

	//initialize OpenGL
	void InitGL();
	
	//initialize ImGui
	void InitGUI();

	//clean up application and close window
	void close();

	//handle any messages from SDL
	void HandleMessage();

	//update the contents of the window 
	void UpdateWindow();

	//OpenGL context
	SDL_GLContext glContext;

	//handle to the window
	SDL_Window* pWindow;

	//handle to current message
	SDL_Event Event;

	//indicate when to quit out of the main loop
	bool bQuit;
	
	//object that does OpenGL operations
	std::unique_ptr<class Graphics> graphics;
};
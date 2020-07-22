#include "Window.h"
#include <gl\glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "Log.h"
#include "Graphics.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"

Window::Window(const char* Title, WINDOWPOS posX, WINDOWPOS posY, unsigned int width, unsigned int height)
{
	bQuit = false;

	InitSDL();

	//create the actual window using SDL
	unsigned int CastedPosX = (unsigned int)posX, CastedPosY = (unsigned int)posY;
	pWindow = SDL_CreateWindow("Aliased vs MSAA", CastedPosX, CastedPosY, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	PRINT_IF_ELSE(pWindow, "Created SDL window", "Failed to create SDL window");

	InitGL();
	graphics = std::make_unique<Graphics>();
	InitGUI();
}

void Window::Run()
{
	while (!bQuit) {
		HandleMessage();
		UpdateWindow();
	}
	close();
}

void Window::UpdateWindow()
{
	//tell graphics to render onto buffer
	graphics->Render();

	//draw imgui widget
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(pWindow);
	ImGui::NewFrame();
	ImGui::Begin("Toggle MSAA");
	//toggle MSAA on or off 
	ImGui::Checkbox("MSAA Enabled", &graphics->isMSAA);
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	//swap buffers
	SDL_GL_SwapWindow(pWindow);
}

void Window::InitSDL()
{
	PRINT_IF_ELSE(!(SDL_Init(SDL_INIT_VIDEO) < 0), "Initialized SDL", "Failed to initialize SDL");

	//prepare SDL for OpenGL usage
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);
}

void Window::InitGL()
{
	glContext = SDL_GL_CreateContext(pWindow);
	PRINT_IF_ELSE(glContext, "Created OpenGL context", "Failed to create OpenGL context");

	//initialize GLEW
	glewExperimental = GL_TRUE;
	PRINT_IF_ELSE(glewInit() == GLEW_OK, "Initialized GLEW", "Failed to initialize GLEW");

	//enable vsync
	PRINT_IF_ELSE(!(SDL_GL_SetSwapInterval(1) < 0), "Enabled vsync", "Failed to enable vsync");
}

void Window::InitGUI()
{
	//initialize ImGui for SDL usage
	PRINT_IF_ELSE(ImGui::CreateContext(), "Created ImGui context", "Failed to create ImGui context");
	PRINT_IF_ELSE(ImGui_ImplSDL2_InitForOpenGL(pWindow, glContext), "Intialized ImGui for SDL", "Failed to initialize ImGui for SDL");
	PRINT_IF_ELSE(ImGui_ImplOpenGL3_Init(), "Intialized ImGui for OpenGL", "Failed to initialize ImGui for OpenGL");
	ImGui::StyleColorsDark();
}

void Window::close()
{
	//clean up SDL and ImGui
	ImGui_ImplSDL2_Shutdown();
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(pWindow);
	pWindow = nullptr;
	SDL_Quit();
}

void Window::HandleMessage()
{
	while (SDL_PollEvent(&Event) != 0) {
		switch (Event.type) {
			case SDL_QUIT: {
				//exit out of main loop if user exits out of window
				bQuit = true;
				
			}
		}
	}
	
}

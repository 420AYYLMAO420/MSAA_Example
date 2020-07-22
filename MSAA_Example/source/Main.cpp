#include "Window.h"

int main(int argc, char* args[])
{
	//create instance of window
	Window* window = new Window();
	if (window) {
		window->Run();
		return 0;
	}
	else 
		return -1;
}
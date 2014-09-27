#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif // SFML_STATIC


#include "Application.h"
#include <iostream>

int main()
{
	Application game;
	try{
		game.run();
	}
	catch (std::exception e){
		std::cout << e.what() << std::endl;
	}

	return 0;
}
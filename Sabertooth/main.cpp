#include "System.h"

#define EXIT_FAILURE -1
#define EXIT_SUCCESS 0

Object cubo;


int main() {

	cubo.readobj("uvmappedcow.obj");
	//cubo.setupMesh();
	System system;

	if ( system.GLFWInit() != 0 ){
		return EXIT_FAILURE;
	}
	if ( system.OpenGLSetup() != 0 ){
		return EXIT_FAILURE;
	}
	if ( system.SystemSetup() != 0 ){
		return EXIT_FAILURE;
	}

	system.Run();

	system.Finish();

	return 0;
}
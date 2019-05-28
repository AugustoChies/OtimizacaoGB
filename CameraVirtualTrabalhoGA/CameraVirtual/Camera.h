#pragma once
#include "Vector3.h"
#include <GL/glew.h>
#include <Windows.h>
#include <GLFW/glfw3.h>
class Camera
{
	
public:
	Camera();
	~Camera();
	Vector3 pos;
	Vector3 watch;
	Vector3 up;									  
	Vector3 dir;								  
	float angatual,angatualvert;
	void movefront();							  
	void moveback();							  
	void straferight();							  
	void strafeleft();							  
	void rise();								  
	void fall();								 
	void rotateLeft();
	void rotateRight();
	void rotateUp();
	void rotateDown();
	void resetlook();
	void hardreset();

protected:
	const float MOVE_SPEED = 0.5;
};


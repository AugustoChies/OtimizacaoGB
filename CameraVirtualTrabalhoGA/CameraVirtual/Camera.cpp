#include "Camera.h"
#include <iostream>


Camera::Camera()
{
	
	pos.x = 0;
	pos.y = 0;
	pos.z = -1;

	watch.x = 0;
	watch.y = 1.5;
	watch.z = 9;

	up.x = 0;
	up.y = 1;
	up.z = 0;

	angatual = 0;
	angatualvert = 0;

	dir.calcularNovoVetor(pos, watch);
	dir.unitarizar();
}


Camera::~Camera()
{
}

void Camera::movefront()
{
	dir.unitarizar();
	pos.x += MOVE_SPEED * dir.x;
	pos.y += MOVE_SPEED * dir.y;
	pos.z += MOVE_SPEED * dir.z;

	watch.x += MOVE_SPEED * dir.x;
	watch.y += MOVE_SPEED * dir.y;
	watch.z += MOVE_SPEED * dir.z;

	dir.calcularNovoVetor(pos, watch);
	
}

void Camera::moveback()
{
	dir.unitarizar();
	pos.x -= MOVE_SPEED * dir.x;
	pos.y -= MOVE_SPEED * dir.y;
	pos.z -= MOVE_SPEED * dir.z;

	watch.x -= MOVE_SPEED * dir.x;
	watch.y -= MOVE_SPEED * dir.y;
	watch.z -= MOVE_SPEED * dir.z;

	dir.calcularNovoVetor(pos, watch);
}

void Camera::straferight()
{
	dir.unitarizar();
	Vector3 strafedir = dir.produtoVetorial(up); 
	pos.x += MOVE_SPEED * strafedir.x;
	pos.y += MOVE_SPEED * strafedir.y;
	pos.z += MOVE_SPEED * strafedir.z;

	watch.x += MOVE_SPEED * strafedir.x;
	watch.y += MOVE_SPEED * strafedir.y;
	watch.z += MOVE_SPEED * strafedir.z;
	dir.calcularNovoVetor(pos, watch);
}

void Camera::strafeleft()					  
{		
	dir.unitarizar();
	Vector3 strafedir = dir.produtoVetorial(up);
	pos.x -= MOVE_SPEED * strafedir.x;
	pos.y -= MOVE_SPEED * strafedir.y;
	pos.z -= MOVE_SPEED * strafedir.z;

	watch.x -= MOVE_SPEED * strafedir.x;
	watch.y -= MOVE_SPEED * strafedir.y;
	watch.z -= MOVE_SPEED * strafedir.z;

	dir.calcularNovoVetor(pos, watch);
}											  
											  
void Camera::rise()							  
{			
	dir.unitarizar();
	pos.x += MOVE_SPEED * up.x;
	pos.y += MOVE_SPEED * up.y;
	pos.z += MOVE_SPEED * up.z;

	watch.x += MOVE_SPEED * up.x;
	watch.y += MOVE_SPEED * up.y;
	watch.z += MOVE_SPEED * up.z;

	dir.calcularNovoVetor(pos, watch);
}											  
void Camera::fall()							  
{
	dir.unitarizar();
	pos.x -= MOVE_SPEED * up.x;
	pos.y -= MOVE_SPEED * up.y;
	pos.z -= MOVE_SPEED * up.z;

	watch.x -= MOVE_SPEED * up.x;
	watch.y -= MOVE_SPEED * up.y;
	watch.z -= MOVE_SPEED * up.z;

	dir.calcularNovoVetor(pos, watch);
}

void Camera::rotateLeft()
{

	int circlepoints = 72;
	int raiox = 1.0f;
	int raioy = 1.0f;
	float angle = 2 * 3.1415* angatual / circlepoints;
	watch.x += cos(angle)*raiox;
	watch.z -= sin(angle)*raioy;
	angatual += 1;
	

	dir.calcularNovoVetor(pos, watch);
}

void Camera::rotateRight()
{
	int circlepoints = 72;
	int raiox = 1.0f;
	int raioy = 1.0f;
	float angle = 2 * 3.1415* angatual / circlepoints;
	watch.x -= cos(angle)*raiox;
	watch.z += sin(angle)*raioy;
	angatual -= 1;


	dir.calcularNovoVetor(pos, watch);
}

void Camera::rotateUp()
{
	int circlepoints = 72;
	int raiox = 1.0f;
	int raioy = 1.0f;
	float angle = 2 * 3.1415* angatualvert / circlepoints;
	watch.y += cos(angle)*raiox;
	watch.z -= sin(angle)*raioy;
	angatualvert += 1;


	dir.calcularNovoVetor(pos, watch);
}

void Camera::rotateDown()
{
	int circlepoints = 72;
	int raiox = 1.0f;
	int raioy = 1.0f;
	float angle = 2 * 3.1415* angatualvert / circlepoints;
	watch.y -= cos(angle)*raiox;
	watch.z += sin(angle)*raioy;
	angatualvert -= 1;


	dir.calcularNovoVetor(pos, watch);
}

void Camera::resetlook()
{
	watch.x = pos.x;
	watch.y = pos.y + 1.5;
	watch.z = pos.z + 10;

	angatual = angatualvert = 0;
	dir.calcularNovoVetor(pos, watch);
}

void Camera::hardreset()
{
	pos.x = 0;
	pos.y = 0;
	pos.z = -1;

	watch.x = 0;
	watch.y = 1.5;
	watch.z = 9;

	up.x = 0;
	up.y = 1;
	up.z = 0;

	angatual = 0;
	angatualvert = 0;

	dir.calcularNovoVetor(pos, watch);
}
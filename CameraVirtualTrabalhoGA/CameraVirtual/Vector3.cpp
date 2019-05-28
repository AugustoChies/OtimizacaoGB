#include "Vector3.h"



Vector3::Vector3()
{
}


Vector3::~Vector3()
{
}


void Vector3::calcularNovoVetor(Vector3 v1, Vector3 v2)
{
	this->x = v2.x - v1.x;
	this->y = v2.y - v1.y;
	this->z = v2.z - v1.z;
}

float Vector3::calcularModulo()
{
	return sqrt(x*x + y*y + z*z);
}

void Vector3::unitarizar()
{
	float modulo = calcularModulo();
	x = x / modulo;
	y = y / modulo;
	z = z / modulo;
}

void Vector3::multiplicarEscalar(float n)
{
	x = x * n;
	y = y*n;
	z = z*n;
}

float Vector3::produtoEscalar(Vector3 v)
{
	return x * v.x + y*v.y + z* v.z;
}

Vector3 Vector3::produtoVetorial(Vector3 v)
{
	Vector3 result;

	result.x = (this->y * v.z) - (this->z * v.y);
	result.y = (this->z * v.x) - (this->x * v.z);
	result.z = (this->x * v.y) - (this->y * v.x);

	return result;
}
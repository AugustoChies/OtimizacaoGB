#pragma once
#include<math.h>

class Vector3
{
public:
	Vector3();
	~Vector3();
	float x, y, z;
	void calcularNovoVetor(Vector3 v1, Vector3 v2);
	float calcularModulo();
	void unitarizar();
	void multiplicarEscalar(float n);
	float produtoEscalar(Vector3 v);
	Vector3 produtoVetorial(Vector3 v);
};


#pragma once
#include "gl_utils.h"
#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <glm\/vec3.hpp>
#include <glm\/vec2.hpp>

using namespace std;

class Object
{
	//vertex normal e texcoord se manteram como struct pois nao funcionaram como simples vec3(provavelmente pq fiz algo errado :p
	struct vertex
	{
		glm::vec3 coord;
	};

	struct normal
	{
		glm::vec3 normalcoord;
	};

	struct texCoord
	{
		glm::vec2 texCoords;
	};


	struct color
	{
		glm::vec3 rgb;
	};

	struct texture {
		GLuint id;
		string type;
	};
	
	struct Mesh
	{
		vector<vertex> trueverts;
		vector<normal> truenorms;
		vector<texCoord> truetexcoords;

		vector<GLuint> vertindices;
		vector<GLuint> normindices;
		vector<GLuint> texindices;



		vector<color> tcolors;
		vector<texture> ttextures;
	};
public:
	Object();
	~Object();
	void draw();
	void drawWire(float x, float y, float z);
	void readobj(const char *arquivo);
	void setupMesh();
	void criaCores();
	void settextures(vector<GLuint> ids,vector<string> types);
protected:
	Mesh m;
	GLuint VAO, vertexVBO,normalVBO, uvVBO, EBO,colorvbo;
};


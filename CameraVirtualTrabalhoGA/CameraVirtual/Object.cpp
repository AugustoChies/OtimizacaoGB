#include "Object.h"



Object::Object()
{
}


Object::~Object()
{
}

void Object::settextures(vector<GLuint> ids, vector<string> types)
{
	for (int i = 0; i < ids.size(); i++)
	{
		texture tokentex;
		tokentex.id = ids[i];
		tokentex.type = types[i];
		m.ttextures.push_back(tokentex);
	}
}

void  Object::criaCores()
{
	float r = 0.0;
	float g = 0.0;
	float b = 0.0;
	int nextcor = 0;

	for (int i = 0; i < m.trueverts.size(); i++)
	{

		color cor;
		cor.rgb[0] = 0.0;
		cor.rgb[1] = 1.0;
		cor.rgb[2] = 0.0;

		m.tcolors.push_back(cor);
	}
}

void Object::setupMesh()
{
	criaCores();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &normalVBO);
	glGenBuffers(1, &uvVBO);
	glGenBuffers(1, &colorvbo);
	glGenBuffers(1, &EBO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, m.trueverts.size() * sizeof(vertex),
		&m.trueverts[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m.vertindices.size() * sizeof(GLuint),
		&m.vertindices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, this->normalVBO);
	glBufferData(GL_ARRAY_BUFFER, m.truenorms.size() * sizeof(normal),
		&m.truenorms[0], GL_STATIC_DRAW);

    

	glBindBuffer(GL_ARRAY_BUFFER, this->colorvbo);
	glBufferData(GL_ARRAY_BUFFER, m.tcolors.size() * sizeof(color),
		&m.tcolors[0], GL_STATIC_DRAW);


	texCoord ttok;
	ttok.texCoords[0] = 0.0;
	ttok.texCoords[1] = 1.0;

	m.truetexcoords.push_back(ttok);
	glBindBuffer(GL_ARRAY_BUFFER, this->uvVBO);
	glBufferData(GL_ARRAY_BUFFER, m.truetexcoords.size() * sizeof(texCoord),
	&m.truetexcoords[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m.vertindices.size() * sizeof(GLuint),
		&m.vertindices[0], GL_STATIC_DRAW);

	// Vertex Positions
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)0);

	//Normals
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(normal),
	(GLvoid*)0);
	
	//color
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, colorvbo);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(color), (GLvoid*)0);

	//texture
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, this->uvVBO);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(texCoord),
		(GLvoid*)0);


	glBindVertexArray(0);

}

void Object::draw()
{
		// Draw mesh
		glBindVertexArray(this->VAO);
		glDrawElements(GL_TRIANGLES, m.vertindices.size(), GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, m.trueverts.size());
		
		glBindVertexArray(0);
}



void Object::readobj(const char *arquivo)
{
	vector<vertex> tempverts;
	vector<normal> tempnorms;
	vector<texCoord> temptexcoords;
	ifstream arq(arquivo);
	char buffer[500];
	while (!arq.eof())
	{
		arq >> buffer;
		if (buffer[0] == 'v' && buffer[1] == 'n')
		{
				normal v;
				arq >> v.normalcoord[0] >> v.normalcoord[1] >> v.normalcoord[2];
				tempnorms.push_back(v);			
		}
		else if (buffer[0] == 'v' && buffer[1] == 't')
		{
				texCoord v;
				arq >> v.texCoords[0] >> v.texCoords[1];
				temptexcoords.push_back(v);
		}
		else if (buffer[0] == '#')
		{
			arq.getline(buffer, 500);
		}
		else if (buffer[0] == 'v')
		{
			vertex v;
			arq >> v.coord[0] >> v.coord[1] >> v.coord[2];
			tempverts.push_back(v);
		}
		else if (buffer[0] == 'f')
		{
			arq.getline(buffer, 500);
			string faceline = buffer;
			vector<string> tokens;
			string token;
			string sub1, sub2;
			int pos;
			istringstream streamstr(faceline);
			do {
				token.clear();
				streamstr >> token;
				if (!token.empty())
					tokens.push_back(token);
			} while (!token.empty());


			for (int i = 0; i < tokens.size(); i++)
			{
				bool temresto = true;
				GLuint index;
				//vertice
				pos = tokens[i].find('/');
				if (pos == -1)
				{
					pos = tokens[i].find(' ');
					temresto = false;
				}
				sub1 = tokens[i].substr(0,pos);
				int tokenint = stoi(sub1);
				tokenint--;  
				index = tokenint;
				m.vertindices.push_back(index);
				if (temresto)
				{
					//textura
					tokens[i] = tokens[i].substr(pos+1);
					pos = tokens[i].find('/');
					if (pos > 0)
					{
						sub2 = tokens[i].substr(0, pos);
						tokenint = stoi(sub2);
						tokenint--;
						index = tokenint;
						m.texindices.push_back(index);
					}
					
					//normal
					tokens[i] = tokens[i].substr(pos + 1);
					tokenint = stoi(tokens[i]);
					tokenint--;
					index = tokenint;
					m.normindices.push_back(index);

				}
			}
		}
	}
	arq.close();

	for (int i = 0; i < m.vertindices.size(); i++)
	{
		m.trueverts.push_back(tempverts[m.vertindices[i]]);
	}

	m.vertindices.clear();
	for (int i = 0; i < m.trueverts.size(); i++)
	{
		m.vertindices.push_back(i);
	}

	for (int i = 0; i < m.normindices.size(); i++)
	{
		m.truenorms.push_back(tempnorms[m.normindices[i]]);
	}

	if (temptexcoords.size() > 0)
	{

		for (int i = 0; i < m.texindices.size(); i++)
		{
			m.truetexcoords.push_back(temptexcoords[m.texindices[i]]);
		}
	}


}
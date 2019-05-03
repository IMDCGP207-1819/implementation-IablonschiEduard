#include "Mesh.h"
#include <vector>


using namespace std;

Mesh::Mesh(Vertex* verts, unsigned int vertCount, unsigned int *indices, unsigned int numIndices)
{
	m_drawCount = numIndices;

	vector<vec3> positions;
	vector<vec2> texCoords;

	for (unsigned int i = 0; i < vertCount; i++)
	{
		positions.push_back(verts[i].Position);
		texCoords.push_back(verts[i].TextureCoord);
	}

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);
	glGenBuffers(NUM_BUFFERS, m_vertexBufferObjects);// m_vertexBufferObjects


	//position
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjects[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(positions[0]),
		&positions[0], GL_STATIC_DRAW);
	glVertexAttribPointer(POSITION_VB, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(POSITION_VB);

	//"in vec2 TexCoords;" - vec2 not vec3 ???

	//Texture coords
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjects[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(texCoords[0]),
		&texCoords[0], GL_STATIC_DRAW);
	glVertexAttribPointer(TEXCOORD_VB, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(TEXCOORD_VB); ///////////////////////////////////// this whole part was commented out

	//index
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexBufferObjects[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int),
		indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	/*
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &m_vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, vertCount * 3 * sizeof(float),
		verts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindVertexArray(0);

	//Transform();
	*/
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);
	//glDrawArrays(GL_TRIANGLES, 0, m_drawCount);
	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
/*
#include "Mesh.h"

Mesh::Mesh(float* verts, unsigned int vertCount)
{
	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &m_vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, vertCount * 3 * sizeof(float),
		verts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindVertexArray(0);

	//Transform();
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
*/


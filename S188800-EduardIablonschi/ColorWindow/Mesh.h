#pragma once
#ifndef MESH_H
#define MESH_H

#include <glm\glm.hpp>
#include <glew.h>
#include "Transform.hpp"
#include "vertex.h"
class Mesh
{
public:
	enum VertexBuffers
	{
		POSITION_VB,
		TEXCOORD_VB,
		INDEX_VB,
		NUM_BUFFERS
	};
	Mesh(Vertex* verts, unsigned int vertCount, unsigned int *indices, unsigned int numIndices);
	void Draw();
	~Mesh();
	Transform m_transform;
	unsigned int m_drawCount;

private:
	GLuint m_vertexBufferObjects[NUM_BUFFERS]; // m_vertexBufferObject = 0;
	GLuint m_vertexArrayObject = 0;
};

#endif // !MESH_H



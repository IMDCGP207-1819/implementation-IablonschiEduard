#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>
using namespace glm;

struct Vertex
{
	vec3 Position;
	vec2 TextureCoord;

	Vertex(const float x, const float y, const float z)
	{
		this->Position.x = x;
		this->Position.y = y;
		this->Position.z = z;

		TextureCoord = { 0,0 };
	}

	Vertex(const vec3 position): Vertex(position.x, position.y, position.z)
	{

	}

	Vertex(const vec3 position, const vec2 texCoord)
	{
		this->Position = position;
		this->TextureCoord = texCoord;
	}
};
/*
class vertex
{
public:
	vertex();
	~vertex();
};
*/
#endif // !VERTEX_H


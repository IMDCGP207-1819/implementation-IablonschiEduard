#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <glew.h>
#include <SDL_opengl.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <SDL.h>

#include "Transform.hpp"

using namespace glm;

class Camera
{
public:
	Camera();
	Camera(glm::vec3 m_StartPosition, glm::vec3 m_StartUp, GLfloat StartYaw, GLfloat StartPitch, GLfloat StartMoveSpeed, GLfloat StartTurnSpeed);

	glm::mat4 CalculateViewMatrix();

	glm::mat4 GetPerspective();

	void CameraKeyControl(GLfloat DeltaTime);
	//void CameraMouseControl(GLfloat xChange, GLfloat yChange);

	~Camera();

	void update();

private:
	Transform transform;
	vec3 m_Up;
	vec3 m_Forward; // Direction, Front
	vec3 m_Right;
	vec3 m_WorldUp = vec3(0, 1, 0);
	vec3 m_Position;
	vec3 m_Target = vec3(0,0,0); // ???

	GLfloat Yaw; // look left and right with the camera
	GLfloat Pitch; // look up and down with the camera

	GLfloat MoveSpeed;
	GLfloat TurnSpeed;

	
	
	//vec3 m_Forward = normalize(vec3(0) - m_Position); // m_Target
	//vec3 m_Right = normalize(cross(m_WorldUp, m_Forward));
	//vec3 m_Up = cross(m_Forward, m_Right);
	//glm::lookAt(m_Position, m_Position + m_Forward, m_Up); // in middle WAS - vec3(0) = m_Position + m_Forward ???

	//m_PerspectiveProjection = glm::perspective(fov, aspect, zNear, zFar);

	

};


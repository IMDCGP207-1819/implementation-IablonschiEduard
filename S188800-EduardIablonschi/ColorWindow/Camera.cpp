#include "Camera.h"
#include <iostream>
Camera::Camera()
{

}

Camera::Camera(glm::vec3 m_StartPosition, glm::vec3 m_StartUp, GLfloat StartYaw, GLfloat StartPitch, GLfloat StartMoveSpeed, GLfloat StartTurnSpeed)
{
	m_Position = m_StartPosition;
	m_WorldUp = m_StartUp; // was m_Up
	Yaw = StartYaw;
	Pitch = StartPitch;
	m_Forward = glm::vec3(0.0f, 0.0f, -1.0f);

	MoveSpeed = StartMoveSpeed;
	TurnSpeed = StartTurnSpeed;

	update();
}

glm::mat4 Camera::CalculateViewMatrix()
{
	return glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
	//return glm::lookAt(m_Position, m_Target, vec3(0,1,0));
}

glm::mat4 Camera::GetPerspective()
{
	return glm::perspective(70.0f, (float)800/(float)600, 0.01f, 1000.0f);
}

void Camera::update()
{
	m_Forward.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	m_Forward.y = sin(glm::radians(Pitch));
	m_Forward.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	m_Forward = glm::normalize(m_Forward);

	//m_Forward = m_Target - m_Position;

	m_Right = glm::normalize(glm::cross(m_WorldUp, m_Forward));
	m_Up = glm::normalize(glm::cross (m_Forward, m_Right));
}
//???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
void Camera::CameraKeyControl(GLfloat DeltaTime)
{
	
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		const Uint8* KeyState = SDL_GetKeyboardState(NULL);
		GLfloat Velocity = MoveSpeed * DeltaTime;

		if (KeyState[SDL_GetScancodeFromKey(SDLK_w)])
		{
			m_Position += vec3(0, 0, 1) * 0.2f;//m_Forward * Velocity;
			/*vec3 temp = normalize(vec3(sin(Yaw), sin(Pitch), cos(Yaw)));
			m_Position += temp;
			std::cout << temp.x<< temp.y << temp.z << std::endl;*/
		}

		if (KeyState[SDL_GetScancodeFromKey(SDLK_s)])
		{
			m_Position -= vec3(0, 0, 1)* 0.2f;//m_Forward * Velocity;
		}

		if (KeyState[SDL_GetScancodeFromKey(SDLK_a)])
		{
			m_Position += vec3(1, 0, 0)* 0.2f; // m_Right * Velocity;
		}

		if (KeyState[SDL_GetScancodeFromKey(SDLK_d)])
		{
			m_Position -= vec3(1, 0, 0)* 0.2f; // m_Right * Velocity;
		}

		if (KeyState[SDL_GetScancodeFromKey(SDLK_UP)])
		{
			m_Position += vec3(0, 1, 0)* 0.2f; // m_Right * Velocity;
		}

		if (KeyState[SDL_GetScancodeFromKey(SDLK_DOWN)])
		{
			m_Position -= vec3(0, 1, 0)* 0.2f; // m_Right * Velocity;
		}

		if (KeyState[SDL_GetScancodeFromKey(SDLK_i)])
		{
			Pitch += 1.0f;
		}
		if (KeyState[SDL_GetScancodeFromKey(SDLK_k)])
		{
			Pitch -= 1.0f;
		}
		if (KeyState[SDL_GetScancodeFromKey(SDLK_l)])
		{
			Yaw += 1.0f;
		}
		if (KeyState[SDL_GetScancodeFromKey(SDLK_j)])
		{
			Yaw -= 1.0f;
		}

		if (Pitch > 89.0f)
		{
			Pitch = 89.0f;
		}

		if (Pitch < -89.0f)
		{
			Pitch = -89.0f;
		}

		if (e.type == SDL_QUIT)
		{
			//m_Quit = true;
		}
	}
	

}

/*void Camera::CameraMouseControl(GLfloat xChange, GLfloat yChange)
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	//

	GLint x = e->wheel.x;
	GLint y = e->wheel.y;
	//

	xChange *= TurnSpeed;
	yChange *= TurnSpeed;

	Yaw += xChange;
	Pitch += yChange;

	if (Pitch > 89.0f)
	{
		Pitch = 89.0f;
	}

	if (Pitch < -89.0f)
	{
		Pitch = -89.0f;
	}



	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEWHEEL)
		{

		}

	}

	update();
}
*/


Camera::~Camera()
{
}

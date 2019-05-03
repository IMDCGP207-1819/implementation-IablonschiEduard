#define GLEW_STATIC

#include <glew.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL.h>
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include "Mesh.h"
#include "vertex.h"
#include <vector>
#include "Camera.h"
#include <fstream>
using namespace std;


GLfloat DeltaTime = 0.0f;
GLfloat LastTime = 0.0f;

void openGL()
{
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); // 32 bit inc RGBA
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16); // depth is not 32 bit
}

 
void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string &errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		cerr << errorMessage << ": '" << error << "'" << endl;
	}
}



int main(int arcg, char *argv[])
{
	

	SDL_Init(SDL_INIT_EVERYTHING);

	openGL();

	SDL_Window* window = SDL_CreateWindow("My window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	SDL_GLContext GLContext = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;
	GLenum status = glewInit();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	Camera camera = Camera(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 1.0f, 1.0f);
	/* glm::vec3 m_StartPosition, glm::vec3 m_StartUp, GLfloat StartYaw, GLfloat StartPitch, GLfloat StartMoveSpeed, GLfloat StartTurnSpeed */

	if (status != GLEW_OK)
	{
		cout << "GLEW failed to initialize!" << endl;
	}

	//while (true)
	//{
	//	SDL_Delay(175);
	//	glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	glViewport(0, 0, 800, 600);

	//	SDL_GL_SwapWindow(window);


	//	/*SDL_Delay(175);
	//	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	glViewport(0, 0, 800, 600);

	//	SDL_GL_SwapWindow(window);
	//	*/
	//}

	//triangle

	
	//float Vertices[]{
	//	/*0.0f, 0.5f, 0.0f,
	//	0.5f, -0.5f, 0.0f,
	//	-0.5f, -0.5f, 0.0f*/
	//	0.0f, 0.5f, 0.0f,
	//	0.5f, -0.5f, 0.0f,
	//	-0.5f, -0.5f, 0.0f
	//};

	//triangle
	/*
	vector<Vertex> Verts;
	Verts.push_back(Vertex(0.0f, 0.5f, 0.0f));
	Verts.push_back(Vertex(0.5f, -0.5f, 0.0f));
	Verts.push_back(Vertex(-0.5f, -0.5f, 0.0f));	

	uint indicies[]{0,1,2};
	*/
	

	vector<Vertex> Verts;
	Verts.push_back(Vertex(vec3(-0.5f, 0.5f, 0.0f), vec2(0.5, 0.5)));
	Verts.push_back(Vertex(vec3(0.5f, 0.5f, 0.0f), vec2(0.5, 0.5)));
	Verts.push_back(Vertex(vec3(0.5f, -0.5f, 0.0f), vec2(0, 0)));//first/close square, bottom right corner
	Verts.push_back(Vertex(vec3(-0.5f, -0.5f, 0.0f), vec2(0.5, 0.5)));
	Verts.push_back(Vertex(vec3(-0.5f, 0.5f, 1.0f), vec2(0, 0)));//second/far square, top left corner
	Verts.push_back(Vertex(vec3(0.5f, 0.5f, 1.0f), vec2(0.5, 0.5)));
	Verts.push_back(Vertex(vec3(0.5f, -0.5f, 1.0f), vec2(0.5, 0.5)));
	Verts.push_back(Vertex(vec3(-0.5f, -0.5f, 1.0f), vec2(0.5, 0.5)));


	uint indicies[]
	{ 
		0,1,2,0,2,3,0,4,5,0,5,1,0,3,7,0,7,4,1,6,2,1,5,6,2,6,7,2,7,3,4,7,6,4,6,5
	};

	Mesh Tri1(&Verts[0], Verts.size(), indicies, 36); 


	const char* VertexShaderCode = 
		
		"#version 450\n"
		"in vec3 vp;"
		//"in vec2 TexCoords;"
		"uniform mat4 model;"
		"uniform mat4 view;"
		"uniform mat4 perspective;"
		"void main() {"
		"  gl_Position = perspective * view * model * vec4(vp, 1.0);"
		"}";
	

	const char* FragmentShaderCode =
		
		"#version 450\n"
		"out vec4 frag_colour;"
		"void main() {"
		"  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
		"}";
		
		

	GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader, 1, &VertexShaderCode, NULL);
	glCompileShader(VertexShader);
	GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, &FragmentShaderCode, NULL);
	glCompileShader(FragmentShader);

	GLuint ShaderPrograme = glCreateProgram(); // essential
	glAttachShader(ShaderPrograme, VertexShader); // essential
	glAttachShader(ShaderPrograme, FragmentShader); // essential

	glLinkProgram(ShaderPrograme); // essential
	CheckShaderError(ShaderPrograme, GL_LINK_STATUS, true,
		"Error: program linking failed: ");
	glValidateProgram(ShaderPrograme);
	CheckShaderError(ShaderPrograme, GL_VALIDATE_STATUS, true,
		"Error: program is invalid: ");

	glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
	glViewport(0, 0, 800, 600);


	while (true)
	{
		GLfloat Now = SDL_GetPerformanceCounter();
		DeltaTime = (Now - LastTime) * 1000 / SDL_GetPerformanceFrequency();
		LastTime = Now;

		camera.CameraKeyControl(DeltaTime);
		/*
		camera.CameraMouseControl(xChange, yChange);
		*/

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(ShaderPrograme);

		GLint modelLoc = glGetUniformLocation(ShaderPrograme, "model"); 
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &Tri1.m_transform.GetModel()[0][0]);

		GLint viewLoc = glGetUniformLocation(ShaderPrograme, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &camera.CalculateViewMatrix()[0][0]);
		//mat4 temp = camera.CalculateViewMatrix();

		GLint perspectiveLoc = glGetUniformLocation(ShaderPrograme, "perspective");
		glUniformMatrix4fv(perspectiveLoc, 1, GL_FALSE, &camera.GetPerspective()[0][0]);

		//Tri1.m_transform.setPos(vec3(-1, 0, 0)); //- change the position of the triangle mesh
		//Tri1.m_transform.setRot(Tri1.m_transform.getRot() + vec3(0, 0.01f, 0)); //- change the rotation of the triangle mesh
		Tri1.Draw();

		//do the steps below for a 2nd mesh
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &Tri2.m_transform.GetModel()[0][0]);
		//Tri2.Draw();
		
		camera.update();


		SDL_GL_SwapWindow(window);
		SDL_Delay(16);

	}

	SDL_GL_DeleteContext(GLContext);
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
	return 0;
	
}


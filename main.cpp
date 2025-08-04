#include<iostream>
//ע��gladͷ�ļ�������glfw����֮ǰ
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <string>
#include <assert.h>
#include "wrapper/checkError.h"
#include "application/Application.h"



/*Ŀ�� ������glfw�Ĵ���ϵͳ
* ���봰��仯���¼��ص�
* ���������Ϣ�¼��ص�
* 
* 1ʹ��glad�������е�ǰ�汾��Ҫ��opengl����
* 2�鿴glad��Դ���룬�������������ʲô
* 3������ϰ
* 3.1 glViewport:�涨�ӿڴ�С
  3.2 glClearColor:���û����������ɫ
  3.3 glClear(GL COLOR BUFFER BIT):ִ�л����������
  3.4 glfwSwapBuffers(window):ִ��˫�����л�
  4.1 ��дһ��OnResize����Ӧ���巢���仯
*/
GLuint vao, program;

void OnResize(int width, int height) {
	GL_CALL(glViewport(0, 0, width, height));
	std::cout << "OnResize" << std::endl;
}

void OnKey(int key, int action, int mods) {
	std::cout << key << std::endl;
}

//void prepareVBO() {
//	//1 ����һ��vbo*******��û�����������Դ�*****
//	GLuint vbo = 0;
//	GL_CALL(glGenBuffers(1, &vbo));
//	//2 ����һ��vbo
//	GL_CALL(glDeleteBuffers(1, &vbo));
//	//3 ����n��vbo
//	GLuint vboArr[] = { 0,0,0 };
//	GL_CALL(glGenBuffers(3, vboArr));
//	//4 ����n��vbo
//	GL_CALL(glDeleteBuffers(3, vboArr));
//
//}
//
//
//void prepare() {
//	float vertices[] = {
//		-0.5f, -0.5f, 0.0f,
//		 0.5f, -0.5f, 0.0f,
//		 0.0f, 0.5f,  0.0f };
//	//����һ��vbo
//	GLuint vbo = 0;
//	GL_CALL(glGenBuffers(1, &vbo));
//	//2 �󶨵�ǰvbo����opengl״̬���ĵ�ǰvbo�����
//	// GL ARRAY BUFFER:��ʾ��ǰvbo������
//	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
//	//3 ��ǰvbo�������ݣ�Ҳ���ڿ����Դ�
//	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
//
//
//}
//
//
//void prepareSingleBuffer() {
//	//1 ׼������λ����������ɫ����
//	float positions[] = {
//		-0.5f, -0.5f, 0.0f,
//		0.5f, -0.5f, 0.0f,
//		0.0f, 0.5f, 0.0f
//	};
//	float colors[] = {
//		1.0f, 0.0f, 0.0f,
//		0.0f, 1.0f, 0.0f,
//		0.0f, 0.0f, 1.0f
//	};
//	
//	//2 Ϊλ��&��ɫ���ݸ�������һ��vbo
//	GLuint posVbo = 0, colorVbo = 0;
//	GL_CALL(glGenBuffers(1, &posVbo));
//	GL_CALL(glGenBuffers(1, &colorVbo));
//	
//	//3 �������ֿ���vbo�����������
//	//positions�������
//	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
//	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));
//
//	//color�������
//	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorVbo));
//	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));
//}
//
//void preparelnterleavedBuffer() {
//	float vertices[] = {
//			-0.5f, -0.5f, 0.0f,1.0f, 0.0f, 0.0f,
//			0.0f, 1.0f, 0.0f,0.0f, 1.0f, 0.0f,
//			0.0f, 0.5f, 0.0f,0.0f, 0.0f, 1.0f
//	};
//	GLuint vbo = 0;
//	GL_CALL(glGenBuffers(1, &vbo));
//	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
//	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
//}
//

//�������ݷ���vao��vbo,���ʳ������vs��fs��
void prepareSingleBuffer() {
	//1 ׼��positions colors����
	float positions[] = {
				-0.5f, -0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
				0.0f, 0.5f, 0.0f
			};
			float colors[] = {
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f
			};
	//2 ʹ��������������vbo posVbo��colorVbo
			GLuint posVbo = 0, colorVbo = 0;
			glGenBuffers(1, &posVbo);
			glGenBuffers(1, &colorVbo);

			glBindBuffer(GL_ARRAY_BUFFER, posVbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	//3 ����vao���Ұ�
			
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

	
	//4 �ֱ�λ��/��ɫ���Ե�������Ϣ����vao����
	//       4.1����λ������
			//ֻ�а���posVbo;��������������Ż����bo���
			glBindBuffer(GL_ARRAY_BUFFER, posVbo);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*)0);
			//4.2������ɫ����
			glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

			glBindVertexArray(0);
}
//λ������ɫ��һ������
void preparelnterleavedBuffer() {
	//1׼����Interleaved����(λ��+��ɫ)
	float vertices[] = {
		   -0.5f, -0.5f, 0.0f,1.0f, 0.0f, 0.0f,
		   0.5f, -0.5f, 0.0f,0.0f, 1.0f, 0.0f,
		   0.0f, 0.5f, 0.0f,0.0f, 0.0f, 1.0f };
	//2 ����Ψһ��vbo
	 GLuint vbo = 0;
	GL_CALL(glGenBuffers(1, &vbo));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
	//3 ��������vao
	
	GL_CALL(glGenVertexArrays(1, &vao));
	GL_CALL(glBindVertexArray(vao));
	//4 Ϊvao����λ�ú���ɫ��������Ϣ
	//4.1λ����Ϣ����
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GL_CALL(glEnableVertexAttribArray(0));
	GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0));
	//4.2��ɫ������Ϣ
	GL_CALL(glEnableVertexAttribArray(1));                                          //(3 * sizeof(float))��������ɫ��ƫ����
	GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))));
	//���ǰvao
	glBindVertexArray(0);
}


void prepareShader() {
	const char* vertexShaderSource =
		"#version 460 core\n"
		"layout(location = 0)in vec3 aPos; \n"
		"void main()\n"
		"{\n"
		"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
		"}\0";
	const char* fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor; \n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";
		//2 ����Shader����(vs��fs)
	GLuint vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
		//3 Ϊshader��������shader����
	glShaderSource(vertex, 1, &vertexShaderSource, NULL);
	glShaderSource(fragment, 1, &fragmentShaderSource, NULL);

	int success = 0;
	char inFolog[1024];
		//4 ִ��shader�������
	glCompileShader(vertex);
	//���vertex������
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 1024, NULL, inFolog);
		std::cout << "Error:SHADER COMPILAE ERROE-VERTEX" << "\n" << inFolog << std::endl;
	}

	glCompileShader(fragment);
	//���fragment������
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 1024, NULL, inFolog);
		std::cout << "Error:SHADER COMPILAE ERROE-FRAGMENT" << "\n" << inFolog << std::endl;
	}
	//5 ����һ��Program����
	
	program = glCreateProgram();
	//6 ��vs��fs����õĽ���ŵ�program���������
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	//7 ִ��program�����Ӳ������γ����տ�ִ��shader����
	glLinkProgram(program);
	//������Ӵ���
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 1024, NULL, inFolog);
		std::cout << "Error:SHADER LINK ERROR" << "\n" << inFolog << std::endl;
	}
	//����
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}


void render() {
	//ִ�л����������
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

	//1 �󶨵�ǰ��program
	glUseProgram(program);
	//2 �󶨵�ǰ��vao
	glBindVertexArray(vao);

	//3 ��������ָ��
	glDrawArrays(GL_TRIANGLES, 0, 3);

}

int main() {
	if (!app->init(800, 600)) {
		return -1;
	}
	//app�Ǻ궨�� Application::getInstance()
	app->SetResizeCallback(OnResize);
	app->SetKeyBoardCallback(OnKey);
	//����opengl�ӿ��Լ�������ɫ
	glViewport(0, 0, 800, 600);
	
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);


	prepareShader();
	//prepareSingleBuffer();
	preparelnterleavedBuffer();
	
//3 ִ�д���ѭ��
	while (app->update()) {

		render();
	
		
		
		//������
		
		//��Ⱦ����
	}
	//4 �˳�����ǰ���������
	app->destroy();
	return 0;
}
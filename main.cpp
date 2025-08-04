#include<iostream>
//注意glad头文件必须在glfw引用之前
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <string>
#include <assert.h>
#include "wrapper/checkError.h"
#include "application/Application.h"



/*目标 ：创建glfw的窗体系统
* 加入窗体变化的事件回调
* 加入键盘消息事件回调
* 
* 1使用glad加载所有当前版本需要的opengl函数
* 2查看glad的源代码，并且理解他做了什么
* 3函数练习
* 3.1 glViewport:规定视口大小
  3.2 glClearColor:设置画布清理的颜色
  3.3 glClear(GL COLOR BUFFER BIT):执行画布清理操作
  3.4 glfwSwapBuffers(window):执行双缓存切换
  4.1 编写一个OnResize，响应窗体发生变化
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
//	//1 创建一个vbo*******还没有真正分配显存*****
//	GLuint vbo = 0;
//	GL_CALL(glGenBuffers(1, &vbo));
//	//2 销毁一个vbo
//	GL_CALL(glDeleteBuffers(1, &vbo));
//	//3 创建n个vbo
//	GLuint vboArr[] = { 0,0,0 };
//	GL_CALL(glGenBuffers(3, vboArr));
//	//4 销毁n个vbo
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
//	//生成一个vbo
//	GLuint vbo = 0;
//	GL_CALL(glGenBuffers(1, &vbo));
//	//2 绑定当前vbo，到opengl状态机的当前vbo插槽上
//	// GL ARRAY BUFFER:表示当前vbo这个插槽
//	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
//	//3 向当前vbo传输数据，也是在开辟显存
//	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
//
//
//}
//
//
//void prepareSingleBuffer() {
//	//1 准备顶点位置数据与颜色数据
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
//	//2 为位置&颜色数据各自生成一个vbo
//	GLuint posVbo = 0, colorVbo = 0;
//	GL_CALL(glGenBuffers(1, &posVbo));
//	GL_CALL(glGenBuffers(1, &colorVbo));
//	
//	//3 给两个分开的vbo各自填充数据
//	//positions填充数据
//	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
//	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));
//
//	//color填充数据
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

//几何数据放在vao与vbo,材质程序放在vs与fs里
void prepareSingleBuffer() {
	//1 准备positions colors数据
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
	//2 使用数据生成两个vbo posVbo，colorVbo
			GLuint posVbo = 0, colorVbo = 0;
			glGenBuffers(1, &posVbo);
			glGenBuffers(1, &colorVbo);

			glBindBuffer(GL_ARRAY_BUFFER, posVbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	//3 生成vao并且绑定
			
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

	
	//4 分别将位置/颜色属性的描述信息加入vao当中
	//       4.1描述位置属性
			//只有绑定了posVbo;下面的属性描述才会与此bo相关
			glBindBuffer(GL_ARRAY_BUFFER, posVbo);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*)0);
			//4.2描述颜色属性
			glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

			glBindVertexArray(0);
}
//位置与颜色放一个数组
void preparelnterleavedBuffer() {
	//1准备好Interleaved数据(位置+颜色)
	float vertices[] = {
		   -0.5f, -0.5f, 0.0f,1.0f, 0.0f, 0.0f,
		   0.5f, -0.5f, 0.0f,0.0f, 1.0f, 0.0f,
		   0.0f, 0.5f, 0.0f,0.0f, 0.0f, 1.0f };
	//2 创建唯一的vbo
	 GLuint vbo = 0;
	GL_CALL(glGenBuffers(1, &vbo));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
	//3 创建并绑定vao
	
	GL_CALL(glGenVertexArrays(1, &vao));
	GL_CALL(glBindVertexArray(vao));
	//4 为vao加入位置和颜色的描述信息
	//4.1位置信息描述
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GL_CALL(glEnableVertexAttribArray(0));
	GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0));
	//4.2颜色描述信息
	GL_CALL(glEnableVertexAttribArray(1));                                          //(3 * sizeof(float))是描述颜色的偏移量
	GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))));
	//解绑当前vao
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
		//2 创建Shader程序(vs、fs)
	GLuint vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
		//3 为shader程序输入shader代码
	glShaderSource(vertex, 1, &vertexShaderSource, NULL);
	glShaderSource(fragment, 1, &fragmentShaderSource, NULL);

	int success = 0;
	char inFolog[1024];
		//4 执行shader代码编译
	glCompileShader(vertex);
	//检查vertex编译结果
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 1024, NULL, inFolog);
		std::cout << "Error:SHADER COMPILAE ERROE-VERTEX" << "\n" << inFolog << std::endl;
	}

	glCompileShader(fragment);
	//检查fragment编译结果
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 1024, NULL, inFolog);
		std::cout << "Error:SHADER COMPILAE ERROE-FRAGMENT" << "\n" << inFolog << std::endl;
	}
	//5 创建一个Program壳子
	
	program = glCreateProgram();
	//6 将vs与fs编译好的结果放到program这个壳子里
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	//7 执行program的链接操作，形成最终可执行shader程序
	glLinkProgram(program);
	//检查链接错误
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 1024, NULL, inFolog);
		std::cout << "Error:SHADER LINK ERROR" << "\n" << inFolog << std::endl;
	}
	//清理
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}


void render() {
	//执行画布清理操作
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

	//1 绑定当前的program
	glUseProgram(program);
	//2 绑定当前的vao
	glBindVertexArray(vao);

	//3 发出绘制指令
	glDrawArrays(GL_TRIANGLES, 0, 3);

}

int main() {
	if (!app->init(800, 600)) {
		return -1;
	}
	//app是宏定义 Application::getInstance()
	app->SetResizeCallback(OnResize);
	app->SetKeyBoardCallback(OnKey);
	//设置opengl视口以及清理颜色
	glViewport(0, 0, 800, 600);
	
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);


	prepareShader();
	//prepareSingleBuffer();
	preparelnterleavedBuffer();
	
//3 执行窗口循环
	while (app->update()) {

		render();
	
		
		
		//检查错误
		
		//渲染操作
	}
	//4 退出程序前做相关清理
	app->destroy();
	return 0;
}
#include "Application.h"
#include<glad/glad.h>
#include<GLFW/glfw3.h>



//初始化Application的静态变量
Application* Application::mInstance = nullptr;
Application* Application::getInstance() {
	//如果mInstance已经实例化了(new出来了)，就直接返回
	//否则需要先new出来，再返回
	if (mInstance == nullptr) {
		mInstance = new Application();
	}
	return mInstance;
}
Application::Application() {

}
Application::~Application() {

}


bool Application::init(const int& width, const int& height){
	mWidth = width;
	mHeigh = height;


	glfwInit();
	//1.1 设置OpenGL主板本号，次版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//1.2 设置OpenGL启用核心模式（非立即渲染模式）
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//创建窗体对象
	mWindow = glfwCreateWindow(mWidth, mHeigh, "Opengl", NULL, NULL);
	if (mWindow == NULL) {
		return false;
	}

	//设置当前窗体对象为OpenGL的绘制舞台
	glfwMakeContextCurrent(mWindow);

	//使用glad加载所有当前版本opengl的函数
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
	glfwSetFramebufferSizeCallback(mWindow, frameBufferSizeCallback);

	//this就是当前全局唯一的Application对象
	glfwSetWindowUserPointer(mWindow, this);

	//键盘响应
	glfwSetKeyCallback(mWindow, keyCallback);
	
	return true;
}

bool Application::update(){
	if (glfwWindowShouldClose(mWindow)) {
		return false;
	}
	//接受并发窗口消息
	//检测消息队列是否有需要处理的鼠标、键盘等消息
	//如果有的话就将消息批量处理，清空队列
	glfwPollEvents();

	//切换双缓存
	glfwSwapBuffers(mWindow);
	return true;
}

void Application::destroy(){
	glfwTerminate();

}

void Application::frameBufferSizeCallback(GLFWwindow* window, int width, int heigh) {
	std::cout << "Resize" << std::endl;

	Application*self =(Application*)glfwGetWindowUserPointer(window);
	if (self->mResizeCallback != nullptr) {
		self->mResizeCallback(width, heigh);
	}
	/*if (Application::getInstance()->mResizeCallback != nullptr) {
		Application::getInstance()->mResizeCallback(width, heigh);
	}*/

}
void Application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mKeyBoardCallback != nullptr) {
		self->mKeyBoardCallback(key, action, mods);
	}
}
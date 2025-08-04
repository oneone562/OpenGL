#pragma once
#include <iostream>


#define app Application::getInstance()

class GLFWwindow;
using ResizeCallback = void(*)(int width, int height);
using KeyBoardCallback = void(*)(int key, int action, int mods);

/*1单例类(全局唯一实例)
  2成员变量 +成员函数
  2.1 成员函数-init(初始化)
  2.2 成员函数-update(每一帧执行)
  2.3 成员函数-destroy(结尾执行)
//3 响应回调函数Resize
  3.1声明一个函数指针ResizeCallback
  3.2声明一个ResizeCallback类型的成员变量
  3.3声明一个SetResizeCallback的函数，设置窗体变化响应回调函数
  3.4声明一个static的静态函数，用于响应glfw窗体变化
  3.5将静态函数设置到glfw的监听Resize监听当中
  3.6*学会使用glfw的UserPointer
  4 响应键盘消息函数(0nKeyBoard)
  3.1声明一个static的静态函数，用于响应glfw的键盘事件
  3.2将静态函数设置到glfw的监听KeyCallback监听当中
  3.3声明一个函数指针KeyBoardCallback
  3.4 声明一个KeyBoardCallback类型的成员变量
  3.5 声明一个SetKeyBoardCallback的函数 ，设置键盘响应回调函数
  3.6*学会使用glfw的UserPointer
*/

class Application {
public:
    ~Application();
    //用于访问实例的静态函数
    static Application* getInstance();

    bool init(const int& width = 800, const int& height = 600);

    bool update();

    void destroy();

    uint32_t getWidth()const {return mWidth;}
    uint32_t getHeigh()const { return mHeigh;}

    void SetResizeCallback(ResizeCallback callback) { mResizeCallback = callback;}
    void SetKeyBoardCallback(KeyBoardCallback callback) { mKeyBoardCallback = callback; }
private:
    static void frameBufferSizeCallback(GLFWwindow* window, int width, int heigh);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
     //全局唯一的静态变量实例
    static Application* mInstance;
    uint32_t mWidth{ 0 };
    uint32_t mHeigh{ 0 };
    GLFWwindow* mWindow{ nullptr };
    ResizeCallback mResizeCallback{ nullptr };
    KeyBoardCallback mKeyBoardCallback{ nullptr };
     Application();
};
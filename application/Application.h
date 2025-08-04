#pragma once
#include <iostream>


#define app Application::getInstance()

class GLFWwindow;
using ResizeCallback = void(*)(int width, int height);
using KeyBoardCallback = void(*)(int key, int action, int mods);

/*1������(ȫ��Ψһʵ��)
  2��Ա���� +��Ա����
  2.1 ��Ա����-init(��ʼ��)
  2.2 ��Ա����-update(ÿһִ֡��)
  2.3 ��Ա����-destroy(��βִ��)
//3 ��Ӧ�ص�����Resize
  3.1����һ������ָ��ResizeCallback
  3.2����һ��ResizeCallback���͵ĳ�Ա����
  3.3����һ��SetResizeCallback�ĺ��������ô���仯��Ӧ�ص�����
  3.4����һ��static�ľ�̬������������Ӧglfw����仯
  3.5����̬�������õ�glfw�ļ���Resize��������
  3.6*ѧ��ʹ��glfw��UserPointer
  4 ��Ӧ������Ϣ����(0nKeyBoard)
  3.1����һ��static�ľ�̬������������Ӧglfw�ļ����¼�
  3.2����̬�������õ�glfw�ļ���KeyCallback��������
  3.3����һ������ָ��KeyBoardCallback
  3.4 ����һ��KeyBoardCallback���͵ĳ�Ա����
  3.5 ����һ��SetKeyBoardCallback�ĺ��� �����ü�����Ӧ�ص�����
  3.6*ѧ��ʹ��glfw��UserPointer
*/

class Application {
public:
    ~Application();
    //���ڷ���ʵ���ľ�̬����
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
     //ȫ��Ψһ�ľ�̬����ʵ��
    static Application* mInstance;
    uint32_t mWidth{ 0 };
    uint32_t mHeigh{ 0 };
    GLFWwindow* mWindow{ nullptr };
    ResizeCallback mResizeCallback{ nullptr };
    KeyBoardCallback mKeyBoardCallback{ nullptr };
     Application();
};
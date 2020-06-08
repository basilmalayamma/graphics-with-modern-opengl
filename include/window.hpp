#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window();
    Window(int width, int height);
    int initialize(void);
    int getBufferWidth(void);
    int getBufferHeight(void);
    int getShouldClose(void);
    void swapBuffers(void);
    ~Window();
private:
    GLFWwindow *mMainWindow;
    GLint mWidth, mHeight;
    int mBufferWidth, mBufferHeight;
};

#endif //_WINDOW_H_

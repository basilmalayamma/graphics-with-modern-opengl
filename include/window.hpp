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
    bool* getKeys(void);
    double getXchange(void);
    double getychange(void);
    ~Window();
private:
    bool mKeys[1024];
    GLFWwindow *mMainWindow;
    GLint mWidth, mHeight;
    int mBufferWidth, mBufferHeight;
    bool mMouseFirstMove;
    double mLastx, mLasty;
    double mXChange, mYChange;
    void createCallbacks(void);
    static void handleKeys(
		    GLFWwindow *window,
		    int key,
		    int code,
		    int action,
		    int mode);
    static void handleMouse(
		    GLFWwindow *window,
		    double xpos,
		    double ypos);
};

#endif //_WINDOW_H_

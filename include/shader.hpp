#ifndef _SHADER_H_
#define _SHADER_H_

#include <GL/glew.h>
#include <string.h>
#include <fstream>

class shader {
public:
    shader();
    void createFromString(
		    const char *vShader,
		    const char *fShader);
    void createFromFiles(
		    const char *vShader,
		    const char *fShader);
    GLuint getUniformModel(void);
    GLuint getUniformProjection(void);
    void useShader(void);
    void clearShader(void);
    ~shader();
private:
    GLuint mShader;
    GLuint mUniformModel, mUniformProjection;
    void compileShaders(
		    const char *vShader,
		    const char *fShader);
    void addShaders(
		const char* shaderCode, 
		GLenum shaderType);
    std::string readFile(const char *location);
};

#endif //_SHADER_H_

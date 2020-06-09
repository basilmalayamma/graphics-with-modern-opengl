#include <iostream>
#include <fstream>
#include <string.h>
#include <shader.hpp>

shader::shader() {
    mShader = 0;
    mUniformModel = 0;
    mUniformProjection = 0;
}

void shader::createFromString(
		const char *vShader,
		const char *fShader) {
    compileShaders(vShader, fShader);
}

void shader::createFromFiles(
		const char *vShader,
		const char *fShader) {
    std::string vsCode = readFile(vShader);
    std::string fsCode = readFile(fShader);
    createFromString(vsCode.c_str(), fsCode.c_str());
}

std::string shader::readFile(const char *location) {
    std::ifstream file;
    file.open(location, std::ios::in);
    if(!file.is_open()) {
	std::cout << "Opening " << location << " failed" << std::endl;
	return "";
    }

    std::string content;
    std::string line;
    while(!file.eof()) {
	std::getline(file, line);
	content.append(line + "\n");
    }
    file.close();
    return content;
}

void shader::compileShaders(const char *vShader, const char *fShader) {
    mShader = glCreateProgram();
    if(!mShader) {
	std::cout << "Error creating shader program" << std::endl;
	return;
    }

    addShaders(vShader, GL_VERTEX_SHADER);
    addShaders(fShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glLinkProgram(mShader);
    glGetProgramiv(mShader, GL_LINK_STATUS, &result);
    if(!result) {
	glGetProgramInfoLog(mShader, sizeof(eLog), NULL, eLog);
	std::cout << "Error linking shader: " << eLog << std::endl;
	return;
    }

    glValidateProgram(mShader);
    glGetProgramiv(mShader, GL_VALIDATE_STATUS, &result);
    if(!result) {
	glGetProgramInfoLog(mShader, sizeof(eLog), NULL, eLog);
	std::cout << "Error validating shader: " << eLog << std::endl;
	return;
    }

    mUniformModel = glGetUniformLocation(mShader, "model");
    mUniformProjection = glGetUniformLocation(mShader, "projection");
}

void shader::addShaders(
		const char* shaderCode, 
		GLenum shaderType) {
    GLuint theshader = glCreateShader(shaderType);
    const GLchar *thecode[1];
    thecode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(theshader, 1, thecode, codeLength);
    glCompileShader(theshader);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glGetShaderiv(theshader, GL_COMPILE_STATUS, &result);
    if(!result) {
	glGetShaderInfoLog(theshader, sizeof(eLog), NULL, eLog);
	std::cout << "Error compiling shader: " << eLog << std::endl;
	return;
    }

    glAttachShader(mShader, theshader);
}

GLuint shader::getUniformModel(void) {
    return mUniformModel;
}

GLuint shader::getUniformProjection(void) {
    return mUniformProjection;
}

void shader::useShader(void) {
    glUseProgram(mShader);
}

void shader::clearShader(void) {
    if(mShader) {
        glDeleteProgram(mShader);
    }
    mShader = 0;
    mUniformProjection = 0;
    mUniformModel = 0;
}

shader::~shader() {
    clearShader();
}

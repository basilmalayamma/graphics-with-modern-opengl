#ifndef _MESH_H_
#define _MESH_H_

#include <GL/glew.h>

class mesh {
public:
    //mesh();
    void renderMesh();
    void createMesh(
		    unsigned int *indices,
		    GLfloat *vertices,
		    unsigned int numofIndices,
		    unsigned int numofVertices);
    void clearMesh(void);
    ~mesh();
private:
    GLsizei mIndexCount = 0;
    GLuint mVAO, mVBO, mIBO;
};

#endif //_MESH_H_

#include <iostream>
#include <mesh.hpp>

void mesh::createMesh(
		unsigned int *indices,
		GLfloat* vertices,
		unsigned int numofIndices,
		unsigned int numofVertices) {

    mIndexCount = numofIndices;

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1, &mIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		    sizeof(indices[0]) * numofIndices,
		    indices, GL_STATIC_DRAW);

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numofVertices,
		    vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    //Unbinding order is important
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void mesh::renderMesh() {
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);

    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0);

    //Unbind
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void mesh::clearMesh() {
    if (mIBO) {
	glDeleteBuffers(1, &mIBO);
    }
    if (mVBO) {
	glDeleteBuffers(1, &mVBO);
    }
    if (mVAO) {
	glDeleteBuffers(1, &mVAO);
    }
    mIndexCount = 0;
}

mesh::~mesh() {
    clearMesh();
}

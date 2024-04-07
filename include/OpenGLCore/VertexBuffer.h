#ifndef _VERTEXBUFFER_H_
#define _VERTEXBUFFER_H_

#include <iostream>
#include <vector>
#include "Renderer.h"
#include "VertexBufferLayout.h"

class VertexBuffer
{
private:
    unsigned int m_RendererID;
public:
    VertexBuffer(const GLfloat* data, unsigned int size);
    ~VertexBuffer();

    void UpdateData(const GLfloat* data, unsigned int offset, unsigned int size);
    void Bind() const;
    void Unbind() const;
};

#endif _VERTEXBUFFER_H_
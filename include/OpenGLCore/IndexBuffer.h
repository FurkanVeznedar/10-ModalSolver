#ifndef _INDEXBUFFER_H_
#define _INDEXBUFFER_H_

#include <vector>
#include "Renderer.h"

class IndexBuffer
{
private:
    unsigned int m_RendererID;
    unsigned int m_Count;
public:
    IndexBuffer(const GLuint* data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const {return m_Count;}
};

#endif _INDEXBUFFER_H_
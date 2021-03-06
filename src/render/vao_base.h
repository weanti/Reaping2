#ifndef INCLUDED_RENDER_VAO_BASE_H
#define INCLUDED_RENDER_VAO_BASE_H
#include "platform/i_platform.h"

class VaoBase
{
    GLuint mDataBuffer;
    GLuint mVAO;
    GLuint mSampler;
public:
    VaoBase();
    ~VaoBase();
    void Init();
    void Bind()const;
    void Unbind()const;
};

#endif//INCLUDED_RENDER_VAO_BASE_H

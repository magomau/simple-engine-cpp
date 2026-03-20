#pragma once

#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_opengl_glext.h>

namespace simple_engine::gl {

extern PFNGLCREATESHADERPROC CreateShader;
extern PFNGLSHADERSOURCEPROC ShaderSource;
extern PFNGLCOMPILESHADERPROC CompileShader;
extern PFNGLGETSHADERIVPROC GetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC GetShaderInfoLog;
extern PFNGLDELETESHADERPROC DeleteShader;
extern PFNGLCREATEPROGRAMPROC CreateProgram;
extern PFNGLATTACHSHADERPROC AttachShader;
extern PFNGLLINKPROGRAMPROC LinkProgram;
extern PFNGLGETPROGRAMIVPROC GetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC GetProgramInfoLog;
extern PFNGLUSEPROGRAMPROC UseProgram;
extern PFNGLDELETEPROGRAMPROC DeleteProgram;
extern PFNGLGETUNIFORMLOCATIONPROC GetUniformLocation;
extern PFNGLUNIFORMMATRIX4FVPROC UniformMatrix4fv;
extern PFNGLUNIFORM1IPROC Uniform1i;
extern PFNGLUNIFORM4FVPROC Uniform4fv;
extern PFNGLACTIVETEXTUREPROC ActiveTexture;
extern PFNGLGENVERTEXARRAYSPROC GenVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC BindVertexArray;
extern PFNGLDELETEVERTEXARRAYSPROC DeleteVertexArrays;
extern PFNGLGENBUFFERSPROC GenBuffers;
extern PFNGLBINDBUFFERPROC BindBuffer;
extern PFNGLBUFFERDATAPROC BufferData;
extern PFNGLDELETEBUFFERSPROC DeleteBuffers;
extern PFNGLVERTEXATTRIBPOINTERPROC VertexAttribPointer;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC EnableVertexAttribArray;

bool loadOpenGLFunctions();

} // namespace simple_engine::gl

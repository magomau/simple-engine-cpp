#include "GLFunctions.h"

#include <SDL3/SDL.h>

#include "core/Logger.h"

namespace simple_engine::gl {

PFNGLCREATESHADERPROC CreateShader = nullptr;
PFNGLSHADERSOURCEPROC ShaderSource = nullptr;
PFNGLCOMPILESHADERPROC CompileShader = nullptr;
PFNGLGETSHADERIVPROC GetShaderiv = nullptr;
PFNGLGETSHADERINFOLOGPROC GetShaderInfoLog = nullptr;
PFNGLDELETESHADERPROC DeleteShader = nullptr;
PFNGLCREATEPROGRAMPROC CreateProgram = nullptr;
PFNGLATTACHSHADERPROC AttachShader = nullptr;
PFNGLLINKPROGRAMPROC LinkProgram = nullptr;
PFNGLGETPROGRAMIVPROC GetProgramiv = nullptr;
PFNGLGETPROGRAMINFOLOGPROC GetProgramInfoLog = nullptr;
PFNGLUSEPROGRAMPROC UseProgram = nullptr;
PFNGLDELETEPROGRAMPROC DeleteProgram = nullptr;
PFNGLGETUNIFORMLOCATIONPROC GetUniformLocation = nullptr;
PFNGLUNIFORMMATRIX4FVPROC UniformMatrix4fv = nullptr;
PFNGLUNIFORM1IPROC Uniform1i = nullptr;
PFNGLUNIFORM2FVPROC Uniform2fv = nullptr;
PFNGLUNIFORM4FVPROC Uniform4fv = nullptr;
PFNGLACTIVETEXTUREPROC ActiveTexture = nullptr;
PFNGLGENVERTEXARRAYSPROC GenVertexArrays = nullptr;
PFNGLBINDVERTEXARRAYPROC BindVertexArray = nullptr;
PFNGLDELETEVERTEXARRAYSPROC DeleteVertexArrays = nullptr;
PFNGLGENBUFFERSPROC GenBuffers = nullptr;
PFNGLBINDBUFFERPROC BindBuffer = nullptr;
PFNGLBUFFERDATAPROC BufferData = nullptr;
PFNGLDELETEBUFFERSPROC DeleteBuffers = nullptr;
PFNGLVERTEXATTRIBPOINTERPROC VertexAttribPointer = nullptr;
PFNGLENABLEVERTEXATTRIBARRAYPROC EnableVertexAttribArray = nullptr;

namespace {

template <typename T>
bool loadFunction(T& functionPointer, const char* functionName) {
    functionPointer = reinterpret_cast<T>(SDL_GL_GetProcAddress(functionName));
    if (!functionPointer) {
        Logger::error(functionName);
        return false;
    }
    return true;
}

} // namespace

bool loadOpenGLFunctions() {
    bool success = true;

    success = loadFunction(CreateShader, "glCreateShader") && success;
    success = loadFunction(ShaderSource, "glShaderSource") && success;
    success = loadFunction(CompileShader, "glCompileShader") && success;
    success = loadFunction(GetShaderiv, "glGetShaderiv") && success;
    success = loadFunction(GetShaderInfoLog, "glGetShaderInfoLog") && success;
    success = loadFunction(DeleteShader, "glDeleteShader") && success;
    success = loadFunction(CreateProgram, "glCreateProgram") && success;
    success = loadFunction(AttachShader, "glAttachShader") && success;
    success = loadFunction(LinkProgram, "glLinkProgram") && success;
    success = loadFunction(GetProgramiv, "glGetProgramiv") && success;
    success = loadFunction(GetProgramInfoLog, "glGetProgramInfoLog") && success;
    success = loadFunction(UseProgram, "glUseProgram") && success;
    success = loadFunction(DeleteProgram, "glDeleteProgram") && success;
    success = loadFunction(GetUniformLocation, "glGetUniformLocation") && success;
    success = loadFunction(UniformMatrix4fv, "glUniformMatrix4fv") && success;
    success = loadFunction(Uniform1i, "glUniform1i") && success;
    success = loadFunction(Uniform2fv, "glUniform2fv") && success;
    success = loadFunction(Uniform4fv, "glUniform4fv") && success;
    success = loadFunction(ActiveTexture, "glActiveTexture") && success;
    success = loadFunction(GenVertexArrays, "glGenVertexArrays") && success;
    success = loadFunction(BindVertexArray, "glBindVertexArray") && success;
    success = loadFunction(DeleteVertexArrays, "glDeleteVertexArrays") && success;
    success = loadFunction(GenBuffers, "glGenBuffers") && success;
    success = loadFunction(BindBuffer, "glBindBuffer") && success;
    success = loadFunction(BufferData, "glBufferData") && success;
    success = loadFunction(DeleteBuffers, "glDeleteBuffers") && success;
    success = loadFunction(VertexAttribPointer, "glVertexAttribPointer") && success;
    success = loadFunction(EnableVertexAttribArray, "glEnableVertexAttribArray") && success;

    if (!success) {
        Logger::error("Failed to load one or more required OpenGL functions.");
        return false;
    }

    Logger::info("OpenGL functions loaded successfully.");
    return true;
}

} // namespace simple_engine::gl

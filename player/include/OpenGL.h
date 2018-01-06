//
// Created by rogan on 6/01/2018.
//

#ifndef VIDEOPLAYER_OPENGL_H
#define VIDEOPLAYER_OPENGL_H

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif
#ifndef WX_PRECOMP

#include "wx/wx.h"

#endif

#include <glad/glad.h>

#include <wx/glcanvas.h>

#define glCheckError2(file, line) \
            ({\
                GLenum error = glGetError();\
                switch (error) {\
                    case GL_NO_ERROR:\
                        break;\
                    case GL_INVALID_ENUM:\
                        wxLogError("OpenGL Error (%s:%d): Invalid Enum", file, line);\
                        break;\
                    case GL_INVALID_VALUE:\
                        wxLogError("OpenGL Error (%s:%d): Invalid Value", file, line);\
                        break;\
                    case GL_INVALID_OPERATION:\
                        wxLogError("OpenGL Error (%s:%d): Invalid Operation", file, line);\
                        break;\
                    case GL_INVALID_FRAMEBUFFER_OPERATION:\
                        wxLogError("OpenGL Error (%s:%d): Invalid Framebuffer Operation", file, line);\
                        break;\
                    case GL_OUT_OF_MEMORY:\
                        wxLogError("OpenGL Error (%s:%d): Out of memory", file, line);\
                        break;\
                    default:\
                        wxLogError("OpenGL Error (%s:%d): Unknown error %d", file, line, error);\
                        break;\
                }\
            })

#define glCheckError() glCheckError2(__FILE__, __LINE__)

typedef struct GLLoaderStats {
    wxGLContext *context;
    bool loaded;
} GLLoaderStats;

static GLLoaderStats glLoader2(wxGLCanvas *owner, const char *file, int line) {
    static bool glLoaded;
    static wxGLContext *openGLContext;
    if (glLoaded) {
        if (!openGLContext->SetCurrent(*owner)) {
            wxLogWarning("OpenGL Context could not be made current: %s:%d", file, line);
            delete openGLContext;
            glLoaded = false;
            return GLLoaderStats{nullptr, glLoaded};
        }
        return GLLoaderStats{openGLContext, glLoaded};
    } else {
        wxGLContextAttrs attrs;
        attrs.PlatformDefaults().CoreProfile().OGLVersion(4, 5).Robust().ResetIsolation().EndList();
        openGLContext = new wxGLContext(owner, nullptr, &attrs);
        openGLContext->SetCurrent(*owner);
        glLoaded = true;
        if (gladLoadGL() == GL_FALSE) {
            wxLogFatalError("Failed to load OpenGL: %s:%d", file, line);
        }
        wxLogInfo("Loaded OpenGL Version %d.%d", GLVersion.major, GLVersion.minor);
        wxLogInfo("OpenGL Information: ");
        wxLogInfo("    OpenGL Vendor: %s", wxString(glGetString(GL_VENDOR)));
        wxLogInfo("    OpenGL Renderer: %s", wxString(glGetString(GL_RENDERER)));
        wxLogInfo("    OpenGL Version: %s", wxString(glGetString(GL_VERSION)));
        wxLogInfo("    OpenGL Shading Language Version: %s", wxString(glGetString(GL_SHADING_LANGUAGE_VERSION)));
        GLint extensionsCount;
        glGetIntegerv(GL_NUM_EXTENSIONS, &extensionsCount);
        wxLogInfo("    OpenGL Extensions (%d):", extensionsCount);
        for (GLint i = 0; i < extensionsCount; i++) {
            wxLogInfo("        %s", wxString(glGetStringi(GL_EXTENSIONS, static_cast<GLuint>(i))));
        }
        return GLLoaderStats{openGLContext, false};
    }
}

#define glLoader(owner) glLoader2(owner, __FILE__, __LINE__);

static __forceinline wxGLAttributes glGetCanvasAttributes2(const char *file, int line) {
    wxGLAttributes attributes;
    attributes.PlatformDefaults().RGBA().DoubleBuffer().EndList();
    return attributes;
}

#define glGetCanvasAttributes() glGetCanvasAttributes2(__FILE__, __LINE__)

#endif //VIDEOPLAYER_OPENGL_H

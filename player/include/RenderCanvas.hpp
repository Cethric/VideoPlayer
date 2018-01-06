//
// Created by rogan on 6/01/2018.
//

#ifndef VIDEOPLAYER_RENDERCANVAS_HPP
#define VIDEOPLAYER_RENDERCANVAS_HPP

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif
#ifndef WX_PRECOMP

#include "wx/wx.h"

#endif

#include <OpenGL.h>
#include "VideoDecoder.hpp"

namespace VP {
    class RenderCanvas : public wxGLCanvas {
    private:

        GLuint videoTexture;

        GLuint shaderProgram;
        GLuint vertexArrayObject;

        GLint textureLocation;
        GLint paramaterPositionLocation;
        GLint paramaterOffsetLocation;
        GLint paramaterSizeLocation;
        GLint paramaterRotationLocation;
        GLint paramaterLayerLocation;
        GLint colourLocation;
        GLint MVPLocation;

    public:
        explicit RenderCanvas(wxWindow *parent);

        void RenderView(VideoDecoder *decoder);

    };
}


#endif //VIDEOPLAYER_RENDERCANVAS_HPP

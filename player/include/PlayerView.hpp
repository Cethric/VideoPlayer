//
// Created by rogan on 6/01/2018.
//

#ifndef VIDEOPLAYER_PLAYERVIEW_HPP
#define VIDEOPLAYER_PLAYERVIEW_HPP

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif
#ifndef WX_PRECOMP

#include "wx/wx.h"

#endif

#include <OpenGL.h>

#include <RenderCanvas.hpp>
#include <VideoDecoder.hpp>

namespace VP {
    class PlayerView : public wxFrame {
    private:
        VideoDecoder *decoder = nullptr;
        wxMenuItem *playPauseItem = nullptr;
        wxTimer *renderTimer = nullptr;

        RenderCanvas *renderCanvas;
    public:
        PlayerView();

        void OnClose(wxCloseEvent &event);

        void OnOpenVideo(wxCommandEvent &event);

        void OnPlayVideo(wxCommandEvent &event);

        void OnStopVideo(wxCommandEvent &event);

        void OnAbout(wxCommandEvent &event);

        void OnRenderView(wxTimerEvent &event);
    };
}


#endif //VIDEOPLAYER_PLAYERVIEW_HPP

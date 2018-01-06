//
// Created by rogan on 6/01/2018.
//

#ifndef VIDEOPLAYER_APPLICATION_HPP
#define VIDEOPLAYER_APPLICATION_HPP

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif
#ifndef WX_PRECOMP

#include "wx/wx.h"

#endif

#include <PlayerView.hpp>

namespace VP {
    class Application : public wxApp {
    private:
        PlayerView *player = nullptr;
    public:
        bool OnInit() wxOVERRIDE;
    };
}

wxDECLARE_APP(VP::Application);


#endif //VIDEOPLAYER_APPLICATION_HPP

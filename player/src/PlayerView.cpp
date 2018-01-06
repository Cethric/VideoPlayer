//
// Created by rogan on 6/01/2018.
//

#include <wx/filehistory.h>
#include <wx/aboutdlg.h>
#include "PlayerView.hpp"

extern "C" {

}

VP::PlayerView::PlayerView() : wxFrame(nullptr, wxID_ANY, "Player View", wxDefaultPosition, wxDefaultSize) {

    auto mainMenuBar = new wxMenuBar(wxMB_DOCKABLE);
    auto fileMenu = new wxMenu((long) 0);
    fileMenu->Append(wxID_OPEN, "&Open\tCTRL+O", "Open a video file", wxITEM_NORMAL);
    mainMenuBar->Append(fileMenu, "&File");

    auto playbackMenu = new wxMenu((long) 0);
    playPauseItem = playbackMenu->Append(wxID_PREVIEW, "&Play\tCTRL+P", "Play loaded video", wxITEM_CHECK);
    playbackMenu->Append(wxID_STOP, "&Stop\tCTRL+S", "Stop loaded video", wxITEM_NORMAL);
    mainMenuBar->Append(playbackMenu, "&Playback");

    auto helpMenu = new wxMenu((long) 0);
    helpMenu->Append(wxID_ABOUT, "&About\tCTRL+A", "Show about", wxITEM_NORMAL);
    mainMenuBar->Append(helpMenu, "&Help");

    SetMenuBar(mainMenuBar);

    renderTimer = new wxTimer(this, wxID_ANY);

    renderTimer->Start(40); // 25 frames per second (1000 / 25 = 40)

    renderCanvas = new RenderCanvas(this);


    wxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(renderCanvas, 10, wxEXPAND | wxALL);
    SetSizerAndFit(sizer);

    Bind(wxEVT_CLOSE_WINDOW, &VP::PlayerView::OnClose, this, this->GetId());
    Bind(wxEVT_MENU, &VP::PlayerView::OnOpenVideo, this, wxID_OPEN);
    Bind(wxEVT_MENU, &VP::PlayerView::OnPlayVideo, this, wxID_PREVIEW);
    Bind(wxEVT_MENU, &VP::PlayerView::OnStopVideo, this, wxID_STOP);
    Bind(wxEVT_MENU, &VP::PlayerView::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_TIMER, &VP::PlayerView::OnRenderView, this, renderTimer->GetId());
}

void VP::PlayerView::OnClose(wxCloseEvent &event) {
    this->renderTimer->Stop();
    delete this->renderTimer;
    delete this->decoder;
}

void VP::PlayerView::OnOpenVideo(wxCommandEvent &event) {
    wxString result = wxLoadFileSelector("Open Video", "mp4", "", this);
    if (!result.IsEmpty()) {
        wxLogInfo("Opening Movie: '%s'", result);
        delete decoder;
        decoder = new VP::VideoDecoder(result);
        playPauseItem->Check(true);
        OnPlayVideo(event);
    }
}

void VP::PlayerView::OnPlayVideo(wxCommandEvent &event) {
    if (decoder->IsFinished()) {
        playPauseItem->SetItemLabel("&Play\tCTRL+P");
        playPauseItem->SetHelp("Play loaded video");
        playPauseItem->Check(false);

    } else {
        if (playPauseItem->IsChecked()) {
            playPauseItem->SetItemLabel("&Pause\tCTRL+P");
            playPauseItem->SetHelp("Pause loaded video");
            decoder->Play();
        } else {
            playPauseItem->SetItemLabel("&Play\tCTRL+P");
            playPauseItem->SetHelp("Play loaded video");
            decoder->Pause();
        }
    }
}

void VP::PlayerView::OnStopVideo(wxCommandEvent &event) {
    playPauseItem->SetItemLabel("&Play\tCTRL+P");
    playPauseItem->SetHelp("Play loaded video");
    playPauseItem->Check(false);
    decoder->Stop();
}

void VP::PlayerView::OnAbout(wxCommandEvent &event) {
    wxAboutDialogInfo aboutDialogInfo;
    aboutDialogInfo.AddDeveloper("Blake Rogan");
    aboutDialogInfo.SetName("Video Palyer");
    aboutDialogInfo.SetDescription("A very basic video player using FFmpeg, OpenGL and wxWidgets");
    aboutDialogInfo.SetLicence(wxString::Format(
            "%s\n"
                    "FFmpeg %s\n"
                    "AVCodec %s %s\n"
                    "AVDevice %s %s\n"
                    "AVFilter %s %s\n"
                    "AVFormat %s %s\n"
                    "AVUtil %s %s\n"
                    "SWResample %s %s\n"
                    "SWScale %s %s\n",
            wxVERSION_STRING,
            av_version_info(),
            AV_STRINGIFY(LIBAVCODEC_VERSION),
            avcodec_license(),
            AV_STRINGIFY(LIBAVDEVICE_VERSION),
            avdevice_license(),
            AV_STRINGIFY(LIBAVFILTER_VERSION),
            avfilter_license(),
            AV_STRINGIFY(LIBAVFORMAT_VERSION),
            avformat_license(),
            AV_STRINGIFY(LIBAVUTIL_VERSION),
            avutil_license(),
            AV_STRINGIFY(LIBSWRESAMPLE_VERSION),
            swresample_license(),
            AV_STRINGIFY(LIBSWSCALE_VERSION),
            swscale_license()
    ));
    aboutDialogInfo.SetVersion("0.0.0", "0.0.0");
    wxAboutBox(aboutDialogInfo, this);
}

void VP::PlayerView::OnRenderView(wxTimerEvent &event) {
    renderCanvas->RenderView(decoder);
}

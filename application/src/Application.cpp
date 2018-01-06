//
// Created by rogan on 6/01/2018.
//

#include "Application.hpp"

bool VP::Application::OnInit() {
    wxLog::SetActiveTarget(new wxLogStream(&std::cout));
    if (wxApp::OnInit()) {
        player = new PlayerView();
        player->Show(true);
        return true;
    }
    return false;
}

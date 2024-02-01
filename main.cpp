#include <iostream>

#include <wx/wx.h>



/*  ==========  Main window class  ========= */
class MainWindow : public wxFrame
{
public:
    MainWindow();
 
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

public:
    enum
    {
        ID_Hello = 1
    };
};

MainWindow::MainWindow()
    : wxFrame(nullptr, wxID_ANY, "Hello World")
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
 
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
 
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
 
    SetMenuBar( menuBar );
 
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
 
    Bind(wxEVT_MENU, &MainWindow::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MainWindow::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainWindow::OnExit, this, wxID_EXIT);
}
 
void MainWindow::OnExit(wxCommandEvent& event)
{
    Close(true);
}
 
void MainWindow::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}
 
void MainWindow::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}



/*  ==========  Application class  ========= */
class Application : public wxApp
{
public:
    bool OnInit() override;
};

bool Application::OnInit()
{
    MainWindow *frame = new MainWindow();
    frame->Show();
    return true;
}

// This defines the equivalent of main() for the current platform.
wxIMPLEMENT_APP(Application);
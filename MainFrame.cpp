#include "MainFrame.h"
#include "Task.h"
#include <wx/wx.h>
#include <vector>
#include <string>

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
    CreateControls();
    BindEventHandlers();
    AddSavedTasks();
}

//create all controls and panels for the frame and allow them to resize when the window is resized
void MainFrame::CreateControls()
{
    wxFont headlineFont(wxFontInfo(wxSize(0, 36)).Bold());
    wxFont mainFont(wxFontInfo(wxSize(0, 18)));

    panel = new wxPanel(this);
    panel->SetFont(mainFont);

    headlineText = new wxStaticText(panel, wxID_ANY, "To-Do List");
    headlineText->SetFont(headlineFont);

    inputField = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(495, 35), wxTE_PROCESS_ENTER);
    addButton = new wxButton(panel, wxID_ANY, "add task");
    checkListBox = new wxCheckListBox(panel, wxID_ANY);
    clearButton = new wxButton(panel, wxID_ANY, "clear tasks");

    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);
    inputSizer->Add(inputField, 1, wxEXPAND | wxALL, 10);
    inputSizer->Add(addButton, 0, wxALIGN_CENTER_VERTICAL | wxALL, 10);

    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
    panelSizer->Add(headlineText, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 20);
    panelSizer->Add(inputSizer, 0, wxEXPAND | wxALL, 10);
    panelSizer->Add(checkListBox, 1, wxEXPAND | wxALL, 10);
    panelSizer->Add(clearButton, 0, wxALIGN_LEFT | wxLEFT | wxBOTTOM, 10);

    panel->SetSizerAndFit(panelSizer);
    SetSize(800, 600); 
}


void MainFrame::BindEventHandlers()
{
    addButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddButtonClicked, this);
    inputField->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnInputEnter, this);
    checkListBox->Bind(wxEVT_KEY_DOWN, &MainFrame::OnListKeyDown, this);
    clearButton->Bind(wxEVT_BUTTON, &MainFrame::OnClearButtonClicked, this);
    this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnWindowClosed, this);

}

void MainFrame::OnAddButtonClicked(wxCommandEvent& evt)
{
    AddTaskFromInput();
}

void MainFrame::AddTaskFromInput()
{
    wxString description = inputField->GetValue();

    if (!description.IsEmpty()) {
        checkListBox->Insert(description, 0);
        inputField->Clear();
    };

    inputField->SetFocus();
}

void MainFrame::OnInputEnter(wxCommandEvent& evt)
{
    AddTaskFromInput();
}

void MainFrame::OnListKeyDown(wxKeyEvent &evt)
{
    switch(evt.GetKeyCode()) {
        case WXK_DELETE:
            DeleteSelectedTask();
            break;
        case WXK_UP:
            MoveSelectedTask(-1);
            break;
        case WXK_DOWN:
            MoveSelectedTask(1);
            break;
    }
}

void MainFrame::DeleteSelectedTask()
{
    int selectedIndex = checkListBox->GetSelection();

    if(selectedIndex == wxNOT_FOUND) {
        return;
    }

    checkListBox->Delete(selectedIndex);
}

void MainFrame::MoveSelectedTask(int offset)
{
    int selectedIndex = checkListBox->GetSelection();

    if (selectedIndex == wxNOT_FOUND){
        return;
    }

    int newIndex = selectedIndex + offset;

    if (newIndex >= 0 && newIndex < checkListBox->GetCount()) {
        SwapTasks(selectedIndex, newIndex);
        checkListBox->SetSelection(newIndex, true);
    }
}

void MainFrame::SwapTasks(int i, int j)
{
    Task taskI{ checkListBox->GetString(i).ToStdString(), checkListBox->IsChecked(i) };
    Task taskJ{ checkListBox->GetString(j).ToStdString(), checkListBox->IsChecked(j) };

    checkListBox->SetString(i, taskJ.description);
    checkListBox->Check(i, taskJ.completed);

    checkListBox->SetString(j, taskI.description);
    checkListBox->Check(j, taskI.completed);
}

void MainFrame::OnClearButtonClicked(wxCommandEvent &evt)
{
    if (checkListBox->IsEmpty()){
        return;
    }

    wxMessageDialog dialog(this, "Are you sure you want to clear all tasks?", "Clear", wxYES_NO | wxCANCEL);
    int result = dialog.ShowModal();

    if(result == wxID_YES){
        checkListBox->Clear();
    }
}

void MainFrame::OnWindowClosed(wxCloseEvent &evt)
{
    std::vector<Task> tasks;

    for (int i=0; i < checkListBox->GetCount(); i++){
        Task task;
        task.description = checkListBox->GetString(i);
        task.completed = checkListBox->IsChecked(i);
        tasks.push_back(task);
    }

    SaveToFile(tasks, "tasks.txt");
    evt.Skip();

}

void MainFrame::AddSavedTasks()
{
    std::vector<Task> tasks = LoadFromFile("tasks.txt");

    for (const Task& task : tasks) {
        int index = checkListBox->GetCount();
        checkListBox->Insert(task.description, index);
        checkListBox->Check(index, task.completed);
    }
}

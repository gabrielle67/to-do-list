#include <wx/wx.h>

class MainFrame : public wxFrame
{
    public:
        MainFrame(const wxString& title);
        
    private:
        //add and manage tasks
        void CreateControls();
        void BindEventHandlers();
        void OnAddButtonClicked(wxCommandEvent& evt);
        void AddTaskFromInput();
        void OnInputEnter(wxCommandEvent& evt);
        void OnListKeyDown(wxKeyEvent& evt);

        //move and delete tasks
        void DeleteSelectedTask();
        void MoveSelectedTask(int offset);
        void SwapTasks(int i, int j);
        void OnClearButtonClicked(wxCommandEvent& evt);

        //keep tasks even after program closes
        void OnWindowClosed(wxCloseEvent& evt);
        void AddSavedTasks();

        wxPanel* panel;
        wxStaticText* headlineText;
        wxTextCtrl* inputField;
        wxButton* addButton;
        wxCheckListBox* checkListBox;
        wxButton* clearButton;
};
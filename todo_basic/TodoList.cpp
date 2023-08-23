#include <iostream>
#include <vector>
#include <string>
using namespace std;

//create Task object to track tasks
struct Task {
    string description;
    bool completed;
};

int main(){
    //create Vector to hold task objects
    vector<Task> taskList;

    while (true) {
        //provide user options
        cout << "To Do List" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. View Tasks" << endl;
        cout << "3. Mark Completed" << endl;
        cout << "4. Exit" << endl;
        cout << "\nEnter the number of an option: ";

        int option;
        cin >> option;

        cin.ignore();

        switch (option){
            case 1:
            {
                Task newTask;
                cout << "Enter task description: ";
                getline(cin, newTask.description);
                newTask.completed = false;
                taskList.push_back(newTask);
            }
            break;

            case 2: 
                cout << "To-Do List:\n";
                for (size_t i = 0; i < taskList.size(); i++){
                    cout << (taskList[i].completed ? "[X] " : "[ ] ") << taskList[i].description<<endl;
                }
                cout << endl << endl;
                break;

            case 3: 
                cout << "Enter task number to mark off: ";
                size_t taskNum;
                cin >> taskNum;

                cin.ignore();

                if (taskNum >= 1 && taskNum <= taskList.size()){
                    taskList[taskNum-1].completed = true;
                } else {
                    cout << "Invalid task number" << endl;
                }
                break;

            case 4: 
                return 0;

            default: 
                cout << "Invalid option, please enter valid option" << endl;
                cin.clear();
                cin.ignore();
                break;

        }
    }
    
    return 0;
}
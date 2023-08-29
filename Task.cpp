#include "Task.h"
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>

void SaveToFile(const std::vector<Task> &tasks, const std::string &fileName)
{
    std::ofstream outFile(fileName);
    outFile << tasks.size();

    for (const Task& task : tasks) {
        std::string description = task.description;
        std::replace(description.begin(), description.end(), ' ', '_');

        outFile << '\n' << description << ' ' << task.completed;
    }
};

std::vector<Task> LoadFromFile(const std::string &fileName)
{
    if (!std::filesystem::exists(fileName)){
        return std::vector<Task>();
    }

    std::vector<Task> tasks;
    std::ifstream inFile(fileName);

    int n;
    inFile >> n;

    for (int i = 0; i < n; i++){
        std::string description;
        bool completed;

        inFile >> description >> completed;
        std::replace(description.begin(), description.end(), '_', ' ');
        tasks.push_back(Task{ description, completed});
    }

    return tasks;
};

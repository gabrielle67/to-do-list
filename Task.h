#include <string>
#include <vector>

struct Task
{
    std::string description;
    bool completed;
};

void SaveToFile(const std::vector<Task>& tasks, const std::string& fileName);
std::vector<Task> LoadFromFile(const std::string& fileName);
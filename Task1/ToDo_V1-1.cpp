#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Define a Task structure
struct Task {
    string description;
    string dueDate;
    bool completed;

    Task(string desc, string due, bool comp = false) {
        description = desc;
        dueDate = due;
        completed = comp;
    }
};

// Function declarations
void addTask(vector<Task>& tasks);
void markTaskCompleted(vector<Task>& tasks);
void viewTasks(const vector<Task>& tasks);
void loadTasksFromFile(vector<Task>& tasks, const string& filename);
void saveTasksToFile(const vector<Task>& tasks, const string& filename);
void showMenu();

int main() {
    vector<Task> tasks;
    const string filename = "tasks.txt";

    // Load tasks on startup
    loadTasksFromFile(tasks, filename);

    int choice;
    do {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                markTaskCompleted(tasks);
                break;
            case 3:
                viewTasks(tasks);
                break;
            case 4:
                saveTasksToFile(tasks, filename);
                cout << "Tasks saved. Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
        cout << endl;

    } while (choice != 4);

    return 0;
}

void showMenu() {
    cout << "====== TO-DO LIST MENU ======\n";
    cout << "1. Add Task\n";
    cout << "2. Mark Task as Completed\n";
    cout << "3. View Tasks\n";
    cout << "4. Save and Exit\n";
}

// Add a new task
void addTask(vector<Task>& tasks) {
    string desc, due;
    cout << "Enter task description: ";
    getline(cin, desc);
    cout << "Enter due date (e.g., 2025-05-24): ";
    getline(cin, due);
    tasks.push_back(Task(desc, due));
    cout << "Task added.\n";
}

// Mark a task as completed
void markTaskCompleted(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks available.\n";
        return;
    }

    viewTasks(tasks);
    int index;
    cout << "Enter the task number to mark as completed: ";
    cin >> index;
    cin.ignore();

    if (index > 0 && index <= tasks.size()) {
        tasks[index - 1].completed = true;
        cout << "Task marked as completed.\n";
    } else {
        cout << "Invalid task number.\n";
    }
}

// View all tasks
void viewTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks to display.\n";
        return;
    }

    cout << "------ TASK LIST ------\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << i + 1 << ". [" << (tasks[i].completed ? "X" : " ") << "] "
             << tasks[i].description << " (Due: " << tasks[i].dueDate << ")\n";
    }
}

// Load tasks from file
void loadTasksFromFile(vector<Task>& tasks, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return; // No file to load
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string desc, due, status;
        getline(iss, desc, '|');
        getline(iss, due, '|');
        getline(iss, status);
        bool completed = (status == "1");
        tasks.push_back(Task(desc, due, completed));
    }
    file.close();
}

// Save tasks to file
void saveTasksToFile(const vector<Task>& tasks, const string& filename) {
    ofstream file(filename);
    for (const auto& task : tasks) {
        file << task.description << "|" << task.dueDate << "|" << (task.completed ? "1" : "0") << "\n";
    }
    file.close();
}

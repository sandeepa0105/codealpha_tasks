#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <ctime>

using namespace std;

struct Task {
    string description;
    string dueDate; // format: YYYY-MM-DD
    bool completed;

    Task(string desc, string due, bool comp = false)
        : description(desc), dueDate(due), completed(comp) {}
};

// Function declarations
void addTask(vector<Task>& tasks);
void markTaskCompleted(vector<Task>& tasks);
void deleteTask(vector<Task>& tasks);
void viewTasks(const vector<Task>& tasks);
void loadTasksFromFile(vector<Task>& tasks, const string& filename);
void saveTasksToFile(const vector<Task>& tasks, const string& filename);
void exportTasksToCSV(const vector<Task>& tasks, const string& filename);
void sortTasksByDueDate(vector<Task>& tasks);
void showMenu();
string getTodayDate();  // ✅ Add this here1

int main() {
    vector<Task> tasks;
    const string dataFile = "tasks.txt";
    const string csvFile = "tasks.csv";

    loadTasksFromFile(tasks, dataFile);

    int choice;
    do {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: addTask(tasks); break;
            case 2: markTaskCompleted(tasks); break;
            case 3: deleteTask(tasks); break;
            case 4: viewTasks(tasks); break;
            case 5: sortTasksByDueDate(tasks); break;
            case 6: exportTasksToCSV(tasks, csvFile); break;
            case 7: 
                saveTasksToFile(tasks, dataFile);
                cout << "Tasks saved. Exiting...\n"; 
                break;
            default: cout << "Invalid choice. Try again.\n";
        }

        cout << endl;
    } while (choice != 7);

    return 0;
}

void showMenu() {
    cout << "====== TO-DO LIST MENU ======\n";
    cout << "1. Add Task\n";
    cout << "2. Mark Task as Completed\n";
    cout << "3. Delete Task\n";
    cout << "4. View Tasks\n";
    cout << "5. Sort Tasks by Due Date\n";
    cout << "6. Export Tasks to CSV\n";
    cout << "7. Save and Exit\n";
}

void addTask(vector<Task>& tasks) {
    string desc, due;
    cout << "Enter task description: ";
    getline(cin, desc);
    cout << "Enter due date (YYYY-MM-DD): ";
    getline(cin, due);
    tasks.emplace_back(desc, due);
    cout << "Task added.\n";
}

void markTaskCompleted(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks available.\n";
        return;
    }

    viewTasks(tasks);
    int index;
    cout << "Enter task number to mark completed: ";
    cin >> index;
    cin.ignore();

    if (index > 0 && index <= tasks.size()) {
        tasks[index - 1].completed = true;
        cout << "Task marked as completed.\n";
    } else {
        cout << "Invalid task number.\n";
    }
}

void deleteTask(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks to delete.\n";
        return;
    }

    viewTasks(tasks);
    int index;
    cout << "Enter task number to delete: ";
    cin >> index;
    cin.ignore();

    if (index > 0 && index <= tasks.size()) {
        tasks.erase(tasks.begin() + index - 1);
        cout << "Task deleted.\n";
    } else {
        cout << "Invalid task number.\n";
    }
}

void viewTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks to display.\n";
        return;
    }

    string today = getTodayDate();

    cout << "------ TASK LIST ------\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        const Task& t = tasks[i];
        bool isOverdue = (t.dueDate < today && !t.completed);

        // Colors
        string color = isOverdue ? "\033[31m" : (t.completed ? "\033[32m" : "\033[0m"); // Red, Green, Default
        string resetColor = "\033[0m";

        cout << color << i + 1 << ". [" << (t.completed ? "X" : " ") << "] "
             << t.description << " (Due: " << t.dueDate << ")";
        if (isOverdue) cout << " 🔴 OVERDUE!";
        cout << resetColor << "\n";
    }
}


void sortTasksByDueDate(vector<Task>& tasks) {
    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.dueDate < b.dueDate;
    });
    cout << "Tasks sorted by due date.\n";
}

void loadTasksFromFile(vector<Task>& tasks, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string desc, due, status;
        getline(iss, desc, '|');
        getline(iss, due, '|');
        getline(iss, status);
        tasks.emplace_back(desc, due, status == "1");
    }

    file.close();
}

void saveTasksToFile(const vector<Task>& tasks, const string& filename) {
    ofstream file(filename);
    for (const auto& task : tasks) {
        file << task.description << "|" << task.dueDate << "|" << (task.completed ? "1" : "0") << "\n";
    }
    file.close();
}

void exportTasksToCSV(const vector<Task>& tasks, const string& filename) {
    ofstream file(filename);
    file << "Task,Due Date,Completed\n";
    for (const auto& task : tasks) {
        file << "\"" << task.description << "\","
             << task.dueDate << ","
             << (task.completed ? "Yes" : "No") << "\n";
    }
    file.close();
    cout << "Tasks exported to " << filename << "\n";
}

string getTodayDate() {
    time_t now = time(nullptr);
    tm* t = localtime(&now);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", t);
    return string(buffer);
}

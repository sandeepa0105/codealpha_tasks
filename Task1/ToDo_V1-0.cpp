#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Define a Task structure
struct Task {
    string description;
    bool completed;

    Task(string desc) {
        description = desc;
        completed = false;
    }
};

// Function declarations
void addTask(vector<Task>& tasks);
void markTaskCompleted(vector<Task>& tasks);
void viewTasks(const vector<Task>& tasks);
void showMenu();

int main() {
    vector<Task> tasks;
    int choice;

    do {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To ignore newline after entering a number

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
                cout << "Exiting application. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
        cout << endl;

    } while (choice != 4);

    return 0;
}

// Function to show the main menu
void showMenu() {
    cout << "====== TO-DO LIST MENU ======\n";
    cout << "1. Add Task\n";
    cout << "2. Mark Task as Completed\n";
    cout << "3. View Tasks\n";
    cout << "4. Exit\n";
}

// Function to add a new task
void addTask(vector<Task>& tasks) {
    string taskDesc;
    cout << "Enter task description: ";
    getline(cin, taskDesc);
    tasks.push_back(Task(taskDesc));
    cout << "Task added successfully.\n";
}

// Function to mark a task as completed
void markTaskCompleted(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks to mark.\n";
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

// Function to view all tasks
void viewTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks found.\n";
        return;
    }

    cout << "------ TASK LIST ------\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << i + 1 << ". [" << (tasks[i].completed ? "X" : " ") << "] " << tasks[i].description << "\n";
    }
}

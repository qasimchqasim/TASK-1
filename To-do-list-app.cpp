#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

class Task
{
private:
    string taskName;
    bool completed;

public:
    Task()
    {
        taskName = "";
        completed = false;
    }

    Task(string name)
    {
        taskName = name;
        completed = false;
    }

    string getTask()
    {
        return taskName;
    }

    bool isCompleted()
    {
        return completed;
    }

    void markCompleted()
    {
        completed = true;
    }

    void setCompleted(bool status)
    {
        completed = status;
    }

    void setTask(string name)
    {
        taskName = name;
    }
};

class TodoList
{
private:
    Task* tasks;
    int count;
    int capacity;

public:
    TodoList(int size = 100)
    {
        capacity = size;
        count = 0;
        tasks = new Task[capacity];
    }

    ~TodoList()
    {
        saveTasks();
        delete[] tasks;
    }

    bool isEmptyTask(string name)
    {
        for (int i = 0; i < name.length(); i++)
        {
            if (name[i] != ' ')
            {
                return false;
            }
        }

        return true;
    }

    void addTask(string name)
    {
        if (isEmptyTask(name))
        {
            cout << "Task cannot be empty!\n";
            return;
        }

        if (count >= capacity)
        {
            cout << "Task list is full!\n";
            return;
        }

        *(tasks + count) = Task(name);
        count++;

        cout << "Task added successfully!\n";
    }

    void viewTasks()
    {
        if (count == 0)
        {
            cout << "\nNo tasks available.\n";
            return;
        }

        cout << "\n========== TASK LIST ==========\n";

        for (int i = 0; i < count; i++)
        {
            cout << i + 1 << ". ";

            if ((*(tasks + i)).isCompleted())
            {
                cout << "[Completed] ";
            }
            else
            {
                cout << "[Pending] ";
            }

            cout << (*(tasks + i)).getTask() << endl;
        }
    }

    void markTaskCompleted(int index)
    {
        if (count == 0)
        {
            cout << "No tasks available!\n";
            return;
        }

        if (index < 1 || index > count)
        {
            cout << "Invalid task number!\n";
            return;
        }

        if ((*(tasks + index - 1)).isCompleted())
        {
            cout << "Task is already completed!\n";
            return;
        }

        (*(tasks + index - 1)).markCompleted();

        cout << "Task marked as completed!\n";
    }

    void deleteTask(int index)
    {
        if (count == 0)
        {
            cout << "No tasks available!\n";
            return;
        }

        if (index < 1 || index > count)
        {
            cout << "Invalid task number!\n";
            return;
        }

        for (int i = index - 1; i < count - 1; i++)
        {
            *(tasks + i) = *(tasks + i + 1);
        }

        count--;

        cout << "Task deleted successfully!\n";
    }

    void saveTasks()
    {
        ofstream fout("tasks.txt");

        if (!fout)
        {
            cout << "Error creating tasks.txt file!\n";
            return;
        }

        for (int i = 0; i < count; i++)
        {
            fout << (*(tasks + i)).getTask()
                 << "|"
                 << (*(tasks + i)).isCompleted()
                 << endl;
        }

        fout.close();
    }

    void loadTasks()
    {
        ifstream fin("tasks.txt");

        if (!fin)
        {
            return;
        }

        string taskName;
        string status;

        while (getline(fin, taskName, '|'))
        {
            getline(fin, status);

            *(tasks + count) = Task(taskName);

            if (status == "1")
            {
                (*(tasks + count)).setCompleted(true);
            }

            count++;
        }

        fin.close();
    }
};

int main()
{
    TodoList todo;

    todo.loadTasks();

    int choice;

    do
    {
        clearScreen();

        cout << "=====================================\n";
        cout << "       TO-DO LIST APPLICATION\n";
        cout << "=====================================\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task Completed\n";
        cout << "4. Delete Task\n";
        cout << "5. Exit\n";
        cout << "Enter Choice: ";

        while (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "Invalid input! Enter a number: ";
        }

        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            string task;

            cout << "\nEnter Task: ";
            getline(cin, task);

            todo.addTask(task);
            break;
        }

        case 2:
        {
            todo.viewTasks();
            break;
        }

        case 3:
        {
            int taskNo;

            todo.viewTasks();

            cout << "\nEnter Task Number: ";

            while (!(cin >> taskNo))
            {
                cin.clear();
                cin.ignore(1000, '\n');

                cout << "Invalid input! Enter a valid task number: ";
            }

            todo.markTaskCompleted(taskNo);
            break;
        }

        case 4:
        {
            int taskNo;

            todo.viewTasks();

            cout << "\nEnter Task Number to Delete: ";

            while (!(cin >> taskNo))
            {
                cin.clear();
                cin.ignore(1000, '\n');

                cout << "Invalid input! Enter a valid task number: ";
            }

            todo.deleteTask(taskNo);
            break;
        }

        case 5:
        {
            todo.saveTasks();

            cout << "\nTasks saved successfully.\n";
            cout << "Exiting program...\n";
            break;
        }

        default:
        {
            cout << "\nInvalid choice! Please select between 1 and 5.\n";
        }
        }

        if (choice != 5)
        {
            cout << "\nPress Enter to continue...";
            cin.ignore(1000, '\n');
            cin.get();
        }

    } while (choice != 5);

    return 0;
}

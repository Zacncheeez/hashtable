#include <iostream>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <vector>

using namespace std;

struct Student {
    char fn[81] = {'\0'};
    char ln[81] = {'\0'};
    int id;
    float gpa;
};

const int TABLE_SIZE = 100;  // You can adjust this

int hashFunction(int id) {
    return id % TABLE_SIZE;
}

void addStudent(vector<vector<Student*>>& table) {
    Student* s = new Student;

    cout << "Please enter first name, last name, ID, and GPA:" << endl;
    cin >> s->fn;
    cin >> s->ln;
    cin >> s->id;
    cin >> s->gpa;

    int index = hashFunction(s->id);
    table[index].push_back(s);

    cout << "Student added to bucket " << index << endl;
}

void printStudents(const vector<vector<Student*>>& table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        for (const Student* s : table[i]) {
            cout << "Name: " << s->fn << " " << s->ln
                 << ", ID: " << s->id
                 << ", GPA: " << s->gpa
                 << " (bucket " << i << ")"
                 << endl;
        }
    }
}

void deleteStudent(vector<vector<Student*>>& table) {
    int id;
    cout << "ID of student you want removed: " << endl;
    cin >> id;

    int index = hashFunction(id);

    for (int i = 0; i < table[index].size(); i++) {
        if (table[index][i]->id == id) {
            cout << "Removed: " << table[index][i]->fn << " "
                 << table[index][i]->ln << endl;

            delete table[index][i];  // free memory
            table[index].erase(table[index].begin() + i);
            return;
        }
    }

    cout << "No student with that ID found." << endl;
}

int main() {
    vector<vector<Student*>> table(TABLE_SIZE);

    int choice = 0;

    while (true) {
        cout << "What would you like to do?: " << endl;
        cout << "1 = Add student" << endl;
        cout << "2 = Print students" << endl;
        cout << "3 = Delete student" << endl;
        cout << "4 = Quit" << endl;

        cin >> choice;

        if (choice == 1) {
            addStudent(table);
        }
        else if (choice == 2) {
            printStudents(table);
        }
        else if (choice == 3) {
            deleteStudent(table);
        }
        else if (choice == 4) {
            break;
        }
    }

    return 0;
}

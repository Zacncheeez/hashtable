#include <iostream>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <vector>
#include <fstream>


using namespace std;

struct Student {
    char fn[81] = {'\0'};
    char ln[81] = {'\0'};
    int id;
    float gpa;
};

const int TABLE_SIZE = 100;

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

vector<string> loadNames(const char* filename) {
    vector<string> names;
    string line;
    ifstream file(filename);

    while (getline(file, line)) {
        if (!line.empty())
            names.push_back(line);
    }
    return names;
}

void generateStudents(vector<vector<Student*>>& table) {
    int count;
    cout << "How many random students would you like to generate? ";
    cin >> count;

    vector<string> firstNames = loadNames("first.txt");
    vector<string> lastNames = loadNames("last.txt");

    if (firstNames.empty() || lastNames.empty()) {
        cout << "Error: name files not found or empty." << endl;
        return;
    }

    for (int i = 0; i < count; i++) {
        Student* s = new Student;

        // Pick random names
        string fn = firstNames[rand() % firstNames.size()];
        string ln = lastNames[rand() % lastNames.size()];

        strncpy(s->fn, fn.c_str(), 80);
        strncpy(s->ln, ln.c_str(), 80);

        // Random 6-digit ID
        s->id = 100000 + rand() % 900000;

        // Random GPA 0.0–4.0
        s->gpa = (rand() % 401) / 100.0f;

        int index = hashFunction(s->id);
        table[index].push_back(s);
    }

    cout << count << " random students generated." << endl;
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
        cout << "5 = Generate random students" << endl;


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
        else if (choice == 5) {
            generateStudents(table);
        }

    }

    return 0;
}

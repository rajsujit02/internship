#include <iostream>
#include <fstream>
using namespace std;

struct Student {
    int roll;
    string name;
    float marks;
};

// ADD STUDENT
void addStudent() {
    Student s;
    ofstream file("students.txt", ios::app);

    cout << "Enter Roll Number: ";
    cin >> s.roll;
    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, s.name);

    cout << "Enter Marks: ";
    cin >> s.marks;

    file << s.roll << " " << s.name << " " << s.marks << endl;
    file.close();

    cout << "Student added successfully!\n";
}

// DISPLAY STUDENTS
void displayStudents() {
    Student s;
    ifstream file("students.txt");

    cout << "\n--- Student Records ---\n";

    while (file >> s.roll >> s.name >> s.marks) {
        cout << "Roll: " << s.roll
             << " Name: " << s.name
             << " Marks: " << s.marks << endl;
    }

    file.close();
}

// UPDATE STUDENT
void updateStudent() {
    Student s;
    ifstream file("students.txt");
    ofstream temp("temp.txt");

    int roll, found = 0;

    cout << "Enter Roll Number to Update: ";
    cin >> roll;

    while (file >> s.roll >> s.name >> s.marks) {
        if (s.roll == roll) {
            cout << "Enter New Name: ";
            cin >> s.name;
            cout << "Enter New Marks: ";
            cin >> s.marks;
            found = 1;
        }
        temp << s.roll << " " << s.name << " " << s.marks << endl;
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "Record updated!\n";
    else
        cout << "Record not found!\n";
}

// DELETE STUDENT
void deleteStudent() {
    Student s;
    ifstream file("students.txt");
    ofstream temp("temp.txt");

    int roll, found = 0;

    cout << "Enter Roll Number to Delete: ";
    cin >> roll;

    while (file >> s.roll >> s.name >> s.marks) {
        if (s.roll != roll) {
            temp << s.roll << " " << s.name << " " << s.marks << endl;
        } else {
            found = 1;
        }
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "Record deleted!\n";
    else
        cout << "Record not found!\n";
}

// MAIN FUNCTION
int main() {
    int choice;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: updateStudent(); break;
            case 4: deleteStudent(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}
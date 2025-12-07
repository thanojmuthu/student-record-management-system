#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h> // for _getch()

using namespace std;

#define STUD_FILE "students.txt"
#define CRE_FILE  "credentials.txt"

string currentUser;
string currentRole;

struct Credential {
    string username;
    string password;
    string role;
};

string getHiddenPassword() {
    string pass = "";
    char ch;

    while (true) {
        ch =_getch();  // take character without echo

        if (ch == 13) break;  // Enter key → finish

        if (ch == 8 && pass.length() > 0) {  // Backspace
            cout << "\b \b"; // erase last dot
            pass.pop_back();
            continue;
        }

        // Accept character and display DOT (●)
        if (ch != 8) {
            pass.push_back(ch);
            cout << ".";   // PRINT DOT
        }
    }

    cout << endl;
    return pass;
}

bool loadCredentials(vector<Credential> &creds) {
    ifstream fin(CRE_FILE);
    if (!fin) {
        cout << "Credential file missing!" << endl;
        return false;
    }

    Credential c;
    while (fin >> c.username >> c.password >> c.role) {
        creds.push_back(c);
    }
    fin.close();
    return true;
}

bool saveCredentials(const vector<Credential> &creds) {
    ofstream fout(CRE_FILE);
    if (!fout) {
        cout << "Error writing credentials!" << endl;
        return false;
    }

    for (const auto &c : creds)
        fout << c.username << " " << c.password << " " << c.role << "\n";

    fout.close();
    return true;
}

void resetPassword() {
    vector<Credential> creds;
    if (!loadCredentials(creds))
        return;

    string user;
    cout << "\n--- RESET PASSWORD ---\n";
    cout << "Enter username: ";
    cin >> user;

    bool found = false;
    for (auto &c : creds) {
        if (c.username == user) {
            cout << "Enter new password: ";
            c.password = getHiddenPassword();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Username not found.\n";
        return;
    }

    saveCredentials(creds);
    cout << "Password updated successfully!\n";
}

bool login() {
    vector<Credential> creds;
    if (!loadCredentials(creds))
        return false;

    for (int attempt = 1; attempt <= 3; attempt++) {
        string inUser, inPass;

        cout << "USERNAME: ";
        cin >> inUser;

        cout << "PASSWORD: ";
        inPass = getHiddenPassword();

        for (auto &c : creds) {
            if (inUser == c.username && inPass == c.password) {
                currentUser = c.username;
                currentRole = c.role;
                cout << "\nLogin successful!\n";
                return true;
            }
        }

        cout << "Incorrect login. Attempt " << attempt << " of 3.\n";
    }

    cout << "\nYou failed 3 attempts.\nForgot password? (y/n): ";
    char ch;
    cin >> ch;

    if (ch == 'y' || ch == 'Y') {
        resetPassword();
        return login();
    }

    return false;
}

void addStudent() {
    int roll;
    string name;
    float mark;

    cout << "Roll: ";
    cin >> roll;
    cout << "Name: ";
    cin >> name;
    cout << "Mark: ";
    cin >> mark;

    ofstream fout(STUD_FILE, ios::app);
    fout << roll << " " << name << " " << mark << "\n";
    fout.close();

    cout << "Student added!\n";
}

void displayStudents() {
    ifstream fin(STUD_FILE);
    if (!fin) {
        cout << "No student file found.\n";
        return;
    }

    int roll;
    string name;
    float mark;

    cout << "Roll\tName\tMark\n";
    while (fin >> roll >> name >> mark)
        cout << roll << "\t" << name << "\t" << mark << endl;

    fin.close();
}

void searchStudent() {
    int findRoll;
    cout << "Enter roll to search: ";
    cin >> findRoll;

    ifstream fin(STUD_FILE);
    int roll;
    string name;
    float mark;

    while (fin >> roll >> name >> mark) {
        if (roll == findRoll) {
            cout << "Found: " << roll << " " << name << " " << mark << endl;
            fin.close();
            return;
        }
    }

    fin.close();
    cout << "Student not found.\n";
}

void deleteStudent() {
    int delRoll;
    cout << "Enter roll to delete: ";
    cin >> delRoll;

    ifstream fin(STUD_FILE);
    ofstream temp("temp.txt");

    int roll;
    string name;
    float mark;
    bool found = false;

    while (fin >> roll >> name >> mark) {
        if (roll != delRoll)
            temp << roll << " " << name << " " << mark << "\n";
        else
            found = true;
    }

    fin.close();
    temp.close();

    remove(STUD_FILE);
    rename("temp.txt", STUD_FILE);

    cout << (found ? "Deleted.\n" : "Roll not found.\n");
}

void updateStudent() {
    int up;
    cout << "Enter roll to update: ";
    cin >> up;

    ifstream fin(STUD_FILE);
    ofstream temp("temp.txt");

    int roll;
    string name;
    float mark;
    bool found = false;

    while (fin >> roll >> name >> mark) {
        if (roll == up) {
            cout << "New Name: ";
            cin >> name;
            cout << "New Mark: ";
            cin >> mark;

            temp << roll << " " << name << " " << mark << "\n";
            found = true;
        } else {
            temp << roll << " " << name << " " << mark << "\n";
        }
    }

    fin.close();
    temp.close();

    remove(STUD_FILE);
    rename("temp.txt", STUD_FILE);

    cout << (found ? "Updated.\n" : "Roll not found.\n");
}

void adminMenu() {
    int c;
    while (true) {
        cout << "\nADMIN MENU\n1.Add\n2.Display\n3.Search\n4.Update\n5.Delete\n6.Logout\n";
        cin >> c;

        if (c == 1) addStudent();
        else if (c == 2) displayStudents();
        else if (c == 3) searchStudent();
        else if (c == 4) updateStudent();
        else if (c == 5) deleteStudent();
        else return;
    }
}

void staffMenu() {
    int c;
    while (true) {
        cout << "\nSTAFF MENU\n1.Add\n2.Display\n3.Search\n4.Update\n5.Logout\n";
        cin >> c;

        if (c == 1) addStudent();
        else if (c == 2) displayStudents();
        else if (c == 3) searchStudent();
        else if (c == 4) updateStudent();
        else return;
    }
}

void guestMenu() {
    int c;
    while (true) {
        cout << "\nGUEST MENU\n1.Display\n2.Search\n3.Logout\n";
        cin >> c;

        if (c == 1) displayStudents();
        else if (c == 2) searchStudent();
        else return;
    }
}

int main() {
    if (!login()) {
        cout << "Exiting.\n";
        return 0;
    }

    cout << "Logged in as: " << currentRole << endl;

    if (currentRole == "admin")
        adminMenu();
    else if (currentRole == "staff")
        staffMenu();
    else
        guestMenu();

    return 0;
}
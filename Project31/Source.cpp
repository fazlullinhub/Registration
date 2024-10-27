#include <iostream>
#include <string>
#include <sqlite_modern_cpp.h>

using namespace std;

void registerUser(sqlite::database& db, const string& username, const string& password) {
    try {
        db << "INSERT INTO users (username, password) VALUES (?, ?)"
            << username
            << password;  
        cout << "����������� ������ �������!" << endl;
    }
    catch (const sqlite::sqlite_exception& e) {
        cout << "������ �����������: " << e.what() << endl;
    }
}

bool loginUser(sqlite::database& db, const string& username, const string& password) {
    string storedPassword;
    try {
        db << "SELECT password FROM users WHERE username = ?"
            << username
            >> storedPassword;
    }
    catch (const sqlite::sqlite_exception& e) {
        cout << "������ �����������: " << e.what() << endl;
        return false;
    }

    if (storedPassword == password) {  
        cout << "�������� �����������!" << endl;
        return true;
    }
    else {
        cout << "�������� ��� ������������ ��� ������." << endl;
        return false;
    }
}

int main() {
    sqlite::database db("users.db");
    db << "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT UNIQUE, password TEXT);";

    while (true) {
        cout << "�������� ��������: 1. ����������� 2. ����������� 3. �����" << endl;
        int choice;
        cin >> choice;

        if (choice == 1) {
            string username, password;
            cout << "������� ��� ������������: ";
            cin >> username;
            cout << "������� ������: ";
            cin >> password;
            registerUser(db, username, password);
        }
        else if (choice == 2) {
            string username, password;
            cout << "������� ��� ������������: ";
            cin >> username;
            cout << "������� ������: ";
            cin >> password;
            loginUser(db, username, password);
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "������������ ����." << endl;
        }
    }
    return 0;
}


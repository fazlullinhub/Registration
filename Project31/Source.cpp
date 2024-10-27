#include <iostream>
#include <string>
#include <sqlite_modern_cpp.h>

using namespace std;

void registerUser(sqlite::database& db, const string& username, const string& password) {
    try {
        db << "INSERT INTO users (username, password) VALUES (?, ?)"
            << username
            << password;  
        cout << "Регистрация прошла успешно!" << endl;
    }
    catch (const sqlite::sqlite_exception& e) {
        cout << "Ошибка регистрации: " << e.what() << endl;
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
        cout << "Ошибка авторизации: " << e.what() << endl;
        return false;
    }

    if (storedPassword == password) {  
        cout << "Успешная авторизация!" << endl;
        return true;
    }
    else {
        cout << "Неверное имя пользователя или пароль." << endl;
        return false;
    }
}

int main() {
    sqlite::database db("users.db");
    db << "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT UNIQUE, password TEXT);";

    while (true) {
        cout << "Выберите действие: 1. Регистрация 2. Авторизация 3. Выход" << endl;
        int choice;
        cin >> choice;

        if (choice == 1) {
            string username, password;
            cout << "Введите имя пользователя: ";
            cin >> username;
            cout << "Введите пароль: ";
            cin >> password;
            registerUser(db, username, password);
        }
        else if (choice == 2) {
            string username, password;
            cout << "Введите имя пользователя: ";
            cin >> username;
            cout << "Введите пароль: ";
            cin >> password;
            loginUser(db, username, password);
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "Недопустимый ввод." << endl;
        }
    }
    return 0;
}


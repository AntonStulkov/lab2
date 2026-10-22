#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

struct Sess {
    int id;
    char role[16];
};

void show_log(const char* msg) {
    // CWE-134: форматная строка
    printf(msg);
    printf("\n");
}

void get_metric() {
    int arr[5] = {10, 20, 30, 40, 50};
    int idx;
    cout << "Enter metric index: ";
    cin >> idx;
    // CWE-129: выход за границы массива
    cout << "Metric value: " << arr[idx] << "\n";
}

void read_raw() {
    char buf[64];
    // CWE-457: чтение неинициализированной памяти
    cout << "Raw buffer data: " << buf << "\n";
}

int main() {
    Sess* s = nullptr;
    char usr[16];
    int cmd;

    while (true) {
        cout << "\n--- CLI Admin Panel ---\n";
        cout << "1. Login & Set Username\n";
        cout << "2. Log Custom Message\n";
        cout << "3. View System Metric\n";
        cout << "4. Read Raw Buffer\n";
        cout << "5. Logout\n";
        cout << "6. Check Session Status\n";
        cout << "7. Exit\n";
        cout << "Select option: ";

        if (!(cin >> cmd)) {
            break;
        }

        switch (cmd) {
            case 1: {
                s = new Sess();
                s->id = 101;
                cout << "Enter username: ";
                // CWE-121: переполнение буфера в стеке
                cin >> usr;
                strcpy(s->role, "Admin");
                cout << "Welcome, " << usr << "\n";
                break;
            }
            case 2: {
                char txt[64];
                cout << "Enter log message: ";
                cin >> txt;
                show_log(txt);
                break;
            }
            case 3:
                get_metric();
                break;
            case 4:
                read_raw();
                break;
            case 5:
                delete s;
                cout << "Logged out.\n";
                break;
            case 6:
                if (s != nullptr) {
                    // CWE-416: использование памяти после освобождения
                    cout << "Session ID: " << s->id << "\n";
                }
                break;
            case 7:
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
    return 0;
}
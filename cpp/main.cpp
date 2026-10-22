#include <iostream>
#include <cstdio>
#include <cstring>

struct UserSession {
    int id;
    char role[16];
};

void printLog(const char* message) {
    // Уязвимость 1: Format String Vulnerability (CWE-134)
    printf(message);
    printf("\n");
}

void printSystemMetric() {
    int metrics[5] = {10, 20, 30, 40, 50};
    int index;
    std::cout << "Enter metric index: ";
    std::cin >> index;
    // Уязвимость 2: Out-of-Bounds Read (CWE-129 / CWE-119)
    std::cout << "Metric value: " << metrics[index] << "\n";
}

void readUninitializedBuffer() {
    char rawData[64];
    // Уязвимость 3: Uninitialized Memory Read (CWE-457)
    std::cout << "Raw buffer data: " << rawData << "\n";
}

int main() {
    UserSession* currentSession = nullptr;
    char username[16];
    int choice;

    while (true) {
        std::cout << "\n--- CLI Admin Panel ---\n";
        std::cout << "1. Login & Set Username\n";
        std::cout << "2. Log Custom Message\n";
        std::cout << "3. View System Metric\n";
        std::cout << "4. Read Raw Buffer\n";
        std::cout << "5. Logout\n";
        std::cout << "6. Check Session Status\n";
        std::cout << "7. Exit\n";
        std::cout << "Select option: ";

        if (!(std::cin >> choice)) {
            break;
        }

        switch (choice) {
            case 1: {
                currentSession = new UserSession();
                currentSession->id = 101;
                std::cout << "Enter username: ";
                // Уязвимость 4: Stack-based Buffer Overflow (CWE-121)
                std::cin >> username;
                strcpy(currentSession->role, "Admin");
                std::cout << "Welcome, " << username << "\n";
                break;
            }
            case 2: {
                char msg[64];
                std::cout << "Enter log message: ";
                std::cin >> msg;
                printLog(msg);
                break;
            }
            case 3:
                printSystemMetric();
                break;
            case 4:
                readUninitializedBuffer();
                break;
            case 5:
                delete currentSession;
                std::cout << "Logged out.\n";
                break;
            case 6:
                if (currentSession != nullptr) {
                    // Уязвимость 5: Use-After-Free (CWE-416)
                    std::cout << "Session ID: " << currentSession->id << "\n";
                }
                break;
            case 7:
                return 0;
            default:
                std::cout << "Invalid choice.\n";
        }
    }
    return 0;
}
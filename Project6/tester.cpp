#include <iostream>
using namespace std;

void removeS(char* ptr) {
    char* freeSpace = ptr;
    while (*ptr != 0) {
        if (tolower(*ptr) != 's') {
            *freeSpace = *ptr;
            freeSpace++;
        }
        ptr++;
    }
    *freeSpace = '\0';
}

int main()
{
    char msg[50] = "She'll blossom like a massless princess.";
    removeS(msg);
    cout << msg;  // prints   he'll bloom like a male prince.
}
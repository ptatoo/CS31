#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
    string institution = "";
    double baseAmount = -1;
    string institutionType = "";

    //input
    cout << "Institution: ";
    getline(cin, institution);
    cout << "Basis Amount (in trillions): ";
    cin >> baseAmount;
    cin.ignore();
    cout << "Institution type: ";
    getline(cin, institutionType);

    cout << "---\n";
    //edge cases
    if (institution == "") {
        cout << "You must enter an institution.\n";
        return 0;
    }
    if (baseAmount <= 0) {
        cout << "The basis amount must be positive.\n";
        return 0;
    }
    if (institutionType == "") {
        cout << "You must enter an institution type.\n";
        return 0;
    }

    //calculate settlement amount
    double settlementAmount = 0;
    if (baseAmount <= 160) {
        settlementAmount += baseAmount * 0.07;
    } else if (baseAmount > 160) {
            settlementAmount += 160 * 0.07;
            baseAmount -= 160;
            if (baseAmount > 600) {
                settlementAmount += 0.11 * (baseAmount - 600);
                baseAmount = 600;
            }
            if (institutionType == "media" || institutionType == "university") {
                settlementAmount += baseAmount * 0.17;
            } else settlementAmount += baseAmount * 0.09;
    }

    //output
    cout.setf(ios::fixed);
    cout.precision(1);
    
    cout << "The settlement amount for " << institution << " is P" << settlementAmount << " trillion.\n";
    return 0;
}
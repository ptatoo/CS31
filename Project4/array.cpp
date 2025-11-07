#include <iostream>
#include <string>
#include <cctype>

using namespace std;

//1
int repeat(string a[], int n) {
    //edge case
    if (n < 0) return -1;
    
    for (int i = 0; i < n; i++) {
        a[i] = a[i] + a[i];
    }
    return n;
}

//2
int detectMatch(const string a[], int n, string target) {
    //edge case
    if (n < 0) return -1;

    for (int i = 0; i < n; i++) {
        if (a[i] == target) return i;
    }
    return -1;
}

//3
int detectMax(const string a[], int n) {
    //edge case
    if (n <= 0) return -1;

    int max = 0;
    for (int i = 0; i < n; i++) {
        //updates max if bigger value found
        if (a[i] > a[max]) max=i;
    }
    return max;
}

//4
int circleLeft(string a[], int n, int pos) {
    //edge case
    if (n < 0 || pos < 0) return -1;

    string eliminated = a[pos];
    for (int i = pos; i < n - 1; i++) {
        a[i] = a[i+1];
    }
    a[n-1] = eliminated;
    return pos;
}

//5
int enumerateRuns(const string a[], int n) {
    //edge cases
    if (n <= 0) return -1;
    if (n == 0) return 0;

    int count = 1;
    for (int i = 1; i < n; i++) {
        //checks if conseq values are different
        if (a[i-1] != a[i]) count++;
    }
    return count;
}

//6
int flip(string a[], int n) {
    //edge case
    if (n < 0) return -1;

    //loops through half the array, swaping corresponding front-back values
    for (int i = 0; i < n/2; i++) {
        string temp = a[i];
        a[i] = a[n-1-i];
        a[n-1-i] = temp;
    }
    return n;
}

//7
int detectDifference(const string a1[], int n1, const string a2[], int n2) {
    //edge case and finding min
    if (n1 < 0 || n2 < 0) return -1;
    int min = 0;
    if (n1 < n2) min = n1;
    else min = n2;

    //loops through min of n1 and n2 looking for differences
    for (int i = 0; i < min; i++) {
        if (a1[i] != a2[i]) return i;
    }
    return min;
}

//8
int subsequence(const string a1[], int n1, const string a2[], int n2) {
    //edge cases
    if (n1 < 0 || n2 < 0) return -1;
    if (n2 == 0) return 0;

    for (int i = 0; i <= n1 - n2; i++) {
        int output = i;
        for (int j = 0; j < n2; j++) {
            if (a1[i+j] != a2[j]) {
                //if smth doesnt match, output is set to -1
                output = -1;
            }
        }
        if (output != -1) return output;
    }
    return -1;
}

//9
int detectAny(const string a1[], int n1, const string a2[], int n2) {
    //edge case
    if (n1 < 0 || n2 < 0) return -1;

    //loops through both arrays
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            if (a1[i] == a2[j]) return i;
        }
    }
    return -1;
}

//10
int split(string a[], int n, string splitter) {
    //edge case
    if (n < 0) return -1;

    int index = 0;
    for (int i = 0; i < n; i++) {
        //if a smaller value is found, its sent to front
        if (a[i] < splitter) {
            string temp = a[index];
            a[index] = a[i];
            a[i] = temp;
            index ++;
        }
    }

    return index;
}

int main() {
    //test variables
    int test_length = 0;
    string test[10000];
    int test2_length = 0;
    string test2[10000];
    string parameter = "";
    int test_num = 1;
    int returnValue = 0;

    //loop to allow multiple tests
    while (true) {
        //test parameters
        cout << "Enter test number: ";
        cin >> test_num;
        cout << "Enter array length: ";
        cin >> test_length;
        cout << "Enter array (ctrl+c to exit):\n";
        for (int i = 0; i < test_length; i++) {
            cin >> test[i];
        }

        //extra parameters for specific tests
        if (test_num == 2 || test_num == 4 || test_num == 10) {
            cout << "Enter parameter: ";
            cin >> parameter;
        }
        if (test_num == 7 || test_num == 8 || test_num == 9) {
            cout << "Enter 2nd array length: ";
            cin >> test2_length;
            cout << "Enter 2nd array (ctrl+c to exit):\n";
            for (int i = 0; i < test2_length; i++) {
                cin >> test2[i];
            }
        }

        //runs specific function
        switch (test_num) {
            case (1):
                returnValue = repeat(test, test_length);
                break;
            case 2:
                returnValue = detectMatch(test, test_length, parameter);
                break;
            case (3):
                returnValue = detectMax(test, test_length);
                break;
            case (4):
                returnValue = circleLeft(test, test_length, stoi(parameter));
                break;
            case (5):
                returnValue = enumerateRuns(test, test_length);
                break;
            case (6):
                returnValue = flip(test, test_length);
                break;
            case (7):
                returnValue = detectDifference(test, test_length, test2, test2_length);
                break;
            case (8):
                returnValue = subsequence(test, test_length, test2, test2_length);
                break;
            case (9):
                returnValue = detectAny(test, test_length, test2, test2_length);
                break;
            case (10):
                returnValue = split(test, test_length, parameter);
                break;
            default:
                break;            
        }

        //prints return value and test array
        cout << "Return Value: " << returnValue << endl;
        for (int i = 0; i < test_length; i++) {
            cout << test[i] << " ";
        }
        cout << endl;
    }

}
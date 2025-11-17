#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>

using namespace std;

//writes word-portions into outf
int writeToFile(int *counter, int lineLength, ostream& outf, char output[121], int numAddedSpaces, bool *newPara) {

    //detects a new paragraph
    if (!strcmp(output, "<P>")) {
        if (numAddedSpaces == 0 && !*newPara) {
            outf << output;
            *counter += static_cast<int>(strlen(output)) + numAddedSpaces;
        }
        else *newPara = true;
        return 0;
    }
    //writes out a new paragraph
    if (*newPara == true && *counter!=0) {
        outf << endl << endl;
        *counter = 0;
    }
    *newPara = false;
    //writes a new line if word-portion too long to fit but not too long to need wrap
    if (strlen(output) + *counter + numAddedSpaces >= lineLength && strlen(output) <= lineLength) {
        outf << endl << output;
        *counter = static_cast<int>(strlen(output));
        return 0;
    }
    //elsewise, print out previous whitespace
    if (*counter != 0 && strlen(output) != 0) {
        for (int i = 0; i < numAddedSpaces; i++) outf << ' ';
        *counter += numAddedSpaces;
    }
    //word-portion is longer then lineLength
    if (strlen(output) > lineLength) {
        //adds characters, and new lines when necessary
        for (int i = 0; i < strlen(output); i++) {
            if (*counter >= lineLength) {
                outf << endl;
                *counter = 0;
            }
            outf << output[i];
            *counter += 1;
        }
        return 2;
    }
    //word-portion is standard
    else {
        outf << output;
        *counter += static_cast<int>(strlen(output));
    }
    
    return 0;
}

int arrange(int lineLength, istream& inf, ostream& outf) {
    //edge case
    if (lineLength < 1) return 1;
    //parameters
    char output[122] = ""; 
    int counter = 0;
    int numAddedSpaces = 0;
    int returnValue = 0;
    char curChar[2] = {'a','\0'};
    char prevC = 'a';
    bool newPara = true;

    while (inf.get(curChar[0])) {
        //if space, write out input (word-portion)
        if (curChar[0] == ' ' || curChar[0] == '\n') {
            if (strlen(output) > 0) {
                if (writeToFile(&counter, lineLength, outf, output, numAddedSpaces, &newPara) == 2) returnValue = 2;
                if ((prevC == '.' || prevC == '?' || prevC == ':')) numAddedSpaces = 2;
                else numAddedSpaces = 1;
                output[0] = '\0';
            }
        }
        //if dash, write out input (word-portion)
        else if (curChar[0] == '-') {
            strcat(output, curChar);
            if (writeToFile(&counter, lineLength, outf, output, numAddedSpaces, &newPara) == 2) returnValue = 2;
            numAddedSpaces = 0;
            output[0] = '\0';
        }
        //else, add char to input (grow word-portion)
        else strcat(output, curChar);
        prevC = curChar[0];
    }
    if (writeToFile(&counter, lineLength, outf, output, numAddedSpaces, &newPara) == 2) returnValue = 2;
    outf << endl;

    return returnValue;
}

//tester main line
int main()
{
    ifstream infile("Input.txt");
    if (!infile) {
        cerr << "Error. infile no read"; 
        return 1;
    }
    ofstream outfile("Output.txt");
    if (!outfile) {
        cerr << "Error. outfile no read";
        return 1;
    }
    // char c = ' ';
    // while (infile.get(c)) {
    //     if (c == '\n') cout << '7';
    //     else cout << c;
    // }

    cout << arrange(10, infile, outfile);
}
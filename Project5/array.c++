#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

//writes word-portions into outf
int writeToFile(int *counter, int lineLength, ostream& outf, char output[121], int numAddedSpaces, bool *newPara) {
    //writes a new paragraph
    if (!strcmp(output, "<P>")) {
        if (!*newPara) {
            outf << endl << endl;
            *counter = 0;
            *newPara = true;
        }
        else *newPara = false;
    }
    //word is longer then lineLength
    else if (strlen(output) > lineLength) {
        //adds req. whitespace before word-portion
        if (*counter != 0) {
            for (int i = 0; i < numAddedSpaces; i++) outf << ' ';
        }
        *counter += numAddedSpaces;
        //adds characters, and new lines when necessary
        for (int i = 0; i < strlen(output); i++) {
            if (*counter >= lineLength) {
                outf << endl << output[i];
                *counter = 1;
            } else {
                outf << output[i];
                *counter += 1;
            }
        }
        return 2;
    }
    //writes a new line if word-portion too long
    else if (strlen(output) + *counter >= lineLength) {
        outf << endl << output;
        *counter = static_cast<int>(strlen(output));
    }
    //writes a word-portion
    else {
        //adds req. whitespace before word-portion
        if (*counter != 0) {
            for (int i = 0; i < numAddedSpaces; i++) outf << ' ';
        }
        outf << output;
        *counter += static_cast<int>(strlen(output)) + numAddedSpaces;
    }

    return 0;
}

int arrange(int lineLength, istream& inf, ostream& outf) {
    //edge case
    if (lineLength < 1) return 1;
    int MAX = 121;
    char output[MAX]; output[0] = '\0';
    int counter = 0;
    int numAddedSpaces = 0;
    int returnValue = 0;
    char curChar[3] = {'a','\0', ' '};
    char prevC = ' ';
    bool newPara = true;

    while (inf.get(curChar[0])) {
        //if space, write out input (word-portion)
        if (curChar[0] == ' ' || curChar[0] == '\n') {
            if (strlen(output) != 0) {
                if (writeToFile(&counter, lineLength, outf, output, numAddedSpaces, &newPara) == 2) returnValue = 2;
                if ((prevC == '.' || prevC == '?' || prevC == ':')) numAddedSpaces = 2;
                else numAddedSpaces = 1;
            }
            output[0] = '\0';
        }
        //if dash, write out input (word-portion)
        else if (curChar[0] == '-') {
            strcat(output, curChar);
            if (writeToFile(&counter, lineLength, outf, output, numAddedSpaces, &newPara) == 2) returnValue = 2;
            output[0] = '\0';
            numAddedSpaces = 0;
        }
        //else, add char to input (grow word-portion)
        else strcat(output, curChar);
        prevC = curChar[0];
    }    
    if (writeToFile(&counter, lineLength, outf, output, numAddedSpaces, &newPara) == 2) returnValue = 2;

    return returnValue;
}

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

    cout << arrange(20, infile, outfile);
}
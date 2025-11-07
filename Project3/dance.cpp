#include <stdio.h>
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool isSyntacticallyCorrect(string dance);

bool isSyntacticallyCorrect(string dance)
{
    const string directions = "LlDdUuRr";

    // loops through every beat
    while (dance.find("/") != string::npos)
    {
        // finds contents in beat
        int index = dance.find("/");
        string prefix = dance.substr(0, index);
        dance = dance.substr(dance.find("/") + 1);

        // checks if the contents are syntactically correct
        if (prefix.length() == 0)
            continue;
        else if (prefix.length() == 1 && directions.find(prefix) != string::npos)
            continue;
        else if (prefix.length() == 2 && isdigit(prefix.at(0)) && directions.find(prefix.at(1)) != string::npos)
            continue;
        else if (prefix.length() == 3 && isdigit(prefix.at(0)) && isdigit(prefix.at(1)) && directions.find(prefix.at(2)) != string::npos)
            continue;
        else
            return false;
    }

    // once all beats (dashes) are gone, checks theres nothing left
    if (dance.length() != 0)
        return false;

    return true;
}

int translateDance(string dance, string &instructions, int &badBeat)
{
    // checks if syntactically correct
    if (!isSyntacticallyCorrect(dance))
        return 1;

    int beatCount = 0;
    int freezeCount = 0;
    string output = "";
    char freezeValue = ' ';

    // loops through every beat
    while (dance.find("/") != string::npos)
    {
        // finds contents in beat
        int index = dance.find("/");
        string prefix = dance.substr(0, index);
        dance = dance.substr(dance.find("/") + 1);
        // updates counts
        beatCount++;

        // freeze too short (0, 00, 1, 01)
        if (prefix.length() == 2 && (prefix.at(0) == '0' || prefix.at(0) == '1'))
        {
            badBeat = beatCount;
            return 2;
        }
        else if (prefix.length() == 3 && (prefix.substr(0, 2) == "00" || prefix.substr(0, 2) == "01"))
        {
            badBeat = beatCount;
            return 2;
        }
        // freeze in effect: not enough beats
        else if (freezeCount > 0 && prefix.length() != 0)
        {
            badBeat = beatCount;
            return 3;
        }
        // freeze initialized: set freezeCount
        else if (prefix.length() == 2)
        {
            freezeCount = stoi(prefix.substr(0, 1));
            freezeValue = prefix.at(1);
        }
        else if (prefix.length() == 3)
        {
            freezeCount = stoi(prefix.substr(0, 2));
            freezeValue = prefix.at(2);
        }

        // update output
        if (prefix.length() == 1)
        {
            output += tolower(prefix.at(0));
        }
        else if (freezeCount > 0)
        {
            output += toupper(freezeValue);
        }
        else if (prefix.length() == 0)
        {
            output += ".";
        }

        // update freezeCount
        if (freezeCount > 0)
            freezeCount--;
    }

    // dance done: freeze not done
    if (freezeCount > 0)
    {
        badBeat = beatCount + 1;
        return 4;
    }

    instructions = output;
    return 0;
}

int main()
{
    while (true)
    {
        // takes in hypothetical dance
        string input = "";
        cout << "Enter input (e to exit): ";
        getline(cin, input);
        if (input == "e")
            break;

        // analyzes dance
        string instructions = "";
        int badBeat = 0;
        int translation = translateDance(input, instructions, badBeat);
        if (translation == 1)
        {
            cout << "false" << endl;
        }
        else if (translation == 0)
        {
            cout << "Translation: " << instructions << endl;
        }
        else
            cout << "Error: " << translation << " BadBeat: " << badBeat << endl;
    }
}
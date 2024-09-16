#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include "git_func.hpp"

using namespace std;

int main() {
    string hash, message, username, date;

    get_details(hash, 1);
    get_details(message, 2);
    get_details(username, 3);
    get_details(date, 4);

    ofstream outputFile("store.txt");

    if (outputFile.is_open()) {
        outputFile << hash << endl;
        outputFile << message << endl;
        outputFile << username << endl;
        outputFile << date << endl;
        outputFile.close();
        cout << "Data written to output.txt successfully." << endl;
    } else {
        cout << "Error opening file." << endl;
    }

    ifstream inputFile("store.txt");

    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            cout << line << endl;
        }
        inputFile.close();
    } else {
        cout << "Error opening file." << endl;
    }


    return 0;
}
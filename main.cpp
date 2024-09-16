#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include "git_func.hpp"

using namespace std;

int main() {
    string hash, message, name, username, id, date;

    get_details(hash, 1);
    get_details(message, 2);
    get_details(name, 3);
    get_details(username, 4);
    get_details(id, 5);
    get_details(date, 6);

    ofstream outputFile("store.txt");

    if (outputFile.is_open()) {
        outputFile << hash << endl;
        outputFile << message << endl;
        outputFile << name << endl;
        outputFile << username << endl;
        outputFile << id << endl;
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
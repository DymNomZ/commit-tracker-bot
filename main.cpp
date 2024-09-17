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

    ofstream outputFile("C:\\Users\\User\\Desktop\\commit-tracker-bot\\MyBot\\store_info.txt");

    if (outputFile.is_open()) {
        outputFile << hash << endl;
        outputFile << message << endl;
        outputFile << username << endl;
        outputFile << date << endl;
        outputFile.close();
        cout << "Data written to store_info.txt successfully. - via run_git_coms" << endl;
    } else {
        cout << "Error opening store_info file. - via run_git_coms" << endl;
    }

    //write file changes stats to files_changed.txt
    FILE* temp_file = tmpfile();
    if (!temp_file) {
        perror("tmpfile");
        return 1;
    }


    int result = system("git show --stat --pretty=format:%s --format=\"\" > C:\\Users\\User\\Desktop\\commit-tracker-bot\\MyBot\\files_changed.txt");
    if (result != 0) {
        perror("git show");
        fclose(temp_file);
        return 1;
    }

    return 0;
}
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

int main() {
    FILE *pipe = popen("git log -1 --pretty=format:'%ad'", "r");
    if (pipe != nullptr) {
        char buffer[128];
        string result;
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            result += buffer;
        }
        pclose(pipe);

        cout << "Latest commit date: " << result << endl;
    } else {
        cerr << "Error executing command." << endl;
    }

    return 0;
}
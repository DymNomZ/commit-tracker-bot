#include <iostream>
#include <string>
#include <string.h>

using namespace std;

void get_details(string& var, int type){
    FILE *pipe;
    int buf_size = 128;
    switch(type){
        case 1:
        pipe = popen("git rev-parse HEAD", "r");
        buf_size = 50;
        break;

        case 2:
        pipe = popen("git log -1 --pretty=format:%s", "r");
        buf_size = 1024;
        break;

        case 3:
        pipe = popen("git log -1 --pretty=format:'%an'", "r");
        buf_size = 20;
        break;

        case 4:
        pipe = popen("git log -1 --pretty=format:'%ad'", "r");
        break;
    }
    
    if (pipe != nullptr) {
        char buffer[buf_size];
        fgets(buffer, sizeof(buffer), pipe);
            int len = strlen(buffer);
            if(buffer[len - 1] == '\n' && type == 1) buffer[len - 1] = '\0';
            if(type == 4){
                int i = 1;
                while(buffer[i] != '+'){
                    var += buffer[i];
                    i++;
                }
            }
            if(type == 5){
                int i = 11;
                while(buffer[i] != '@'){
                    var += buffer[i];
                    i++;
                }
            }
            else{
                if(type != 4) var += buffer;
            }
        pclose(pipe);

        cout << var << endl;
    } else {
        cerr << "Error executing command." << endl;
    }
}
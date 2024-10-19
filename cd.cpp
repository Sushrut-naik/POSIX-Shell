#include "headers.h"
using namespace std;
void change_dir(vector<string> input){
    char cwd[256];
    getcwd(cwd,sizeof(cwd));
    char* home_directory = getenv("NEW_HOME");

    if(input.size() == 1){
        if(chdir(home_directory) != 0){
            perror("Error changing directory");
        }
    }

    if(input.size() > 1 && input[1] == "~"){
        if(chdir(home_directory) != 0){
            perror("Error changing directory");
        }
    }
    else if(input.size() > 1){
        
        if(chdir(input[1].c_str()) != 0){
            perror("Error changing directory");
        }
    }
}
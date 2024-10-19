#include"headers.h"
using namespace std;

int track_pid=0;

void run_in_background(vector<string> input, int hold_bg=0) {
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        return;
    } else if (pid == 0){
        // Convert vector of strings to array of C-style strings
        vector<char*> char_input;
        for (int i=0; i<input.size(); i++){
            char_input.push_back(const_cast<char*>(input[i].c_str()));
        }
        char_input.push_back(NULL);

        if (setsid() < 0) {
            perror("Session separation failed");
            exit(1);
        }

        if (execvp(char_input[0], char_input.data()) < 0){
            perror("Failed to execute command");
            exit(1);
        }
    }
    else{
        if(hold_bg == 0){
            cout<<pid<<endl;
            waitpid(pid, NULL, WNOHANG);
        }
        else{
            int status;
            track_pid = pid;
            int child_status = waitpid(pid, &status, 0);

            if (child_status == -1) {
                perror("Error waiting for the child process");
                return;
            }
        }
    }
}
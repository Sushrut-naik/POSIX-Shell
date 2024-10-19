#include "headers.h"

using namespace std;

void exit_handler() {
    write_history();
}

vector<string> hist_comm_list;


int main(){

    if (atexit(exit_handler) != 0) {
        perror("Failed to register exit handler 1");
        return 1;
    }
    
    signal(SIGTSTP, handle_ctrl_z);
    signal(SIGINT, handle_ctrl_c);
    vector<vector<string>> inp;
    char cwd[256];    
    getcwd(cwd, sizeof(cwd));
    setenv("NEW_HOME", cwd, 1);
    init_history();

    while(1){
        // signal(SIGINT, handle_ctrl_c);
        display_prompt();
        inp = parse_input();
        if(inp.empty())
            continue;
        if(inp[0][0] == "exit" && inp[0].size() == 1){
            cout<<endl;
            break;
        }
        for(int i=0; i<inp.size(); i++){
            int redir_flag = 0, pipe_flag = 0;
            for(int j=0; j<inp[i].size(); j++){
                if(inp[i][j] == "<" || inp[i][j] == ">" || inp[i][j] == ">>"){
                    // redirection_handler(inp[i]);
                    redir_flag = 1;
                }

                if(inp[i][j] == "|"){
                    // pipe_handler(inp[i]);
                    pipe_flag = 1;
                    break;
                }
            }
            if(pipe_flag == 1){
                pipe_handler(inp[i]);
            }
            else if(redir_flag == 1){
                redirection_handler(inp[i]);
            }
            else if(pipe_flag == 0 && redir_flag == 0)
                cmd_handler(inp[i]);
        }
        // cmd_handler(inp);

    }        
}
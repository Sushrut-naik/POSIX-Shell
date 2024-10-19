#include "headers.h"

void handle_ctrl_z(int signal_num){
    cout<<"track_pid is "<<track_pid<<endl;
    if(track_pid != 0){
        if(kill(track_pid, SIGTSTP) == -1){
            perror("Error killing process");
        }
        track_pid = 0;
        
    }else{
        display_prompt();
    }
    return;
}

void handle_ctrl_c(int signal_num){
    
    if(track_pid != 0){
        if(kill(track_pid, SIGINT) == -1){
            perror("Error killing process");
        }
        track_pid = 0;
        
    }else{
        display_prompt();
    }
    
    return;
}
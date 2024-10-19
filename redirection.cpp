#include "headers.h"

void redirection_handler(vector<string> input){

    int fd0, fd1, in=0, out=0, append_flag=0;
    int og_stdout = dup(1);
    int og_stdin = dup(0);
    string in_file, out_file;
    vector<string> cmd_to_pass;

    // finds where '<' or '>' occurs and make that argv[i] = NULL , to ensure that command wont't read that

    for(int i=0; i<input.size(); i++){
        if(input[i] == "<"){
            in_file = input[i+1];
            in = 2;
        }      

        if(input[i] == ">"){
            out_file = input[i+1];
            out = 2;
        }

        if(input[i] == ">>"){
            out_file = input[i+1];
            out = 2;
            append_flag = 1;
        }
    }
    //if '<' char was found in string inputted by user
    if(in == 2 && out == 0){   
        // fd0 is file-descriptor
        
        int fd0;
        if ((fd0 = open(const_cast<char*>(in_file.c_str()), O_RDONLY, 0)) < 0){
            perror("Couldn't open input file");
            return;
        }
        
        if(dup2(fd0, 0) == -1){
            perror("Error changing input file descriptor");
            return;
        }
        close(fd0);

        for(int i=0; i<input.size(); i++){
            if(input[i] == "<")
                break;
            else{
                cmd_to_pass.push_back(input[i]);
            }
        }
        cmd_handler(cmd_to_pass);
        
    }

    //if '>' char was found in string inputted by user 
    if (out == 2 && in == 0){
        int fd1 ;
        if(append_flag == 1){
            if((fd1 = open(const_cast<char*>(out_file.c_str()) , O_WRONLY | O_APPEND | O_CREAT, 0644)) < 0){
                perror("Couldn't open output file");
                return;
            }
        }
        else{
            if((fd1 = open(const_cast<char*>(out_file.c_str()) , O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0){
                perror("Couldn't open output file");
                return;
            }   
        }

        dup2(fd1, STDOUT_FILENO);
        if(append_flag == 1){
            for(int i=0; i<input.size(); i++){
                if(input[i] == ">>")
                    break;
                else{
                    cmd_to_pass.push_back(input[i]);
                }
            }
        }
        else{
            for(int i=0; i<input.size(); i++){
                if(input[i] == ">")
                    break;
                else{
                    cmd_to_pass.push_back(input[i]);
                }
            }
        }
        cmd_handler(cmd_to_pass);
        close(fd1);
    }

    if(in == 2 && out == 2){
        int fd_in, fd_out;

        if ((fd_in = open(const_cast<char*>(in_file.c_str()), O_RDONLY, 0)) < 0){
            perror("Couldn't open input file");
            return;
        }

        if ((fd_out = open(const_cast<char*>(out_file.c_str()) , O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0){
            perror("Couldn't open output file");
            return;
        }

        if(dup2(fd_in, 0) == -1){
            perror("Error changing input file descriptor");
            return;
        }
        close(fd_in);

        if(dup2(fd_out, 1) == -1){
            perror("Error changing output file descriptor");
            return;
        }
        close(fd_out);

        for(int i=0; i<input.size(); i++){
            if(input[i] == "<")
                break;
            else{
                cmd_to_pass.push_back(input[i]);
            }
        }
        cmd_handler(cmd_to_pass);
    }

    if(dup2(og_stdout, STDOUT_FILENO) == -1){
        perror("Error restoring stdout");
        return;
    }
    if(dup2(og_stdin, STDIN_FILENO) == -1){
        perror("Error restoring stdin");
        return;
    }
    close(og_stdout);
    close(og_stdin);
}
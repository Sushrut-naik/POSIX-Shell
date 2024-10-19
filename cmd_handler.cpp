#include "headers.h"
using namespace std;

int detect_bg(vector<string> input){
    for(int i=0;i<input.size();i++){
        if(input[i] == "&")
            return i;
    }
    return -1;
}
void cmd_handler(vector<string> input){

    int bg = detect_bg(input);
    if(bg != -1){
        vector<string> temp;
        for(int i=0; i<bg; i++){
            temp.push_back(input[i]);
        }
        run_in_background(temp, 0);
        return;
    }

    if(input[0] == "pwd"){
        pwd();
    }
    else if(input[0] == "echo"){
        for(int i=1; i<input.size(); i++){
            if(i == input.size()-1)
                cout<<input[i]<<endl;
            else
                cout<<input[i]<<" ";
        }
    }
    else if(input[0] == "cd"){
        if(input.size() > 2){
            cout<<"Invalid arguments for error handling\n";
            return;
        }
        change_dir(input);
    }
    else if(input[0] == "ls"){
        ls(input);
    }
    else if(input[0] == "pinfo"){
        int pid;
        if(input.size() == 1)
            pid = -1;
        else
            pid = stoi(input[1]);
        get_pinfo(pid);
    }
    else if(input[0] == "search"){
        if(input.size() == 1)
            cout<<"Please enter a directory to search\n";
        else
            cout<<search(input[1], ".")<<endl;
    }
    else if(input[0] == "history"){
        if(input.size() == 1){
            history(10);
        }
        else if(input.size() == 2){
            history(stoi(input[1]));
        }
    }
    else{
        run_in_background(input, 1);
    }
}
#include "headers.h"
using namespace std;

string extract_value_memory(string content){
    size_t  state_pos = content.find("VmSize:");
    if (state_pos != std::string::npos) {
        return content.substr(state_pos + 8); // Skip "State: " and extract the rest
    }
    return "";
}

string extract_value_status(string content){
    size_t  state_pos = content.find("State:");
    if (state_pos != std::string::npos) {
        return content.substr(state_pos + 7); // Skip "State: " and extract the rest
    }
    return "";
}

string read_data(int pid, string entry, string what_to_retrieve) {
    string file_path;
    if(pid == -1)
        file_path = "/proc/self/" + entry;
    else
        file_path = "/proc/" + to_string(pid) + "/" + entry;
    ifstream file(file_path);
    if (!file.is_open()) {
        return "N/A";
    }
    string content, ret_val;
    if(what_to_retrieve == "status"){
        while(getline(file, content)){
            ret_val = extract_value_status(content);
            if(ret_val != "")
                break;
        }
        return ret_val;
    }
    else if(what_to_retrieve == "memory"){
        while(getline(file, content)){
            ret_val = extract_value_memory(content);
            if(ret_val != "")
                break;
        }
        return ret_val;
    }
    else if(what_to_retrieve == "exe"){
        char exe_path[256];
        if(pid == -1)
            file_path = "/proc/self/exe";
        else
            file_path = "/proc/" + to_string(pid) + "/exe";

        int len = readlink(file_path.c_str(), exe_path, sizeof(exe_path));
        if (len != -1) {
            exe_path[len] = '\0';
            return string(exe_path);
        } else {
            return "Unknown"; // Process may have terminated or doesn't exist
        }
    }
    return "Unknown";
}

string get_status(int pid) {
    return read_data(pid, "status", "status");
}

// Function to get memory allocated
string get_memory(int pid) {
    return read_data(pid, "status", "memory"); // You need to extract the memory information from the status file
}

// Function to get executable path
string get_exe_path(int pid) {
    return read_data(pid,"", "exe");
}

void get_pinfo(int pid){
    string status = get_status(pid);
    string status_code;
    for(int i=0; i<status.length(); i++){        
        if(status[i] == 'S' || status[i] == 'R' || status[i] == 'Z' || status[i] == 'T'){
            status_code = status[i];
            if(status[i+1] == '+'){
                status_code += '+';
            }
            break;
        }
    }

    string memory = get_memory(pid);
    string memory_op;

    string exe_path = get_exe_path(pid);

    memory_op = regex_replace(memory, regex("[^0-9]*([0-9]+).*"), string("$1"));

    int get_foreground_group = tcgetpgrp(STDIN_FILENO);
    int get_pid_group;
    if(pid != -1){
        get_pid_group = getpgid(pid);
    }
    else{
        get_pid_group = getpgid(getpid());
    }    

    if(get_foreground_group == get_pid_group){
        status_code += "+";
    }

    cout<<"Process Status -- "<<status_code<<endl;
    cout<<"memory -- "<<memory_op<<endl;
    cout<<"Executable Path -- "<<exe_path<<endl;    
}
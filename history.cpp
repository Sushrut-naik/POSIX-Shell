#include "headers.h"

void history(int num=10){
    // hist_comm_list
    if(hist_comm_list.size() < num){
        for (int i = 0; i < hist_comm_list.size(); ++i) {
            cout<<hist_comm_list[i]<<endl;
        }
    }

    for (int i = hist_comm_list.size() - num; i < hist_comm_list.size(); ++i) {
        cout<<hist_comm_list[i]<<endl;
    }
}

void record_command(string comm){
    if(hist_comm_list.size() > 0)
        if(comm == hist_comm_list[hist_comm_list.size()-1])
            return;
    if(hist_comm_list.size() < 20){
        hist_comm_list.push_back(comm);
    }

    else if(hist_comm_list.size() == 20){
        hist_comm_list.erase(hist_comm_list.begin());
        hist_comm_list.push_back(comm);
    }
}

void init_history(){
    char * history_file_path = getenv("NEW_HOME");
    string path = history_file_path;
    path += "/history.txt";
    int fd= open(path.c_str(), O_CREAT | O_RDONLY, 0644);

    ifstream ip_file;
    ip_file.open(path.c_str());

    if (!ip_file.is_open()) {
        perror("Error opening history file for reading");
        return;
    }

    hist_comm_list.clear();
    string line;
    while (getline(ip_file, line)) {
        hist_comm_list.push_back(line);
    }
}

void write_history(){
    char * history_file_path = getenv("NEW_HOME");
    string path = history_file_path;
    path += "/history.txt";
    ofstream op_file(path, ios::trunc);
    if (!op_file.is_open()) {
        perror("Error opening history file for writing");
        return;
    }

    for (string& line : hist_comm_list) {
        op_file << line << "\n";
    }
}
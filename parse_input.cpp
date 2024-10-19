#include "headers.h"
using namespace std;

vector<vector<string>> parse_input(){
    string placeholder;
    char inp[256];
    char *tok;
    vector<string> temp;
    vector<string> temp_2d;
    vector<vector<string>> ret_val;

    // cin.getline(inp, sizeof(inp));
    if (!cin.getline(inp, sizeof(inp))) {
        // Ctrl+D (EOF) was detected, exit the loop
        // vector<string> exit;
        // exit.push_back("exit");
        // ret_val.push_back(exit);
        // return ret_val;

        exit(0);
    }

    record_command(inp);
    tok = strtok (inp,";");
    while (tok != NULL)
    {
        placeholder = tok;
        temp.push_back(placeholder);
        tok = strtok (NULL, ";");
    }

    for(int i=0; i<temp.size(); i++){
        char* temp_cstr = new char[temp[i].length() + 1];
        strcpy(temp_cstr, temp[i].c_str());
        tok = strtok (temp_cstr," ");
        while (tok != NULL)
        {
            placeholder = tok;
            temp_2d.push_back(placeholder);
            tok = strtok (NULL, " ");
        }
        ret_val.push_back(temp_2d);
        temp_2d.clear();
    }
    return ret_val;
}
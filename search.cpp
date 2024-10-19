#include "headers.h"

string search(string file_name, string dir){
    struct dirent *myfile;
    DIR *mydir;
    int flag=0;
    mydir=opendir(dir.c_str());

    if (mydir == NULL){
        perror("Error opening directory");
        return "False";
    }

    while ((myfile = readdir(mydir)) != NULL){
        if(strcmp(myfile->d_name, ".") == 0 || strcmp(myfile->d_name, "..") == 0){
            continue;
        }

        string dir_path = dir + "/" + myfile->d_name;

        if(myfile->d_type == DT_DIR){ // Check if it's a directory
            if(search(file_name , dir_path) == "True") {
                closedir(mydir);
                return "True";
            }
        }

        else if(myfile->d_name == file_name){
            flag = 1;
            return "True";
        }
    }
    if(flag == 0)
        return "False";
}
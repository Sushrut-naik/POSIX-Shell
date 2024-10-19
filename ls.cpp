#include "headers.h"
using namespace std;

void printl(char* dir, int hidden_flag=0){

// cout << hidden_flag << endl;
// return;
    struct passwd *pw;
    struct group *grp;
    long long int total_blocks = 0;
    DIR *mydir;
    DIR *total_count;
    char *c;
    int i;
    string total_dir = dir;
    struct dirent *myfile;
    struct stat file_stat;
    mydir=opendir(dir);
    if (mydir == NULL){
        perror("Error opening directory");
        return;
    }
    
    printf("\n%s\n", dir);

    while((myfile=readdir(mydir))!=NULL){
        string fileWithPath = string(dir) + "/" + myfile->d_name;
        if(hidden_flag == 0){          
            if(myfile->d_name[0] != '.'){
                stat(fileWithPath.c_str(),&file_stat);  
            }
            else
                continue;
        }
        else{
            stat(fileWithPath.c_str(),&file_stat);
        }

        total_blocks += file_stat.st_blocks / 2;
    }

    cout<<"total "<<total_blocks<<endl;
    mydir=opendir(dir);

    if(hidden_flag == 0){
        while((myfile=readdir(mydir))){

            if(myfile->d_name[0] != '.'){

                string fileWithPath = string(dir) + "/" + myfile->d_name;

                stat(fileWithPath.c_str(), &file_stat); 
                
                cout<<((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
                cout<<((file_stat.st_mode & S_IRUSR) ? "r" : "-");
                cout<<((file_stat.st_mode & S_IWUSR) ? "w" : "-");
                cout<<((file_stat.st_mode & S_IXUSR) ? "x" : "-");
                cout<<((file_stat.st_mode & S_IRGRP) ? "r" : "-");
                cout<<((file_stat.st_mode & S_IWGRP) ? "w" : "-");
                cout<<((file_stat.st_mode & S_IXGRP) ? "x" : "-");
                cout<<((file_stat.st_mode & S_IROTH) ? "r" : "-");
                cout<<((file_stat.st_mode & S_IWOTH) ? "w" : "-");
                cout<<((file_stat.st_mode & S_IXOTH) ? "x" : "-");
                cout<<" ";
                cout<<file_stat.st_nlink;
                cout<<" ";
                pw=getpwuid(file_stat.st_uid);
                cout<<pw->pw_name;
                cout<<" ";
                grp=getgrgid(file_stat.st_gid);
                cout<<grp->gr_name;
                cout<<" ";
                cout<<file_stat.st_size;
                cout<<"\t";
                c=ctime(&file_stat.st_mtime);
                for(i=4;i<=15;i++)
                    cout<<c[i];
                cout<<" ";
                cout<<myfile->d_name<<endl; 
            }
        }
        closedir(mydir);
    }
    else{
        while((myfile=readdir(mydir))!=NULL){   
            string fileWithPath = string(dir) + "/" + myfile->d_name;                    
            stat(fileWithPath.c_str(),&file_stat);

            cout<<((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
            cout<<((file_stat.st_mode & S_IRUSR) ? "r" : "-");
            cout<<((file_stat.st_mode & S_IWUSR) ? "w" : "-");
            cout<<((file_stat.st_mode & S_IXUSR) ? "x" : "-");
            cout<<((file_stat.st_mode & S_IRGRP) ? "r" : "-");
            cout<<((file_stat.st_mode & S_IWGRP) ? "w" : "-");
            cout<<((file_stat.st_mode & S_IXGRP) ? "x" : "-");
            cout<<((file_stat.st_mode & S_IROTH) ? "r" : "-");
            cout<<((file_stat.st_mode & S_IWOTH) ? "w" : "-");
            cout<<((file_stat.st_mode & S_IXOTH) ? "x" : "-");
            cout<<" ";
            cout<<file_stat.st_nlink;
            cout<<" ";
            pw=getpwuid(file_stat.st_uid);
            cout<<pw->pw_name;
            cout<<" ";
            grp=getgrgid(file_stat.st_gid);
            cout<<grp->gr_name;
            cout<<" ";
            cout<<file_stat.st_size;
            cout<<"\t";
            c=ctime(&file_stat.st_mtime);
            for(i=4;i<=15;i++)
                cout<<c[i];
            cout<<" ";
            cout<<myfile->d_name<<endl; 
        }
        closedir(mydir);
    }
}

string is_al(vector<string> input){
    int lflag=0, aflag=0;
    
    for(int i=1; i<input.size(); i++){
        if(input[i] == "-a"){
            aflag=1;
        }
        if(input[i] == "-l"){
            lflag=1;
        }
        if(input[i] == "-la"){
            aflag=1;
            lflag=1;
        }
        if(input[i] == "-al"){
            aflag=1;
            lflag=1;
        }        
    }

    if(lflag && aflag){
        return "al";
    }
    else if(lflag==1 && aflag==0){
        return "l";
    }
    else if(lflag==0 && aflag==1){
        return "a";
    }
    else{
        return "noflag";
    }
}

void ls(vector<string> input){
    struct dirent *files;

    if(input.size() == 2 && input[1] == "~"){
        char *home = getenv("NEW_HOME");
        DIR *dir = opendir(home);
        if (dir == NULL){
            perror("Error opening directory");
            return;
        }
        while ((files = readdir(dir)) != NULL){
            if(files->d_name[0] != '.')
                cout<<files->d_name<<endl;
        }
        closedir(dir);
    }

    else if(is_al(input) == "al"){
        int flag = 0;
        if(input.size() <= 3){
            if(input.size() == 2){
                if(input[1] == "-al" || input[1] == "-la"){
                    printl(".", 1);
                    flag = 1;
                }
            }
            else if(input.size() == 3){
                if((input[1] == "-a" && input[2] == "-l") || (input[1] == "-l" && input[2] == "-a")){
                    printl(".", 1);
                    flag = 1;
                }
            }
        }
        for(int i=1; i<input.size(); i++){
            if(flag == 0){
                if(input[i] != "-a" && input[i] != "-l" && input[i] != "-al" && input[i] != "-la"){
                    char* temp_cstr = new char[input[i].length() + 1];
                    strcpy(temp_cstr, input[i].c_str());
                    printl(temp_cstr, 1);
                }
            }
        }        
    }

    else if(is_al(input) == "a"){
        int flag = 0;
        if(input.size() == 2){
            DIR *dir = opendir(".");
            if (dir == NULL){
                perror("Error opening directory");
                return;
            }
            while ((files = readdir(dir)) != NULL){
                cout<<files->d_name<<endl;
            }
            closedir(dir);
            flag = 1;
        }
        for(int i=1; i<input.size(); i++){
            if(flag == 0){
                if(input[i] != "-a" && input[i] != "-l" && input[i] != "-al" && input[i] != "-la"){
                    char* temp_cstr = new char[input[i].length() + 1];
                    strcpy(temp_cstr, input[i].c_str());
                    DIR *dir = opendir(temp_cstr);
                    if (dir == NULL){
                        perror("Error opening directory");
                        return;
                    }
                    while ((files = readdir(dir)) != NULL){
                        cout<<files->d_name<<endl;
                    }
                    closedir(dir);
                }
            }
        }
    }

    else if(is_al(input) == "l"){
        int flag = 0;
        if(input.size() == 2){
            printl(".", 0);
            flag = 1;
        }
        for(int i=1; i<input.size(); i++){
            if(flag == 0){
                if(input[i] != "-a" && input[i] != "-l" && input[i] != "-al" && input[i] != "-la"){
                    char* temp_cstr = new char[input[i].length() + 1];
                    strcpy(temp_cstr, input[i].c_str());
                    printl(temp_cstr, 0);
                }
            }
        }
    }

    else if(is_al(input) == "noflag"){
        int flag = 0;
        if(input.size() == 1){
            DIR *dir = opendir(".");
            if (dir == NULL){
                perror("Error opening directory");
                return;
            }
            while ((files = readdir(dir)) != NULL){
                if(files->d_name[0] != '.')
                    cout<<files->d_name<<endl;
            }
            closedir(dir);
        }
        else{
            for(int i=1; i<input.size(); i++){
                if(flag == 0){
                    if(input[i] != "-a" && input[i] != "-l" && input[i] != "-al" && input[i] != "-la"){
                        char* temp_cstr = new char[input[i].length() + 1];
                        strcpy(temp_cstr, input[i].c_str());
                        DIR *dir = opendir(temp_cstr);
                        if (dir == NULL){
                            perror("Error opening directory");
                            return;
                        }
                        while ((files = readdir(dir)) != NULL){
                            if(files->d_name[0] != '.')
                                cout<<files->d_name<<endl;
                        }
                        closedir(dir);
                    }
                }
            }
        }
    }    
}
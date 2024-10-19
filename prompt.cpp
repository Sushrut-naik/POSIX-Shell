#include "headers.h"
using namespace std;

int is_home(char *directory) {
    char* home_directory = getenv("NEW_HOME");
    if(strcmp(home_directory, directory) == 0){
        return 1;
    }
    else{
        return 0;
    }
}

// --------------------storing old_pwd is still remaining---------------------------------

void display_prompt(){
    struct utsname username;
    char hostbuffer[256];
    char cwd[256], home_dir[256];
    uname(&username);
    uid_t uid = getuid();
    struct passwd *userInfo = getpwuid(uid);

    if (getcwd(cwd, sizeof(cwd)) == NULL)
        perror("getcwd() error");


    if(is_home(cwd)){
        cout<<userInfo->pw_name<<"@"<<username.nodename<<":~>";
    }
    else{
        cout<<userInfo->pw_name<<"@"<<username.nodename<<":"<<cwd<<">";
    }
}
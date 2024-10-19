#include "headers.h"
using namespace std;
void pwd(){
    char cwd[256];
    getcwd(cwd,sizeof(cwd));
    cout<<cwd<<endl;
}
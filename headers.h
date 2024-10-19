#ifndef HEADER_H
#define HEADER_H

#include<unistd.h>
#include<iostream>
#include<sys/utsname.h>
#include<cstring>
#include<string>
#include<pwd.h>
#include<vector>
#include<bits/stdc++.h>
#include<sys/syscall.h>
#include<dirent.h>
#include<time.h>
#include<grp.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<regex>
#include<fcntl.h>
#include<stdio.h>
#include<signal.h>
#include<cstdlib>
#include<fstream>

using namespace std;

extern int track_pid;
extern int old_dir;
extern vector<string> hist_comm_list;

void pwd();
void display_prompt();
vector<vector<string>> parse_input();
void cmd_handler(vector<string>);
void change_dir(vector<string>);
void ls(vector<string>);
void run_in_background(vector<string>, int);
void get_pinfo(int);
string search(string, string);
void redirection_handler(vector<string>);
void pipe_handler(vector<string>);
void handle_ctrl_z(int);
void handle_ctrl_c(int);
void init_history();
void write_history();
void record_command(string);
void history(int);
  
#endif
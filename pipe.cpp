#include "headers.h"

void pipe_handler(vector<string> input)
{
	int fd[2];
	pid_t pid;
	int fdd = 0;
    string curr_command = "";
    int temp = 0;
    vector<string> command_list;
    for(int i=0; i<input.size(); i++){
        if(i == input.size()-1){
            for(int j=temp; j<=i; j++){
                curr_command += input[j];
                curr_command += " ";
            }
        }
        if(input[i] == "|"){
            for(int j=temp; j<i; j++){
                curr_command += input[j];
                curr_command += " ";
            }
            temp = i+1;
        }
        
        if(curr_command != ""){
            command_list.push_back(curr_command);
        }
        curr_command = "";
    }

    int i=0;
	while (i < command_list.size()) {
		pipe(fd);
		if ((pid = fork()) == -1) {
			perror("fork");
			exit(1);
		}
		else if (pid == 0) {
			dup2(fdd, 0);
			if (i != command_list.size()-1) {
				dup2(fd[1], 1);
			}
			close(fd[0]);

            char* temp_cstr = new char[command_list[i].length() + 1];
            char* tok;
            string placeholder;
            vector<string> tokenized;
            strcpy(temp_cstr, command_list[i].c_str());
            tok = strtok (temp_cstr," ");

            while (tok != NULL)
            {
                placeholder = tok;
                tokenized.push_back(placeholder);
                tok = strtok (NULL, " ");
            }

            // int comm_size = tokenized[i].size()+1;
            // char *comm[comm_size];

            // for(int j=0; j<tokenized[i].size(); j++){
            //     comm[j] = const_cast<char*>(tokenized[j].c_str());
            // }

            // comm[comm_size-1] = NULL;

            int redir = 0;
            for(int i=0; i < tokenized.size(); i++){
                if(tokenized[i] == "<" || tokenized[i] == ">" || tokenized[i] == ">>"){
                    redir = 1;
                    break;
                }
            }

            if(redir){
                redirection_handler(tokenized);
            }
            else{
                cmd_handler(tokenized);
            }

            
            // cout<<"Passing command "<<comm[0]<<endl;
			// execvp(comm[0], comm);
			exit(1);
		}
		else {
			wait(NULL);
			close(fd[1]);
			fdd = fd[0];
			i++;
		}
	}
}



// {
    
//     int temp = 0;
//     string curr_command = "";
//     vector<string> command_list;
//     for(int i=0; i<input.size(); i++){
//         if(i == input.size()-1){
//             for(int j=temp; j<=i; j++){
//                 curr_command += input[j];
//                 curr_command += " ";
//             }
//         }
//         if(input[i] == "|"){
//             for(int j=temp; j<i; j++){
//                 curr_command += input[j];
//                 curr_command += " ";
//             }
//             // cout<<"curr_command is"<<curr_command<<endl;
//             temp = i+1;
//         }
        
//         if(curr_command != ""){
//             command_list.push_back(curr_command);
//         }
//         curr_command = "";
//     }
//     int num_of_cmds = command_list.size();

//     int pipefds[num_of_cmds-1][2]; // Create pipes
//     int og_stdout = dup(1);
//     int og_stdin = dup(0);
//     // Create processes and set up pipes
//     for(int i = 0; i < num_of_cmds; ++i){
//         if (i < num_of_cmds - 1){
//             if (pipe(pipefds[i]) == -1){
//                 perror("pipe");
//                 return;
//             }
//         }

//         pid_t pid = fork();
//         if (pid == -1) {
//             perror("fork");
//             return;
//         }

//         if (pid == 0){ // Child process
//             if (i == num_of_cmds-1 || i != 0){
//                 // Close read end of previous pipe
//                 close(pipefds[i - 1][1]);
//                 // Redirect stdin to the read end of the previous pipe
//                 dup2(pipefds[i - 1][0], STDIN_FILENO);
//                 close(pipefds[i - 1][0]);
//             }

//             if (i == 0 || i < num_of_cmds-1){
//                 // Close write end of current pipe
//                 close(pipefds[i][0]);
//                 // Redirect stdout to the write end of the current pipe
//                 dup2(pipefds[i][1], STDOUT_FILENO);
//                 close(pipefds[i][1]);
//             }

//             if(i == num_of_cmds-1){
//                 cout<<"Last pipe\n";
//                 if(dup2(og_stdout, STDOUT_FILENO) == -1){
//                     perror("Error restoring stdout");
//                     return;
//                 }
//                 if(dup2(og_stdin, STDIN_FILENO) == -1){
//                     perror("Error restoring stdin");
//                     return;
//                 }
//             }

//             // Execute the command
//             char* command = const_cast<char*>(command_list[i].c_str());
//             char* temp_cstr = new char[command_list[i].length() + 1];
//             char* tok;
//             string placeholder;
//             vector<string> tokenized;
//             strcpy(temp_cstr, command_list[i].c_str());
//             tok = strtok (temp_cstr," ");

//             while (tok != NULL)
//             {
//                 placeholder = tok;
//                 tokenized.push_back(placeholder);
//                 tok = strtok (NULL, " ");
//             }

//             cmd_handler(tokenized);            
//             // char* args[] = {command, nullptr};
//             // cout<<"command is\n";
//             // cout<<command<<endl;
//             // if(execvp(command, args) < 0){   
//             //     perror("execvp"); // This line will be reached if execvp fails
//             //     return;
//             // }
//         }
//     }

//     // Close all pipe ends in the parent process
//     for (int i = 0; i < num_of_cmds - 1; ++i) {
//         close(pipefds[i][0]);
//         close(pipefds[i][1]);
//     }

//     if(dup2(og_stdout, STDOUT_FILENO) == -1){
//         perror("Error restoring stdout");
//         return;
//     }
//     if(dup2(og_stdin, STDIN_FILENO) == -1){
//         perror("Error restoring stdin");
//         return;
//     }        

//     // Wait for all child processes to finish
//     for (int i = 0; i < num_of_cmds; ++i) {
//         wait(nullptr);
//     }

//     return;
// }
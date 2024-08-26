#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include <stddef.h>





void execute_line(char* line) {
  char* args[MAXARG];
  int num_args = 0;

  // Parse the command
  char* token = line;
  while (*line) {
    if (*line == ' ' || *line == '\t' || *line == '\n') {
      *line = '\0'; 
      if (token != line) {
        args[num_args] = token;
        num_args++;
      }
      token = line + 1;  
    }
    line++;
  }
  if (token != line) {
    args[num_args] = token;
    num_args++;
  }
  


  if ( num_args > 0 && strcmp(args[0], "exit") == 0 ) {
    if (num_args==1)
        exit(0); // no errors
  }
  if ( num_args > 0 && strcmp(args[0], "cd") == 0 ) {
    // Handle the cd command 
    if (num_args != 2) {
      fprintf(2, "Usage: cd <directory>\n");
    }   
    else {
      if (chdir(args[1]) < 0) {
        fprintf(2, "cd: cannot change directory to %s\n", args[1]);
      }
     
    }
  }
  else
   {
    char* filename = 0;
    int file_mode = -1;
    int p[2];
    int pointer=0;
    for (int i=0; i < num_args; i++){
      if (strcmp(args[i], "<") == 0){
        file_mode = 1;
        filename = args[i+1];
        args[i] = 0;
        args[i+1] = 0;
        break;
      }

      if (strcmp(args[i], ">") == 0){
        file_mode = 2;
        filename = args[i+1];
        args[i] = 0;
        args[i+1] = 0;
        break;
      }

      if (strcmp(args[i], "|")== 0){
        file_mode = 3;
        pointer =i ;
        pipe(p);
      }
    }
  
  
    int pid = fork();
    if (pid < 0) {
      fprintf(2, "fork failed\n");
      exit(1);
    } 
    else if (pid == 0) 
    {
      // Child process
      if (num_args > 0) 
        {  
          const char *command = args[0];
          if(file_mode==1)
            { 
              close(0);
              open(filename, O_RDONLY);
            }
          else if(file_mode==2)
            {
              close(1);
              open(filename, O_CREATE | O_WRONLY);
            }

          else if(file_mode==3)
            {   
                command = args[0];
                printf("command %s\n", command);
                char* new_args[MAXARG];
                printf("args 1 %s\n", args[0]);
                printf("args 2 %s\n", args[1]);
                for (int i = 0; i < pointer; i++) {
                  new_args[i]= args[i];
                }
                close(1);
                dup(p[1]);
                close(p[1]);
                close(p[0]);
                exec(command, new_args);
                fprintf(2, "exec failed for command: %s\n", command);
                // exit(1);
            }
              exec(command, args);
              fprintf(2, "exec failed for command: %s\n", command);
              exit(1);
          }
      
      else 
        {
          fprintf(2, "No command provided.\n");
          exit(1);
        }
  }
   
  else {
    // Parent process
    
    if(file_mode==3)
      { 
        const char *command = args[pointer+1];
        char* new_args[MAXARG];
          
        for (int i = pointer+1, j=0; i < num_args; i++, j++) {
            new_args[j]= args[i];
           
            }
      
        close(0); // closes std_in and make fd 0 refer to read end
        dup(p[0]);
        close(p[0]); // closes file descriptors p - for parent
        close(p[1]);
        exec(command, new_args);                
        fprintf(2, "exec failed for command: %s\n", command);
        // exit(1);
      }
      wait(0);
    
  }
 
  }
  
}
  



void main(int argc, char *argv[]) {

  if(argc != 1) {
    fprintf(2, "my_shell takes no arguments");
    exit(1);
  }

  
  while (1)
  {
    char line[512];
  
    printf(">>> ");
    gets(line, 512);
    execute_line(line);
    memset(line, 0, 512);

  }
   exit(1);
}
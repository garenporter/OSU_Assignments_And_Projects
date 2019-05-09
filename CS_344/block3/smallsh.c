#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/fcntl.h>

int background_procs[1000]; //arry that holds the current background processes
int back_num = 0; // current number of background processes
int num_args = 0; // number of user arguments
int background = 0; // true/false of whether or not given command should be background process
int last_foreground = 0; // holds the pid of last forground process
int current_foreground = -1; // pid of the current foreground process
int fgrnd_only = 0; // boolean for foreground-only mode
int term_by_sig = 0; // boolean for temination by signal
char* in_file = '\0'; //input file, if specified
char* out_file = '\0'; //output file, if specified
char* args_redir[512]; //array of strings before > or <
int redir_input = 0; //true/false for if input is being redirected

//following function tokenizes user input into array of arguments
char** split_line(char* line){

    num_args = 0; //resets number of user arguments to 0
    int bufsize = 512; //max number of arguments
    int position = 0; // current position in argument array
    char** tokens = malloc(bufsize * sizeof(char*)); //allocate argument array
    char* token; //variable to hold tokenized string

    if(!tokens){ //check for bad allocation
        fprintf(stderr, "allocation error\n");
        exit(1);
    }

    token = strtok(line, " \t\r\n\a"); // tokenize the user input
    while(token != NULL){ //while still reading valid characters, fill tokens array with each string
        tokens[position] = token; //add token to tokens array
        if(position > 0){
          if(strcmp(tokens[position-1], "<") == 0) //if < is read, make next argument input file
            in_file = tokens[position];

          else if(strcmp(tokens[position-1], ">") == 0) //if > is read, make next argument output file
            out_file = tokens[position];
        }
        if(strcmp(tokens[position], ">") == 0 || strcmp(tokens[position], "<") ==0)
          redir_input = 1;

        if(redir_input == 0) // if >/< has not been read yet, add token to args_redir
          args_redir[position] = token;

        position++;
        num_args++;

        if(position >= bufsize){ //if the number of arguments ever exceeds max, reallocate
            bufsize += 512;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if(!tokens){ //check for reallocation error
                fprintf(stderr, "allocation error\n");
                exit(1);
            }
        }

        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[position] = NULL; //last array element gets NULL
    return tokens; //return token array
}

//following function is the implementation for the status command
void shell_status(){
  if(term_by_sig == 0) //if not terminated by signal...
    printf("exit value %d\n", last_foreground);
  else //if terminated by signal
    printf("terminated by signal %d\n", last_foreground);
  term_by_sig = 0; //reset to 0
  last_foreground = 0; //reset to 0
}

//implementation for the cd function
void shell_cd(char* new_dir){

    char cwd[1024]; //holds current working directory

    if(getcwd(cwd, sizeof(cwd)) == NULL) //checking for successful cwd
       printf("Error changing directory\n");

   chdir(new_dir); //change the directory

   if(getcwd(new_dir, sizeof(cwd)) != NULL){ //check for successful cwd

        last_foreground = 0;
   }
    else
        printf("Error changing directory\n");


}

//exits the shell and performs cleanup
void shell_exit(){


    exit(0); //exit the shell with status 0
}

//checks if the user input should be ran in the background
int is_background(char** args){

    if(strcmp(args[num_args-1], "&") == 0){ //if last argument is &...
      return 1; // return true
    }

    return 0; //return false
}

//function for cleaning up zombie processes that were ran in the background
void clean_background(){


  int i;
  pid_t wpid;
  int status, pid;
  fflush(stdout);
  for(i=0; i<back_num; i++){ //for each background process...
    if(background_procs[i] != 0){ //if pid is not 0...

      pid = background_procs[i];
      wpid = waitpid(pid, &status, WNOHANG); //wait with nohang, which will clean the process if it is a zombie
    }
    if(kill(pid, 0) != 0) { //if process does not exist anymore (it was cleaned)
      printf("background pid %d is done: exit value %d\n", pid, status); // notify user
      fflush(stdout);
      background_procs[i] = 0;
    }
  }
}

//calls whatever command user gives if it is not status, exit, or cd
int shell_exec(char** args){
    pid_t pid, wpid;
    int status, r1, r2, r3, r4, r5;


    pid = fork(); // fork off child

    if(is_background(args) == 1){ //if background process, set last argument to NULL
        background = 1;
        args_redir[num_args-1] = NULL;
    }
    //printf("out_file: %s\nin_file: %s\n", out_file, in_file);
    if(pid == 0){ //child process functionality
      int dev_null = open("/dev/null", O_WRONLY); //make a fd to point to /dev/null
      if(out_file != '\0'){ // if out_file has been specified
        int fd_o = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644); //open specified file for writing
        if(fd_o == -1){
          write(1, "Error opening file\n", 20); //print error if file cannot be opened
        }
        else
          r1 = dup2(fd_o, 1); //redirect stdout
      }
      if(in_file != '\0'){ //if in_file has been specified
        int fd_i = open(in_file, O_RDONLY); //open up specified file for reading
        if(fd_i == -1)
          write(1, "Error opening file\n", 20); //print error if file cannot be opened
        else
          r2 = dup2(fd_i, 0); //redirect stdin
      }
      if(background == 1 && fgrnd_only == 0) //if it's a background process and foreground-only is off
           r3 = dup2(dev_null, 1); //redirect stdout to dev_null
      else if(background == 1 && in_file == '\0' && fgrnd_only == 0){ //if it's a background process and in_file has been specified and foreground-only is off
           r4 = dup2(dev_null, 1); //redirect stdout to dev_null
           r5 = dup2(dev_null, 0); //redirect stdin to dev_null
      }
      //  if(execvp(args[0], args) == -1){ //run exec() on arguments, if it is not successful, print error
          if(execvp(args_redir[0], args_redir) == -1){
          printf("error in exec()\n");
          //printf("args[0]: %s\n", args[0]);
          exit(1);
        }
    }
    else if(pid <0) { //if fork() error, notify user
        printf("error forking\n");
    }
    else{

        if(background == 1 && fgrnd_only == 0){ // if process is specified as background and foreground-only mode is disabled

            wpid = waitpid(pid, &status, WNOHANG); //wait with nohang
            background_procs[back_num] = pid; // add pid to background pid array
            back_num++; //increment number of running background processes

            printf("background pid is %d\n", pid); // notify user background pid
            background = 0;

        }
        else{ //else run process as foreground process
            current_foreground = pid; // set current foregounf pid
            do{
                wpid = waitpid(pid, &status, WUNTRACED); //wait for child to finish executing
            }
            while (!WIFEXITED(status) && !WIFSIGNALED(status)); //while the process has not been terminated
            if(WIFSIGNALED(status) == 1){ //if child was killed by signal..
              last_foreground = WTERMSIG(status); //set last_foreground to the signal number
              term_by_sig = 1; //set terminated by signal to true
            }
            else
              last_foreground = WEXITSTATUS(status); //set last foreground to the exit status
        }
        current_foreground = 0;
    }
    //reset variables
    redir_input = 0;
    background = 0;
    in_file = '\0';
    out_file = '\0';
    return 1;

}

//signal handler for SIGTSTP
void catch_SIGTSTP(int signo){

  if(fgrnd_only == 1){ //if already in foreground-only mode...
    write(1, "\nExiting foreground-only mode\n", 31); //notify user that they are exiting foreground-only mode
    write(1, ": ", 2);
    fflush(stdout);
    fgrnd_only = 0; //set foreground-only mode back to false
  }
  else{ //else user is not in foreground-only mode, notify them that they are entering foreground-only mode
    write(1, "\nentering foreground-only mode (& is now ignored)\n", 50);
    write(1, ": ", 2);
    fflush(stdout);
    fgrnd_only = 1; //set foreground-only mode to true
  }

}

//signal handler fpr SIGINT
void catch_SIGINT(int signo){

  if(current_foreground != 0){ // if there is a foreground process running
    kill(current_foreground, SIGINT); //send the SIGINT signal to the process
    write(1, "terminated by signal 2\n", 24);
    fflush(stdout);
    current_foreground = 0; //set current_foreground back to 0
  }
  else{ // do nothing if there is no foreground process running
    write(1, "\n: ", 4);
    fflush(stdout);
  }
}

//function to replace all instances of "$$" with pid
void str_replace(char *string, char *search, char *replace){
   char buffer[2048];
   char*p = string;
   while((p=strstr(p, search))){
       strncpy(buffer, string, p-string);
       buffer[p-string] = '\0';
       strcat(buffer, replace);
       strcat(buffer, p+strlen(search));
       strcpy(string, buffer);
       p++;
   }
}
int main(int argc, char **argv){

    //following 3 lines gets the pid of the shell and turns it into a string
    int id = getpid();
    char ids[10];
    sprintf(ids,"%d", id);

    memset(background_procs, 0, sizeof(background_procs)); //set background_procs array to all 0s
    struct sigaction SIGINT_action = {0}, SIGTSTP_action = {0}; //create 2 sigaction structs, one for each signal i need to handle

    SIGINT_action.sa_handler = catch_SIGINT; //set handler to appropriate function
    sigfillset(&SIGINT_action.sa_mask); //add sa.mask
    SIGINT_action.sa_flags = SA_RESTART; //set flag to SA_RESTART so that getline can work

    //the following 3 lines are the same as the previous 3 lines, but for SIGTSTP
    SIGTSTP_action.sa_handler = catch_SIGTSTP;
    sigfillset(&SIGTSTP_action.sa_mask);
    SIGTSTP_action.sa_flags = SA_RESTART;

    //call sigaction() on each Signal with its appropriate signal handler
    sigaction(SIGINT, &SIGINT_action, NULL);
    sigaction(SIGTSTP, &SIGTSTP_action, NULL);

    //main while loop for grabbing, parsing, and processing user input
    while(1){

        memset(args_redir, '\0', sizeof(args_redir));
        clean_background(); //look for and clean up an zombie children
        size_t input_read, input_size; //values for getline
        char* input; //string to hold user input
        char** input_args; //string to hold each indevidual input argument
        input_size = 2048; //max number of input characters
        input = (char *) malloc(input_size+1); //allocate space for the input

        while(1){ //while input is bad
          write(1, ": ", 2); //shell input prompt
          input_read = getline(&input, &input_size, stdin); //get user input
          if(input_read == -1 || input_read == 0) //check for getline error or empty input
            clearerr(stdin);
          else
            break; //break if input is valid
          }
        str_replace(input, "$$", ids); //replace all instances of "$$" with shell's pid
        input_args = split_line(input); //split user input into indevidual arguments

        if(strcmp(input_args[0], "exit") == 0){ //check if command is exit

            shell_exit(); //call exit function
        }
        //if user input was status, call status
        else if(strcmp(input_args[0], "status") == 0){
          shell_status();
        }
        //if user input was cd, call cd
        else if(strcmp(input_args[0], "cd") == 0){ //check if command is cd
                shell_cd(input_args[1]); //call shell_cd function with second user argument as input
        }
        //if user input was #, treat line as a comment
        else if(input[0] == '#'){
          //do nothing
         // printf("%s\n", input);
        }
        //else call exec on whatever the user gave as input
        else{ // run the given command through exec()
            shell_exec(input_args);

        }

    free(input); //free the memory allocated by input
    }
    return 0;
}

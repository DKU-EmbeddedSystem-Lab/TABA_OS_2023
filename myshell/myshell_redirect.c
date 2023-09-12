#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MAX_PATH 1024

struct COMMAND{
        char* name;
		char* desc;
		int (*func )( int argc, char* argv[]);
};

int cmd_cd(int argc, char* argv[]);
int cmd_help(int argc, char* argv[]);
int cmd_exit( int argc, char* argv[]);
int tokenize( char* buf, char* delims, char* tokens[], int maxTokens);
int run(char* line);

struct COMMAND builtin_cmds[]={
		{ "cd", "change directory", cmd_cd}, 
		{"exit", "exit this shell", cmd_exit },
        {"quit", "quit this shell",cmd_exit },
        {"help", "show this help",cmd_help},
        { "?","show this help", cmd_help}
};

int main(void)
{
	char line[MAX_PATH];
    char currentDir[MAX_PATH];

	while(1){
        if (getcwd(currentDir, sizeof(currentDir)) == NULL) {
            perror("getcwd() error");
            return 0;
        }

		printf("%s $", currentDir);     // Hint. Where are you?
		fgets( line, sizeof(line) - 1, stdin);
		if(run(line) == -1)
			break;
	}
	return 0;
}

int cmd_cd(int argc, char* argv[]) {
    if (argc == 1)
        chdir(getenv("HOME"));
    else if (argc == 2) {
        if (chdir(argv[1]))
            printf("USAGE: cd [dir]\n");
    } else
        printf("No directory\n");
    return 1;
}

int cmd_exit( int argc, char* argv[]){
		return -1;
}

int cmd_help(int argc, char* argv[]) {
    int i;
    for (i = 0; i < sizeof(builtin_cmds) / sizeof(struct COMMAND); i++) {
        if (argc == 1 || strcmp(builtin_cmds[i].name, argv[1]) == 0)
            printf("%-10s: %s\n", builtin_cmds[i].name, builtin_cmds[i].desc);
    }
    return 1; 
}

int execute_builtin_command(char* tokens[], int token_count) {
    int i;
    for (i = 0; i < sizeof(builtin_cmds) / sizeof(struct COMMAND); i++) {
        if (strcmp(builtin_cmds[i].name, tokens[0]) == 0)  
            return builtin_cmds[i].func(token_count, tokens);
    }
    return 0;
}

int tokenize(char* buf, char* delims, char* tokens[], int maxTokens) {
    int token_count = 0;
    char* token = strtok(buf, delims);
    while (token != NULL && token_count < maxTokens) {
        tokens[token_count] = token;
        token_count++;
        token = strtok(NULL, delims);
    }
    tokens[token_count] = NULL;
    return token_count;
}

bool check_for_background(char* tokens[], int token_count) {
    if (strcmp(tokens[token_count - 1], "&") == 0) {
        tokens[token_count - 1] = NULL; // Nullify the background token
        return true;
    }
    return false;
}

int handle_redirection(char* tokens[], int token_count) {
    int i;
    int fd_out = 0;

    for (i = 0; i < token_count; i++) {
        if (strcmp(tokens[i], ">") == 0) {
            if (i == token_count - 1) {
                printf("Error: No redirection file specified.\n");
                return -1;  
            }
            fd_out = open(tokens[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out == -1) {
                perror("Error opening file for redirection");
                return -1;  
            }
            tokens[i] = NULL;  
            break;
        }
    }
    
    return fd_out;
}

int run(char* line) {
    char delims[] = " \r\n\t";
    char* tokens[128];
    int token_count;
    int i;
    int status;
    pid_t child;
    int built_in = 1;

    token_count = tokenize(line, delims, tokens, sizeof(tokens) / sizeof(char*));

    if (token_count == 0)
        return 1;

    if ((built_in = execute_builtin_command(tokens, token_count)) != 0)
        return built_in;

    bool is_background = check_for_background(tokens, token_count);

	int fd_out = handle_redirection(tokens, token_count);
    if (fd_out == -1) {
        return true;
    }

	// Run process
    child = fork();
	if (child < 0){
		printf("Failed to fork()!");
		_exit(0);
	}

    if (child == 0) {
		// Redirection
		if (fd_out != -1) {
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }

        execvp(tokens[0], tokens);
        printf("No such file\n");
        _exit(0);
    } else{
        if (!is_background) {  // Only wait if not a background task
			while (wait(NULL) > 0); 
			// waitpid(child, &status, 0);
        } else {
            printf("[BG] %d\n", child); // print the child process ID
        }
	}
	return 1;
}

#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>

/* Constants */
#define PROMPT "hsh$ "
#define TOKEN_DELIMS " \t\r\n\a"

/* Accès à l’environnement */
extern char **environ;

/* ==== loop.c ==== */
/* Boucle principale du shell */
int shell_loop(void);

/* ==== input.c ==== */
char *read_input(void);
void print_prompt(void);
int is_interactive(void);

/* ==== parse.c ==== */
char **tokenize(char *line);
size_t count_tokens(const char *line);
void free_tokens(char **argv);

/* ==== execute.c ==== */
int execute_command(char **argv, int *exit_shell, int *exit_status);
pid_t launch_process(const char *path, char **argv, char **envp, int *status);

/* ==== path.c ==== */
char *resolve_path(const char *cmd);
int is_executable(const char *path);
char *join_path(const char *dir, const char *cmd);

/* ==== builtins.c ==== */
int is_builtin(const char *cmd);
int run_builtin(char **argv, int *exit_shell, int *exit_status);

/* ==== builtin_exit.c ==== */
int bi_exit(char **argv, int *exit_shell, int *exit_status);

/* ==== builtin_env.c ==== */
int bi_env(char **argv, int *exit_status);

/* ==== signals.c ==== */
void setup_signals(void);
void sigint_handler(int signo);

/* ==== errors.c ==== */
void print_error(const char *prog, int line_no,
const char *cmd, const char *msg);
void perror_cmd(const char *prog);

/* ==== memory.c ==== */
void *xmalloc(size_t size);
void *xrealloc(void *ptr, size_t size);
void free_null_terminated(char **arr);

#endif

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

/* Structures utilitaires (ex: table des builtins) */
typedef int (*builtin_fn)(char **argv, int *exit_status);
typedef struct builtin_s {
    const char *name;
    builtin_fn  func;
} builtin_t;

/* ==== loop.c ==== */
/* Boucle principale du shell */
void shell_loop(void);

/* ==== input.c ==== */
/* Lit une ligne depuis stdin. Retourne un buffer alloué (à free). NULL si EOF/erreur. */
char *read_input(void);
/* Affiche le prompt si mode interactif. */
void print_prompt(void);
/* 1 si stdin est un terminal, 0 sinon. */
int is_interactive(void);

/* ==== parse.c ==== */
/* Tokenise une ligne en argv NULL-terminé (tableau alloué à libérer avec free_tokens). */
char **tokenize(char *line);
/* Compte (sans allouer) le nombre de tokens de 'line'. */
size_t count_tokens(const char *line);
/* Libère un tableau argv NULL-terminé. */
void free_tokens(char **argv);

/* ==== execute.c ==== */
/* Routeur d’exécution : builtins puis commandes externes. 
   Renvoie le code de statut (comme shell). */
int execute_command(char **argv, int *exit_shell, int *exit_status);
/* Lance un binaire via fork/execve; remplit *status avec le code de retour. */
pid_t launch_process(const char *path, char **argv, char **envp, int *status);

/* ==== path.c ==== */
/* Résout un nom de commande via PATH; renvoie chemin alloué (à free) ou NULL. */
char *resolve_path(const char *cmd);
/* Teste si 'path' est exécutable (0 = non, 1 = oui). */
int is_executable(const char *path);
/* Concatène dir + "/" + cmd; renvoie chaîne allouée (à free) ou NULL. */
char *join_path(const char *dir, const char *cmd);

/* ==== builtins.c ==== */
/* Renvoie 1 si cmd est un builtin, 0 sinon. */
int is_builtin(const char *cmd);
/* Exécute le builtin correspondant. Met à jour exit_shell/exit_status si besoin. */
int run_builtin(char **argv, int *exit_shell, int *exit_status);

/* ==== builtin_exit.c ==== */
/* builtin 'exit' : gère l’argument numérique, met *exit_shell=1 et *exit_status. */
int bi_exit(char **argv, int *exit_shell, int *exit_status);

/* ==== builtin_env.c ==== */
/* builtin 'env' : affiche l’environnement actuel; renvoie un code de statut. */
int bi_env(char **argv, int *exit_status);

/* ==== environment helpers (optionnels mais utiles) ==== */
/* Version maison de getenv (renvoie pointeur dans environ, NE PAS free). */
char *_getenv(const char *name);
/* Ajoute/modifie une variable d’environnement (sans setenv). 0=ok, -1=err. */
int _setenv(const char *name, const char *value, int overwrite);
/* Supprime une variable d’environnement (sans unsetenv). 0=ok, -1=err. */
int _unsetenv(const char *name);

/* ==== signals.c ==== */
/* Installe les handlers nécessaires (SIGINT). */
void setup_signals(void);
/* Handler SIGINT : ne pas quitter le shell, réafficher prompt si besoin. */
void sigint_handler(int signo);

/* ==== errors.c ==== */
/* Affiche "prog: n: cmd: message" sur stderr (style hsh). */
void print_error(const char *prog, int line_no, const char *cmd, const char *msg);
/* Affiche via perror avec préfixe "prog". */
void perror_cmd(const char *prog);

/* ==== memory.c ==== */
/* Wrappers sécurisés (optionnels) et utilitaires de libération. */
void *xmalloc(size_t size);
void *xrealloc(void *ptr, size_t size);
/* Libère un tableau NULL-terminé générique. */
void free_null_terminated(char **arr);

#endif /* SIMPLE_SHELL_H */

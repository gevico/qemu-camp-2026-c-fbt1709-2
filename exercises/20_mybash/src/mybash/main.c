#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "common.h"

#define MAX_INPUT 1024
#define MAX_ARGS 64

typedef int (*cmd_func_0_t)(void);
typedef int (*cmd_func_1_t)(const char *);
typedef int (*cmd_func_2_t)(const char *, const char *);

typedef struct {
  const char *name;
  int is_arg_required;
  union {
    cmd_func_0_t func_0;
    cmd_func_1_t func_1;
    cmd_func_2_t func_2;
  } func;
} Command;

Command commands[] = {
    {"myfile", 1, .func.func_1 = __cmd_myfile},
    {"mysed", 2, .func.func_2 = __cmd_mysed},
    {"mytrans", 1, .func.func_1 = __cmd_mytrans},
    {"mywc", 1, .func.func_1 = __cmd_mywc},
    {NULL, 0, .func.func_0 = NULL}};

static void free_args(char **args, int n) {
  for (int j = 0; j < n; j++) {
    free(args[j]);
    args[j] = NULL;
  }
}

void execute_cd(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "mybash: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("mybash");
    }
  }
}

void execute_exit(void) { exit(0); }

int is_builtin_command(char **args) {
  if (args[0] == NULL)
    return 0;

  if (strcmp(args[0], "cd") == 0) {
    execute_cd(args);
    return 1;
  }
  if (strcmp(args[0], "exit") == 0) {
    execute_exit();
  }
  return 0;
}

int parse_input(char *input, char **args) {
  int i = 0;
  int in_quotes = 0;
  char *buf = input;
  char arg_buf[MAX_INPUT];
  int arg_buf_idx = 0;

  memset(arg_buf, 0, sizeof(arg_buf));

  while (*buf != '\0' && i < MAX_ARGS - 1) {
    char c = *buf;

    if (c == '"') {
      in_quotes = !in_quotes;
      buf++;
      continue;
    }

    if (!in_quotes && isspace((unsigned char)c)) {
      if (arg_buf_idx > 0) {
        arg_buf[arg_buf_idx] = '\0';
        args[i++] = strdup(arg_buf);
        arg_buf_idx = 0;
        memset(arg_buf, 0, sizeof(arg_buf));
      }
      buf++;
      continue;
    }

    if (arg_buf_idx < MAX_INPUT - 1)
      arg_buf[arg_buf_idx++] = c;
    buf++;
  }

  if (arg_buf_idx > 0) {
    arg_buf[arg_buf_idx] = '\0';
    args[i++] = strdup(arg_buf);
  }

  args[i] = NULL;
  return i;
}

static void dispatch_command(int argc_parsed, char **args) {
  if (argc_parsed == 0)
    return;

  if (is_builtin_command(args)) {
    return;
  }

  const char *cmd_name = args[0];
  const char *cmd_arg1 = (argc_parsed >= 2) ? args[1] : NULL;
  const char *cmd_arg2 = (argc_parsed >= 3) ? args[2] : NULL;

  printf("cmd_name: %s\n", cmd_name);
  printf("cmd_arg1: %s\n", cmd_arg1 ? cmd_arg1 : "");
  printf("cmd_arg2: %s\n", cmd_arg2 ? cmd_arg2 : "");

  int found = 0;
  for (Command *cmd = commands; cmd->name != NULL; cmd++) {
    if (strcmp(cmd_name, cmd->name) == 0) {
      found = 1;
      if (cmd->is_arg_required == 0) {
        cmd->func.func_0();
      } else if (cmd->is_arg_required == 1) {
        cmd->func.func_1(cmd_arg1);
      } else if (cmd->is_arg_required == 2) {
        cmd->func.func_2(cmd_arg1, cmd_arg2);
      }
      break;
    }
  }

  if (!found) {
    fprintf(stderr, "mybash: command not found: %s\n", cmd_name);
  }
}

int main(int argc, char *argv[]) {
  char input[MAX_INPUT];
  char *args[MAX_ARGS];

  if (argc > 1) {
    const char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (!file) {
      printf("mybash: cannot open file: %s\n", filename);
      return 1;
    }

    printf("mybash: reading commands from file '%s'\n", filename);

    while (fgets(input, sizeof(input), file)) {
      input[strcspn(input, "\n")] = '\0';

      int argc_parsed = parse_input(input, args);

      if (argc_parsed == 0) {
        continue;
      }

      dispatch_command(argc_parsed, args);
      free_args(args, argc_parsed);
    }

    fclose(file);
    return 0;
  }

  while (1) {
    printf("mybash$ ");
    fflush(stdout);

    if (fgets(input, sizeof(input), stdin) == NULL) {
      printf("\n");
      break;
    }

    input[strcspn(input, "\n")] = '\0';

    int n = parse_input(input, args);

    if (n == 0) {
      continue;
    }

    dispatch_command(n, args);
    free_args(args, n);
  }

  return 0;
}

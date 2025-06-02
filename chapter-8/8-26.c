#include <signal.h>
#include <sys/errno.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define	MAXLINE	4096  /* Max text line length */
#define MAXARGS 128
#define SHELLLIMIT 100
#define RUNNING 0
#define STOPPED -1

void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);
void jobs(void);
int addjob(int pid, char *cmdline);
void deletejob(int pid);
void addargv(char *job, char **argv);
void sigint_handler(int sig);
void sigtstp_handler(int sig);
void fg(char **argv);
void bg(char **argv);
void stopjob(int pid);

extern char **environ;
extern int errno;

pid_t PIDS[SHELLLIMIT];
char JOBS[SHELLLIMIT][MAXLINE];
int STATUS[SHELLLIMIT];
pid_t FG;

int main() {
  char cmdline[MAXLINE];
  pid_t pid;
  int status;


  if (signal(SIGINT, sigint_handler) == SIG_ERR) {
    fprintf(stderr, "signal failed");
    exit(1);
  }
  if (signal(SIGTSTP, sigtstp_handler) == SIG_ERR) {
    fprintf(stderr, "signal failed");
    exit(1);
  }

  while (1) {
    while ((pid = waitpid(-1, NULL, WNOHANG)) > 0) {
      deletejob(pid);
    }
    if (errno != ECHILD) {
      printf("waitpid error\n");
    }
    printf("> ");
    if (fgets(cmdline, MAXLINE, stdin) == NULL && ferror(stdin)) {
      fprintf(stderr, "fgets failed\n");
      exit(1);
    }
    eval(cmdline);
    if (FG != 0) {
      waitpid(FG, &status, WUNTRACED);
      if (WIFSIGNALED(status)) {
	if (WTERMSIG(status) == 2)
	  printf("\nJob %d terminated by signal: Interrupt\n", FG);
	else
	  printf("\nJob %d terminated by an unknown signal\n", FG);
	deletejob(FG);
	FG = 0;
	continue;
      }
      if (WIFSTOPPED(status)) {
	printf("\nJob %d stopped by signal: Stopped\n", FG);
	stopjob(FG);
	FG = 0;
	continue;
      }
      if (errno != ECHILD) {
	printf("waitpid error\n");
	exit(1);
      }
      deletejob(FG);
      FG = 0;
    }
  }
}

/* eval - Evaluate a command line */
void eval(char *cmdline) {
  char *argv[MAXARGS];
  char buf[MAXLINE];
  int bg, jid;
  pid_t pid;
  sigset_t mask;

  strcpy(buf, cmdline);
  bg = parseline(buf, argv);
  if (argv[0] == NULL) {
    return;
  }

  if (!builtin_command(argv)) {
    sigemptyset(&mask);
    sigaddset(&mask, SIGCHLD);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    if ((pid = fork()) < 0) {
      fprintf(stderr, "fork failed\n");
      exit(1);
    }
    if (pid == 0) {
      sigprocmask(SIG_UNBLOCK, &mask, NULL);
      if (setpgid(0, 0) < 0) {
	perror("setpgid failed");
      }
      if (execve(argv[0], argv, environ) < 0) {
	printf("%s: Command not found.\n", argv[0]);
	exit(0);
      }
    }

    // Commands needed before allowing signals from child
    jid = addjob(pid, cmdline); 
    sigprocmask(SIG_UNBLOCK, &mask, NULL);

    if (!bg) {
      FG = pid;
    } else {
      printf("[%d] %d %s", jid, pid, cmdline);
    }
  }
  return;
}

/*
 * parseline - Returns 1 if buf ends with '&', else returns 0.
 * Each word seperated by one or more spaces is put into argv
 * as a NULL terminates string. This is accomplished by replacing
 * the spaces in buf with '\0' and storing the pointer to the first
 * char in the word in argv. The buf arguement is altered in place
 * and should not be modified after.
 *
 * buf - NULL terminates string containing a shell command line
 * argv - empty string
 */
int parseline(char *buf, char **argv) {
  char *delim;
  int argc;
  int bg;

  buf[strlen(buf)-1] = ' ';
  while (*buf && (*buf == ' '))
    buf++;

  argc = 0;
  while ((delim = strchr(buf, ' '))) {
    argv[argc++] = buf;
    *delim = '\0';
    buf = delim + 1;
    while (*buf && (*buf == ' '))
      buf++;
  }
  argv[argc] = NULL;

  if (argc == 0)
    return 1;

  if ((bg = (*argv[argc - 1] == '&')) != 0)
    argv[--argc] = NULL;

  return bg;
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv) {
  if (!strcmp(argv[0], "quit"))
    exit(0);
  if (!strcmp(argv[0], "&"))
    return 1;
  if (!strcmp(argv[0], "jobs")) {
    jobs();
    return 1;
  }
  if (!strcmp(argv[0], "fg")) {
    fg(argv);
    return 1;
  }
  if (!strcmp(argv[0], "bg")) {
    bg(argv);
    return 1;
  }
  return 0;
}

/*
 * jobs - iterates through the PIDS array and prints each no-zero value as
 * the PID. Prints the index as the JID. And prints the index into JOBS
 * as a string representation of argv.
 */
void jobs(void) {
  int i;
  char running[] = "Running";
  char stopped[] = "Stopped";
  char *status;

  for (i = 0; i < SHELLLIMIT; i++) {
    if (PIDS[i] != 0) {
      if(STATUS[i] == RUNNING)
	status = running;
      if(STATUS[i] == STOPPED)
	status = stopped;
      printf("[%d] %d %s   %s", i+1, PIDS[i], status, JOBS[i]);
    }
  }
}

void fg(char **argv) {
  pid_t pid = 0;
  int i, jid, argc;

  for (i = 0; ; i++) {
    if (argv[i] == NULL) {
      break;
    }
    argc++;
  }
	
  if(argc != 2) {
    printf("fg requires a single JID or PID\n");
    return;
  }
  else if(argv[1][0] == '%') {
    jid = atoi(&argv[1][1]);	
    if (jid > 0 && jid <= SHELLLIMIT) {
      pid = PIDS[jid-1];
    }
  } else {
    i = atoi(&argv[1][0]);
    for (jid = 1; jid <= SHELLLIMIT; jid++) {
      if (PIDS[jid-1] == i) {
	pid = PIDS[jid-1];
	break;
      }
    }
  }
  if (pid != 0) {
    kill(pid, SIGCONT);
    STATUS[jid-1] = RUNNING;
    FG = pid;
  }
  return;
}

void bg(char **argv) {
  pid_t pid = 0;
  int i, jid, argc;

  for (i = 0; ; i++) {
    if (argv[i] == NULL) {
      break;
    }
    argc++;
  }
	
  if(argc != 2) {
    printf("bg requires a single JID or PID\n");
    return;
  }
  else if(argv[1][0] == '%') {
    jid = atoi(&argv[1][1]);	
    if (jid > 0 && jid <= SHELLLIMIT) {
      pid = PIDS[jid-1];
    }
  } else {
    i = atoi(&argv[1][0]);
    for (jid = 1; jid <= SHELLLIMIT; jid++) {
      if (PIDS[jid-1] == i) {
	pid = PIDS[jid-1];
	break;
      }
    }
  }
  if (pid != 0) {
    kill(pid, SIGCONT);
    STATUS[jid-1] = RUNNING;
  }
  return;
}
/*
 * addjob - stores the pid in the first non-zero index in PIDS. The index
 * is used as the JID. The argv is stored as a space separated string
 * in JOBS.
 *
 * Returns the JID for the process
 */
int addjob(int pid, char *cmdline) {
  int i;
  for (i = 0; i < SHELLLIMIT; i++) {
    if (PIDS[i] == 0) {
      PIDS[i] = pid;
      strcpy(JOBS[i], cmdline);
      return ++i;
    }
  }
  return 0;
}

void deletejob(int pid) {
  int i;
  for (i = 0; i < SHELLLIMIT; i++) {
    if (PIDS[i] == pid) {
      PIDS[i] = 0;
      return;
    }
  }
}

void stopjob(int pid) {
  int i;
  for (i = 0; i < SHELLLIMIT; i++) {
    if (PIDS[i] == pid) {
      STATUS[i] = STOPPED;
      return;
    }
  }
}

void sigint_handler(int sig) {
  if (FG != 0) {
    kill(FG, SIGINT);
  }
}

void sigtstp_handler(int sig) {
  if (FG != 0) {
    kill(FG, SIGTSTP);
  }
}


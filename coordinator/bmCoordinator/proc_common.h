#ifndef PROC_COMMON_H
#define PROC_COMMON_H

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

struct sProcess{
    int pfd[2];
    pid_t pid;
    char* cmd;   
    char* file;
    char** args;
    FILE* fileFd;
};

typedef struct sProcess tProcess;
typedef tProcess* pProcess; 


pid_t startProc(pProcess proc);
bool isStartedProc(pProcess proc);
int waitForProc(pProcess proc);
int closeProc(pProcess proc);
int dumpPipe(pProcess proc);
void ucaseFile(char* file);

int waitRead(int seconds, pProcess proc);

#define PIPE_RE 0
#define PIPE_WE 1

#endif //PROC_COMMON_H
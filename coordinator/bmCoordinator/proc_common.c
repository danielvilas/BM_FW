#include "proc_common.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>

void printCmd(pProcess proc){
    int i=0;
    while(proc->args[i]!=NULL){
        printf("%s ",proc->args[i]);
        i++;
    }
    printf("\n");
}

pid_t startProc(pProcess proc){
    //Create Pipes and fork
    pipe(proc->pfd);//TODO error check
    printCmd(proc);
    proc->pid = fork();
    
    if(proc->pid==-1){
        perror("fork rp");
        return -1;
    }
    //Run cmd
    if(proc->pid==0){
        dup2(proc->pfd[PIPE_WE],STDOUT_FILENO);
        close(proc->pfd[PIPE_RE]);
        close(proc->pfd[PIPE_WE]);
        if(execvp(proc->cmd,proc->args)==-1){
            perror(proc->cmd);
        }
        return -1;
    }
    //Configure Pipes
    close(proc->pfd[PIPE_WE]); //parent don't need pipe out;
    
    int retval = fcntl( proc->pfd[PIPE_RE], F_SETFL, fcntl(proc->pfd[PIPE_RE], F_GETFL) | O_NONBLOCK);
    if(retval)    
    {
        printf("failed to set O_NONBLOCK\n");
        perror("O_NONBLOCK");
    }
    //Create out files
    proc->fileFd=fopen(proc->file,"w");
    if(proc->fileFd==NULL){
        perror(proc->file);
    }

    return proc->pid;
}

bool isStartedProc(pProcess proc){
    pid_t pid = proc->pid;
    usleep(1000);
    int status=-1;
    if(waitpid(pid,&status,  WNOHANG)!=0){
        if ( WIFEXITED(status) ) {
            const int es = WEXITSTATUS(status);
            printf("%s exit status was %d\n",proc->cmd, es);
        }
        return false;
    }
    return true;
}

int waitForProc(pProcess proc){
    pid_t pid = proc->pid;
    int status;
    if(waitpid(pid,&status, 0)==pid){
        if ( WIFEXITED(status) ) {
            const int es = WEXITSTATUS(status);
            printf("%s exit status was %d\n",proc->cmd, es);
            return es;
        }
        return 0;
    }
    return -1;
}

int closeProc(pProcess proc){
    fclose(proc->fileFd);
    close(proc->pfd[PIPE_RE]);
    //kill(proc->pid, SIGINT);
    free(proc->args);
    return 0;
}

int dumpPipe(pProcess proc){        
    char buff[1024];
    ssize_t r=read(proc->pfd[PIPE_RE], buff, sizeof(buff) );
    if ( r > 0 ){
        //printf("%s read: %li\n",proc->cmd,r);
        //printf("Buffer: %s\n", buff);
        fwrite(buff, sizeof(char),r,proc->fileFd);
        fflush(proc->fileFd);
    }else{
        int err=errno;
        if(!isStartedProc(proc))return -1;
        if(err==EAGAIN)return 0;
    }
    return r;
}


void ucaseFile(char* file){
    char* s=file;
    while(*s && (*s) !='.'){
        *s=toupper(*s);
        s++;
    }
}

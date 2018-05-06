#include "proc_common.h"
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

bool isStarted(pid_t pid){
    usleep(1000);
    int status=-1;
    if(waitpid(pid,&status,  WNOHANG)!=0){
        printf("Error al ejecutar %i\n",status);
        if ( WIFEXITED(status) ) {
            const int es = WEXITSTATUS(status);
            printf("exit status was %d\n", es);
        }
        return false;
    }
    return true;
}

int waitForPid(pid_t pid){
    int status;
    if(waitpid(pid,&status, 0)==pid){
        if ( WIFEXITED(status) ) {
            const int es = WEXITSTATUS(status);
            //printf("exit status was %d\n", es);
            return es;
        }
        return 0;
    }
    return -1;
}
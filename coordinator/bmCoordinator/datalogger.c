#include "datalogger.h"
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

char* rp="../../rp_datalogger/Debug/rp_datalogger";//TODO extract from cfg
char* fileRp="C_MQTT_1.txt";

pid_t startDataLogger(pProcess proc){
    proc->cmd=rp;
    proc->args =(char**) malloc(2*sizeof(char*));
    proc->args[0]=rp;
    proc->args[1]=(char *)NULL;
    proc->file=fileRp;
    
    return startProc(proc);
    
}

int closeDataLogger(pProcess proc){
    //Left for future cases of closeDL
    kill(proc->pid, SIGINT);
    //closeProc(proc);
    while(1){
        int r = dumpPipe(proc);
        if(r==-1)break;
    }
    closeProc(proc);
    waitForProc(proc);
    return 0;
}
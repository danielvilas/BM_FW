#include "datalogger.h"
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

char fileRp[255];

pid_t startDataLogger(pProcess proc,pConfig cfg, pPlatform plat, pLang lang, pProtocol proto,int i){
    int w =sprintf(fileRp,"%s_%s_%i.txt",lang->name,proto->name,i);
    fileRp[w]='\0';
    ucaseFile(fileRp);
    proc->cmd=cfg->datalogerCmd;
    proc->args =(char**) malloc(2*sizeof(char*));
    proc->args[0]=cfg->datalogerCmd;
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
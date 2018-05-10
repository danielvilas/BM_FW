#include "datalogger.h"
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

char fileRp[255];

int mkpath(char* file_path, mode_t mode) {
//  assert(file_path && *file_path);
  char* p;
  for (p=strchr(file_path+1, '/'); p; p=strchr(p+1, '/')) {
    *p='\0';
    if (mkdir(file_path, mode)==-1) {
      if (errno!=EEXIST) { *p='/'; return -1; }
    }
    *p='/';
  }
  return 0;
}

pid_t startDataLogger(pProcess proc,pConfig cfg, pPlatform plat, pLang lang, pProtocol proto,int i){
    char fileName[255];
    int w =sprintf(fileName,"%s_%s_%i.txt",lang->name,proto->name,i);
    fileName[w]='\0';
    ucaseFile(fileName);
    char dirs[255];
    w=sprintf(dirs,"%s/%s/%s/",plat->name,lang->name,proto->name);
    dirs[w]='\0';
    struct stat st = {0};

    if (stat(dirs, &st) == -1) {
        printf("Creating dir %s\n",dirs);
        mkpath(dirs, 0700);
    }
    
    w=sprintf(fileRp,"%s%s",dirs,fileName);
    fileRp[w]='\0';
    
    if( access( fileRp, F_OK ) != -1 ) {
        printf("\tOmitted %s exists\n",fileRp);
        return -1;
    }
    
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
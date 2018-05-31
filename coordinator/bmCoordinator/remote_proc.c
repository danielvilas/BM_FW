#include "remote_proc.h"
#include <stdio.h>
#include <stdlib.h>

//ssh -oBatchMode=yes -l<user> -i<keyfile> serverpi.local "cd bm_c && sudo lpm -o FILE.txt -s ./bmc_full -d 0Initial -p MQTT"
char* batchMode="-oBatchMode=yes";
char user[255];
char key[255];
char cmd[512];
char file[255];
char remoteFile[255];
char localFile[255];
char fileScp[255];

void fillRemoteProc(pProcess proc, pConfig cfg, pPlatform plat, pLang lang, pProtocol proto, const char* tmpCmd,const char* localExt, int i){
    char fileWoExt[255];
    int w =sprintf(fileWoExt,"%s_%s_MEM_%i.",lang->name,proto->name,i);
    fileWoExt[w]='\0';
    ucaseFile(fileWoExt);
    
    w =sprintf(file,"%s/%s/%s/%s%s",plat->name,lang->name,proto->name,fileWoExt,localExt);
    file[w]='\0';
    
    w=sprintf(user,"-l%s",plat->user);
    user[w]='\0';
    
    w=sprintf(key,"-i%s",plat->key);
    key[w]='\0';
    char tmp[512];
    w=sprintf(tmp,tmpCmd,lang->dir,fileWoExt,lang->cmd);
    tmp[w]='\0';
    w=sprintf(cmd,tmp,proto->param);
    tmp[w]='\0';

    proc->cmd=cfg->sshCmd;
    proc->args =(char**) malloc(7*sizeof(char*));
    proc->args[0]=cfg->sshCmd;
    proc->args[1]=batchMode;
    proc->args[2]=user;
    proc->args[3]=key;
    proc->args[4]=plat->host;
    proc->args[5]=cmd;
    proc->args[6]=(char *)NULL;
    proc->file=file;
    
}

void fillRemoteGet(pProcess proc, pConfig cfg, pPlatform plat, pLang lang, pProtocol proto, int i){
    // /usr/bin/scp -oBatchMode=yes -i~/beaglebone.key serverpi.local:./bm_c/C_KAFKA_MEM_1.txt file

    char fileWoExt[255];
    int w =sprintf(fileWoExt,"%s_%s_MEM_%i.",lang->name,proto->name,i);
    fileWoExt[w]='\0';
    ucaseFile(fileWoExt);

    w =sprintf(localFile,"%s/%s/%s/%stxt",plat->name,lang->name,proto->name,fileWoExt);
    localFile[w]='\0';

    w =sprintf(fileScp,"%s/%s/%s/%sscp_txt",plat->name,lang->name,proto->name,fileWoExt);
    fileScp[w]='\0';

    w=sprintf(remoteFile,"%s@%s:./%s/%stxt",plat->user,plat->host,lang->dir,fileWoExt);
    remoteFile[w]='\0';


    proc->cmd=cfg->scpCmd;
    proc->args =(char**) malloc(6*sizeof(char*));
    proc->args[0]=cfg->scpCmd;
    proc->args[1]=batchMode;
    proc->args[2]=key;
    proc->args[3]=remoteFile;
    proc->args[4]=localFile;
    proc->args[5]=(char *)NULL;
    proc->file=fileScp;
}

pid_t startRemoteProc(pProcess proc,pConfig cfg, pPlatform plat, pLang lang, pProtocol proto,int i){
    fillRemoteProc(proc,cfg,plat, lang,proto,"cd %s && sudo lpm -o %stxt -s %s","out",i);
    return startProc(proc);
}

int getRemoteProc(pProcess proc,pConfig cfg, pPlatform plat, pLang lang, pProtocol proto,int i){


    fillRemoteGet(proc,cfg,plat, lang,proto,i);
    pid_t pid= startProc(proc);
    if(pid<0)return pid;
    while(1){

        sleep(1);
        int r = dumpPipe(proc);
        if(r==-1)break;
        
    }
    closeRemoteProc(proc);
    return 0;
}

int closeRemoteProc(pProcess proc){
    //Left for future cases of closeDL
    closeProc(proc);
    waitForProc(proc);
    return 0;
}

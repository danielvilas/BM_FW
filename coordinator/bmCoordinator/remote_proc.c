#include "remote_proc.h"
#include <stdio.h>
#include <stdlib.h>

//ssh -oBatchMode=yes -l<user> -i<keyfile> serverpi.local "cd bm_c && sudo lpm -o FILE.txt -s ./bmc_full -d 0Initial -p MQTT"
char* batchMode="-oBatchMode=yes";
//char* user="-ldaniel"; //TODO extract from cfg
char user[255];
//char* key="-i~/.ssh/id_rsa"; //cfg
char key[255];
//char* host="localhost"; //cfg
//char* cmd="cd bm_c && sudo lpm -o FILE.txt -s ./bmc_full -d 0Initial -p REST";//Build from CFG
char cmd[512];
//char* file="C_MQTT_1.out";
char file[255];


void fillRemoteProc(pProcess proc,pConfig cfg, pPlatform plat, pLang lang, pProtocol proto, const char* tmpCmd,const char* localExt, int i){
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

pid_t startRemoteProc(pProcess proc,pConfig cfg, pPlatform plat, pLang lang, pProtocol proto,int i){
    fillRemoteProc(proc,cfg,plat, lang,proto,"cd %s && sudo lpm -o %stxt -s %s","out",i);
    return startProc(proc);
}

int getRemoteProc(pProcess proc,pConfig cfg, pPlatform plat, pLang lang, pProtocol proto,int i){
    fillRemoteProc(proc,cfg,plat, lang,proto,"cd %s && cat %stxt ","txt",i);
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

#include "remote_proc.h"
#include <stdio.h>
#include <stdlib.h>

//ssh -oBatchMode=yes -l<user> -i<keyfile> serverpi.local "cd bm_c && sudo lpm -o FILE.txt -s ./bmc_full -d 0Initial -p MQTT"
char* ssh="/usr/bin/ssh";
char* batchMode="-oBatchMode=yes";
char* user="-ldaniel"; //TODO extract from cfg
char* key="-i~/.ssh/id_rsa"; //cfg
char* host="serverpi.local"; //cfg
//char* host="localhost"; //cfg
char* cmd="cd bm_c && sudo lpm -o FILE.txt -s ./bmc_full -d 0Initial -p REST";//Build from CFG
char* file="C_MQTT_1.out";


pid_t startRemoteProc(pProcess proc){
    proc->cmd=ssh;
    proc->args =(char**) malloc(7*sizeof(char*));
    proc->args[0]=ssh;
    proc->args[1]=batchMode;
    proc->args[2]=user;
    proc->args[3]=key;
    proc->args[4]=host;
    proc->args[5]=cmd;
    proc->args[6]=(char *)NULL;
    proc->file=file;
    
    return startProc(proc);
}

int closeRemoteProc(pProcess proc){
    //Left for future cases of closeDL
    closeProc(proc);
    waitForProc(proc);
    return 0;
}
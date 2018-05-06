#include "remote_proc.h"
#include <stdio.h>

//ssh -oBatchMode=yes -l<user> -i<keyfile> serverpi.local "cd bm_c && sudo lpm -o FILE.txt -s ./bmc_full -d 0Initial -p MQTT"
const char* ssh="/usr/bin/ssh";
const char* batchMode="-oBatchMode=yes";
const char* user="-ldaniel"; //TODO extract from cfg
const char* key="-i~/.ssh/id_rsa"; //cfg
const char* host="serverpi.local"; //cfg
const char* cmd="cd bm_c && sudo lpm -o FILE.txt -s ./bmc_full -d 0Initial -p MQTT";

pid_t startRemoteProc(){
    pid_t rp_dataloggerPid;
    rp_dataloggerPid = fork();
    
    if(rp_dataloggerPid==-1){
        perror("fork rp");
        return -1;
    }
    if(rp_dataloggerPid==0){
        if(execl(ssh,ssh,batchMode,user,key, host, cmd,(char *)NULL)==-1){
            perror(ssh);
        }
        return -1;
    }
    
    return rp_dataloggerPid;
}
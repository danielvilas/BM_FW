#include "datalogger.h"
#include <stdio.h>

const char* rp="../../rp_datalogger/Debug/rp_datalogger";//TODO extract from cfg

pid_t startDataLogger(){
    pid_t rp_dataloggerPid;
    rp_dataloggerPid = fork();
    
    if(rp_dataloggerPid==-1){
        perror("fork rp");
        return -1;
    }
    if(rp_dataloggerPid==0){
        if(execl(rp,rp,(char *)NULL)==-1){
            perror(rp);
        }
        return -1;
    }
    
    return rp_dataloggerPid;
}
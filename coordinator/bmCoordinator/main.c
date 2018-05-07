#include <unistd.h>
#include <stdio.h>


#include "datalogger.h"
#include "proc_common.h"
#include "remote_proc.h"

int main(int argc, char **argv)
{
	printf("BMF Coordinator\n");
    
    tProcess rp_datalogger;
    tProcess remoteProc;
    
    pid_t rp_dataloggerPid=startDataLogger(&rp_datalogger);
    if(rp_dataloggerPid==-1)return -1;
    if(!isStartedProc(&rp_datalogger)) return -1;
    sleep(3);
    pid_t remoteProcPid = startRemoteProc(&remoteProc);
    if(remoteProcPid==-1)return -1;
    if(!isStartedProc(&remoteProc)) return -1;
    //waitForProc(&remoteProc);
    while(1){
        sleep(1);
        int r = dumpPipe(&remoteProc);
        if(r==-1)break;
        r=dumpPipe(&rp_datalogger);
        
    }
    closeRemoteProc(&remoteProc);
    sleep(3);
    closeDataLogger(&rp_datalogger);
    
	return 0;
}

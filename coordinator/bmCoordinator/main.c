#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "datalogger.h"
#include "proc_common.h"
#include "remote_proc.h"

int main(int argc, char **argv)
{
	printf("BMF Coordinator\n");
    
    //pid_t rp_dataloggerPid=startDataLogger();
    //if(rp_dataloggerPid==-1)return -1;
    //if(!isStarted(rp_dataloggerPid)) return -1;
    
    pid_t remote_proc= startRemoteProc();
    if(remote_proc==-1)return -1;
    if(!isStarted(remote_proc)) return -1;
    waitForPid(remote_proc);
    //sleep(5);
    //kill(rp_dataloggerPid, SIGINT);
    //waitForPid(rp_dataloggerPid);
    
	return 0;
}

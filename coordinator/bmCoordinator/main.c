#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "datalogger.h"
#include "proc_common.h"
#include "remote_proc.h"
#include "config.h"

int execute(pConfig cfg, pPlatform plat, pLang lang, pProtocol proto, int i){
    printf("Excuting %s %s %s (%i)\n",plat->name, lang->name, proto->name,i);
    
    tProcess rp_datalogger;
    tProcess remoteProc;
    
    pid_t rp_dataloggerPid=startDataLogger(&rp_datalogger, cfg,plat,lang, proto,i);
    if(rp_dataloggerPid==-1)return -1;
    if(!isStartedProc(&rp_datalogger)) return -1;
    sleep(3);
    pid_t remoteProcPid = startRemoteProc(&remoteProc,cfg,plat,lang, proto,i);
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
    sleep(6);
    closeDataLogger(&rp_datalogger);
    return getRemoteProc(&remoteProc,cfg,plat,lang, proto,i);
}

void executePlat(pConfig cfg, pPlatform plat){
    pLang lang = cfg->firstLang;
    while (lang!=NULL){
        for(int i =1;i<=cfg->times;i++){
            pProtocol proto=cfg->firstProtocol;
            while(proto!=NULL){
                execute(cfg, plat, lang, proto,i);
                proto=proto->next;
            }
        }
        lang=lang->next;
    }
    
    
}

int main(int argc, char **argv)
{
	printf("BMF Coordinator\n");
    if(argc<2){
        printf("Usage: %s <configFile> [platform]\n",argv[0]);
        return -1;
    }
    
    tConfig cfg;
    
    if(readYaml(argv[1],&cfg)){
        return -1;
    }
    
    if(argc<3){
        printf("Usage: %s <configFile> [platform]\n\nConfig File is:\n",argv[0]);
        printConfig(&cfg);
        printf("\nDetected Platforms:\n");
    }
    pPlatform plat = cfg.firstPlatform;
    
    while(plat!=NULL){
        if(argc<3){
            printf("  %s\n",plat->name);
        }else{
            if(strcmp(argv[2],plat->name)==0){
                executePlat(&cfg, plat);
                return 0;
            }
        }
        plat=plat->next;
    }
    
    if(argc<3){
        return -1;
    }else{
        printf("Platform %s not found\n",argv[2]);
        return -1;
    }

	return 0;
}

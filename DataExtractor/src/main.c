#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "config.h"
#include "common.h"
#include "memory.h"
#include "power.h"
#include "process.h"




void execute(char* dir, pConfig cfg){
    pName plat=cfg->firstPlatform;
    while(plat!=NULL){
        pName lang = cfg->firstLang;
        while(lang!=NULL){
            pName proto=cfg->firstProtocol;
            while(proto!=NULL){
                executeOne(dir,cfg,plat,lang,proto);
                proto=proto->next;
            }
            lang=lang->next;
        }
        plat=plat->next;
    }
}

int main(int argc, char** argv) {
    printf("BenchMark Framework Data Parser!\n");
    //return 0;

    if(argc<2){
        printf("Usage: %s <configFile> [raw_data_dir]\n",argv[0]);
        return -1;
    }

    tConfig cfg;

    if(readYaml(argv[1],&cfg)){
        return -1;
    }
    if(argc<3){
        printConfig(&cfg);
    }else{
        //executeOne(argv[2],cfg.firstPlatform,cfg.firstLang,cfg.firstProtocol);
        execute(argv[2],&cfg);
    }

    return 0;
}
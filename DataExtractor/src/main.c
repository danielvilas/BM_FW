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
    int col=1;
    while(plat!=NULL){
        char filePath[BUFFER_SIZE];
        int w=sprintf(filePath,"%s/%s/SUMARY.xlsx",dir,plat->name);
        filePath[w]='\0';
        lxw_workbook  *workbook  = workbook_new(filePath);
        lxw_worksheet *worksheet = createSumaryWorkSheet(workbook);
        pName lang = cfg->firstLang;
        while(lang!=NULL){
            pName proto=cfg->firstProtocol;
            while(proto!=NULL){
                pExecuteInfo info =executeOne(dir,cfg,plat,lang,proto);
                fillSumaryWorkSheet(worksheet, plat, lang, proto, &info->mem, &info->power, col++);
                proto=proto->next;
            }
            lang=lang->next;
        }
        plat=plat->next;
        workbook_close(workbook);
        printf("Report: %s saved\n",filePath);
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
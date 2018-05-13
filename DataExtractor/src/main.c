#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "config.h"
#include "common.h"
#include "memory.h"
#include "power.h"
#include <xlsxwriter.h>

void executeOne(char* dir, pName plat, pName lang, pName proto ){
    char filename[FILENAME_MAX];
    char filePath[FILENAME_MAX];
    int w= fillName(filename,lang,proto);
    if(w==0)return;;
    w=sprintf(filePath,"%s/%s/%s.xlsx",dir,plat->name,filename);
    filePath[w]='\0';

    lxw_workbook  *workbook  = workbook_new(filePath);
    //For each File
    int i=1;
    while(1){
        fillNameSuffixIndex(filename,lang,proto,i,"MEM_");
        pvMemInfoEntry mem =parseMemData(dir,plat,lang,proto,i);
        if(mem==NULL)break;
        createMemSheet(workbook,filename,mem);
        free(mem->data);
        free(mem);

        fillNameSuffixIndex(filename,lang,proto,i,"PWR_");
        pPowerInfo pwr=parsePowerData(dir,plat,lang,proto,1);
        //if(pwr==NULL)break;
        createPowerSheet(workbook,filename,pwr);
        free(pwr->groupData->data);
        free(pwr->groupData);
        free(pwr->fullData->data);
        free(pwr->fullData);
        free(pwr);

        i++;
    }
    //End for each file

    workbook_close(workbook);
    printf("Report: %s saved\n",filePath);
    return;
}

void execute(char* dir, pConfig cfg){
    pName plat=cfg->firstPlatform;
    while(plat!=NULL){
        pName lang = cfg->firstLang;
        while(lang!=NULL){
            pName proto=cfg->firstProtocol;
            while(proto!=NULL){
                executeOne(dir,plat,lang,proto);
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
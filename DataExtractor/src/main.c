#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "config.h"
#include "common.h"
#include "memory.h"
#include "power.h"
#include "process.h"



void execute(char* dir, pConfig cfg) {
    pName plat = cfg->firstPlatform;
    char filePath[BUFFER_SIZE];
    int w = sprintf(filePath, "%s/REPORT.xlsx", dir);
    filePath[w] = '\0';
    lxw_workbook *workbook = workbook_new(filePath);
    lxw_worksheet *worksheet = createSumaryWorkSheet(workbook);
    int col = 1;

    //pExecuteInfo table[cfg->nProtocols][cfg->nLanguages*cfg->nPlatforms];

    pExecuteInfo **table;
    table= malloc(cfg->nProtocols * sizeof(pExecuteInfo *));
    for (int i = 0; i < cfg->nProtocols; i++) {
        table[i] = (pExecuteInfo *) malloc(cfg->nLanguages*cfg->nPlatforms* sizeof(pExecuteInfo));
    }

    int iPlat=0;
    while(plat!=NULL){
        w=sprintf(filePath,"%s/%s/SUMARY.xlsx",dir,plat->name);filePath[w]='\0';
        lxw_workbook  *plat_workbook  = workbook_new(filePath);
        lxw_worksheet *plat_worksheet = createSumaryWorkSheet(plat_workbook);
        pName lang = cfg->firstLang;
        int plat_col=1;
        int iLang=0;
        while(lang!=NULL){
            pName proto=cfg->firstProtocol;
            int iProto=0;
            while(proto!=NULL){
                pExecuteInfo info =executeOne(dir,cfg,plat,lang,proto);
                fillSumaryWorkSheet(plat_worksheet, plat, lang, proto, &info->mem, &info->power, plat_col++);
                fillSumaryWorkSheet(worksheet, plat, lang, proto, &info->mem, &info->power, col++);

                pExecuteInfo* row = table[iProto];
                row[iLang*cfg->nPlatforms+iPlat]=info;

                proto=proto->next;
                iProto++;
            }
            lang=lang->next;
            iLang++;
        }
        plat=plat->next;
        iPlat++;

        workbook_close(plat_workbook);
        printf("Report: %s saved\n",filePath);
    }

    lxw_worksheet *mem_worksheet = workbook_add_worksheet(workbook, "Memory");
    for(int iProto=0;iProto<cfg->nProtocols;iProto++){
        pExecuteInfo* row = table[iProto];
        worksheet_write_string (mem_worksheet, iProto+1, 0, row[0]->proto->name, NULL);
        for(int iLang=0;iLang<cfg->nLanguages;iLang++){
            for(int iPlat=0;iPlat<cfg->nPlatforms;iPlat++){
                int cIndex=iLang*cfg->nPlatforms+iPlat;
                pExecuteInfo  info = row[cIndex];
                char cName[255];
                sprintf(cName,"%s-%s",info->lang->name, info->plat->name);
                worksheet_write_string (mem_worksheet, 0, cIndex+1, cName, NULL);
                worksheet_write_number(mem_worksheet,iProto+1,cIndex+1,info->mem.cpuAvg,NULL);

            }
        }
    }

    workbook_close(workbook);
    printf("Report: %s/REPORT.xlsx saved\n",dir);
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
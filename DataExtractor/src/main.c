#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "config.h"
#include "common.h"
#include "memory.h"
#include "power.h"
#include "process.h"
#include "report.h"
#include "xls/proccessXls.h"

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
    tReportInfo avg,max;
    fillReportCfg(&avg, extract_memAvgKb, "Memory usage Average of all measures","Memory usage (KB)","MemAvg");
    fillReportCfg(&max,extract_memMaxKb,"Max Memory","KB","MemMax");
    createDoubleReport(cfg,workbook,table, "Memory",&avg,&max);


    fillReportCfg(&avg, extract_cpuAvg, "CPU usage Average of all measures","CPU usage (%%)","CPU Avg");
    fillReportCfg(&max,extract_maxCpu,"Max CPU","% CPU","CPU Max");
    createDoubleReport(cfg,workbook,table, "Cpu",&avg,&max);

    fillReportCfg(&avg, extract_netOutKb, "Network usage Out data","Data sent (KB)","Out");
    fillReportCfg(&max,extract_netInKb,"Network usage In data","Data received (KB)","In");
    createDoubleReport(cfg,workbook,table, "NetWork",&avg,&max);

    fillReportCfg(&avg, extract_steadyCurrent_mA, "Current in Wait state","Current (mA)","Steady");
    fillReportCfg(&max,extract_runCurrent_mA,"Current in Run State","Current (mA)","Run");
    createDoubleReport(cfg,workbook,table, "Current",&avg,&max);

    fillReportCfg(&avg, extract_runEnergy_J, "Energy in Jules","Jules","Jules");
    fillReportCfg(&max,extract_runEnergy_mAs,"Energy in mAs","mAs","mAs");
    createDoubleReport(cfg,workbook,table, "Energy",&avg,&max);

    fillReportCfg(&avg,extract_runEnergy_mAh,"Energy usage","Energy (mAh)","mAh");
    createReport(cfg,workbook,table,"Energy mAh",&avg);

    fillReportCfg(&avg, extract_time_ms, "Total Time","ms","Total");
    fillReportCfg(&max,extract_cycleTime_ms,"One Cycle time per protocol","Cycle time(ms)","Cycle");
    createDoubleReport(cfg,workbook,table, "Time",&avg,&max);

    fillReportCfg(&avg,extract_estEnergy_mAh,"Estimated Energy","Energy (mAh)","Estimated");
    createReport(cfg,workbook,table,"Estimated Energy",&avg);


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
//
// Created by Daniel Vilas Perulan on 2019-07-31.
//

#include "proccessXls.h"
#include "../process.h"
#include "../power.h"
#include "../memory.h"
#include "powerXls.h"
#include "memoryXls.h"

void fillSumaryWorkSheet(lxw_worksheet *worksheet,
                         pName plat, pName lang, pName proto,
                         pMemInfo mem_avg, pPowerInfo pwr_avg,
                         int col) {
    int i=0;
    worksheet_write_string (worksheet, i++, col, plat->name, NULL);
    worksheet_write_string (worksheet, i++, col, lang->name, NULL);
    worksheet_write_string (worksheet, i++, col, proto->name, NULL);
    worksheet_write_number (worksheet, i++, col, mem_avg->memAvgKb, NULL);
    worksheet_write_number (worksheet, i++, col, mem_avg->memMaxKb, NULL);
    worksheet_write_number (worksheet, i++, col, mem_avg->cpuAvg, NULL);
    worksheet_write_number (worksheet, i++, col, mem_avg->maxCpu, NULL);
    worksheet_write_number (worksheet, i++, col, mem_avg->netOutKb, NULL);
    worksheet_write_number (worksheet, i++, col, mem_avg->netInKb, NULL);
    worksheet_write_number (worksheet, i++, col, pwr_avg->steadyCurrent_mA, NULL);
    worksheet_write_number (worksheet, i++, col, pwr_avg->runCurrent_mA, NULL);
    worksheet_write_number (worksheet, i++, col, pwr_avg->runEnergy_J, NULL);
    worksheet_write_number (worksheet, i++, col, pwr_avg->runEnergy_mAs, NULL);
    worksheet_write_number (worksheet, i++, col, pwr_avg->runEnergy_mAh, NULL);
    worksheet_write_number (worksheet, i++, col, pwr_avg->time_ms, NULL);
    worksheet_write_number (worksheet, i++, col, pwr_avg->cycleTime_ms, NULL);
    worksheet_write_number (worksheet, i++, col, pwr_avg->estEnergy_mAh, NULL);
    worksheet_set_column(worksheet, col, col, 12.0, NULL);
}

lxw_worksheet* createSumaryWorkSheet(lxw_workbook* workbook){
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, "SUMARY");
    int i=0;
    worksheet_write_string (worksheet, i++, 0, "platform", NULL);
    worksheet_write_string (worksheet, i++, 0, "lang", NULL);
    worksheet_write_string (worksheet, i++, 0, "protocol", NULL);
    worksheet_write_string (worksheet, i++, 0, "memAvgKb", NULL);
    worksheet_write_string (worksheet, i++, 0, "memMaxKb", NULL);
    worksheet_write_string (worksheet, i++, 0, "cpuAvg", NULL);
    worksheet_write_string (worksheet, i++, 0, "maxCpu", NULL);
    worksheet_write_string (worksheet, i++, 0, "netOutKb", NULL);
    worksheet_write_string (worksheet, i++, 0, "netInKb", NULL);
    worksheet_write_string (worksheet, i++, 0, "steadyCurrent_mA", NULL);
    worksheet_write_string (worksheet, i++, 0, "runCurrent_mA", NULL);
    worksheet_write_string (worksheet, i++, 0, "runEnergy_J", NULL);
    worksheet_write_string (worksheet, i++, 0, "runEnergy_mAs", NULL);
    worksheet_write_string (worksheet, i++, 0, "runEnergy_mAh", NULL);
    worksheet_write_string (worksheet, i++, 0, "time_ms", NULL);
    worksheet_write_string (worksheet, i++, 0, "cycleTime_ms", NULL);
    worksheet_write_string (worksheet, i++, 0, "estEnergy_mAh", NULL);
    worksheet_set_column(worksheet,0,0,16.0,NULL);
    return worksheet;
}

pExecuteInfo executeOne(char* dir,pConfig cfg, pName plat, pName lang, pName proto ){
    char filename[FILENAME_MAX];
    char filePath[FILENAME_MAX];
    int w= fillName(filename,lang,proto);
    if(w==0)return NULL;
    w=sprintf(filePath,"%s/%s/%s.xlsx",dir,plat->name,filename);
    filePath[w]='\0';

    lxw_workbook  *workbook  = workbook_new(filePath);
    lxw_worksheet *worksheet = createSumaryWorkSheet(workbook);
    //For each File
    int i=1;
    tPowerInfo pwr_avg;
    tMemInfo mem_avg;

    initAvg(&pwr_avg, &mem_avg);
    while(1){
        fillNameSuffixIndex(filename,lang,proto,i,"MEM_");
        pMemInfo mem =parseMemData(dir,plat,lang,proto,i);
        if(mem==NULL)break;
        createMemSheet(workbook,filename,mem->entries);
        updateMemAvgAndFree(&mem_avg, mem);


        fillNameSuffixIndex(filename,lang,proto,i,"PWR_");
        pPowerInfo pwr=parsePowerData(dir,plat,lang,proto,i);
        //if(pwr==NULL)break;
        createPowerSheet(workbook,filename,pwr);

        updatePowerAvgAndFree(&pwr_avg,pwr);
        i++;
    }
    //End for each file
    i--;

    finishAvg(cfg,&pwr_avg,&mem_avg,i);
    fillSumaryWorkSheet(worksheet, plat, lang, proto, &mem_avg, &pwr_avg, 1);

    workbook_close(workbook);
    printf("Report: %s saved\n",filePath);
    printJsonData(dir,plat,lang, proto,&mem_avg,&pwr_avg);
    pExecuteInfo ret = malloc(sizeof(tExecuteInfo));
    ret->power=pwr_avg;
    ret->mem=mem_avg;
    ret->plat=plat;
    ret->lang=lang;
    ret->proto=proto;
    return ret;
}
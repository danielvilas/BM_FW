#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "config.h"
#include "common.h"
#include "memory.h"
#include "power.h"
#include <xlsxwriter.h>


void initAvg(pPowerInfo pwr_avg){
    pwr_avg->steadyCurrent_mA=0.0;
    pwr_avg->runCurrent_mA=0.0;
    pwr_avg->runEnergy_J=0.0;
    pwr_avg->runEnergy_mAs=0.0;
    pwr_avg->runEnergy_mAh=0.0;
    pwr_avg->time_ms=0.0;
    pwr_avg->cycleTime_ms=0.0;
    pwr_avg->estEnergy_mAh=0.0;
}

void finishAvg(pConfig cfg, pPowerInfo pwr_avg, int i){
    pwr_avg->steadyCurrent_mA/=i;
    pwr_avg->runCurrent_mA/=i;
    pwr_avg->runEnergy_J/=i;
    pwr_avg->runEnergy_mAs/=i;
    pwr_avg->runEnergy_mAh/=i;
    pwr_avg->time_ms/=i;
    pwr_avg->cycleTime_ms=((float)pwr_avg->time_ms)/((float)cfg->cycles);

    /*
     eProcess= data.runCurrentAvg*data.cycleTime/1000;
     eWait= data.preCurrentAvg*(stdPeriod - data.cycleTime/1000);
     eCycle= eProcess + eWait; (in mAs)
    */
    float eProcess=pwr_avg->runCurrent_mA*pwr_avg->cycleTime_ms/1000;
    float eWait = pwr_avg->steadyCurrent_mA*(cfg->interval-pwr_avg->cycleTime_ms/1000);
    float eCycle=eWait+eProcess;
    /*
     %EHour(mAh) = ECycle(mAh)*3600/stdPeriod;
      data.powerEstimation=eCycle/3600*3600/stdPeriod;
     */
    pwr_avg->estEnergy_mAh=(eCycle/3600)*(3600/cfg->interval);
}

void updatePowerAvgAndFree(pPowerInfo pwr_avg, pPowerInfo pwr){
    pwr_avg->steadyCurrent_mA+=pwr->steadyCurrent_mA;
    pwr_avg->runCurrent_mA+=pwr->runCurrent_mA;
    pwr_avg->runEnergy_J+=pwr->runEnergy_J;
    pwr_avg->runEnergy_mAs+=pwr->runEnergy_mAs;
    pwr_avg->runEnergy_mAh+=pwr->runEnergy_mAh;
    pwr_avg->time_ms+=pwr->time_ms;

    free(pwr->groupData->data);
    free(pwr->groupData);
    free(pwr->fullData->data);
    free(pwr->fullData);
    free(pwr);

}

void executeOne(char* dir,pConfig cfg, pName plat, pName lang, pName proto ){
    char filename[FILENAME_MAX];
    char filePath[FILENAME_MAX];
    int w= fillName(filename,lang,proto);
    if(w==0)return;;
    w=sprintf(filePath,"%s/%s/%s.xlsx",dir,plat->name,filename);
    filePath[w]='\0';

    lxw_workbook  *workbook  = workbook_new(filePath);
    //For each File
    int i=1;
    tPowerInfo pwr_avg;

    initAvg(&pwr_avg);
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

        updatePowerAvgAndFree(&pwr_avg,pwr);
        i++;
    }
    //End for each file
    i--;

    finishAvg(cfg,&pwr_avg,i);

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
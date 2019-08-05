//
// Created by dvilaspe on 16/05/2018.
//

#include "process.h"
#include "power.h"
#include "memory.h"

void initAvg(pPowerInfo pwr_avg, pMemInfo mem_avg){
    pwr_avg->steadyCurrent_mA=0.0;
    pwr_avg->runCurrent_mA=0.0;
    pwr_avg->runEnergy_J=0.0;
    pwr_avg->runEnergy_mAs=0.0;
    pwr_avg->runEnergy_mAh=0.0;
    pwr_avg->time_ms=0.0;
    pwr_avg->cycleTime_ms=0.0;
    pwr_avg->estEnergy_mAh=0.0;

    mem_avg->cpuAvg=0.0;
    mem_avg->maxCpu=0.0;
    mem_avg->memAvgKb=0.0;
    mem_avg->memMaxKb=0.0;
    mem_avg->netOutKb=0.0;
    mem_avg->netInKb=0.0;
}

void finishAvg(pConfig cfg, pPowerInfo pwr_avg, pMemInfo mem_avg, int i){
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


    mem_avg->cpuAvg/=i;
    mem_avg->maxCpu/=i;
    mem_avg->memAvgKb/=i;
    mem_avg->memMaxKb/=i;
    mem_avg->netOutKb/=i;
    mem_avg->netInKb/=i;

}

void updateMemAvgAndFree(pMemInfo mem_avg, pMemInfo mem){
    mem_avg->cpuAvg+=mem->cpuAvg;
    mem_avg->maxCpu+=mem->maxCpu;
    mem_avg->memAvgKb+=mem->memAvgKb;
    mem_avg->memMaxKb+=mem->memMaxKb;
    mem_avg->netOutKb+=mem->netOutKb;
    mem_avg->netInKb+=mem->netInKb;


    free(mem->entries->data);
    free(mem->entries);
    free(mem);
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

void printJsonData(char*dir, pName plat, pName lang, pName proto,pMemInfo mem_avg,pPowerInfo pwr_avg){
    char filename[FILENAME_MAX];
    char filePath[FILENAME_MAX];
    int w= fillName(filename,lang,proto);
    w=sprintf(filePath,"%s/%s/%s.json",dir,plat->name,filename);
    filePath[w]='\0';
    FILE * json=fopen(filePath,"w");
    fprintf(json,"{\n");
    fprintf(json,"  \"platform\": \"%s\",\n",plat->name);
    fprintf(json,"  \"lang\": \"%s\",\n",lang->name);
    fprintf(json,"  \"protocol\": \"%s\",\n",proto->name);
    fprintf(json,"  \"memAvgKb\": %f,\n",mem_avg->memAvgKb);
    fprintf(json,"  \"memMaxKb\": %f,\n",mem_avg->memMaxKb);
    fprintf(json,"  \"cpuAvg\": %f,\n",mem_avg->cpuAvg);
    fprintf(json,"  \"maxCpu\": %f,\n",mem_avg->maxCpu);
    fprintf(json,"  \"netOutKb\": %f,\n",mem_avg->netOutKb);
    fprintf(json,"  \"netInKb\": %f,\n",mem_avg->netInKb);
    fprintf(json,"  \"steadyCurrent_mA\": %f,\n",pwr_avg->steadyCurrent_mA);
    fprintf(json,"  \"runCurrent_mA\": %f,\n",pwr_avg->runCurrent_mA);
    fprintf(json,"  \"runEnergy_J\": %f,\n",pwr_avg->runEnergy_J);
    fprintf(json,"  \"runEnergy_mAs\": %f,\n",pwr_avg->runEnergy_mAs);
    fprintf(json,"  \"runEnergy_mAh\": %f,\n",pwr_avg->runEnergy_mAh);
    fprintf(json,"  \"time_ms\": %f,\n",pwr_avg->time_ms);
    fprintf(json,"  \"cycleTime_ms\": %f,\n",pwr_avg->cycleTime_ms);
    fprintf(json,"  \"estEnergy_mAh\": %f\n",pwr_avg->estEnergy_mAh);
    fprintf(json,"}\n");
    fclose(json);
}

#define EXTRACT_CODE(field,data) double extract_##field (pExecuteInfo info){ \
    return info->data.field; \
} \

EXTRACT_CODE(memAvgKb,mem)
EXTRACT_CODE(memMaxKb,mem)
EXTRACT_CODE(cpuAvg,mem)
EXTRACT_CODE(maxCpu,mem)
EXTRACT_CODE(netOutKb,mem)
EXTRACT_CODE(netInKb,mem)
EXTRACT_CODE(steadyCurrent_mA,power);
EXTRACT_CODE(runCurrent_mA,power);
EXTRACT_CODE(runEnergy_J,power);
EXTRACT_CODE(runEnergy_mAs,power);
EXTRACT_CODE(runEnergy_mAh,power);
EXTRACT_CODE(time_ms,power);
EXTRACT_CODE(cycleTime_ms,power);
EXTRACT_CODE(estEnergy_mAh,power);
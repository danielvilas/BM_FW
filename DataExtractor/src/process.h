//
// Created by dvilaspe on 16/05/2018.
//

#ifndef DATAEXTRACTOR_PROCESS_H
#define DATAEXTRACTOR_PROCESS_H

#include "config.h"
#include "power.h"
#include "memory.h"
struct sExecuteInfo{
    tPowerInfo power;
    tMemInfo mem;
    pName plat;
    pName lang;
    pName proto;
};
STRUCT_TYPES(ExecuteInfo)
VECTOR(ExecuteInfo)

void initAvg(pPowerInfo pwr_avg, pMemInfo mem_avg);
void finishAvg(pConfig cfg, pPowerInfo pwr_avg, pMemInfo mem_avg, int i);
void updateMemAvgAndFree(pMemInfo mem_avg, pMemInfo mem);
void updatePowerAvgAndFree(pPowerInfo pwr_avg, pPowerInfo pwr);
void printJsonData(char*dir, pName plat, pName lang, pName proto,pMemInfo mem_avg,pPowerInfo pwr_avg);

#define EXTRACT(field) double extract_##field(pExecuteInfo info);
EXTRACT(memAvgKb);
EXTRACT(memMaxKb);
EXTRACT(cpuAvg);
EXTRACT(maxCpu);
EXTRACT(netOutKb);
EXTRACT(netInKb);

EXTRACT(steadyCurrent_mA);
EXTRACT(runCurrent_mA);
EXTRACT(runEnergy_J);
EXTRACT(runEnergy_mAs);
EXTRACT(runEnergy_mAh);
EXTRACT(time_ms);
EXTRACT(cycleTime_ms);
EXTRACT(estEnergy_mAh);
#endif //DATAEXTRACTOR_PROCESS_H

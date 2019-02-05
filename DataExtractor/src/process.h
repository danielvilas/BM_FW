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

pExecuteInfo executeOne(char* dir, pConfig cfg, pName plat, pName lang, pName proto );
lxw_worksheet* createSumaryWorkSheet(lxw_workbook* workbook);
void fillSumaryWorkSheet(lxw_worksheet *worksheet,
                         pName plat, pName lang, pName proto,
                         pMemInfo mem_avg, pPowerInfo pwr_avg,
                         int col);


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

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

#endif //DATAEXTRACTOR_PROCESS_H

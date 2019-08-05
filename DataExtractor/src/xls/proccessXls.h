//
// Created by Daniel Vilas Perulan on 2019-07-31.
//

#ifndef DATAEXTRACTOR_PROCCESSXLS_H
#define DATAEXTRACTOR_PROCCESSXLS_H
#include "../process.h"

pExecuteInfo executeOne(char* dir, pConfig cfg, pName plat, pName lang, pName proto );
lxw_worksheet* createSumaryWorkSheet(lxw_workbook* workbook);
void fillSumaryWorkSheet(lxw_worksheet *worksheet,
                         pName plat, pName lang, pName proto,
                         pMemInfo mem_avg, pPowerInfo pwr_avg,
                         int col);

#endif //DATAEXTRACTOR_PROCCESSXLS_H

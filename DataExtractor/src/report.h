//
// Created by Daniel Vilas Perulan on 3/7/18.
//

#ifndef DATAEXTRACTOR_REPORT_H
#define DATAEXTRACTOR_REPORT_H


#include <xlsxwriter.h>
#include "config.h"
#include "process.h"

struct sReportInfo{
    double (*extractInfo)(pExecuteInfo info);
    char* chartName;
    char* units;
    char* tableName;
};

STRUCT_TYPES(ReportInfo)

void createReport(pConfig cfg, lxw_workbook *workbook, pExecuteInfo **table, char* name, pReportInfo reportAvgCfg);
void createDoubleReport(pConfig cfg, lxw_workbook *workbook, pExecuteInfo **table, char* name, pReportInfo reportAvgCfg,pReportInfo reportMaxCfg );

void fillReportCfg(tReportInfo *pInfo, double (*executeInfo)(pExecuteInfo), char *chartName,char* units,char* tableName);

#endif //DATAEXTRACTOR_REPORT_H

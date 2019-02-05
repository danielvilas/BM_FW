//
// Created by Daniel Vilas Perulan on 3/7/18.
//

#include "report.h"

void writeReport(lxw_worksheet *mem_worksheet, pConfig cfg,pExecuteInfo **table,char* tableName,double (*extractInfo)(pExecuteInfo info),int startRow){
    for(int iProto=0;iProto<cfg->nProtocols;iProto++){
        pExecuteInfo* row = table[iProto];
        worksheet_write_string (mem_worksheet, startRow + iProto+1, 0, row[0]->proto->name, NULL);
        for(int iLang=0;iLang<cfg->nLanguages;iLang++){
            for(int iPlat=0;iPlat<cfg->nPlatforms;iPlat++){
                int cIndex=iLang*cfg->nPlatforms+iPlat;
                pExecuteInfo  info = row[cIndex];
                char cName[255];
                sprintf(cName,"%s-%s",info->lang->name, info->plat->name);
                worksheet_write_string (mem_worksheet, startRow , cIndex+1, cName, NULL);
                worksheet_write_number(mem_worksheet, startRow + iProto+1,cIndex+1,extractInfo(info),NULL);
            }
        }
    }
    worksheet_write_string (mem_worksheet, startRow , 0, tableName, NULL);
}

void createReportChart(lxw_workbook *workbook, lxw_worksheet *mem_worksheet, pConfig cfg, char *name, pReportInfo chartCfg, int startRow,
                       int chartRow, int chartColum) {
    lxw_chart *chart = workbook_add_chart(workbook, LXW_CHART_COLUMN);
    chart_set_style(chart, 10);

    for(int iLang=0;iLang<cfg->nLanguages;iLang++){
        for(int iPlat=0;iPlat<cfg->nPlatforms;iPlat++) {
            int cIndex = iLang * cfg->nPlatforms + iPlat;
            lxw_chart_series*  series = chart_add_series(chart, NULL, NULL);
            chart_series_set_categories(series, name, startRow+ 1, 0, startRow+cfg->nProtocols, 0);
            chart_series_set_values(series,     name, startRow+ 1, cIndex+1, startRow+cfg->nProtocols, cIndex+1);
            chart_series_set_name_range(series, name, startRow, cIndex+1);
        }
    }

    /* Insert the chart into the worksheet. */
    chart_title_set_name(chart,        chartCfg->chartName);
    chart_axis_set_name(chart->y_axis, chartCfg->units);
    chart_legend_set_position(chart, LXW_CHART_LEGEND_BOTTOM);
    worksheet_insert_chart(mem_worksheet, chartRow + cfg->nProtocols+2,chartColum, chart);
}

void createDoubleReport(pConfig cfg, lxw_workbook *workbook, pExecuteInfo **table, char* name, pReportInfo reportAvgCfg,pReportInfo reportMaxCfg ) {
    lxw_worksheet *mem_worksheet = workbook_add_worksheet(workbook, name);
    writeReport(mem_worksheet,cfg,table,reportAvgCfg->tableName,reportAvgCfg->extractInfo,0);
    writeReport(mem_worksheet,cfg,table,reportMaxCfg->tableName,reportMaxCfg->extractInfo,cfg->nProtocols+2);
    createReportChart(workbook, mem_worksheet, cfg, name, reportAvgCfg, 0, cfg->nProtocols + 2, 1);
    createReportChart(workbook, mem_worksheet, cfg, name, reportMaxCfg, cfg->nProtocols + 2, cfg->nProtocols + 2, 9);

}

void createReport( pConfig cfg, lxw_workbook *workbook, pExecuteInfo **table, char* name, pReportInfo reportAvgCfg){
    lxw_worksheet *mem_worksheet = workbook_add_worksheet(workbook, name);
    writeReport(mem_worksheet,cfg,table,reportAvgCfg->tableName,reportAvgCfg->extractInfo,0);
    createReportChart(workbook, mem_worksheet, cfg, name, reportAvgCfg, 0, 1, 0);
}

void fillReportCfg(tReportInfo *pInfo, double (*executeInfo)(pExecuteInfo), char *chartName,char* units,char* tableName){
    pInfo->extractInfo=executeInfo;
    pInfo->chartName=chartName;
    pInfo->units=units;
    pInfo->tableName=tableName;
}
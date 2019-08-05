//
// Created by Daniel Vilas Perulan on 2019-07-31.
//

#include "powerXls.h"
#define HEADER_ROW 0
#define TITLE_ROW 1
#define START_ROW 2

#define FULL_TIME_COL 0
#define FULL_FLAG_COL 1
#define FULL_CURRENT_COL 2
#define FULL_MAS_COL 3
#define FULL_POWER_COL 4
#define GROUP_TIME_COL 5
#define GROUP_FLAG_COL 6
#define GROUP_CURRENT_COL 7
#define GROUP_MAS_COL 8
#define GROUP_POWER_COL 9
#define AVG_TIME_COL 10
#define AVG_CURRENT_COL 11

lxw_worksheet* createPowerWorkSheet(lxw_workbook* workbook,char* filename){
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, filename);
    worksheet_set_footer(worksheet,filename);
    worksheet_merge_range(worksheet,HEADER_ROW,FULL_TIME_COL,HEADER_ROW,FULL_POWER_COL,"Full",NULL);
    worksheet_write_string (worksheet, TITLE_ROW, FULL_TIME_COL, "time", NULL);//a2
    worksheet_write_string (worksheet, TITLE_ROW, FULL_FLAG_COL, "flag", NULL);//a2
    worksheet_write_string (worksheet, TITLE_ROW, FULL_CURRENT_COL, "current", NULL);//b2
    worksheet_write_string (worksheet, TITLE_ROW, FULL_MAS_COL, "mAs", NULL);//b2
    worksheet_write_string (worksheet, TITLE_ROW, FULL_POWER_COL, "power", NULL);//c2

    worksheet_merge_range(worksheet,HEADER_ROW,GROUP_TIME_COL,HEADER_ROW,GROUP_POWER_COL,"Aggregated",NULL);
    worksheet_write_string (worksheet, TITLE_ROW, GROUP_TIME_COL, "time", NULL);//d2
    worksheet_write_string (worksheet, TITLE_ROW, GROUP_FLAG_COL, "flag", NULL);//d2
    worksheet_write_string (worksheet, TITLE_ROW, GROUP_CURRENT_COL, "current", NULL);//e2
    worksheet_write_string (worksheet, TITLE_ROW, GROUP_MAS_COL, "mAs", NULL);//b2
    worksheet_write_string (worksheet, TITLE_ROW, GROUP_POWER_COL, "power", NULL);//f2

    worksheet_merge_range(worksheet,HEADER_ROW,AVG_TIME_COL,HEADER_ROW,AVG_CURRENT_COL,"Average",NULL);
    worksheet_write_string (worksheet, TITLE_ROW, AVG_TIME_COL, "time", NULL);//d2
    worksheet_write_string (worksheet, TITLE_ROW, AVG_CURRENT_COL, "current", NULL);//e2

    return worksheet;
}

void fillWorkSheetPowerData(pPowerInfo pwr, lxw_worksheet* worksheet){
    for(int i=0;i<pwr->fullData->size;i++) {
        worksheet_write_number(worksheet, i + START_ROW, FULL_TIME_COL, pwr->fullData->data[i].time, NULL);
        worksheet_write_number(worksheet, i + START_ROW, FULL_CURRENT_COL, pwr->fullData->data[i].current, NULL);
        worksheet_write_number(worksheet, i + START_ROW, FULL_POWER_COL, pwr->fullData->data[i].power, NULL);
        worksheet_write_number(worksheet, i + START_ROW, FULL_MAS_COL, pwr->fullData->data[i].mAmpsS, NULL);
        worksheet_write_number(worksheet, i + START_ROW, FULL_FLAG_COL, pwr->fullData->data[i].flag, NULL);
    }
    for(int i=0;i<pwr->groupData->size;i++){
        worksheet_write_number (worksheet, i+START_ROW, GROUP_TIME_COL, pwr->groupData->data[i].time, NULL);
        worksheet_write_number (worksheet, i+START_ROW, GROUP_CURRENT_COL, pwr->groupData->data[i].current, NULL);
        worksheet_write_number (worksheet, i+START_ROW, GROUP_POWER_COL, pwr->groupData->data[i].power, NULL);
        worksheet_write_number(worksheet, i + START_ROW, GROUP_MAS_COL, pwr->groupData->data[i].mAmpsS, NULL);
        worksheet_write_number(worksheet, i + START_ROW, GROUP_FLAG_COL, pwr->groupData->data[i].flag, NULL);
    }
    int limit = pwr->groupData->size;
    worksheet_write_number (worksheet, START_ROW, AVG_TIME_COL, pwr->groupData->data[0].time, NULL);
    worksheet_write_number (worksheet, START_ROW, AVG_CURRENT_COL, pwr->groupData->data[0].current, NULL);
    worksheet_write_number (worksheet, START_ROW+1, AVG_TIME_COL, pwr->groupData->data[1].time, NULL);
    worksheet_write_number (worksheet, START_ROW+1, AVG_CURRENT_COL, pwr->groupData->data[1].current, NULL);

    worksheet_write_number (worksheet, START_ROW+2, AVG_TIME_COL, pwr->groupData->data[1].time, NULL);
    worksheet_write_number (worksheet, START_ROW+2, AVG_CURRENT_COL, pwr->runCurrent_mA, NULL);
    worksheet_write_number (worksheet, START_ROW+3, AVG_TIME_COL, pwr->groupData->data[limit-2].time, NULL);
    worksheet_write_number (worksheet, START_ROW+3, AVG_CURRENT_COL, pwr->runCurrent_mA, NULL);

    worksheet_write_number (worksheet, START_ROW+4, AVG_TIME_COL, pwr->groupData->data[limit-2].time, NULL);
    worksheet_write_number (worksheet, START_ROW+4, AVG_CURRENT_COL, pwr->groupData->data[limit-2].current, NULL);
    worksheet_write_number (worksheet, START_ROW+5, AVG_TIME_COL, pwr->groupData->data[limit-1].time, NULL);
    worksheet_write_number (worksheet, START_ROW+5, AVG_CURRENT_COL, pwr->groupData->data[limit-1].current, NULL);

}

void createCurrentChart(lxw_workbook* workbook, lxw_worksheet *worksheet, pPowerInfo pwr, char* filename) {
    lxw_chart *chart = workbook_add_chart(workbook, LXW_CHART_SCATTER_STRAIGHT);
    int fsize=pwr->fullData->size;
    int gsize=pwr->groupData->size;

    lxw_chart_series*  series = chart_add_series(chart, NULL, NULL);
    chart_series_set_categories(series, filename, START_ROW, FULL_TIME_COL, fsize+1, FULL_TIME_COL);
    chart_series_set_values(series,     filename, START_ROW, FULL_CURRENT_COL, fsize+1, FULL_CURRENT_COL);
    chart_series_set_name_range(series, filename, 0, FULL_TIME_COL);

    series = chart_add_series(chart, NULL, NULL);
    chart_series_set_categories(series, filename, START_ROW, GROUP_TIME_COL, gsize+1, GROUP_TIME_COL);
    chart_series_set_values(series,     filename, START_ROW, GROUP_CURRENT_COL, gsize+1, GROUP_CURRENT_COL);
    chart_series_set_name_range(series, filename, 0, GROUP_TIME_COL);

    series = chart_add_series(chart, NULL, NULL);
    chart_series_set_categories(series, filename, START_ROW, AVG_TIME_COL, START_ROW+6, AVG_TIME_COL);
    chart_series_set_values(series,     filename, START_ROW, AVG_CURRENT_COL, START_ROW+6, AVG_CURRENT_COL);
    chart_series_set_name_range(series, filename, 0, AVG_TIME_COL);


    //Field string

    chart_title_set_name(chart,        "Current");
    chart_axis_set_name(chart->x_axis, "ms");
    chart_axis_set_name(chart->y_axis, "mAmps");
    /* Set an Excel chart style. */
    chart_set_style(chart, 10);
    /* Insert the chart into the worksheet. */
    worksheet_insert_chart(worksheet, CELL("I9"), chart);
}

void createPowerSheet(lxw_workbook* workbook,char* filename, pPowerInfo pwr){
    lxw_worksheet *worksheet = createPowerWorkSheet(workbook,filename);
    fillWorkSheetPowerData(pwr, worksheet);
    //Create charts
    createCurrentChart(workbook,worksheet,pwr,filename);
}

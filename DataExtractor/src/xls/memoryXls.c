//
// Created by Daniel Vilas Perulan on 2019-07-31.
//

#include "memoryXls.h"
void addMemSerie(char *filename, tvMemInfoEntry *mem, lxw_chart *chart, int field) {
    lxw_chart_series*  series = chart_add_series(chart, NULL, NULL);
    chart_series_set_categories(series, filename, 1, 0, mem->size, 0);  //Time
    chart_series_set_values(series,     filename, 1, field, mem->size, field);  //field
    chart_series_set_name_range(series, filename, 0, field);
}

lxw_worksheet* createMemWorkSheet(lxw_workbook* workbook,char* filename){
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, filename);
    worksheet_set_footer(worksheet,filename);
    worksheet_write_string (worksheet, 0, 0, "time", NULL);
    worksheet_write_string (worksheet, 0, 1, "cpu", NULL);
    worksheet_write_string (worksheet, 0, 2, "dCpu", NULL);
    worksheet_write_string (worksheet, 0, 3, "mem", NULL);
    worksheet_write_string (worksheet, 0, 4, "octIn", NULL);
    worksheet_write_string (worksheet, 0, 5, "octOut", NULL);
    return worksheet;
}

void fillWorkSheetMemoryData(pvMemInfoEntry mem, lxw_worksheet* worksheet){
    for(int i=0;i<mem->size;i++){
        worksheet_write_number (worksheet, i+1, 0, mem->data[i].time, NULL);
        worksheet_write_number (worksheet, i+1, 1, mem->data[i].cpu, NULL);
        worksheet_write_number (worksheet, i+1, 2, mem->data[i].dcpu, NULL);
        worksheet_write_number (worksheet, i+1, 3, mem->data[i].mem, NULL);
        worksheet_write_number (worksheet, i+1, 4, mem->data[i].oct_in, NULL);
        worksheet_write_number (worksheet, i+1, 5, mem->data[i].oct_out, NULL);
    }
}

void createCpuChart(lxw_workbook* workbook, lxw_worksheet *worksheet, pvMemInfoEntry mem, char* filename) {
    lxw_chart *chart = workbook_add_chart(workbook, LXW_CHART_LINE);
    addMemSerie(filename, mem, chart,1);//CPU
    addMemSerie(filename, mem, chart,2);//DPU
    //Field string

    chart_title_set_name(chart,        "Cpu Usage");
    chart_axis_set_name(chart->x_axis, "ms");
    chart_axis_set_name(chart->y_axis, "% usage");
    /* Set an Excel chart style. */
    chart_set_style(chart, 10);
    /* Insert the chart into the worksheet. */
    worksheet_insert_chart(worksheet, CELL("H2"), chart);
}
void createMemChart(lxw_workbook* workbook, lxw_worksheet *worksheet, pvMemInfoEntry mem, char* filename) {
    lxw_chart *chart = workbook_add_chart(workbook, LXW_CHART_LINE);
    addMemSerie(filename, mem, chart,3);//CPU
    //Field string

    chart_title_set_name(chart,        "Memory");
    chart_axis_set_name(chart->x_axis, "ms");
    chart_axis_set_name(chart->y_axis, "Mem");
    /* Set an Excel chart style. */
    chart_set_style(chart, 10);
    /* Insert the chart into the worksheet. */
    worksheet_insert_chart(worksheet, CELL("H17"), chart);
}


void createNetChart(lxw_workbook* workbook, lxw_worksheet *worksheet, pvMemInfoEntry mem, char* filename) {
    lxw_chart *chart = workbook_add_chart(workbook, LXW_CHART_LINE);
    addMemSerie(filename, mem, chart,4);
    addMemSerie(filename, mem, chart,5);
    //Field string

    chart_title_set_name(chart,        "Network");
    chart_axis_set_name(chart->x_axis, "ms");
    chart_axis_set_name(chart->y_axis, "Mem");
    /* Set an Excel chart style. */
    chart_set_style(chart, 10);
    /* Insert the chart into the worksheet. */
    worksheet_insert_chart(worksheet, CELL("H32"), chart);
}


void createMemSheet(lxw_workbook* workbook,char* filename, pvMemInfoEntry mem){
    lxw_worksheet *worksheet = createMemWorkSheet(workbook,filename);
    fillWorkSheetMemoryData(mem, worksheet);
    //Create charts
    createCpuChart(workbook,worksheet,mem,filename);
    createMemChart(workbook,worksheet,mem,filename);
    createNetChart(workbook,worksheet,mem,filename);
}
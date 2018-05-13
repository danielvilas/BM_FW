//
// Created by dvilaspe on 10/05/2018.
//

#include <stdlib.h>
#include "memory.h"
#include "common.h"

FILE* openFileMem(char* dir,pName plat, pName lang, pName proto, int i){
    return openFile(dir, plat, lang, proto, i,"MEM_");
}
int readForCheckAndSizeMem(FILE* file){
    char sInputBuf [BUFFER_SIZE];
    int line=0;
    tMemDataEntry entry;
    while (!feof(file)) {
        //First scan to check data and get size of lines
        // load line into static buffer
        if(fgets(sInputBuf, BUFFER_SIZE-1, file)==NULL)
            break;
        line++;
        if(line==1)continue;
        //printf(sInputBuf);

        sscanf(sInputBuf, "%lld;%ld;%ld;%ld;%ld;%ld;%ld", &entry.currentTs, &entry.total_time, &entry.total_utime,
               &entry.total_stime, &entry.virtual_size, &entry.in_octets, &entry.out_octets);
        //printf("%lld;%lld;%lld;%lld;%lld;%lld;%lld\n", entry.currentTs , entry.total_time, entry.total_utime,
        //       entry.total_stime,  entry.virtual_size, entry.in_octets, entry.out_octets);
    }
    return line;
}

pMemInfoEntry readDataMem(FILE* file, int lines){
    pMemInfoEntry data=(pMemInfoEntry )malloc(sizeof(tMemInfoEntry)*lines+1);
    pMemDataEntry read =(pMemDataEntry)malloc(sizeof(tMemDataEntry)*lines+1);

    int line=-2;
    char sInputBuf [BUFFER_SIZE];
    long long baseTs=0;
    //long baseIn_network;
    //long baseOut_Network;
    tMemDataEntry entry;
    while(!feof(file)){
        if(fgets(sInputBuf, BUFFER_SIZE-1, file)==NULL)
            break;
        line++;
        if(line==-1)continue;
        //printf(sInputBuf);
        sscanf(sInputBuf, "%lld;%ld;%ld;%ld;%ld;%ld;%ld\n", &entry.currentTs, &entry.total_time, &entry.total_utime,
               &entry.total_stime, &entry.virtual_size, &entry.in_octets, &entry.out_octets);
        read[line]=entry;
        if(line==0){
            baseTs=entry.currentTs;
        }

        long long time =entry.currentTs-baseTs;
        long cpuTime = entry.total_utime+entry.total_stime;
        long tTime = entry.total_time;

        long dTime;
        long dCpuTime;
        if(line!=0){
            dTime=tTime-read[line-1].total_time;
            data[line].oct_in=entry.in_octets - read[line-1].in_octets;
            data[line].oct_out=entry.out_octets - read[line-1].out_octets;
            dCpuTime=cpuTime-read[line-1].total_stime-read[line-1].total_utime;
        }else{
            dTime=tTime;
            data[line].oct_in=0;//entry.in_octets;
            data[line].oct_out=0;//entry.out_octets;
            dCpuTime=cpuTime;
        }
        data[line].time=time;
        data[line].mem=entry.virtual_size;

        if(tTime==0){
            data[line].cpu=0.0;
            data[line].dcpu=0.0;
        }else{
            data[line].cpu=((float)(cpuTime))/((float)tTime)*100.0;
            data[line].dcpu=((float)dCpuTime)/((float)dTime)*100.0;
        }
    }
    /*for(int i = 0;i<=line;i++){
        tMemDataEntry entry = read[i];
        printf("%lld;%lld;%lld;%lld;%lld;%lld;%lld\n", entry.currentTs , entry.total_time, entry.total_utime,
               entry.total_stime,  entry.virtual_size, entry.in_octets, entry.out_octets);
    }*/
    /*for(int i = 0;i<=line;i++){
        tMemInfoEntry entry = data[i];
        printf("%lld;%f;%f;%lld;%lld;%lld\n", entry.time , entry.cpu, entry.dcpu,
               entry.mem,  entry.oct_in, entry.oct_out);
    }
     */
    free(read);
    return data;
}

pvMemInfoEntry parseMemData(char* dir,pName plat, pName lang, pName proto, int i){
    FILE* file = openFileMem(dir,plat,lang,proto,i);
    if(file==0) return 0;

    int line = readForCheckAndSizeMem(file);

    //Reset the file if we have data
    fclose(file);
    if(line==0)return NULL;
    file = openFileMem(dir,plat,lang,proto,i);

    pMemInfoEntry data =readDataMem(file, line);
    fclose(file);
    if(data==0)return NULL;

    pvMemInfoEntry ret= malloc(sizeof(tvMemInfoEntry));
    ret->data=data;
    ret->size=line-1;
    return ret;
}

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
//
// Created by dvilaspe on 11/05/2018.
//

#include <stdlib.h>
#include "power.h"

//MOVE to cfg
#define CH1_MUL 1.0601
#define CH2_MUL 1.0575
#define R_SHUNT 0.12

FILE* openFilePower(char* dir, pName plat, pName lang, pName proto, int i){
    return openFile(dir, plat, lang, proto, i,"");
}


int readForCheckAndSizePower(FILE*  file, int* total){
    char sInputBuf [BUFFER_SIZE];
    int line=-1;
    int fline=0;
    tPowerDataEntry entry;
    int lastFlag=-1;
    while (!feof(file)) {
        //First scan to check data and get size of lines
        // load line into static buffer
        if(fgets(sInputBuf, BUFFER_SIZE-1, file)==NULL)
            break;

        //printf(sInputBuf);
        int r=sscanf(sInputBuf, "%lld,%f,%f,%f,%i", &entry.currentTs, &entry.chPlus, &entry.chMinus,&entry.diff,
               &entry.flag);
        if(r<5){
            break;
        }
        //printf("%lld,%f,%f,%f,%ld\n", entry.currentTs , entry.chPlus, entry.chMinus,entry.diff,  entry.flag);
        if(lastFlag!=entry.flag){
            line++;
            lastFlag=entry.flag;
        }
        fline++;
    }
    *total=fline;
    return line+1;
}

pPowerInfo readDataPower(FILE* file, int lines, int total){
    //printf("need %i Lines\n",lines);
    //return NULL;

    pPowerInfoEntry res_data=(pPowerInfoEntry )malloc(sizeof(tPowerInfoEntry)*(lines+2));
    pPowerInfoEntry data=(pPowerInfoEntry )malloc(sizeof(tPowerInfoEntry)*total);

    tPowerDataEntry lastRead;
    int rline=0;
    int fline=-1;
    char sInputBuf [BUFFER_SIZE];
    long long baseTs=0;
    //long baseIn_network;
    //long baseOut_Network;
    tPowerDataEntry entry;
    int lastFlag=-1;
    int cnt=0;
    while(!feof(file)){
        if(fgets(sInputBuf, BUFFER_SIZE-1, file)==NULL)
            break;
        //printf(sInputBuf);
        int r=sscanf(sInputBuf, "%lld,%f,%f,%f,%i", &entry.currentTs, &entry.chPlus, &entry.chMinus,&entry.diff,
               &entry.flag);
        //printf("%lld,%f,%f,%f,%ld\n", entry.currentTs , entry.chPlus, entry.chMinus,entry.diff,  entry.flag);
        if(r<5){
            break;
        }
        fline++;
        if(fline==0){
            baseTs=entry.currentTs;
        }

        long long time =entry.currentTs-baseTs;
        data[fline].time=time;
        data[fline].flag=entry.flag;

        entry.chPlus = entry.chPlus*CH1_MUL;
        entry.chMinus = entry.chMinus*CH2_MUL;

        float mAmp=(entry.chPlus-entry.chMinus)/R_SHUNT*1000.0;
        data[fline].current=mAmp;
        if(fline==0){
            data[fline].power=0;
        }else{
            data[fline].power=(data[fline].current+data[fline-1].current)/2000*
                    (entry.chMinus+lastRead.chMinus)/2*
                    (entry.currentTs-lastRead.currentTs)/1000;
            data[fline].mAmpsS=(data[fline].current+data[fline-1].current)/2*
                              (entry.currentTs-lastRead.currentTs)/1000;
        }
        if(lastFlag!=entry.flag){
            if(fline!=0){
                res_data[rline].current=res_data[rline].current/cnt;
                //res_data[rline].power=0;
               // fline++;
            }
            rline++;
            lastFlag=entry.flag;
            res_data[rline].time=data[fline].time;
            res_data[rline].current=data[fline].current;
            res_data[rline].power=data[fline].power;
            res_data[rline].mAmpsS=data[fline].mAmpsS;
            res_data[rline].flag=data[fline].flag;
            cnt=1;
        }else{
            res_data[rline].current+=data[fline].current;
            res_data[rline].power+=data[fline].power;
            res_data[rline].mAmpsS+=data[fline].mAmpsS;
            cnt++;
        }


        lastRead=entry;

    }
    res_data[0].time=0;
    res_data[0].current=res_data[1].current;
    res_data[0].power=0;
    res_data[0].mAmpsS=0;
    res_data[1].time=res_data[2].time;
    res_data[rline].current=res_data[rline].current/cnt;
    rline++;
    res_data[rline].time=data[fline].time;
    res_data[rline].current=res_data[rline-1].current;
    res_data[rline].power=0;
    res_data[rline].mAmpsS=0;
    fline++;
    rline++;

    pvPowerInfoEntry vData= malloc(sizeof(tvPowerInfoEntry));
    vData->data=data;
    vData->size=fline;

    pvPowerInfoEntry rData= malloc(sizeof(tvPowerInfoEntry));
    rData->data=res_data;
    rData->size=rline;


    pPowerInfo info = malloc(sizeof(tPowerInfo));
    info->fullData=vData;
    info->groupData=rData;

    float avg=0.0;
    float powerJ=0.0;
    float mas=0.0;
    for(int i=2;i<rline-2;i++){
        //if(i>1 && i< pwr->groupData->size-2){
            avg+=res_data[i].current/(rline-4);
            powerJ+=res_data[i].power;
            mas+=res_data[i].mAmpsS;
        //}
    }
    info->steadyCurrent_mA=res_data[0].current;
    info->runCurrent_mA=avg;
    info->runEnergy_J=powerJ;
    info->runEnergy_mAs=mas;
    info->runEnergy_mAh=mas/3600;
    info->time_ms=res_data[rline-2].time-res_data[1].time;

    return info;

    //return data;
}


pPowerInfo parsePowerData(char* dir,pName plat, pName lang, pName proto, int i){
    FILE* file = openFilePower(dir,plat,lang,proto,i);
    if(file==0) return 0;
    int fline;
    int line = readForCheckAndSizePower(file,&fline);

    //Reset the file if we have data
    fclose(file);
    if(line==0)return NULL;
    file = openFilePower(dir,plat,lang,proto,i);

    pPowerInfo data =readDataPower(file, line,fline);
    fclose(file);
    if(data==0)return NULL;


    return data;
}

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

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
        sscanf(sInputBuf, "%lld,%f,%f,%f,%i", &entry.currentTs, &entry.chPlus, &entry.chMinus,&entry.diff,
               &entry.flag);
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
        sscanf(sInputBuf, "%lld,%f,%f,%f,%i", &entry.currentTs, &entry.chPlus, &entry.chMinus,&entry.diff,
               &entry.flag);
        //printf("%lld,%f,%f,%f,%ld\n", entry.currentTs , entry.chPlus, entry.chMinus,entry.diff,  entry.flag);

        fline++;
        if(fline==0){
            baseTs=entry.currentTs;
        }

        long long time =entry.currentTs-baseTs;
        data[fline].time=time;

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
            cnt=1;
        }else{
            res_data[rline].current+=data[fline].current;
            res_data[rline].power+=data[fline].power;
            cnt++;
        }


        lastRead=entry;

    }
    res_data[0].time=0;
    res_data[0].current=res_data[1].current;
    res_data[0].power=0;
    res_data[1].time=res_data[2].time;
    res_data[rline].current=res_data[rline].current/cnt;
    rline++;
    res_data[rline].time=data[fline].time;
    res_data[rline].current=res_data[rline-1].current;
    res_data[rline].power=0;
    fline++;
    rline++;


    /*printf("Used: %i lines of %i\n",rline,lines);
    float power=0.0;
    for(int i = 0;i<=rline;i++){
        tPowerInfoEntry entry = res_data[i];
        printf("%lld;%f;%f\n", entry.time , entry.current, entry.power);
        if(i>0 && i< rline-1){
            power+=entry.power;
        }
    }*/
    //free(read);
    pvPowerInfoEntry vData= malloc(sizeof(tvPowerInfoEntry));
    vData->data=data;
    vData->size=fline;

    pvPowerInfoEntry rData= malloc(sizeof(tvPowerInfoEntry));
    rData->data=res_data;
    rData->size=rline;


    pPowerInfo info = malloc(sizeof(tPowerInfo));
    info->fullData=vData;
    info->groupData=rData;
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

lxw_worksheet* createPowerWorkSheet(lxw_workbook* workbook,char* filename){
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, filename);
    worksheet_set_footer(worksheet,filename);
    worksheet_merge_range(worksheet,0,0,0,2,"Full",NULL);
    worksheet_write_string (worksheet, 1, 0, "time", NULL);//a2
    worksheet_write_string (worksheet, 1, 1, "current", NULL);//b2
    worksheet_write_string (worksheet, 1, 2, "power", NULL);//c2

    worksheet_merge_range(worksheet,0,3,0,5,"Aggregated",NULL);
    worksheet_write_string (worksheet, 1, 3, "time", NULL);//d2
    worksheet_write_string (worksheet, 1, 4, "current", NULL);//e2
    worksheet_write_string (worksheet, 1, 5, "power", NULL);//f2

    worksheet_merge_range(worksheet,0,6,0,7,"Average",NULL);
    worksheet_write_string (worksheet, 1, 6, "time", NULL);//d2
    worksheet_write_string (worksheet, 1, 7, "current", NULL);//e2

    return worksheet;
}

void fillWorkSheetPowerData(pPowerInfo pwr, lxw_worksheet* worksheet){
    for(int i=0;i<pwr->fullData->size;i++) {
        worksheet_write_number(worksheet, i + 2, 0, pwr->fullData->data[i].time, NULL);
        worksheet_write_number(worksheet, i + 2, 1, pwr->fullData->data[i].current, NULL);
        worksheet_write_number(worksheet, i + 2, 2, pwr->fullData->data[i].power, NULL);
    }
    double avg=0.0;
    for(int i=0;i<pwr->groupData->size;i++){
        worksheet_write_number (worksheet, i+2, 3, pwr->groupData->data[i].time, NULL);
        worksheet_write_number (worksheet, i+2, 4, pwr->groupData->data[i].current, NULL);
        worksheet_write_number (worksheet, i+2, 5, pwr->groupData->data[i].power, NULL);
        if(i>1 && i< pwr->groupData->size-2){
            avg+=pwr->groupData->data[i].current/(pwr->groupData->size-4);
        }
    }
    int limit = pwr->groupData->size;
    worksheet_write_number (worksheet, 2, 6, pwr->groupData->data[0].time, NULL);
    worksheet_write_number (worksheet, 2, 7, pwr->groupData->data[0].current, NULL);
    worksheet_write_number (worksheet, 3, 6, pwr->groupData->data[1].time, NULL);
    worksheet_write_number (worksheet, 3, 7, pwr->groupData->data[1].current, NULL);

    worksheet_write_number (worksheet, 4, 6, pwr->groupData->data[1].time, NULL);
    worksheet_write_number (worksheet, 4, 7, avg, NULL);
    worksheet_write_number (worksheet, 5, 6, pwr->groupData->data[limit-2].time, NULL);
    worksheet_write_number (worksheet, 5, 7, avg, NULL);

    worksheet_write_number (worksheet, 6, 6, pwr->groupData->data[limit-2].time, NULL);
    worksheet_write_number (worksheet, 6, 7, pwr->groupData->data[limit-2].current, NULL);
    worksheet_write_number (worksheet, 7, 6, pwr->groupData->data[limit-1].time, NULL);
    worksheet_write_number (worksheet, 7, 7, pwr->groupData->data[limit-1].current, NULL);

}

void createCurrentChart(lxw_workbook* workbook, lxw_worksheet *worksheet, pPowerInfo pwr, char* filename) {
    lxw_chart *chart = workbook_add_chart(workbook, LXW_CHART_SCATTER_STRAIGHT);
    int fsize=pwr->fullData->size;
    int gsize=pwr->groupData->size;

    lxw_chart_series*  series = chart_add_series(chart, NULL, NULL);
    chart_series_set_categories(series, filename, 2, 0, fsize+1, 0);
    chart_series_set_values(series,     filename, 2, 1, fsize+1, 1);
    chart_series_set_name_range(series, filename, 0, 0);

    series = chart_add_series(chart, NULL, NULL);
    chart_series_set_categories(series, filename, 2, 3, gsize+1, 3);
    chart_series_set_values(series,     filename, 2, 4, gsize+1, 4);
    chart_series_set_name_range(series, filename, 0, 3);

    series = chart_add_series(chart, NULL, NULL);
    chart_series_set_categories(series, filename, 2, 6, 8, 6);
    chart_series_set_values(series,     filename, 2, 7, 8, 7);
    chart_series_set_name_range(series, filename, 0, 6);


    //Field string

    chart_title_set_name(chart,        "Current");
    chart_axis_set_name(chart->x_axis, "ms");
    chart_axis_set_name(chart->y_axis, "mAmps");
    /* Set an Excel chart style. */
    chart_set_style(chart, 10);
    /* Insert the chart into the worksheet. */
    worksheet_insert_chart(worksheet, CELL("H2"), chart);
}

void createPowerSheet(lxw_workbook* workbook,char* filename, pPowerInfo pwr){
    lxw_worksheet *worksheet = createPowerWorkSheet(workbook,filename);
    fillWorkSheetPowerData(pwr, worksheet);
    //Create charts
    createCurrentChart(workbook,worksheet,pwr,filename);
}

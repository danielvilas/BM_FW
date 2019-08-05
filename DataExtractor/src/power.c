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

            res_data[rline].time=data[fline].time;
            res_data[rline].current=data[fline].current;
            res_data[rline].power=data[fline].power;
            res_data[rline].mAmpsS=data[fline].mAmpsS;
            res_data[rline].flag=lastFlag;
            lastFlag=entry.flag;
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
    res_data[0].flag=1;
    res_data[1].time=res_data[2].time;
    res_data[1].flag=1;
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


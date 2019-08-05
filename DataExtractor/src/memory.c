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

pMemInfoEntry readDataMem(FILE* file, int lines, long long *retBase){
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
    *retBase=baseTs;
    free(read);
    return data;
}

pMemInfo parseMemData(char* dir,pName plat, pName lang, pName proto, int i){
    FILE* file = openFileMem(dir,plat,lang,proto,i);
    if(file==0) return 0;

    int line = readForCheckAndSizeMem(file);

    //Reset the file if we have data
    fclose(file);
    if(line==0)return NULL;
    file = openFileMem(dir,plat,lang,proto,i);

    long long baseTs;
    pMemInfoEntry data =readDataMem(file, line,&baseTs);
    fclose(file);
    if(data==0)return NULL;

    pvMemInfoEntry ret= malloc(sizeof(tvMemInfoEntry));
    ret->data=data;
    ret->size=line- 1;

    pMemInfo out = malloc(sizeof(tMemInfo));
    out->entries=ret;

    out->cpuAvg=0.0;
    out->maxCpu=0.0;
    out->memAvgKb=0.0;
    out->memMaxKb=0.0;
    out->netOutKb=0.0;
    out->netInKb=0.0;
    out->start=baseTs;

    for(int i = 0;i<ret->size;i++){

        out->cpuAvg+=data[i].dcpu/(ret->size);
        if(data[i].dcpu>out->maxCpu){
            out->maxCpu=data[i].dcpu;
        }
        out->memAvgKb+=data[i].mem/(ret->size);
        if(data[i].mem>out->memMaxKb) {
            out->memMaxKb = data[i].mem;
        }
        out->netOutKb+=data[i].oct_out;
        out->netInKb+=data[i].oct_in;
    }

    out->memAvgKb/=1024;
    out->memMaxKb/=1024;
    out->netOutKb/=1024;
    out->netInKb/=1024;

    return out;
}


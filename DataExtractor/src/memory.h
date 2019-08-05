//
// Created by dvilaspe on 10/05/2018.
//

#ifndef DATAEXTRACTOR_MEMORY_H
#define DATAEXTRACTOR_MEMORY_H

#include <stdio.h>
#include "config.h"
#include "common.h"

struct sMemDataEntry{
    long long currentTs; //uSeconds from Epcoh
    long total_time, // Number of Ticks from start
            total_utime, //Number of ticks used in userspace from start
            total_stime,//Number of ticks used in sysspace from start
            virtual_size, // Current memory in bytes
            in_octets, // number of bytes received
            out_octets; //number of bytes sent
};
STRUCT_TYPES(MemDataEntry)
//typedef struct sMemDataEntry tMemDataEntry;
//typedef tMemDataEntry* pMemDataEntry;

struct sMemInfoEntry{
    //Public
    long long time; // uSeconds from start app
    float cpu; //% cpu Total
    float dcpu; //%Cpu instantanous
    long mem; //Current memory in bytes
    long oct_out; // total number of bytes sent
    long oct_in; // total number of bytes received
};
STRUCT_TYPES(MemInfoEntry)
VECTOR(MemInfoEntry)

struct sMemInfo{
    float memAvgKb;
    float memMaxKb;
    float cpuAvg;
    float maxCpu;
    float netOutKb;
    float netInKb;
    long long start;
    pvMemInfoEntry entries;
};
STRUCT_TYPES(MemInfo)

pMemInfo parseMemData(char* dir,pName plat, pName lang, pName proto, int i);


#endif //DATAEXTRACTOR_MEMORY_H

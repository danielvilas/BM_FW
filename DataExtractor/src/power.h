//
// Created by dvilaspe on 11/05/2018.
//

#ifndef DATAEXTRACTOR_POWER_H
#define DATAEXTRACTOR_POWER_H
#include <stdio.h>
#include "config.h"
#include "common.h"
struct sPowerDataEntry{
    long long currentTs; //uSeconds from Epcoh
    float chPlus, // Recorded high (v)
            chMinus, //Recorded Low(v)
            diff;//recorded Diff(v)
    int flag; //number of bytes sent (01)
};
STRUCT_TYPES(PowerDataEntry)

struct sPowerInfoEntry{
    long long time; // uSeconds from start app
    float current; //% cpu Total
    float power;
    float mAmpsS;
};
STRUCT_TYPES(PowerInfoEntry)
VECTOR(PowerInfoEntry)

struct sPowerInfo{
    float steadyCurrent_mA;
    float runCurrent_mA;
    float runEnergy_J;
    float runEnergy_mAs;
    float runEnergy_mAh;
    float time_ms;
    float cycleTime_ms;
    float estEnergy_mAh;
    pvPowerInfoEntry fullData;
    pvPowerInfoEntry groupData;

};
STRUCT_TYPES(PowerInfo)
pPowerInfo parsePowerData(char* dir,pName plat, pName lang, pName proto, int i);
void createPowerSheet(lxw_workbook* workbook,char* filename, pPowerInfo pwr);

#endif //DATAEXTRACTOR_POWER_H

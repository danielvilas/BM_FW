//
// Created by Daniel Vilas Perulan on 2019-07-31.
//

#include "processInflux.h"
#include "influxdb.h"
#include "sys/socket.h"
#include "errno.h" //For errno - the error number
#include "netdb.h"	//hostent
#include "arpa/inet.h"


void sendMemory(tName *plat, tName *lang, tName *proto, int i,
                influx_client_t *client, tMemInfo *mem, char *suffix);

void sendPower(tName *plat, tName *lang, tName *proto, int i,
               influx_client_t *client, pvPowerInfoEntry pwr, long long memStart, char *suffix);

long long findStart(pvPowerInfoEntry data) {
    int j = 0;
    while (j < data->size && data->data[j].flag) {
        j++;
    }
    if (j == data->size)return 0;
    return data->data[j - 1].time;
}

 influx_client_t getClient(){
    influx_client_t client;
    client.host = "127.0.0.1";
    client.port = 8086;
    client.db = "bmfw";
    client.usr = "";
    client.pwd = "";
    if(getenv(ENV_INFLUXDB_HOST)!=NULL){
        client.host=getenv(ENV_INFLUXDB_HOST);
    }
    if(getenv(ENV_INFLUXDB_PORT)!=NULL){
        client.port=atoi(getenv(ENV_INFLUXDB_PORT));
    }
    if(getenv(ENV_INFLUXDB_DB)!=NULL){
        client.db=getenv(ENV_INFLUXDB_DB);
    }
    if(getenv(ENV_INFLUXDB_USR)!=NULL){
        client.usr=getenv(ENV_INFLUXDB_USR);
    }
    if(getenv(ENV_INFLUXDB_PWD)!=NULL){
        client.pwd=getenv(ENV_INFLUXDB_PWD);
    }

    if( inet_addr(client.host) == INADDR_NONE) {
        struct hostent *he;
        struct in_addr **addr_list;
        if ( (he = gethostbyname( client.host ) ) == NULL) {
		    // get the host info
		    herror("gethostbyname");
		    return client;
	    }
        addr_list = (struct in_addr **) he->h_addr_list;
        client.host = inet_ntoa(*addr_list[0]);
    }
    return client;
 }

pExecuteInfo executeOneInflux(char *dir, pConfig cfg, pName plat, pName lang, pName proto) {
    printf("Processing %s %s %s\n", plat->name, lang->name, proto->name);
    //For each File
    int i = 1;
    tPowerInfo pwr_avg;
    tMemInfo mem_avg;

    influx_client_t client = getClient(); 


    initAvg(&pwr_avg, &mem_avg);
    while (1) {
        pMemInfo mem = parseMemData(dir, plat, lang, proto, i);
        if (mem == NULL)break;

        sendMemory(plat, lang, proto, i, &client, mem, "");
        sendMemory(plat, lang, proto, i, &client, mem, "_Group");
        updateMemAvgAndFree(&mem_avg, mem);
        pPowerInfo pwr = parsePowerData(dir, plat, lang, proto, i);
        //printf("%s -> pwr->fullData->size %i\n",testName,pwr->fullData->size);ç

        sendPower(plat, lang, proto, i, &client, pwr->fullData, mem->start, "");
        sendPower(plat, lang, proto, i, &client, pwr->groupData, mem->start, "_Group");
        updatePowerAvgAndFree(&pwr_avg, pwr);
        i++;
    }
    //End for each file
    i--;

    finishAvg(cfg, &pwr_avg, &mem_avg, i);

    //printJsonData(dir,plat,lang, proto,&mem_avg,&pwr_avg);
    pExecuteInfo ret = malloc(sizeof(tExecuteInfo));
    ret->power = pwr_avg;
    ret->mem = mem_avg;
    ret->plat = plat;
    ret->lang = lang;
    ret->proto = proto;
    return ret;
}

void sendPower(tName *plat, tName *lang, tName *proto, int i,
               influx_client_t *client, pvPowerInfoEntry pwr, long long memStart, char *suffix) {
    char measureName[FILENAME_MAX];
    int w = sprintf(measureName, "%s_%s_%s%s", plat->name, lang->name, proto->name,suffix);
    measureName[w] = '\0';
    char testName[FILENAME_MAX];
    fillNameSuffixIndex(testName, lang, proto, i, "");

    long long start = memStart - findStart(pwr);
    for (int j = 0; j < pwr->size; j++) {
        int res = post_http(client,
                            INFLUX_MEAS(measureName),
                            INFLUX_TAG("testName", testName),
                            INFLUX_TAG("origin", "power"),
                            INFLUX_F_FLT("current", pwr->data[j].current, 2),
                            INFLUX_F_FLT("power", pwr->data[j].power, 2),
                            INFLUX_F_FLT("mAmpsS", pwr->data[j].mAmpsS, 2),
                            INFLUX_F_INT("flag", pwr->data[j].flag),
                            INFLUX_TS((pwr->data[j].time + start) * 1000000),
                            INFLUX_END);
        if (res != 0)printf("res: %i\n", res);
    }
}

void sendMemory(tName *plat, tName *lang, tName *proto, int i,
                influx_client_t *client, tMemInfo *mem, char *suffix) {
    char measureName[FILENAME_MAX];
    int w = sprintf(measureName, "%s_%s_%s%s", plat->name, lang->name, proto->name,suffix);
    measureName[w] = '\0';
    char testName[FILENAME_MAX];
    fillNameSuffixIndex(testName, lang, proto, i, "");

    for (int j = 0; j < mem->entries->size; j++) {
        int res = post_http(client,
                            INFLUX_MEAS(measureName),
                            INFLUX_TAG("testName", testName),
                            INFLUX_TAG("origin", "memory"),
                            INFLUX_F_FLT("cpu", mem->entries->data[j].cpu, 2),
                            INFLUX_F_FLT("dcpu", mem->entries->data[j].dcpu, 2),
                            INFLUX_F_INT("mem", mem->entries->data[j].mem),
                            INFLUX_F_INT("oct_out", mem->entries->data[j].oct_out),
                            INFLUX_F_INT("oct_in", mem->entries->data[j].oct_in),
                            INFLUX_TS((mem->entries->data[j].time + mem->start) * 1000000),
                            INFLUX_END);
        if (res != 0)printf("res: %i\n", res);
    }
}
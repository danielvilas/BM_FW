//
// Created by Daniel Vilas Perulan on 2019-07-31.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "config.h"
#include "process.h"
#include "influx/processInflux.h"

void printInfluxConfig(){
    influx_client_t client = getClient();
    printf("\n----- Influx Config -----\n");
    printf("host\t%s\t"ENV_INFLUXDB_HOST"=%s\n",client.host,getenv(ENV_INFLUXDB_HOST));
    printf("port\t%i\t"ENV_INFLUXDB_PORT"=%s\n",client.port,getenv(ENV_INFLUXDB_PORT));
    printf("db\t%s\t"ENV_INFLUXDB_DB"=%s\n",client.db,getenv(ENV_INFLUXDB_DB));
    printf("usr\t%s\t"ENV_INFLUXDB_USR"=%s\n",client.usr,getenv(ENV_INFLUXDB_USR));
    printf("pwd\t%s\t"ENV_INFLUXDB_PWD"=%s\n",client.pwd,getenv(ENV_INFLUXDB_PWD));
    
}

void execute(char* dir, pConfig cfg) {
    pName plat = cfg->firstPlatform;


    pExecuteInfo **table;
    table= malloc(cfg->nProtocols * sizeof(pExecuteInfo *));
    for (int i = 0; i < cfg->nProtocols; i++) {
        table[i] = (pExecuteInfo *) malloc(cfg->nLanguages*cfg->nPlatforms* sizeof(pExecuteInfo));
    }

    int iPlat=0;
    while(plat!=NULL){
        pName lang = cfg->firstLang;
        int plat_col=1;
        int iLang=0;
        while(lang!=NULL){
            pName proto=cfg->firstProtocol;
            int iProto=0;
            while(proto!=NULL){
                pExecuteInfo info =executeOneInflux(dir,cfg,plat,lang,proto);
                pExecuteInfo* row = table[iProto];
                row[iLang*cfg->nPlatforms+iPlat]=info;
                proto=proto->next;
                iProto++;
                //exit(0);//Debug process
            }
            lang=lang->next;
            iLang++;
        }
        plat=plat->next;
        iPlat++;
    }
}

int main(int argc, char** argv) {
    printf("BenchMark Framework Data Parser!\n");
    //return 0;

    if(argc<2){
        printf("Usage: %s <configFile> [raw_data_dir]\n",argv[0]);
        return -1;
    }

    tConfig cfg;

    if(readYaml(argv[1],&cfg)){
        return -1;
    }
    if(argc<3){
        printConfig(&cfg);
        printInfluxConfig();
    }else{
        //executeOne(argv[2],cfg.firstPlatform,cfg.firstLang,cfg.firstProtocol);
        execute(argv[2],&cfg);
    }

    return 0;
}
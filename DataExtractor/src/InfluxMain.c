//
// Created by Daniel Vilas Perulan on 2019-07-31.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "config.h"
#include "process.h"
#include "influx/processInflux.h"

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
    }else{
        //executeOne(argv[2],cfg.firstPlatform,cfg.firstLang,cfg.firstProtocol);
        execute(argv[2],&cfg);
    }

    return 0;
}
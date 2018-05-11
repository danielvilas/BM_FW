#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "config.h"
#include "common.h"
#include "memory.h"



FILE* openFilePower(char* dir, pName plat, pName lang, pName proto, int i){
    return openFile(dir, plat, lang, proto, i,"");
}


void executeOne(char* dir, pName plat, pName lang, pName proto ){
    char filename[FILENAME_MAX];
    char filePath[FILENAME_MAX];
    int w= fillName(filename,lang,proto);
    if(w==0)return;;
    w=sprintf(filePath,"%s/%s/%s.xlsx",dir,plat->name,filename);
    filePath[w]='\0';

    lxw_workbook  *workbook  = workbook_new(filePath);
    //For each File
    int i=1;
    while(1){
        fillNameSuffixIndex(filename,lang,proto,i,"MEM_");
        pvMemInfoEntry mem =parseMemData(dir,plat,lang,proto,i);
        if(mem==NULL)break;
        createMemSheet(workbook,filename,mem);
        free(mem->data);
        free(mem);
        i++;
    }
    //End for each file

    workbook_close(workbook);
    printf("Report: %s saved\n",filePath);
    return;
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
        executeOne(argv[2],cfg.firstPlatform,cfg.firstLang,cfg.firstProtocol);

    }

    return 0;
}
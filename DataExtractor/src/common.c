//
// Created by dvilaspe on 10/05/2018.
//

#include <stdio.h>
#include <ctype.h>
#include "common.h"
#include "config.h"

void ucaseFile(char* file){
    char* s=file;
    while(*s && (*s) !='.'){
        *s=toupper(*s);
        s++;
    }
}

int fillNameSuffixIndex(char* dest, pName lang, pName proto, int i,char * suffix ){
    int w=sprintf(dest,"%s_%s_%s%i",lang->name,proto->name,suffix,i);
    dest[w]='\0';
    ucaseFile(dest);
    return w;
}

int fillName(char* dest, pName lang, pName proto ){
    int w=sprintf(dest,"%s_%s",lang->name,proto->name);
    dest[w]='\0';
    ucaseFile(dest);
    return w;
}

FILE* openFile(char* dir,pName plat, pName lang, pName proto, int i,char * suffix){
    char filename[FILENAME_MAX];
    char filePath[FILENAME_MAX];
    int w= fillNameSuffixIndex(filename,lang,proto,i,suffix);
    if(w==0)return NULL;
    w=sprintf(filePath,"%s/%s/%s/%s/%s.txt",dir,plat->name,lang->name,proto->name,filename);
    filePath[w]='\0';
    FILE* file = fopen(filePath,"r");
    if(!file) {
        if(errno==ENOFILE){
            printf("%s: No such file or directory -> Stop finding\n",filePath); //Expected
        }else{
            perror(filePath);
        }
        return 0;
    }
    return file;
}




//
// Created by dvilaspe on 10/05/2018.
//

#ifndef DATAEXTRACTOR_COMMON_H
#define DATAEXTRACTOR_COMMON_H

#include "config.h"
#include <stdio.h>
#include <xlsxwriter.h>


#define BUFFER_SIZE 256    //Lines are 50 max chars
#define VECTOR(type) struct sv##type {int size; p##type data;}; typedef struct sv##type tv##type; typedef tv##type* pv##type;
#define STRUCT_TYPES(type) typedef struct s##type t##type; typedef t##type* p##type;


void ucaseFile(char* file);
FILE* openFile(char* dir,pName plat, pName lang, pName proto, int i,char * suffix);

int fillName(char* dest, pName lang, pName proto );
int fillNameSuffixIndex(char* dest, pName lang, pName proto, int i,char * suffix );

#endif //DATAEXTRACTOR_COMMON_H

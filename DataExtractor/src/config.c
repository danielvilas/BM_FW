#include "config.h"
#include <yaml.h>
#include <stdbool.h>

#define STR_PLATFORMS "platforms"
#define STR_PROTOCOLS "protocols"
#define STR_LANGUAGES "languages"
#define STR_NAME_PAR "name"
#define STR_ESTIMATION "estimation"
#define STR_CYCLES "cycles"
#define STR_INTERVAL "interval"


void debug(yaml_token_t token){
        switch(token.type)
    {
    /* Stream start/end */
    case YAML_STREAM_START_TOKEN: puts("STREAM START"); break;
    case YAML_STREAM_END_TOKEN:   /*puts("STREAM END");*/   break;
    /* Token types (read before actual token) */
    case YAML_KEY_TOKEN:   printf("(Key token)   "); break;
    case YAML_VALUE_TOKEN: printf("(Value token) "); break;
    /* Block delimeters */
    case YAML_BLOCK_SEQUENCE_START_TOKEN: puts("<b>Start Block (Sequence)</b>"); break;
    case YAML_BLOCK_ENTRY_TOKEN:          puts("<b>Start Block (Entry)</b>");    break;
    case YAML_BLOCK_END_TOKEN:            puts("<b>End block</b>");              break;
    /* Data */
    case YAML_BLOCK_MAPPING_START_TOKEN:  puts("[Block mapping]");            break;
    case YAML_SCALAR_TOKEN:  printf("scalar %s \n", token.data.scalar.value); break;
    /* Others */
    default:
      printf("Got token of type %d\n", token.type);
    }
}

enum {NONE, NAME_PAR,INTERVAL_PAR, CYCLES_PAR} lastParam;
enum {TOK_NONE, KEY,VALUE} lastToken;
enum eMode {
    MODE_START=0,
    MODE_GLOBAL,
    MODE_PLATFORMS,
    MODE_PROTOCOLS,
    MODE_LANGS,
    MODE_ESTIMATION,
    MODE_UNKNOWK
} parser_mode;
enum{NAME_NONE,NAME_START,NAME_DATA} name_mode;
pName lastName;


char* strClone(yaml_char_t* in){
    int s= strlen((const char*)in);
    char* ret = malloc((s+1)*sizeof(char));
    memcpy(ret,in,s);
    ret[s]='\0';
    return ret;
}

bool checkMode(yaml_token_t token){
    if(strcmp(STR_PLATFORMS,(const char*)token.data.scalar.value)==0){
        parser_mode=MODE_PLATFORMS;
        lastParam=NONE;
        return true;
    }
    if(strcmp(STR_PROTOCOLS,(const char*)token.data.scalar.value)==0){
        parser_mode=MODE_PROTOCOLS;
        lastParam=NONE;
        return true;
    }
    if(strcmp(STR_LANGUAGES,(const char*)token.data.scalar.value)==0){
        parser_mode=MODE_LANGS;
        lastParam=NONE;
        return true;
    }
    if(strcmp(STR_ESTIMATION,(const char*)token.data.scalar.value)==0){
        parser_mode=MODE_ESTIMATION;
        lastParam=NONE;
        return true;
    }
    return false;
}

void parseGlobal(yaml_token_t token, pConfig cfg){
    if(token.type==YAML_BLOCK_MAPPING_START_TOKEN ||
    token.type==YAML_KEY_TOKEN || token.type==YAML_VALUE_TOKEN)return;
    
    if(token.type==YAML_SCALAR_TOKEN){
        if(checkMode(token))return;
        printf("scalar %s \n", token.data.scalar.value);
        return;
    }
    debug(token);
}


void parseName(yaml_token_t token, pConfig cfg){
    if(token.type==YAML_KEY_TOKEN 
    || token.type==YAML_VALUE_TOKEN
    || token.type==YAML_BLOCK_END_TOKEN
    || token.type==YAML_BLOCK_MAPPING_START_TOKEN)return;
    
    
    if(token.type==YAML_BLOCK_SEQUENCE_START_TOKEN){
        name_mode=NAME_START;
        return;
    }
    if(token.type==YAML_BLOCK_ENTRY_TOKEN){
        pName newPlatform = malloc(sizeof(tName));
        newPlatform->next=NULL;
        if(name_mode==NAME_START){
            switch (parser_mode){
                case MODE_LANGS: cfg->firstLang=newPlatform; break;
                case MODE_PLATFORMS: cfg->firstPlatform=newPlatform; break;
                case MODE_PROTOCOLS: cfg->firstProtocol=newPlatform; break;
            }

            name_mode=NAME_DATA;
        }else if(name_mode==NAME_DATA){
            lastName->next=newPlatform;
        }
        lastName=newPlatform;
        return;
    }
    if(token.type==YAML_SCALAR_TOKEN){
        if(checkMode(token))return;     
        if(name_mode!=NAME_DATA){
            printf("Error Scalar %s \n", token.data.scalar.value);
            return;    
        }
        if(lastToken==KEY){
            if(strcmp(STR_NAME_PAR,(const char*)token.data.scalar.value)==0){
                lastParam=NAME_PAR;
            }
            return;
        }
         if(lastToken==VALUE){
            if(lastParam==NAME_PAR){
                lastName->name=strClone(token.data.scalar.value);
            }
            lastToken=TOK_NONE;
            return;
        }
        printf("Scalar %s \n", token.data.scalar.value);
        return;
    }
    debug(token);
}


void parseEstimation(yaml_token_t token, pConfig cfg){
    if(token.type==YAML_KEY_TOKEN
       || token.type==YAML_VALUE_TOKEN
       || token.type==YAML_BLOCK_END_TOKEN
       || token.type==YAML_BLOCK_MAPPING_START_TOKEN)return;


    if(token.type==YAML_BLOCK_SEQUENCE_START_TOKEN){
        return;
    }
    if(token.type==YAML_BLOCK_ENTRY_TOKEN){
        return;
    }
    if(token.type==YAML_SCALAR_TOKEN){
        if(checkMode(token))return;
        if(lastToken==KEY){
            if(strcmp(STR_CYCLES,(const char*)token.data.scalar.value)==0){
                lastParam=CYCLES_PAR;
            }else if(strcmp(STR_INTERVAL,(const char*)token.data.scalar.value)==0){
                lastParam=INTERVAL_PAR;
            }
            return;
        }
        if(lastToken==VALUE){
            if(lastParam==CYCLES_PAR){
                cfg->cycles=atoi(token.data.scalar.value);
            }else if(lastParam==INTERVAL_PAR){
                cfg->interval=atoi(token.data.scalar.value);
            }
            lastToken=TOK_NONE;
            return;
        }
        printf("Scalar %s \n", token.data.scalar.value);
        return;
    }
    debug(token);
}

int readYaml (char filename[], pConfig cfg){
    FILE *fh = fopen(filename, "r");
  yaml_parser_t parser;
  yaml_token_t token;
  parser_mode=MODE_START;
  name_mode=NAME_NONE;

  /* Initialize parser */
  if(!yaml_parser_initialize(&parser))
    fputs("Failed to initialize parser!\n", stderr);
  if(fh == NULL)
    fputs("Failed to open file!\n", stderr);

  /* Set input file */
  yaml_parser_set_input_file(&parser, fh);

  /* CODE HERE */
  do {
    yaml_parser_scan(&parser, &token);
    if(token.type==YAML_KEY_TOKEN){
        lastToken=KEY;
    }
    if(token.type==YAML_VALUE_TOKEN){
        lastToken=VALUE;
    }
    if(parser_mode==MODE_START){
        if(token.type==YAML_STREAM_START_TOKEN){
            parser_mode=MODE_GLOBAL;
        }else{
            debug(token);
        }
    }else if(parser_mode==MODE_GLOBAL){
        parseGlobal(token, cfg);
    }else if(parser_mode==MODE_ESTIMATION){
        parseEstimation(token, cfg);
    }else if(parser_mode==MODE_PLATFORMS){
        parseName(token, cfg);
    }else if(parser_mode==MODE_PROTOCOLS){
        parseName(token, cfg);
    }else if(parser_mode==MODE_LANGS){
        parseName(token, cfg);
    }else{
        debug(token);
    }
    if(token.type != YAML_STREAM_END_TOKEN)
      yaml_token_delete(&token);
  } while(token.type != YAML_STREAM_END_TOKEN);
  yaml_token_delete(&token);
  /* END new code */
  /* Cleanup */
  yaml_parser_delete(&parser);
  fclose(fh);
  return 0;
}

void printConfig(pConfig cfg){
    printf(STR_ESTIMATION":\n");
    printf("   "STR_CYCLES": %i\n",cfg->cycles);
    printf("   "STR_INTERVAL": %i\n",cfg->interval);

    printf(STR_PLATFORMS":\n");
    pName ptr = cfg->firstPlatform;
    while(ptr!=NULL){
        printf(" - "STR_NAME_PAR": %s\n",ptr->name);
        ptr=ptr->next;
    }
    printf(STR_PROTOCOLS":\n");
    pName ptProto = cfg->firstProtocol;
    while(ptProto!=NULL){
        printf(" - "STR_NAME_PAR": %s\n",ptProto->name);
        ptProto=ptProto->next;
    }
    printf(STR_LANGUAGES":\n");
    pName ptLang = cfg->firstLang;
    while(ptLang!=NULL){
        printf(" - "STR_NAME_PAR": %s\n",ptLang->name);
        ptLang=ptLang->next;
    }
    
    //printf(cfg->firstLang->cmd,"Hi\n");
}
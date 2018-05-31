/* Red Pitaya C API example Acquiring a signal from a buffer  
 * This application acquires a signal on a specific channel */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <sys/wait.h>
#include <stdint.h>
#include <signal.h>

static volatile int need_exit = 0;

long long current_timestamp() {
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000; // caculate milliseconds
    // printf("milliseconds: %lld\n", milliseconds);
    return milliseconds;
}

void readOne(uint32_t buff_size,float *buff_c1, float *buff_c2, long long currentTs ){
   /* rp_pinState_t pinState=0;
    rp_DpinGetState (RP_DIO0_P, &pinState);
    rp_AcqStart();
    rp_AcqSetTriggerSrc(RP_TRIG_SRC_NOW);
    rp_acq_trig_state_t state = RP_TRIG_STATE_TRIGGERED;
    
    while(1){
        rp_AcqGetTriggerState(&state);
        if(state == RP_TRIG_STATE_TRIGGERED){
            //printf("Trig sleep\n");
            usleep(1000);
            //printf("Trig sleep\n");
            break;
        }
    }
    
    rp_AcqGetOldestDataV(RP_CH_1, &buff_size, buff_c1);
    rp_AcqGetOldestDataV(RP_CH_2, &buff_size, buff_c2);
    
    int i;
    float mean_c1=0.0;
    float mean_c2=0.0;
    for(i = 0; i < buff_size; i++){
        mean_c1+=buff_c1[i]/buff_size;
        mean_c2+=buff_c2[i]/buff_size;
    }
    mean_c2*=10;
    mean_c1*=10;*/
    float mean_c1=4.60;
    float mean_c2=mean_c1-0.029;
    int pinState=0;
    printf("%lld,%f,%f,%f,%i\n",currentTs, mean_c1,mean_c2,mean_c1-mean_c2,pinState);
}

static void on_sigint(int unused)
{
    fprintf(stderr,"Cleaning and exiting\n");
    need_exit = 1;
}


int main(int argc, char **argv){

    /* Print error, if rp_Init() function failed */
    /*if(rp_Init() != RP_OK){
        fprintf(stderr, "Rp api init failed!\n");
    }*/
    
    signal(SIGINT, &on_sigint);
    siginterrupt(SIGINT, 1);
    signal(SIGTERM, &on_sigint);
    siginterrupt(SIGTERM, 1);

    uint32_t buff_size = 128;
    float *buff_c1 = (float *)malloc(buff_size * sizeof(float));
    float *buff_c2 = (float *)malloc(buff_size * sizeof(float));
/*
    rp_DpinSetDirection (RP_DIO0_P, RP_IN);
    rp_AcqReset();
    rp_AcqSetDecimation(3);
    rp_AcqSetTriggerDelay(0);
*/
   

    /* After acquisition is started some time delay is needed in order to acquire fresh samples in to buffer*/
    /* Here we have used time delay of one second but you can calculate exact value taking in to account buffer*/
    /*length and smaling rate*/

    fprintf(stderr,"start sleep\n");
    sleep(1);
    fprintf(stderr,"start done\n");
    while(!need_exit){
        long long currentTs = current_timestamp();
        readOne(buff_size,buff_c1,buff_c2, currentTs);
        long wait = 10 + currentTs - current_timestamp();
        if(wait>0) //Prevents infinite wait on debug
            usleep(wait * 1000);
        else
            fprintf(stderr,"lost\n");
    }
    /* Releasing resources */
    free(buff_c1);
    free(buff_c2);
   // rp_Release();

    return 0;
}


#include <xinu.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void stopwatch(void){
    int stopwatchcount=1;
    int Display[7]={0,0,0,0,0,0,0};
    char OnScreen;
    int i,j,k,c;
    while(1){
        wait(SongSem);


        j=stopwatchcount;
        c=0;
        while(j){
            k=j%10;
            j=j/10;
            Display[c]=k;
            c++;
            if(c>6){
                for(i=0;i<7;i++){
                    Display[i]=9;
                }
                break;
            }
        }
        for(i=c-1;i>=0;i--){
            OnScreen='0'+Display[i];
            fputc(OnScreen, SCREEN);
        }
        fputc(' ', SCREEN);
        if(stopwatchcount%10==0){
            send(RingProcessId,1);
        }
        stopwatchcount++;
        sleepms(1000);

        
        signal(SongSem);
    }
}

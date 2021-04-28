#include <xinu.h>
#include <stdio.h>
#include<string.h>
#include <stdlib.h>


void ring(void){

    umsg32 message;

    int i,j;

    while(1){

        message = receive();

        if(message!=0){
            char Lyric[5]="BEEP " ;
            fputc('\n',SCREEN);
            for(i=0;i<message;i++){
                for(j=0;j<5;j++){

                    fputc(Lyric[j], SCREEN);
                }
            }
            fputc('\n',SCREEN);
        }
    }
}
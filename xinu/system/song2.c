#include <xinu.h>
#include <stdio.h>


void song2(void){
    wait(SongSem);


    char Lyric1[100]="Started Playing an English Song         ";
    strcpy(SongText,Lyric1);
    fputc('\n',SCREEN);
    int i;
    for(i=0;i<100;i++){
        if(SongText[i]!=NULL) fputc(SongText[i], SCREEN);
    }

    sleepms(1000);

    char Lyric2[100]="Playing an English Song                 ";
    strcpy(SongText,Lyric2);
    fputc('\n',SCREEN);
    for(i=0;i<100;i++){
        if(SongText[i]!=NULL) fputc(SongText[i], SCREEN);
    }
    
    sleepms(1000);

    char Lyric3[100]="Completed Playing an English Song       ";
    strcpy(SongText,Lyric3);
    fputc('\n',SCREEN);
    for(i=0;i<100;i++){
        if(SongText[i]!=NULL) fputc(SongText[i], SCREEN);
    }


    fputc('\n',SCREEN);
    fputc('\n',SCREEN);
    fputc('\n',SCREEN);




    signal(SongSem);
}
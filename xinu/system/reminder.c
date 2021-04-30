#include<xinu.h>

void reminder(void){
    ReminderPoolId=mkbufpool(sizeof(struct bpentry),4);
	ReminderPoolTail=NULL;
	ReminderPoolHead=NULL;
    struct bpentry* headtemp;
    int i,j;
    while(1){
        headtemp=ReminderPoolHead;
        while(headtemp){ // print all the buffers using the while loop.
			if(headtemp->Reminder.Time==clktime && headtemp->Reminder.DoneRinging==0){
                char Lyric[9]="REMINDER " ;
                fputc('\n',SCREEN);
                for(i=0;i<headtemp->Reminder.NumberOfRings;i++){
                    for(j=0;j<30;j++){
                        if(headtemp->Reminder.ReminderMessage[j]==NULL) break;
                        fputc(headtemp->Reminder.ReminderMessage[j], SCREEN);
                    }
                    fputc(' ', SCREEN);
                    fputc(' ', SCREEN);
                }
                fputc('\n',SCREEN);
                headtemp->Reminder.DoneRinging=1;
            }
			headtemp=headtemp->bpnext;
		}
    }
}
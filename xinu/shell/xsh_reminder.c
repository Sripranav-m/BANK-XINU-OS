#include <xinu.h>

shellcmd xsh_reminder(int32 nargs, char *args[]) {
    if(nargs==4){
        NumberOfReminders++;
		if(ReminderPoolHead==NULL){ 
			struct bpentry* buffer=(struct bpentry*) getbuf(ReminderPoolId);
            buffer->Reminder.NumberOfRings=atoi(args[3]);
            buffer->Reminder.Time=atoi(args[1]);
            strcpy(buffer->Reminder.ReminderMessage,args[2]);
            buffer->Reminder.DoneRinging=0;
			buffer->bpnext=NULL;
			ReminderPoolHead=buffer;
			ReminderPoolTail=buffer;
		}
		else{
			if(NumberOfReminders>MAX_NUMBER_OF_REMINDERS){
                NumberOfReminders--;
				char* removingbuf=(char*) ReminderPoolHead;
				ReminderPoolHead=ReminderPoolHead->bpnext;
				freebuf(removingbuf);
			}
			struct bpentry* buffer=(struct bpentry*) getbuf(ReminderPoolId);
			buffer->Reminder.NumberOfRings=atoi(args[3]);
            buffer->Reminder.Time=atoi(args[1]);
            strcpy(buffer->Reminder.ReminderMessage,args[2]);
            buffer->Reminder.DoneRinging=0;
			buffer->bpnext=NULL;
			ReminderPoolTail->bpnext=buffer;
			ReminderPoolTail=buffer;
		}
    }
    else if(nargs==3){
        if(strcmp("show",args[1])==0){
            if(strcmp("all",args[2])==0){
                struct bpentry* headtemp;
                headtemp=ReminderPoolHead;
                int i,j;
                kprintf("Time\t\t");
                kprintf("ReminderMessage\t\t");
                kprintf("No of Rings\n");
                while(headtemp){ 
                    kprintf("%d\t\t",headtemp->Reminder.Time);
                    kprintf("%s\t\t",headtemp->Reminder.ReminderMessage);
                    kprintf("%d\n",headtemp->Reminder.NumberOfRings);
                    headtemp=headtemp->bpnext;
                }
            }
            if(strcmp("upcoming",args[2])==0){
                struct bpentry* headtemp;
                headtemp=ReminderPoolHead;
                int i,j;
                kprintf("Time\t\t");
                kprintf("ReminderMessage\t\t");
                kprintf("No of Rings\n");
                while(headtemp){ 
                    if(headtemp->Reminder.DoneRinging==0){
                        kprintf("%d\t\t",headtemp->Reminder.Time);
                        kprintf("%s\t\t",headtemp->Reminder.ReminderMessage);
                        kprintf("%d\n",headtemp->Reminder.NumberOfRings);
                    }
                    headtemp=headtemp->bpnext;
                }
            }
        }
    }
    else{
        kprintf("\nFollow the following Format:\n");
        kprintf("'reminder [time] [message] [number-of-rings] : to set reminder\n");
        kprintf("'reminder show all: To show reminders\n");
        kprintf("'reminder show upcoming: To show upcoming reminders\n");
    }
	return 0;
}

#include <xinu.h>
#include <stdio.h>
#include <string.h>



shellcmd xsh_stopwatch(int32 nargs, char *args[]) {
	
	if(nargs==2){
        if(strcmp(args[1],"start")==0){
            if(StopWatchProcessId){
                kprintf("\n Already a stopwatch is running ... \n");
            }
            else{
                StopWatchProcessId=create(stopwatch,8192,25,"StopWatch",0);
                resume(StopWatchProcessId);
            }
        }
        else if(strcmp(args[1],"stop")==0){
            if(StopWatchProcessId){
                kprintf("\n Stopped the StopWatch ... \n");
                kill(StopWatchProcessId);
                StopWatchProcessId=0;
            }
            else{
                kprintf("\n No stopwatch is running ... \n");
            }
        }
        else if(strcmp(args[1],"resume")==0){
            if(StopWatchProcessId){
                kprintf("\n Resumed the StopWatch ... \n");
                resume(StopWatchProcessId);
            }
            else{
                kprintf("\n No stopwatch is running ... \n");
            }
        }
        else if(strcmp(args[1],"pause")==0){
            if(StopWatchProcessId){
                kprintf("\n Paused the StopWatch ... \n");
                pri16 SuspendedStopWatchProcessPri=suspend(StopWatchProcessId);
                //kprintf("\nThe Return Value is : %d\n",SuspendedStopWatchProcessPri);
            }
            else{
                kprintf("\n No stopwatch is running ... \n");
            }
        }
        else if(strcmp(args[1],"help")==0){
            kprintf("\n The available Commands are : ");
            kprintf("\n 'stopwatch start' ");
            kprintf("\n 'stopwatch stop' ");
            kprintf("\n 'stopwatch resume' ");
            kprintf("\n 'stopwatch pause' \n");
        }
    }
    else{
        kprintf("\n The available Commands are : ");
        kprintf("\n 'stopwatch start' ");
        kprintf("\n 'stopwatch stop' ");
        kprintf("\n 'stopwatch resume' ");
        kprintf("\n 'stopwatch pause' \n");
    }

	
	return 0;
}

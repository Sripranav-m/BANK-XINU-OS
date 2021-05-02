#include<xinu.h>

void review(void){
    wait(ScreenSem);
    AllocatedResources[2][1]=1;
    clearScreen();

    int i;
    char* Ss="$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
    char* Rev1="\nHow Do You Like Our Bank Services?\n";
    char* Rev2="Please Give us your review\n";
    char* Rev5="Please Provide your review after 10 seconds...\n";
    char* Rev4="Please Provide your review now...\n\n";
    char* Rev6="Your ";
    char* Se="\n\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
    for(i=0;i<strlen(Ss);i++){
        fputc(Ss[i],SCREEN);
    }
    for(i=0;i<strlen(Rev1);i++){
        fputc(Rev1[i],SCREEN);
    }
    for(i=0;i<strlen(Rev2);i++){
        fputc(Rev2[i],SCREEN);
    }
    for(i=0;i<strlen(Rev5);i++){
        fputc(Rev5[i],SCREEN);
    }

    sleepms(10000);


    wait(KeyboardSem);
    AllocatedResources[2][0]=1;


    kill(ShellProcessId);
    ShellProcessId=0;


    for(i=0;i<strlen(Rev4);i++){
        fputc(Rev4[i],SCREEN);
    }
    kprintf("\nReview : \t");
    int val,j;
    char Comment[1000];
    val=fgetc(CONSOLE);
    i=0;j=0;
    while(val!=10){
        if(i<1000) Comment[i]='\x00'+(val);
        i++;
        j=i;
        val=fgetc(CONSOLE);
    }
    for(i=0;i<strlen(Rev6);i++){
        fputc(Rev6[i],SCREEN);
    }
    for(i=0;i<j;i++){
        if(Comment[i]!=NULL) fputc(Comment[i],SCREEN);
    }
    for(i=0;i<strlen(Se);i++){
        fputc(Se[i],SCREEN);
    }


    ShellProcessId=create(shell, 50, 50, "shell", 1, CONSOLE);
	resume(ShellProcessId);


    signal(KeyboardSem);
    AllocatedResources[2][0]=0;


    signal(ScreenSem);
    AllocatedResources[2][1]=0;
}

void comment(void){
    wait(KeyboardSem);
    AllocatedResources[1][0]=1;


    kill(ShellProcessId);
    ShellProcessId=0;


    kprintf("\n Comment:\t");
    int val,i,j;
    char Comment[1000];
    val=fgetc(CONSOLE);
    i=0;j=0;
    while(val!=10){
        if(i<1000) Comment[i]='\x00'+(val);
        val=fgetc(CONSOLE);
        i++;
        j=i;
    }


    wait(ScreenSem);
    AllocatedResources[1][1]=1;
    

    char* Ss="\n\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
    char* Rev1="\nThanks for providing your valuale comment...\n";
    char* Rev2="You Wrote :\n\n";
    for(i=0;i<strlen(Ss);i++){
        fputc(Ss[i],SCREEN);
    }
    for(i=0;i<strlen(Rev1);i++){
        fputc(Rev1[i],SCREEN);
    }
    for(i=0;i<strlen(Rev2);i++){
        fputc(Rev2[i],SCREEN);
    }
    for(i=0;i<j;i++){
        if(Comment[i]!=NULL) fputc(Comment[i],SCREEN);
    }
    fputc('\n',SCREEN);
    for(i=0;i<strlen(Ss);i++){
        fputc(Ss[i],SCREEN);
    }


    ShellProcessId=create(shell, 50, 50, "shell", 1, CONSOLE);
	resume(ShellProcessId);


    signal(ScreenSem);
    AllocatedResources[1][1]=0;


    signal(KeyboardSem);
    AllocatedResources[1][0]=0;
}
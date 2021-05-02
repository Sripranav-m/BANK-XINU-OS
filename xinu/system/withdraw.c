#include<xinu.h>



void withdraw(void){
    wait(TransactionSem);//wait the transaction semaphore 

    int i,j;
    char* L="***************************************************";
    for(j=0;j<strlen(L);j++){
        fputc(L[j], SCREEN);
    }
    umsg32 message;
    message=receive();
    ///////////////////////////////////////STAGE 1 : SAY STARTED /////////////////////////////////////
    fputc('\n', SCREEN);
    char* Lyric="Started Withdraw Process with amount Rs " ;
    for(j=0;j<strlen(Lyric);j++){
        fputc(Lyric[j], SCREEN);
    }
    int Display[10]={0,0,0,0,0,0,0,0,0,0};
    char OnScreen;
    j=message;
    int c=0,k;
    while(j){
        k=j%10;
        j=j/10;
        Display[c]=k;
        c++;
        if(c>9){
            for(i=0;i<10;i++){
                Display[i]=9;
            }
            break;
        }
    }
    if(c==0){
        fputc('0', SCREEN);
    }
    for(i=c-1;i>=0;i--){
        OnScreen='0'+Display[i];
        fputc(OnScreen, SCREEN);
    }

    fputc('\n', SCREEN);fputc('\n', SCREEN);

    sleepms(1000);fputc('.',SCREEN);fputc('.',SCREEN);fputc('.',SCREEN);
    sleepms(1000);fputc('.',SCREEN);fputc('.',SCREEN);fputc('.',SCREEN);
    sleepms(1000);fputc('.',SCREEN);fputc('.',SCREEN);fputc('.',SCREEN);
    sleepms(1000);fputc('.',SCREEN);fputc('.',SCREEN);fputc('.',SCREEN);
    sleepms(1000);
    ///////////////////////////////////////STAGE 2 : PROCESS THE Withdrawl /////////////////////////////////////
    struct bpentry* headtemp;
    headtemp=BankAccountPoolHead;
    while(headtemp){
        if(strcmp(headtemp->BankAccount.AccountNumber,LoggedInUserAccount)==0 && strcmp(headtemp->BankAccount.UserName,LoggedInUserName)==0){
            break;
        }
        headtemp=headtemp->bpnext;
    }
    if(headtemp->BankAccount.Balance>message){
        char* Lyricc="\nWithdrawing" ;
        for(j=0;j<strlen(Lyricc);j++){
            fputc(Lyricc[j], SCREEN);
        }
        fputc('\n',SCREEN);


        sleepms(1000);fputc('.',SCREEN);fputc('.',SCREEN);fputc('.',SCREEN);
        sleepms(1000);fputc('.',SCREEN);fputc('.',SCREEN);fputc('.',SCREEN);
        sleepms(1000);fputc('.',SCREEN);fputc('.',SCREEN);fputc('.',SCREEN);
        sleepms(1000);fputc('.',SCREEN);fputc('.',SCREEN);fputc('.',SCREEN);
        sleepms(1000);

        ///////////////////////////////////////STAGE 3 : DO THE WITHDRAW AND DONE /////////////////////////////////////

        headtemp->BankAccount.Balance-=message;

        char* Lyriccc="\Withdrawed the amount" ;
        fputc('\n',SCREEN);
        for(j=0;j<strlen(Lyriccc);j++){
            fputc(Lyriccc[j], SCREEN);
        }
        fputc('\n', SCREEN);
        char* Lyricccc="Balance in Your Account is: Rs " ;
        fputc('\n',SCREEN);
        for(j=0;j<strlen(Lyricccc);j++){
            fputc(Lyricccc[j], SCREEN);
        }
        int Displayy[10]={0,0,0,0,0,0,0,0,0,0};
        j=headtemp->BankAccount.Balance;
        c=0;
        while(j){
            k=j%10;
            j=j/10;
            Displayy[c]=k;
            c++;
            if(c>9){
                for(i=0;i<10;i++){
                    Displayy[i]=9;
                }
                break;
            }
        }
        if(c==0){
            fputc('0', SCREEN);
        }
        for(i=c-1;i>=0;i--){
            OnScreen='0'+Displayy[i];
            fputc(OnScreen, SCREEN);
        }
        fputc('\n', SCREEN);
        fputc('\n', SCREEN);

        for(j=0;j<strlen(L);j++){
            fputc(L[j], SCREEN);
        }
        fputc('\n', SCREEN);
        fputc('\n', SCREEN);
    }

    else{
        char* Lyricc="\nNo Sufficient Balance to Withdraw\n" ;
        for(j=0;j<strlen(Lyricc);j++){
            fputc(Lyricc[j], SCREEN);
        }
        fputc('\n',SCREEN);
        for(j=0;j<strlen(L);j++){
            fputc(L[j], SCREEN);
        }
        fputc('\n', SCREEN);
        fputc('\n', SCREEN);
        send(RingProcessId,2);
    }
    signal(TransactionSem);//signal the transaction semaphore 
}
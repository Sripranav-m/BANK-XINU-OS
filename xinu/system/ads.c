#include<xinu.h>

void ads(void){
    int AdIdToShow=0,i;
    char* Ad1;
    char* Ad2;
    char* Ss;
    char* Se;

    while(1){
        wait(ScreenSem);
        AllocatedResources[0][1]=1;
        AvailableResources[1]=0;

        AdIdToShow++;
        AdIdToShow=AdIdToShow%5;
        Ss ="\n\n######################   ADVERTISEMENT   ######################\n";
        if(AdIdToShow==0){
        Ad1="#####     Make A Smart Move and Switch Your Home Loan     #####";
        Ad2="#####     To our Bank at just 9%Interest (T&C apply)      #####";
        }
        else if(AdIdToShow==1){
        Ad1="#####    Use our Credit Card and Get 10X Reward Points    #####";
        Ad2="#####     On Dining, Movies, Shopping and much more       #####";
        }
        else if(AdIdToShow==2){
        Ad1="#####        Worried about Your Education Cost?           #####";
        Ad2="#####    Get a Student Loan at just 1%pa interest         #####";
        }
        else if(AdIdToShow==3){
        Ad1="#####    Open your Deemat Account with our Bank           #####";
        Ad2="#####    And start trading with just 0.5% brokerage       #####";
        }
        else{
        Ad1="#####   High Returns+Full Liquidity : Start your          #####";
        Ad2="#####   Fixed Deposit with our bank at 10%interest        #####";
        }
        Se="###############################################################\n\n";
        for(i=0;i<strlen(Ss);i++){
            fputc(Ss[i],SCREEN);
        }
        for(i=0;i<strlen(Ad1);i++){
            fputc(Ad1[i],SCREEN);
        }
        fputc('\n',SCREEN);
        for(i=0;i<strlen(Ad2);i++){
            fputc(Ad2[i],SCREEN);
        }
        fputc('\n',SCREEN);
        for(i=0;i<strlen(Se);i++){
            fputc(Se[i],SCREEN);
        }

        signal(ScreenSem);
        AllocatedResources[0][1]=0;
        AvailableResources[1]=1;
        
        sleepms(30000);
    }
}
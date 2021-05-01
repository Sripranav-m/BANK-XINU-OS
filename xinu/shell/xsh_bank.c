#include <xinu.h>

shellcmd xsh_bank(int32 nargs, char *args[]) {
    if(nargs==2 && strcmp(args[1],"addaccount")==0){
        kprintf("\nPlease Fill the Following Details\n");
        kprintf("========================================================\n");
        //////////////////////////////////////ASK USER NAME////////////////////////////////////////
        kprintf("UserName           :\t");
        int val;
        int i,j,k,c;
        char UserName[20];
        for(i=0;i<20;i++){
            UserName[i]=NULL;
        }
        val=fgetc(CONSOLE);
        i=0;j=0;
        while(val!=10){
            if(i<20) UserName[i]='a'+(val-97);
            val=fgetc(CONSOLE);
            i++;
        }
        if(i>20){
            kprintf("\nThe account name should be less than 20 characters\n");
            send(RingProcessId,1);
            exit();
        }
        for(j=0;j<i;j++){
            if(UserName[j]<'a' || UserName[j]>'z'){
                kprintf("\nThe account name should only contain small case english alphabets\n");
                send(RingProcessId,1);
                exit();
                break;
            }
        }
        //////////////////////////////////////CHECK USER NAME IF ALREADY EXISTS////////////////////////////////////////
        struct bpentry* headtemp;
        headtemp=BankAccountPoolHead;
        i=0;
        while(headtemp){
            if(strcmp(headtemp->BankAccount.UserName,UserName)==0){
                i=1;
                break;
            }
            headtemp=headtemp->bpnext;
        }
        if(i==1){
            kprintf("\nAlready a User exists with the following Name\n");
            send(RingProcessId,5);
        }
        else{
            //////////////////////////////////////ASK USER PASSWORD////////////////////////////////////////
            kprintf("\nPassWord           :\t");
            char Password[10];
            for(i=0;i<10;i++){
                Password[i]=NULL;
            }
            val=fgetc(CONSOLE);
            i=0;j=0;
            while(val!=10){
                if(i<10) Password[i]='0'+(val-48);
                val=fgetc(CONSOLE);
                i++;
            }
            if(i>10){
                kprintf("\nThe password length should be less than 10\n");
                send(RingProcessId,1);
                exit();
            }
            for(j=0;j<i;j++){
                if(Password[j]<'0' || Password[j]>'9'){
                    kprintf("\nThe account password should only contain numbers from 0 to 9\n");
                    send(RingProcessId,1);
                    exit();
                    break;
                }
            }
            //////////////////////////////////////RE ASK USER PASSWORD////////////////////////////////////////
            kprintf("\ReEnter            :\t");
            char PPassword[10];
            for(i=0;i<10;i++){
                PPassword[i]=NULL;
            }
            val=fgetc(CONSOLE);
            i=0;
            while(val!=10){
                if(i<10) PPassword[i]='0'+(val-48);
                val=fgetc(CONSOLE);
                i++;
            }
            if(i>10){
                kprintf("\nThe password length should be less than 10\n");
                send(RingProcessId,1);
                exit();
            }
            for(j=0;j<i;j++){
                if(PPassword[j]<'0' || PPassword[j]>'9'){
                    kprintf("\nThe account password should only contain numbers from 0 to 9\n");
                    send(RingProcessId,1);
                    exit();
                    break;
                }
            }
            if(strcmp(Password,PPassword)!=0){
                kprintf("Password Mismatch Occured...");
                send(RingProcessId,1);
            }
            else{
                //////////////////////////////////////ASSIGN ACCOUNT NUMBER////////////////////////////////////////
                TotalBankAccounts+=1;
                int UserAccountNumber=TotalBankAccounts;
                int AccountNum[5]={0,0,0,0,0};
                j=UserAccountNumber;
                c=0;
                while(j){
                    k=j%10;
                    j=j/10;
                    AccountNum[c]=k;
                    c++;
                }
                char UserAccount[5]={'0','0','0','0','0'};
                for(i=0;i<5;i++){
                    UserAccount[i]='0'+AccountNum[4-i];
                }

                kprintf("\nYour Account Number:\t");
                kprintf("%s\n",UserAccount);

                if(BankAccountPoolHead==NULL){ 
                    struct bpentry* buffer=(struct bpentry*) getbuf(BankAccountPoolId);
                    strcpy(buffer->BankAccount.UserName,UserName);
                    strcpy(buffer->BankAccount.UserPassword,Password);
                    strcpy(buffer->BankAccount.AccountNumber,UserAccount);
                    buffer->BankAccount.Balance=0;
                    buffer->bpnext=NULL;
                    BankAccountPoolHead=buffer;
                    BankAccountPoolTail=buffer;
                }
                else{
                    struct bpentry* buffer=(struct bpentry*) getbuf(BankAccountPoolId);
                    strcpy(buffer->BankAccount.UserName,UserName);
                    strcpy(buffer->BankAccount.UserPassword,Password);
                    strcpy(buffer->BankAccount.AccountNumber,UserAccount);
                    buffer->BankAccount.Balance=0;
                    buffer->bpnext=NULL;
                    BankAccountPoolTail->bpnext=buffer;
                    BankAccountPoolTail=buffer;
                }
            }
        }
        kprintf("========================================================\n\n");
    }

    else if(nargs==3 && strcmp(args[1],"account")==0 && strcmp(args[2],"rules")==0){
        kprintf("\nFollow The Rules given below while creating an account\n");
        kprintf("\nThe account Name should only contain small case english alphabets");
        kprintf("\nThe account Name should be less than 20 characters");
        kprintf("\nThe account Password should only contain numbers from 0 to 9");
        kprintf("\nThe account Password length should be less than 10\n\n");

    }

    else if(nargs==4 && strcmp(args[1],"account")==0 && strcmp(args[2],"show")==0 && strcmp(args[3],"all")==0){
        struct bpentry* headtemp;
        headtemp=BankAccountPoolHead;
        int i,j;
        char UN[20]="UserName            ";
        char UA[15]="AccountNumber  ";
        char BA[10]="Balance \n\n";
        for(i=0;i<20;i++){
            fputc(UN[i], SCREEN);
        }
        for(i=0;i<15;i++){
            fputc(UA[i], SCREEN);
        }
        for(i=0;i<10;i++){
            fputc(BA[i], SCREEN);
        }
        while(headtemp){
            for(i=0;i<20;i++){
                if(headtemp->BankAccount.UserName[i]!=NULL) fputc(headtemp->BankAccount.UserName[i], SCREEN);
                else break;
            }
            for(j=i;j<20;j++){
                fputc(' ', SCREEN);
            }
            for(i=0;i<5;i++){
                fputc(headtemp->BankAccount.AccountNumber[i], SCREEN);
            }
            for(j=0;j<10;j++){
                fputc(' ', SCREEN);
            }

            int Display[10]={0,0,0,0,0,0,0,0,0,0};
            char OnScreen;
            j=headtemp->BankAccount.Balance;
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
            fputc(' ', SCREEN);
            fputc('\n', SCREEN);
            headtemp=headtemp->bpnext;
        }
    }

    else{
        kprintf("\nAvailable Commands are:\n");
        kprintf("bank addaccount\n");
        kprintf("bank account rules\n");
        kprintf("bank account show all\n\n");
    }
	return 0;
}
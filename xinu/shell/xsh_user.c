#include <xinu.h>

shellcmd xsh_user(int32 nargs, char *args[]) {

    if(nargs==2 && strcmp(args[1],"login")==0){
        if(LoggedIn==1){
            kprintf("\nAlready a user is logged in.\n");
            printf("%s\n",LoggedInUserName);
            kprintf("\nLogout the user to continue\n");
            send(RingProcessId,2);
        }
        else{
            kprintf("\nPlease Fill the Following Details\n");
            kprintf("========================================================\n");
            //////////////////////////////////////ASK USER ACCOUNT NUMBER////////////////////////////////////////
            kprintf("Account Number     :\t");
            int val;
            int i,j,k,c;
            char UserAccount[5];
            for(i=0;i<5;i++){
                UserAccount[i]=NULL;
            }
            val=fgetc(CONSOLE);
            i=0;
            while(val!=10){
                UserAccount[i]='0'+(val-48);
                val=fgetc(CONSOLE);
                i++;
            }
            if(i>5){
                kprintf("\nThe Account Number length should be less than or equal to 5\n");
                send(RingProcessId,1);
                exit();
            }
            for(j=0;j<i;j++){
                if(UserAccount[j]<'0' || UserAccount[j]>'9'){
                    kprintf("\nThe User Account Number should only contain numbers from 0 to 9\n");
                    send(RingProcessId,1);
                    exit();
                    break;
                }
            }
            //////////////////////////////////////CHECK USER ACCOUNT NUMBER////////////////////////////////////////
            struct bpentry* headtemp;
            headtemp=BankAccountPoolHead;
            i=0,j;
            while(headtemp){
                if(strncmp(headtemp->BankAccount.AccountNumber,UserAccount,5)==0){
                    i=1;
                    break;
                }
                headtemp=headtemp->bpnext;
            }
            if(i==0){
                kprintf("\nNo account exists with this account number\n");
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
                i=0;
                while(val!=10){
                    Password[i]='0'+(val-48);
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
                //////////////////////////////////////CHECK USER PASSWORD////////////////////////////////////////
                headtemp=BankAccountPoolHead;
                i=0;
                while(headtemp){
                    if(strncmp(headtemp->BankAccount.AccountNumber,UserAccount,5)==0 && strcmp(headtemp->BankAccount.UserPassword,Password)==0){
                        i=1;
                        break;
                    }
                    headtemp=headtemp->bpnext;
                }
                if(i==0){
                    kprintf("\nWrong Password Entered\n");
                    send(RingProcessId,7);
                }
                else{
                    strcpy(LoggedInUserName,headtemp->BankAccount.UserName);
                    strcpy(LoggedInUserAccount,headtemp->BankAccount.AccountNumber);
                    kprintf("\nWelcone, ");
                    kprintf("%s\n",LoggedInUserName);
                    LoggedIn=1;

                }
            }
            kprintf("========================================================\n\n");
        }
    }
    else if(nargs==3 && strcmp(args[1],"deposit")==0){
        if(LoggedIn==1){
            int amount=atoi(args[2]);
            DepositProcessId=create(deposit,8192,20,"Deposit",0);
            resume(DepositProcessId);
            send(DepositProcessId,amount);
        }
    }
    else if(nargs==3 && strcmp(args[1],"withdraw")==0){
        if(LoggedIn==1){
            int amount=atoi(args[2]);
            WithdrawProcessId=create(withdraw,8192,20,"Withdraw",0);
            resume(WithdrawProcessId);
            send(WithdrawProcessId,amount);
        }
    }

    else if(nargs==4 && strcmp(args[1],"transfer")==0){
        if(LoggedIn==1){
            int amount=atoi(args[3]);
            strcpy(TransferToAccount,args[2]);
            TransferProcessId=create(transfer,8192,20,"Transfer",0);
            resume(TransferProcessId);
            send(TransferProcessId,amount);
        }
    }
    else if(nargs==2 && strcmp(args[1],"logout")==0){
        if(LoggedIn==1){
            kprintf("\nLogging out the user :\t");
            printf("%s\n\n",LoggedInUserName);
            LoggedIn=0;
            send(RingProcessId,1);
        }
    }

    else{
        kprintf("\nAvailable Commands are:\n");
        kprintf("user login\n");
        kprintf("user withdraw\n");
        kprintf("user deposit\n\n");
        kprintf("user transfer\n\n");
    }
	return 0;
}
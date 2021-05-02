#include <xinu.h>
// #include <memory.h>

process main(void)
{
	/* Run the Xinu shell */

	SecurityProcessId=create(security,8192,75,"SECURITY",0);
	kprintf("\033[0m\033[2J\033[H\n");

	ShellSem=semcreate(1);

	resume(SecurityProcessId);

	wait(ShellSem);
	signal(ShellSem);

	kprintf("\033[0m\033[2J\033[H\n");
	kprintf("TEAM 2:\n\n");
	kprintf("SRIPRANAV MANNEPALLI \n");
	kprintf("S R V S MAHESWARA REDDY\n");
	kprintf("CHIRAG GUPTA\n");
	kprintf("A V S HRUDAI\n");

	kprintf("WELCOME TO THE BANK OF INDIA\n\n\n");

	recvclr();

	TransactionSem=semcreate(1);// create a transaction semaphore 

	KeyboardSem=semcreate(1);// create a keyboard resource semaphore 

	ScreenSem=semcreate(1);// create a screen resource semaphore 

	RingProcessId=create(ring,8192,20,"Ring",0);//Create a ring process.This process is always run in background.It is like a malicious activity detector process.

	AdProcessId=create(ads,8192,20,"Ads",0);//Create aa ad process.This process is always run in background.It shows ads to user on vga(screen)

	DeadlockProcessId=create(DeadlockDetect,8192,20,"Deadlock",0);// create a process to check deadlocks. It runs for every 5 seconds

	ShellProcessId=create(shell, 4096, 20, "shell", 1, CONSOLE); // create shell process

	resume(ShellProcessId);

	resume(RingProcessId);

	resume(AdProcessId);

	resume(DeadlockProcessId);


	while (TRUE) {
		if(!ShellProcessId){
			receive();
			wait(ShellSem);
			signal(ShellSem);
			//kprintf("\n\nMain process recreating shell\n\n");
			ShellProcessId=create(shell, 4096, 20, "shell", 1, CONSOLE);
			resume(ShellProcessId);
		}
	}

	return OK;
}

void security(void){
    wait(ShellSem);
	while(1){
		kprintf("\n(As this is a test version, we are giving our password.)\n");
		kprintf("(Our Password is : 'team2rocks') \n\n");
		kprintf("Enter Password: ");
		int val,i,j;
		val=fgetc(CONSOLE);
		i=0;j=0;
		char Password[50];
		while(val!=10){
			if(i<50) Password[i]='\x00'+(val);
			i++;
			j=i;
			val=fgetc(CONSOLE);
		}
		if(strncmp(Password,"team2rocks",10)==0){
			break;
		}
		kprintf("\nPlease Enter the Correct Password...\n");
	}
	signal(ShellSem);
	kill(SecurityProcessId);
}



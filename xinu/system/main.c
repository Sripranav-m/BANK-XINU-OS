#include <xinu.h>
// #include <memory.h>

process main(void)
{

	/* Run the Xinu shell */

	recvclr();

	TransactionSem=semcreate(1);

	KeyboardSem=semcreate(1);

	ScreenSem=semcreate(1);

	RingProcessId=create(ring,8192,20,"Ring",0);

	AdProcessId=create(ads,8192,20,"Ads",0);

	//DeadlockProcessId=create(DeadlockDetect,8192,20,"Deadlock",0);

	ShellProcessId=create(shell, 50, 50, "shell", 1, CONSOLE);

	resume(ShellProcessId);

	resume(RingProcessId);

	resume(AdProcessId);

	//resume(DeadlockDetect);

	return OK;
    
}

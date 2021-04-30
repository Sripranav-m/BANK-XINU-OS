#include <xinu.h>
// #include <memory.h>

process main(void)
{

	/* Run the Xinu shell */

	recvclr();

	SongSem=semcreate(1);

	RingProcessId=create(ring,8192,20,"Ring",0);

	ReminderProcessId=create(reminder,8192,20,"Reminder",0);

	resume(create(shell, 50, 50, "shell", 1, CONSOLE));

	resume(RingProcessId);

	resume(ReminderProcessId);

	return OK;
    
}

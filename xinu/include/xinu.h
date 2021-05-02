/* xinu.h - include all system header files */

#include <kernel.h>
#include <conf.h>
#include <process.h>
#include <queue.h>
#include <resched.h>
#include <mark.h>
#include <semaphore.h>
#include <memory.h>
#include <bufpool.h>
#include <clock.h>
#include <ports.h>
#include <io.h>
#include <uart.h>
#include <tty.h>
#include <device.h>
#include <interrupt.h>
#include <file.h>


#include <lfilesys.h>
#include <ether.h>
#include <net.h>
#include <ip.h>
#include <arp.h>
#include <udp.h>
#include <dhcp.h>
#include <icmp.h>
#include <tftp.h>
#include <name.h>
#include <shell.h>
#include <date.h>
#include <prototypes.h>
#include <delay.h>
#include <i386.h>
#include <pci.h>
#include <e1000e.h>
#include <quark_pdat.h>
#include <quark_irq.h>
#include <multiboot.h>
#include <stdio.h>
#include <string.h>

extern pid32 SecurityProcessId;

extern pid32 ShellProcessId;

extern pid32 RingProcessId;

extern pid32 DeadlockProcessId;

extern pid32 ReviewProcessId;

extern pid32 CommentProcessId;

extern sid32 ShellSem;

extern void clearScreen();      // Clear the Screen

extern bpid32 BankAccountPoolId;
extern struct bpentry* BankAccountPoolHead;
extern struct bpentry* BankAccountPoolTail;

extern int TotalBankAccounts;

extern char LoggedInUserName[20];
extern char LoggedInUserAccount[5];
extern int LoggedIn;

extern sid32 TransactionSem;
extern pid32 DepositProcessId;
extern pid32 WithdrawProcessId;
extern pid32 TransferProcessId;
extern pid32 AdProcessId;

extern char TransferToAccount[5];

extern sid32 KeyboardSem;
extern sid32 ScreenSem;

#define NumberOfResources 2
#define NumberOfProcesses 3
#define R 2
#define P 3

extern int AvailableResources[R];
extern int MaxResources[P][R];//max
extern int AllocatedResources[P][R];//alloc
extern int NeedResources[P][R];//need
extern int processes[P];
extern int Finish[P];
/* xsh_clear.c - xsh_clear */

#include <xinu.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xsh_clear - clear the display window (assumes xterm / VT100)
 *------------------------------------------------------------------------
 */
shellcmd xsh_clear(int nargs, char *args[])
{

    /* Insure no arguments were passed */

    if (nargs > 2) {
	kprintf("\n Usage of Clear :");
    kprintf("\n 'clear' : To clear console ");
    kprintf("\n 'clear screen' : To clear screen ");
	return 0;
    }
    else if(nargs == 2){
        if(strcmp("screen",args[1])==0){
            clearScreen();
        }
        else{
            kprintf("\n Usage of Clear :");
            kprintf("\n 'clear' : To clear console ");
            kprintf("\n 'clear screen' : To clear screen ");
        }
        return 0;
    }
    printf("\033[0m\033[2J\033[H\n");
    return 0;
}

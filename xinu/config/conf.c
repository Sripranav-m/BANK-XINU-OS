/* conf.c (GENERATED FILE; DO NOT EDIT) */

#include <xinu.h>


extern	devcall	ioerr(void);
extern	devcall	ionull(void);

/* Device independent I/O switch */

struct	dentry	devtab[NDEVS] =
{
/**
 * Format of entries is:
 * dev-number, minor-number, dev-name,
 * init, open, close,
 * read, write, seek,
 * getc, putc, control,
 * dev-csr-address, intr-handler, irq
 */

/* CONSOLE is tty */
	{ 0, 0, "CONSOLE",
	  (void *)ttyinit, (void *)ionull, (void *)ionull,
	  (void *)ttyread, (void *)ttywrite, (void *)ioerr,
	  (void *)ttygetc, (void *)ttyputc, (void *)ttycontrol,
	  (void *)0x3f8, (void *)ttydispatch, 36 },

/* NULLDEV is null */
	{ 1, 0, "NULLDEV",
	  (void *)ionull, (void *)ionull, (void *)ionull,
	  (void *)ionull, (void *)ionull, (void *)ioerr,
	  (void *)ionull, (void *)ionull, (void *)ioerr,
	  (void *)0x0, (void *)ioerr, 0 },

/* ETHER0 is eth */
	{ 2, 0, "ETHER0",
	  (void *)ethinit, (void *)ioerr, (void *)ioerr,
	  (void *)ethread, (void *)ethwrite, (void *)ioerr,
	  (void *)ioerr, (void *)ioerr, (void *)ethcontrol,
	  (void *)0x0, (void *)ethdispatch, 0 },

/* RAM0 is ram */
	{ 3, 0, "RAM0",
	  (void *)raminit, (void *)ramopen, (void *)ramclose,
	  (void *)ramread, (void *)ramwrite, (void *)ioerr,
	  (void *)ioerr, (void *)ioerr, (void *)ioerr,
	  (void *)0x0, (void *)ionull, 0 },

/* SCREEN is vga */
	{ 4, 0, "SCREEN",
	  (void *)vgainit, (void *)ionull, (void *)ionull,
	  (void *)ioerr, (void *)vgawrite, (void *)ioerr,
	  (void *)ioerr, (void *)vgaputc, (void *)ioerr,
	  (void *)0x0, (void *)ionull, 0 }
};

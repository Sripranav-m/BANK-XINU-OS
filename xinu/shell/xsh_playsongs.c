#include <xinu.h>
#include <stdio.h>
#include <string.h>


char SongText[100];



sid32 SongSem;

shellcmd xsh_playsongs(int32 nargs, char *args[]) {
	
	if(nargs==1){
        Song1ProcId=create(song1,8192,35,"Song1",0);
        Song2ProcId=create(song2,8192,35,"Song2",0);
        Song3ProcId=create(song3,8192,35,"Song3",0);
        resume(Song1ProcId);
        resume(Song2ProcId);
        resume(Song3ProcId);
    }
    else{
        kprintf("\n Please folow the format : 'play' \n");
    }

	
	return 0;
}

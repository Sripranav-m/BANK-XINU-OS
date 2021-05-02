#include <xinu.h>

shellcmd xsh_reviewcomment(int32 nargs, char *args[]) {
    if(LoggedIn==1){
		if(nargs==1 && strcmp("review",args[0])==0){
			ReviewProcessId=create(review,8192,45,"Review",0);
			resume(ReviewProcessId);
		}
		else if(nargs==1 && strcmp("comment",args[0])==0){
			CommentProcessId=create(comment,8192,40,"Comment",0);
			resume(CommentProcessId);
		}
	}
	else{
		kprintf("\nPlease log in to continue..\n");
	}
	return 0;
}
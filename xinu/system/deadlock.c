#include<xinu.h>

void calculateNeed(){ // calculate the resources needed
    int i,j;
    for (i = 0 ; i < P ; i++){
        for (j = 0 ; j < R ; j++){
            NeedResources[i][j] = MaxResources[i][j] - AllocatedResources[i][j];
        }
    }
}
  
// Function to find the system is in safe state or not
int isSafe(){
    calculateNeed();
    int i;
    int finish[P];
    for(i=0;i<P;i++){
        finish[i]=0;
    }
    int work[R];
    int safeSeq[P];
    for (i = 0; i < R ; i++){
        work[i] = AvailableResources[i];
    }
    // While all processes are not finished
    // or system is not in safe state.
    int count = 0,k,p;
    while (count < P){
        // Find a process which is not finish and
        // whose needs can be satisfied with current
        // work[] resources.
        int found = 0;
        for (p = 0; p < P; p++){
            // First check if a process is finished,
            // if no, go for next condition
            if (finish[p] == 0)
            {
                // Check if for all resources of
                // current P need is less
                // than work
                int j;
                for (j = 0; j < R; j++){
                    if (NeedResources[p][j] > work[j]){
                        break;
                    }
                }
                // If all needs of p were satisfied.
                if (j == R)
                {
                    // Add the allocated resources of
                    // current P to the AvailableResourcesable/work
                    // resources i.e.free the resources
                    for (k = 0 ; k < R ; k++){
                        work[k] += AllocatedResources[p][k];
                    }
                    safeSeq[count++] = p;
                    // Mark this p as finished
                    finish[p] = 1;
  
                    found = 1;
                }
            }
        }
        // If we could not find a next process in safe
        // sequence.
        if (found == 0){
            return 0;
        }
    }
    return 1;
}
void DeadlockDetect(void)
{
    while(1){
        // The processes
        // Ads:0
        // Review:1
        // Comment:2
        // The Resources
        // KeyBoard:0
        // Screen :1
        // Resources allocated to processes
        // Check system is in safe state or not
        int IsSafe=isSafe();
        if(!IsSafe){
            kprintf("\nDEADLOCK OCCURED...\n");
            int i,j;
            kprintf("\nTotal Available Resources :\n");
            kprintf("Keyboard\tScreen\t\n");
            for(i=0;i<R;i++){
                kprintf("%d       \t",AvailableResources[i]);
            }
            kprintf("\nCurrently Allocated Resources :\n");
            kprintf("Process      :\tKeyboard\tScreen\t\n");
            for(i=0;i<P;i++){
                if(i==0) kprintf("Advertisement:\t");
                else if(i==2) kprintf("Comment      :\t");
                else kprintf("Review       :\t");
                for(j=0;j<R;j++){
                    kprintf("%d       \t",AllocatedResources[i][j]);
                }
                kprintf("\n");
            }
            kprintf("\nResources Needed :\n");
            kprintf("Process\t\tKeyboard\tScreen\t\n");
            for(i=0;i<P;i++){
                if(i==0) kprintf("Advertisement:\t");
                else if(i==2) kprintf("Comment      :\t");
                else kprintf("Review       :\t");
                for(j=0;j<R;j++){
                    kprintf("%d       \t",MaxResources[i][j]);
                }
                kprintf("\n");
            }
            DeadlockRecovery();
            // kill(DeadlockProcessId);
            // DeadlockProcessId=0;
        }
        else{
            //kprintf("\nSAFE STATE...\n");
            sleepms(1000);// If it is in safe state, sleep for 1 seconds...
        }
    }
}

void changeState(int storeBackup[],int idx){
    int k;
    for(k=0;k<R;k++){
        AllocatedResources[idx][k]+=storeBackup[k];
        AvailableResources[k] -= storeBackup[k];
        storeBackup[k] = 0;
    }
}

// Function to find the system is in safe state or not
int CausesDeadlock(int idx){
    int storeBackup[R];
    int k,i,p;
    for(k=0;k<R;k++){
        storeBackup[k] = AllocatedResources[idx][k];
        AllocatedResources[idx][k]=0;
        AvailableResources[k] += storeBackup[k];
    }
    int finish[P];
    for(i=0;i<P;i++){
        finish[i]=0;
    }
    int work[R];
    int safeSeq[P];
    calculateNeed();
    for (i = 0; i < R ; i++){
        work[i] = AvailableResources[i];
    }
    // While all processes are not finished
    // or system is not in safe state.
    int count = 0;
    while (count < P){
        // Find a process which is not finish and
        // whose needs can be satisfied with current
        // work[] resources.
        int found = 0;
        for (p = 0; p < P; p++){
            // First check if a process is finished,
            // if no, go for next condition
            if (finish[p] == 0)
            {
                // Check if for all resources of
                // current P need is less
                // than work
                int j;
                for (j = 0; j < R; j++){
                    if (NeedResources[p][j] > work[j]){
                        break;
                    }
                }
                // If all needs of p were satisfied.
                if (j == R)
                {
                    // Add the allocated resources of
                    // current P to the AvailableResourcesable/work
                    // resources i.e.free the resources
                    for (k = 0 ; k < R ; k++){
                        work[k] += AllocatedResources[p][k];
                    }
                    safeSeq[count++] = p;
                    // Mark this p as finished
                    finish[p] = 1;
  
                    found = 1;
                }
            }
        }
        // If we could not find a next process in safe
        // sequence.
        if (found == 0){
            changeState(storeBackup,idx);
            return 0;
        }
    }
    changeState(storeBackup,idx);
    return 1;
}


void DeadlockRecovery(void){
    int arr[P];
    int currIdx = 0;
    int i;
    for(i=0;i<P;i++){
        if(CausesDeadlock(i)){
            int k;
            for(k=0;k<R;k++){
                if(AllocatedResources[i][k]){
                    AvailableResources[k] += AllocatedResources[i][k];
                    AllocatedResources[i][k]=0;
                    kprintf("Deallocating a Resource :\n");
                    if(k==0) {
                        signal(KeyboardSem);
                        signal(ShellSem);
                        kprintf("\t\t Keyboard\n");
                    }
                    else {
                        kprintf("\t\t Screen\n");
                        signal(ScreenSem);
                    }
                }
            }
            kprintf("Killing The process :\n");
            if(i==0){
                kill(AdProcessId);
                kprintf("\t\tAdvertisement\n");
            }
            else if(i==1) {
                kill(CommentProcessId);
                kill(ShellProcessId);
                ShellProcessId=0;
                kprintf("\t\tComment      \n");
            }
            else {
                kill(ReviewProcessId);
                kill(ShellProcessId);
                ShellProcessId=0;
                kprintf("\t\tReview       \n");
            }
            break;
        }
    }
    kprintf("\n\n\n");
    DeadlockDetect();
}
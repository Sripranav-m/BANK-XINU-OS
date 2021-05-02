#include<xinu.h>

void calculateNeed(){
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
                kprintf("%d\t",AvailableResources[i]);
            }
            kprintf("\nCurrently Allocated Resources :\n");
            kprintf("Process\t\tKeyboard\tScreen\t\n");
            for(i=0;i<P;i++){
                if(i==0) kprintf("Advertisement\t\t");
                else if(i==2) kprintf("Comment\t\t");
                else kprintf("Review\t\t");
                for(j=0;j<R;j++){
                    kprintf("%d\t",AllocatedResources[i][j]);
                }
                kprintf("\n");
            }
            kprintf("\nResources Needed :\n");
            kprintf("Process\t\tKeyboard\tScreen\t\n");
            for(i=0;i<P;i++){
                if(i==0) kprintf("Advertisement\t\t");
                else if(i==2) kprintf("Comment\t\t");
                else kprintf("Review\t\t");
                for(j=0;j<R;j++){
                    kprintf("%d\t",MaxResources[i][j]);
                }
                kprintf("\n");
            }
            kill(DeadlockProcessId);
            DeadlockProcessId=0;
            //DeadlockRecovery();
        }
        else{
            //kprintf("\nSAFE STATE...\n");
        }
        sleepms(10000);
    }
}





void changeState(int storeBackup[],int AllocatedResources[][R],int AvailableResources[],int idx){
    int k;
    for(k=0;k<R;k++){
        AllocatedResources[idx][k]+=storeBackup[k];
        AvailableResources[k] -= storeBackup[k];
        storeBackup[k] = 0;
    }
}

// Function to find the system is in safe state or not
int isSafeRecovery(int processes[], int AvailableResources[], int MaxResources[][R],int AllocatedResources[][R],int idx){
    int finish[P] = {0};
    int storeBackup[R];
    int k,i,p;
    for(k=0;k<R;k++){
        storeBackup[k] = AllocatedResources[idx][k];
        AllocatedResources[idx][k]=0;
        AvailableResources[k] += storeBackup[k];
    }
    calculateNeed();
    int safeSeq[P];
  
    int work[R];
    for (i = 0; i < R ; i++){
        work[i] = AvailableResources[i];
    }
  
    // While all processes are not finished
    // or system is not in safe state.
    int count = 0;
    while (count < P)
    {
        // Find a process which is not finish and
        // whose needs can be satisfied with current
        // work[] resources.
        int found = 0;
        for (p = 0; p < P; p++)
        {
            // First check if a process is finished,
            // if no, go for next condition
            if (finish[p] == 0 && p!=idx)
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
                    for (k = 0 ; k < R ; k++)
                        work[k] += AllocatedResources[p][k];
  
                    // Add this process to safe sequence.
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
            changeState(storeBackup,AllocatedResources,AvailableResources,idx);
            return 0;
        }
    }
    changeState(storeBackup,AllocatedResources,AvailableResources,idx);
    return 1;
}

void DeadlockRecovery(void){
    // The processes
    int processes[P] = {0, 1, 2};
    // AvailableResourcesable instances of resources
    int AvailableResources[R] = {1, 1};
  
    // Maximum R that can be allocated
    // to processes
    int MaxResources[P][R] = {{0, 1},
                     {1, 1},
                     {1, 1}};

    // Resources allocated to processes
    int AllocatedResources[P][R] = {{0, 1},
                                    {1, 0},
                                    {0, 0}};

    int arr[P];
    int currIdx = 0;
    int i;
    for(i=0;i<P;i++){
        if(!isSafeRecovery(processes, AvailableResources, MaxResources, AllocatedResources,i)){
            arr[currIdx] = i;
            currIdx++;
        }
    }

}
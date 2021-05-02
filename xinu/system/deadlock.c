// #include<xinu.h>

// void calculateNeed(){
//     for (int i = 0 ; i < P ; i++){
//         for (int j = 0 ; j < R ; j++){
//             NeedResources[i][j] = MaxResources[i][j] - AllocatedResources[i][j];
//         }
//     }
// }
  
// // Function to find the system is in safe state or not
// int isSafe(){
//     calculateNeed();

//     int finish[P] = {0};
  
//     int safeSeq[P];
  
//     int work[R];
//     for (int i = 0; i < R ; i++){
//         work[i] = AvailableResources[i];
//     }
  
//     // While all processes are not finished
//     // or system is not in safe state.
//     int count = 0;
//     while (count < P)
//     {
//         // Find a process which is not finish and
//         // whose needs can be satisfied with current
//         // work[] resources.
//         int found = 0;
//         for (int p = 0; p < P; p++)
//         {
//             // First check if a process is finished,
//             // if no, go for next condition
//             if (finish[p] == 0)
//             {
//                 // Check if for all resources of
//                 // current P need is less
//                 // than work
//                 int j;
//                 for (j = 0; j < R; j++){
//                     if (NeedResources[p][j] > work[j]){
//                         break;
//                     }
//                 }
  
//                 // If all needs of p were satisfied.
//                 if (j == R)
//                 {
//                     // Add the allocated resources of
//                     // current P to the AvailableResourcesable/work
//                     // resources i.e.free the resources
//                     for (int k = 0 ; k < R ; k++)
//                         work[k] += AllocatedResources[p][k];
  
//                     // Add this process to safe sequence.
//                     safeSeq[count++] = p;
  
//                     // Mark this p as finished
//                     finish[p] = 1;
  
//                     found = 1;
//                 }
//             }
//         }
//         // If we could not find a next process in safe
//         // sequence.
//         if (found == 0){
//             return 0;
//         }
//     }
//     return 1;
// }
  
// // Driver code
// void DeadlockDetect(void)
// {
//     while(1){

//         // Process 0 is Ads
//         // Process 1 is Comments
//         // Process 2 is reviews

//         // Resource 0 is Keyboard
//         // Resource 1 is Screen

//         int processes[P] = {0, 1, 2};
//         // AvailableResourcesable instances of resources
//         int AvailableResources[R] = {1, 1};
    
//         // Maximum R that can be allocated
//         // to processes
//         int MaxResources[P][R] = {{0, 1},
//                         {1, 1},
//                         {1, 1}};
//         // Resources allocated to processes
//         int AllocatedResources[P][R] = {{0, 1},
//                                         {1, 0},
//                                         {0, 0}};
//         // Check system is in safe state or not
//         isSafe();
//     }
// }



// #include<stdio.h>

// void calculateNeed(){
//     for (int i = 0 ; i < P ; i++){
//         for (int j = 0 ; j < R ; j++){
//             NeedResources[i][j] = MaxResources[i][j] - AllocatedResources[i][j];
//         }
//     }
// }
  
// // Function to find the system is in safe state or not
// int isSafe(int processes[], int AvailableResources[], int MaxResources[][R],int AllocatedResources[][R]){
//     calculateNeed();

//     int finish[P] = {0};
  
//     int safeSeq[P];
  
//     int work[R];
//     for (int i = 0; i < R ; i++){
//         work[i] = AvailableResources[i];
//     }
  
//     // While all processes are not finished
//     // or system is not in safe state.
//     int count = 0;
//     while (count < P)
//     {
//         // Find a process which is not finish and
//         // whose needs can be satisfied with current
//         // work[] resources.
//         int found = 0;
//         for (int p = 0; p < P; p++)
//         {
//             // First check if a process is finished,
//             // if no, go for next condition
//             if (finish[p] == 0)
//             {
//                 // Check if for all resources of
//                 // current P need is less
//                 // than work
//                 int j;
//                 for (j = 0; j < R; j++){
//                     if (NeedResources[p][j] > work[j]){
//                         break;
//                     }
//                 }
  
//                 // If all needs of p were satisfied.
//                 if (j == R)
//                 {
//                     // Add the allocated resources of
//                     // current P to the AvailableResourcesable/work
//                     // resources i.e.free the resources
//                     for (int k = 0 ; k < R ; k++)
//                         work[k] += AllocatedResources[p][k];
  
//                     // Add this process to safe sequence.
//                     safeSeq[count++] = p;
  
//                     // Mark this p as finished
//                     finish[p] = 1;
  
//                     found = 1;
//                 }
//             }
//         }
//         // If we could not find a next process in safe
//         // sequence.
//         if (found == 0){
//             return 0;
//         }
//     }
//     return 1;
// }


// void changeState(int storeBackup[],int AllocatedResources[][R],int AvailableResources[],int idx){
//     int k;
//     for(k=0;k<R;k++){
//         AllocatedResources[idx][k]+=storeBackup[k];
//         AvailableResources[k] -= storeBackup[k];
//         storeBackup[k] = 0;
//     }
// }

// // Function to find the system is in safe state or not
// int isSafeRecovery(int processes[], int AvailableResources[], int MaxResources[][R],int AllocatedResources[][R],int idx){
    

//     int finish[P] = {0};

//     int storeBackup[R];
//     int k;
//     for(k=0;k<R;k++){
//         storeBackup[k] = AllocatedResources[idx][k];
//         AllocatedResources[idx][k]=0;
//         AvailableResources[k] += storeBackup[k];
//     }
//     calculateNeed();
//     int safeSeq[P];
  
//     int work[R];
//     for (int i = 0; i < R ; i++){
//         work[i] = AvailableResources[i];
//     }
  
//     // While all processes are not finished
//     // or system is not in safe state.
//     int count = 0;
//     while (count < P)
//     {
//         // Find a process which is not finish and
//         // whose needs can be satisfied with current
//         // work[] resources.
//         int found = 0;
//         for (int p = 0; p < P; p++)
//         {
//             // First check if a process is finished,
//             // if no, go for next condition
//             if (finish[p] == 0 && p!=idx)
//             {
//                 // Check if for all resources of
//                 // current P need is less
//                 // than work
//                 int j;
//                 for (j = 0; j < R; j++){
//                     if (NeedResources[p][j] > work[j]){
//                         break;
//                     }
//                 }
  
//                 // If all needs of p were satisfied.
//                 if (j == R)
//                 {
//                     // Add the allocated resources of
//                     // current P to the AvailableResourcesable/work
//                     // resources i.e.free the resources
//                     for (int k = 0 ; k < R ; k++)
//                         work[k] += AllocatedResources[p][k];
  
//                     // Add this process to safe sequence.
//                     safeSeq[count++] = p;
  
//                     // Mark this p as finished
//                     finish[p] = 1;
  
//                     found = 1;
//                 }
//             }
//         }
//         // If we could not find a next process in safe
//         // sequence.
//         if (found == 0){
//             changeState(storeBackup,AllocatedResources,AvailableResources,idx);
//             return 0;
//         }
//     }

//     changeState(storeBackup,AllocatedResources,AvailableResources,idx);
//     return 1;
// }



  
// // Driver code
// void DeadlockDetect(void)
// {
//     // The processes
//     int processes[P] = {0, 1, 2};
//     // AvailableResourcesable instances of resources
//     int AvailableResources[R] = {1, 1};
  
//     // Maximum R that can be allocated
//     // to processes
//     int MaxResources[P][R] = {{0, 1},
//                      {1, 1},
//                      {1, 1}};

//     // Resources allocated to processes
//     int AllocatedResources[P][R] = {{0, 1},
//                                     {1, 0},
//                                     {0, 0}};
//     // Check system is in safe state or not
//     isSafe(processes, AvailableResources, MaxResources, AllocatedResources);


// }



// void deadlockRecovery(void){
//     // The processes
//     int processes[P] = {0, 1, 2};
//     // AvailableResourcesable instances of resources
//     int AvailableResources[R] = {1, 1};
  
//     // Maximum R that can be allocated
//     // to processes
//     int MaxResources[P][R] = {{0, 1},
//                      {1, 1},
//                      {1, 1}};

//     // Resources allocated to processes
//     int AllocatedResources[P][R] = {{0, 1},
//                                     {1, 0},
//                                     {0, 0}};

//     int arr[P];
//     int currIdx = 0;
//     int i;
//     for(i=0;i<P;i++){
//         if(!isSafeRecovery(processes, AvailableResources, MaxResources, AllocatedResources,i)){
//             arr[currIdx] = i;
//             currIdx++;
//         }
//     }

// }
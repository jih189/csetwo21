#include <stdint.h>
#include <iostream>
#include <time.h>
#include <sched.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <thread>

using namespace std;
unsigned int high, low, id;
uint64_t starttime;

static inline uint64_t start_timer(){
    __asm__ volatile ( "cpuid \n\t"
         "rdtsc \n\t"
         "mov %%edx, %0 \n\t"
         "mov %%eax, %1 \n\t"
         : "=r"(high), "=r"(low)
         :: "%rax", "%rbx", "%rcx", "%rdx"
     );
    return ((uint64_t)high << 32)|low;
}


static inline uint64_t end_timer(){
    __asm__ volatile ( 
         "rdtscp \n\t"
         "mov %%edx, %0 \n\t"
         "mov %%eax, %1 \n\t"
         "cpuid \n\t"
         : "=r"(high), "=r"(low)
         :: "%rax", "%rbx", "%rcx", "%rdx"
     );
    return ((uint64_t)high << 32)|low;
}

void* foo(void*) {
    uint64_t end = end_timer();
    cout << end - starttime << endl;
    pthread_exit(NULL);
}

int main(int argc, char **argv){
    pthread_t td;
    for(int i = 0; i < 100; i++){
        starttime = start_timer();
        pthread_create(&td, NULL, foo, NULL);
        pthread_join(td, NULL);
    }
    
    //std::thread first (foo);
    //first.join();
    
/*
    int counter = 0;
    uint64_t start, end1, end2;
    start = start_timer();
    pid_t pid = fork();
    if(pid == 0){
        // child process
        end1 = end_timer();
        cout << (end1 - start) << endl;
   
    }
    else if(pid > 0){
        end2 = end_timer();
        cout << (end2 - start) << endl;
        // parent process
    }
*/

    return 0;

}

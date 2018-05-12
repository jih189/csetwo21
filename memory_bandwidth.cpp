#include <stdint.h>
#include <iostream>
#include <time.h>
#include <sched.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

using namespace std;
unsigned int high, low, id;
uint64_t start, endt;
#define L3CACHSIZE 4194304 
static inline uint64_t start_timer(){
    __asm__ volatile( "cpuid \n\t"
        "rdtsc \n\t"
        "mov %%edx, %0 \n\t"
        "mov %%eax, %1 \n\t"
        : "=r"(high), "=r"(low)
        :: "%rax", "%rbx", "%rcx", "%rdx"
    );
    return ((uint64_t)high <<32) | low;
}
static inline uint64_t end_timer(){
    __asm__ volatile( 
        "rdtscp \n\t"
        "mov %%edx, %0 \n\t"
        "mov %%eax, %1 \n\t"
        "cpuid \n\t"
        : "=r"(high), "=r"(low)
        :: "%rax", "%rbx", "rcx", "%rdx"
    );
    return ((uint64_t)high <<32) | low;
}

int main(int argc, char *argv[]){
    uint64_t start, end;
    // create a memory on heap
    uint64_t offset = L3CACHSIZE / sizeof(int);
    int *mem = (int *)malloc(L3CACHSIZE * 50);
    int in;
    start = start_timer();
    in = mem[0+1];
    in = mem[offset+1];
    in = mem[2*offset+1];
    in = mem[3*offset+1];
    in = mem[4*offset+1];
    in = mem[5*offset+1];
    in = mem[6*offset+1];
    in = mem[7*offset+1];
    in = mem[8*offset+1];
    in = mem[9*offset+1];
    in = mem[10*offset+1];
    in = mem[11*offset+1];
    in = mem[12*offset+1];
    in = mem[13*offset+1];
    in = mem[14*offset+1];
    in = mem[15*offset+1];
    in = mem[16*offset+1];
    in = mem[17*offset+1];
    in = mem[18*offset+1];
    in = mem[19*offset+1];
    in = mem[20*offset+1];
    in = mem[21*offset+1];
    in = mem[22*offset+1];
    in = mem[23*offset+1];
    in = mem[24*offset+1];
    in = mem[25*offset+1];
    in = mem[26*offset+1];
    in = mem[27*offset+1];
    in = mem[28*offset+1];
    in = mem[29*offset+1];
    in = mem[30*offset+1];
    in = mem[31*offset+1];
    in = mem[32*offset+1];
    in = mem[33*offset+1];
    in = mem[34*offset+1];
    in = mem[35*offset+1];
    in = mem[36*offset+1];
    in = mem[37*offset+1];
    in = mem[38*offset+1];
    in = mem[39*offset+1];
    in = mem[40*offset+1];
    in = mem[41*offset+1];
    in = mem[42*offset+1];
    in = mem[43*offset+1];
    in = mem[44*offset+1];
    in = mem[45*offset+1];
    in = mem[46*offset+1];
    in = mem[47*offset+1];
    in = mem[48*offset+1];
    in = mem[49*offset+1];
    end = end_timer();
    std::cout << in;
    std::cout << "overhead of reading from main memory : " << (end - start) / 50 << std::endl; 
    start = start_timer();
    mem[0] = 6;
    mem[offset] = 6;
    mem[2*offset] = 6;
    mem[3*offset] = 6;
    mem[4*offset] = 6;
    mem[5*offset] = 6;
    mem[6*offset] = 6;
    mem[7*offset] = 6;
    mem[8*offset] = 6;
    mem[9*offset] = 6;
    mem[10*offset] = 6;
    mem[11*offset] = 6;
    mem[12*offset] = 6;
    mem[13*offset] = 6;
    mem[14*offset] = 6;
    mem[15*offset] = 6;
    mem[16*offset] = 6;
    mem[17*offset] = 6;
    mem[18*offset] = 6;
    mem[19*offset] = 6;
    mem[20*offset] = 6;
    mem[21*offset] = 6;
    mem[22*offset] = 6;
    mem[23*offset] = 6;
    mem[24*offset] = 6;
    mem[25*offset] = 6;
    mem[26*offset] = 6;
    mem[27*offset] = 6;
    mem[28*offset] = 6;
    mem[29*offset] = 6;
    mem[30*offset] = 6;
    mem[31*offset] = 6;
    mem[32*offset] = 6;
    mem[33*offset] = 6;
    mem[34*offset] = 6;
    mem[35*offset] = 6;
    mem[36*offset] = 6;
    mem[37*offset] = 6;
    mem[38*offset] = 6;
    mem[39*offset] = 6;
    mem[40*offset] = 6;
    mem[41*offset] = 6;
    mem[42*offset] = 6;
    mem[43*offset] = 6;
    mem[44*offset] = 6;
    mem[45*offset] = 6;
    mem[46*offset] = 6;
    mem[47*offset] = 6;
    mem[48*offset] = 6;
    mem[49*offset] = 6;
    end = end_timer();
    std::cout << "overhead of writing to main memory : " << (end - start) / 50 << std::endl; 
    free(mem);
    return 0; 
}

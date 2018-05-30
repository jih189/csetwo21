#include <stdio.h>
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <cerrno>

using namespace std;
unsigned int high, low, id;

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


/**
 the idea of code is
*/ 

int main(int argc, char **argv){

    uint64_t BLOCKSIZE = 64;

    string filename = "";
    filename += argv[1];
    uint64_t sum = 0;
    uint64_t start, end;
    int file;
    // open the file 
    file = open(filename.c_str(), O_DIRECT);
    // check for error
    if(file < 0){
        printf("Error opening file: %s\n", strerror(errno));
    }
    char* buf = (char *) malloc(64);
    int res = 1; 
    while( res != 0){
        start = start_timer();
        res = read(file, buf, 64);
        end = end_timer();
        cout << end - start << endl;
    }
    close(file);
    free(buf);
    return 0;
}

//Sameeksha Cherla.

#include "sem.h"

Queue* RunQ;

Sem* readerSemaphore;
Sem* writerSemaphore;
Sem* mx;

int readerCount = 0;
int readerWaitingCount = 0;
int writerWaitingCount = 0;
int writerCount = 0;
int clicker = 0;
int read = 1;
int write = 1;

//Function Prototype decelerations and function pointers.
void reader();
void (*Reader1)();
void (*Reader2)();
void (*Reader3)();
void writer();
void (*Writer1)();
void (*Writer2)();

void reader()
{
    printf("*******Reader %d Created :: %p********\n", read, RunQ->head);
    read++;
    
    while(1){
        // Reader Start
        P(mx);
        if(writerWaitingCount>0 || writerCount>0) {
            readerWaitingCount++;
            V(mx);
            P(readerSemaphore);
            readerWaitingCount--;
        }
        
        readerCount++;
        if(readerWaitingCount>0){
            V(readerSemaphore);
        }
        else{
            V(mx);
        }
        
        printf("Reader %p\n", RunQ->head);
        printf("Reading clicker: %d \n", clicker);
        
        // Reader End
        P(mx);
        readerCount--;
        if(readerCount==0 && writerWaitingCount>0){
            V(writerSemaphore);
        }
        else{
            V(mx);
        }
    }
}

void writer()
{
    int i;
    printf("########## Writer %d Created: %p########\n", write, RunQ->head);
    write++;
    
    while(1) {
        // Writer Start
        P(mx);
        if(readerCount>0 || writerCount>0) {
            writerWaitingCount++;
            V(mx);
            P(writerSemaphore);
            writerWaitingCount--;
        }
        
        writerCount++;
        V(mx);
        
        printf("Writer %p\n", RunQ->head);
        clicker++;
        printf("Writing and updating clicker: %d \n", clicker);
        
        // Writer End
        P(mx);
        writerCount--;
        if(readerWaitingCount>0){
            V(readerSemaphore);
        }
        else {
            if(writerWaitingCount>0){
                V(writerSemaphore);
            }
            else{
                V(mx);
            }
        }
    }
}

int main()
{
    RunQ = new_Queue();
    
    mx = (Sem*)malloc(sizeof(Sem));
    mx->queue = new_Queue();
    initSem(mx, 1);
    
    readerSemaphore = (Sem*)malloc(sizeof(Sem));
    readerSemaphore->queue = new_Queue();
    initSem(readerSemaphore,0);
    
    writerSemaphore = (Sem*)malloc(sizeof(Sem));
    writerSemaphore->queue = new_Queue();
    initSem(writerSemaphore,0);
    
    Reader1 = reader;
    Reader2 = reader;
    Reader3 = reader;
    Writer1 = writer;
    Writer2 = writer;
    
    start_thread(Reader1);
    start_thread(Writer1);
    start_thread(Writer2);
    start_thread(Reader2);
    start_thread(Reader3);
    
    run();
    
    return 0;
}

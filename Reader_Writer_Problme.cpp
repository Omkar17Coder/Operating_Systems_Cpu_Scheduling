#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>

// Reader Writer problem.
// We need two semaphores to code it.

sem_t readtoken,writetoken;
int currentReaderCount=0;


void * Reader_Function(void * args);
void * Writer_Function(void * args);

/*

Case1 Reader-> Reader Allow  together access.
Case2 Writer-> Reader block the reader
Case3 Reader-> Writer block the writer
Case4 Writer->Writer block the writer

*/



int main(){
sem_init(&readtoken,0,1);
sem_init(& writetoken,0,1);
// Main method.

int ReaderCount;
int WriterCount;
printf("OMKAR PRASHANT 21BCE1023\n");
printf("Enter the number of  Reader:");
scanf("%d",&ReaderCount);
printf("Enter the number of Writer:");
scanf("%d",&WriterCount);




pthread_t Reader[ReaderCount];
pthread_t Writer[WriterCount];

for(int i=0;i<ReaderCount;i++){
    pthread_create(&Reader[i],NULL,Reader_Function,NULL);
}

for(int j=0;j<WriterCount;j++){
    pthread_create(&Writer[j],NULL,Writer_Function,NULL);

}

for(int i=0;i<ReaderCount;i++){
    pthread_join(Reader[i],NULL);

}
for(int j=0;j<WriterCount;j++){
    pthread_join(Writer[j],NULL);
}

printf("Complete the Reader Writer problem\n");


return 0;

}

void * Reader_Function(void * args){

printf("Reader is Waiting\n");
    sem_wait(&readtoken);
    
    currentReaderCount+=1;
    if(currentReaderCount==1){
        printf("First Reader is Waiting\n");
        sem_wait(&writetoken);
        printf("First Reader is Entering\n");
    }
    sem_post(&readtoken);
    
    printf("Reader Is Reading from the database\n");
    
    sem_wait(&readtoken);
    currentReaderCount-=1;
    if(currentReaderCount==0){
        sem_post(&writetoken);
    }
    printf("Reader is Leaving\n");
    sem_post(&readtoken);

    
}



void * Writer_Function(void * args){


    printf("Writer is Waiting\n");
    sem_wait(&writetoken);
    printf("Writer is Writing to the database\n");

    sem_post(&writetoken);
        printf("Writer is leaving\n");
        



 
}


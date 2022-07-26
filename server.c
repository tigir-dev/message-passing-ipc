#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdbool.h>
#include <unistd.h>
#include "math.h"
#include "string.h"

pthread_t main_t,worker_t;
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
bool worker_finished;
key_t key;
int msgid;

struct msg_buf{
    int arr[1000];//max 500 elemanli array gonderebildik
    pid_t process_id;
    long mesg_type;
}message;


int comparator(const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}
/*
int to_string(char* dest, pid_t pid){
    int mod_val=1,len=0;
    int prev_val=0;
    do{
        mod_val*=10;
        prev_val=(((pid%mod_val)-prev_val)/(int)(pow(10,len)));
        dest[len++]=(char)(prev_val+48);
    }while(pid%mod_val!=pid);
    dest[len]='\0';
    return len;
}

char* reverse_string(char* string, int len){
    char* reversed= calloc(1,20);
    for(int i=0;i<=len;++i){
        reversed[i] = string[len-i];
    }
    reversed[len+1] = '\0';
    return reversed;
}
*/
void write_array(int array[], int size, char* filename)
{
    FILE* file=fopen(filename, "w");
    int i;
    for (i = 0; i < size; ++i){
        fprintf(file, "%d ", array[i]);
        if(i%50==0)
            fprintf(file, "\n");
    }
    fclose(file);
}

void print_array(int array[], int n)
{
    int i;
    printf("\n\n\n\n");
    for (i = 0; i < n; ++i)
        printf("%d ", array[i]);
}

void worker_thread_func(){
    //printf("worker kullanildi");
    worker_finished=false;
    pthread_mutex_lock(&lock);
    char* filename = calloc(1,20);

    sprintf(filename,"%d", message.process_id);
    strcat(filename,".txt");

    qsort(message.arr,sizeof(message.arr)/4, sizeof(int), comparator);
    //msgsnd(msgid,&sent.arr[0], sizeof(message.arr)/2, 0);
    //msgsnd(msgid,&sent.arr[500], sizeof(message.arr)/2, 0);
    write_array(message.arr, sizeof(message.arr)/4, filename);
    //free(reversed);
    free(filename);
    pthread_mutex_unlock(&lock);
    worker_finished=true;
}

void main_thread_func(){

    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    //printf("fonksiyona girdim");

    while(1){
        pthread_mutex_lock(&lock);
        msgrcv(msgid,&message.arr[0], sizeof(message.arr)/2, 0, 0);
        msgrcv(msgid,&message.arr[500], sizeof(message.arr)/2, 0, 0);
        msgrcv(msgid,&message.process_id, sizeof(pid_t), 0, 0);
        //print_array(message.arr, 1000);
        //printf("\n\nprocess id: %d\n", message.process_id);
        //printf("mesajlari aldim");
        pthread_mutex_unlock(&lock);
        pthread_create(&worker_t, NULL, (void *(*)(void *)) worker_thread_func, 0);
        pthread_join(worker_t,NULL);
        while(!worker_finished);
    }
}


int main() {
    worker_finished=false;
    pthread_create(&main_t, NULL, (void *(*)(void *)) main_thread_func, 0);
    pthread_join(main_t,NULL);
    printf("server is closed");
    return 0;
}

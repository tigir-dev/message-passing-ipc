#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include "string.h"



/*struct msg_buf{
    int arr[1000];
    pid_t process_id;
    long mesg_type;
}message;


void randomize_array(){
    srand(time(NULL));
    for(int i=0;i<1000;++i){
        message.arr[i]=rand()%100;
    }
}



void print_array(int array[], int n)
{
    int i;
    printf("\n\n\n\n");
    for (i = 0; i < n; ++i)
        printf("%d ", array[i]);
}

int main() {
    key_t key;
    int msgid;
    char* string=calloc(1,sizeof(char)*20);
    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.mesg_type = 1;
    message.process_id=getpid();

    while(1){
        randomize_array();

        msgsnd(msgid, &message.arr[0], sizeof(message.arr)/2, 0);
        msgsnd(msgid, &message.arr[500], sizeof(message.arr)/2, 0);
        msgsnd(msgid, &message.process_id, sizeof(pid_t), 0);
        print_array(message.arr, 1000);
        //msgrcv(msgid,&received.arr[0], sizeof(received.arr)/2, 0, 0);
        //msgrcv(msgid,&received.arr[500], sizeof(received.arr)/2, 0, 0);
        //print_array(received.arr, 1000);
        sleep(10);
    }
    //printf("Sent message is : %d \n", ww);
    printf("client is closed");
    return 0;
    /*
    int len= to_string(string, process_id);
    char* reversed = reverse_string(string, len);
    strcpy(string, reversed);
    string[len+1]='\0';
    strcpy(message.process_id, string);
     */
//}

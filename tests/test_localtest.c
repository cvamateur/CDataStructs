//
// Created by sparkai on 22-11-1.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


typedef struct  {
    int agentID;
    int numTicketsToSell;
} thread_data;


void* sellTickets(void *data);


int main() {

    int numAgents = 10;
    int numTickets = 150;

    pthread_t agentIDs[numAgents];
    thread_data agentWords[numAgents];

    for (int i = 0; i < numAgents; ++i) {
        agentWords[i].agentID = i;
        agentWords[i].numTicketsToSell = numTickets / numAgents;

        // create a new thread
        int rc = pthread_create(&agentIDs[i], NULL, sellTickets, &agentWords[i]);
        if (rc) {
            printf("\n error: return code from pthread_create is %d\n",rc);
            exit(1);
        }
    }
    pthread_exit(NULL);
}

void* sellTickets(void *threadarg) {
    thread_data *data;
    data = (thread_data*) threadarg;
    while (data->numTicketsToSell > 0) {
        printf("Agent[%d] sell a ticket\n", data->agentID);
        --data->numTicketsToSell;
        sleep(1);
    }
    printf("Agent[%d] all done!\n", data->agentID);
    return NULL;
}
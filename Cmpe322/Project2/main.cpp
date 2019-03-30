#include <iostream>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <pthread.h>
#include <unistd.h>
#include <ctime>
using namespace std;

//Mutex for client operations
pthread_mutex_t client_mutex = PTHREAD_MUTEX_INITIALIZER;
//Mutex for server operations
pthread_mutex_t server_mutex = PTHREAD_MUTEX_INITIALIZER;
//Array representing seats of plane
int seats[101];
//How many seat there are in plane actually
int seat_number;
//To provide a unique id to each client
int counter=1;
ofstream myfile;

//Method for server to reserve seat for its paired client
void *reserveSeat(void *param) {
    pthread_mutex_lock(&server_mutex);
    //Order is id of client
    int order= *((int *) param);
    pthread_mutex_unlock(&server_mutex);
    
    //In busy waiting state, server checks constantly if client makes a request for reservation
    int reservedSeat;
    bool x=true;
    while(x){
        for(int i=1;i<=seat_number;i++){
            if(seats[i]==(order*-1)){
                reservedSeat=i;
                x=false;
                break;
            }
        }
    }
    
    //Reserves the seat and print to the output file
    pthread_mutex_lock(&server_mutex);
    myfile << "Client" << -1*seats[reservedSeat] << " reserves Seat" << reservedSeat << endl;
    seats[reservedSeat]*=-1;
    pthread_mutex_unlock(&server_mutex);
    pthread_exit(0);
}
//Method for client to make a request
void *requestSeat(void *param) {
    
    pthread_mutex_lock(&client_mutex);
    //Order is id of the client
    int order=counter;
    int sleep_time = 1000*(rand() % 151 + 50);
    counter++;
    pthread_mutex_unlock(&client_mutex);
    
    usleep(sleep_time);
    
    pthread_t serverThread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&serverThread,&attr,reserveSeat,&order);
    
    //Looks for available seat in plane randomly and makes a request when it finds one
    pthread_mutex_lock(&client_mutex);
    int seat= rand() % seat_number +1;
    while(seats[seat]!=0){
        seat= rand() % seat_number +1;
    }
    seats[seat]=(-1*order);
    pthread_mutex_unlock(&client_mutex);
    
    pthread_join(serverThread, NULL);
    pthread_exit(0);
}


int main(int argc, char* argv[]) {
    //To produce different random numbers
    srand((unsigned)time(NULL));
    string file = argv[1];
    int number = atoi(file.c_str());
    myfile.open("output.txt");
    
    for(int i=0;i<101;i++){
        seats[i]=0;
    }
    //Array representing client threads
    pthread_t clients[number];
    pthread_attr_t attr[number];
    for(int i=0;i<number;i++){
        pthread_attr_init(&attr[i]);
    }
    seat_number=number;
    
    myfile << "Number of total seats: " << seat_number << endl;
    for(int i=0;i<number;i++){
        pthread_create(&clients[i],&attr[i],requestSeat, NULL);
    }
    for(int i=0;i<number;i++){
        pthread_join(clients[i], NULL);
    }
    
    myfile << "All seats are reserved." << endl;
    
    return 0;
}

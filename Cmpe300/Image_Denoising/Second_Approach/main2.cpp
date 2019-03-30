/*
 Student Name: Fahri Can Şanlı
 Student Number: 2015400096
 Compile Status: Compiling
 Program Status: Working
 */

#include <mpi.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <iterator>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <ctime>
using namespace std;

//To split lines read by the master processor
template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}

int main(int argc, char* argv[]) {
    //To produce random numbers
    srand((unsigned)time(NULL));
    //Rank of each processor and total size
    int rank, size;
    double beta, pi, gamma;
    string be = argv[3];
    string p = argv[4];
    beta = atof(be.c_str());
    pi = atof(p.c_str());
    gamma = 0.5 * log((1-pi)/pi);
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    //Number of slave processor
    int N = size -1;
    //Number of slave processor in each row
    int M = (int)sqrt(N);
    //How many row and column each slave processor will process
    int row= 200/M;
    //In total how many pixels each slave processor will process
    int data = row * row;
    //Total iteration amount
    int T=500000;
    //Denotes master process
    if(rank == 0){
        //Noisy image
        int xPicture [200][200];
        //Resulting image
        int result[200][200];
        int lin=0;
        //Reads from input file
        ifstream infile(argv[1]);
        string line;
        while(getline(infile,line)){
            vector<string> words;
            split1(line,words);
            for(int i=0;i<words.size();i++){
                xPicture[lin][i]=atoi(words[i].c_str());
            }
            lin++;
        }
        //Sends to each slave processor
        for(int i=1;i<=N;i++){
            for(int j=0;j<row;j++){
                MPI_Send(&xPicture[row*((i-1)/M)+j][row*((i-1)%M)], row, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }
        //Receives from each processor in order and place them into result array
        for(int t=1;t<=N;t++){
            for(int y=0;y<row;y++){
                int* subarr1 = NULL;
                subarr1 = (int *)malloc(sizeof(int) * row);
                MPI_Recv(subarr1, row, MPI_INT, t, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                for(int i=0;i<row;i++){
                    result[y+row*((t-1)/M)][row*((t-1)%M)+i]=subarr1[i];
                }
                delete subarr1;
            }
        }
        //Writes to output file
        ofstream myfile;
        myfile.open(argv[2]);
        for(int i=0;i<200;i++){
            for(int j=0;j<199;j++){
                myfile << result[i][j] << " ";
                
            }
            myfile << result[i][199] << endl;
        }
    }
    //Represents the slave processors
    else{
        //At first receive from master processor and replace each pixel temporary X image array and temporary Z image array
        int tempX[row][row];
        int tempZ[row][row];
        for(int i=0;i<row;i++){
            int* subarr = NULL;
            subarr = (int *)malloc(sizeof(int) * row);
            MPI_Recv(subarr, row, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for(int j=0;j<row;j++){
                tempX[i][j]=subarr[j];
                tempZ[i][j]=subarr[j];
            }
            delete subarr;
        }
        for(int a=0;a<(T/N);a++){
            int right[row][1];
            int left[row][1];
            int down[row];
            int up[row];
            int rightDownCorner;
            int leftDownCorner;
            int rightUpCorner;
            int leftUpCorner;
            int sendRight[row];
            int sendLeft[row];
            for(int s=0;s<row;s++){
                sendRight[s]=tempZ[s][row-1];
                sendLeft[s]=tempZ[s][0];
            }
            //Communication of processors
            //Left-right communication
            if(rank%M!=0){
                int* sub = NULL;
                sub = (int *)malloc(sizeof(int) * row);
                MPI_Recv(sub, row, MPI_INT, rank+1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                for(int s=0;s<row;s++){
                    right[s][0]=sub[s];
                }
                delete sub;
                MPI_Send(sendRight, row, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
            }
            if(rank%M!=1){
                MPI_Send(sendLeft, row, MPI_INT, rank-1, 0, MPI_COMM_WORLD);
                int* sub1 = NULL;
                sub1= (int *)malloc(sizeof(int) * row);
                MPI_Recv(sub1, row, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                for(int s=0;s<row;s++){
                    left[s][0]=sub1[s];
                }
                delete sub1;
            }
            //Up-down communication
            if((rank-1)/M!=(M-1)){
                int* sub2 = NULL;
                sub2= (int *)malloc(sizeof(int) * row);
                MPI_Recv(sub2, row, MPI_INT, rank+M, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                for(int s=0;s<row;s++){
                    down[s]=sub2[s];
                }
                delete sub2;
                MPI_Send(tempZ[row-1], row, MPI_INT, rank+M, 0, MPI_COMM_WORLD);
            }
            if((rank-1)/M!=0){
                MPI_Send(tempZ[0], row, MPI_INT, rank-M, 0, MPI_COMM_WORLD);
                int* sub3 = NULL;
                sub3 = (int *)malloc(sizeof(int) * row);
                MPI_Recv(sub3, row, MPI_INT, rank-M, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                for(int s=0;s<row;s++){
                    up[s]=sub3[s];
                }
                delete sub3;
            }
            //Diagonal communication(from left upper to right bottom corner)
            if(rank%M!=0 && (rank-1)/M!=(M-1) ){
                int* sub4 = NULL;
                sub4 = (int *)malloc(sizeof(int));
                MPI_Recv(sub4, 1, MPI_INT, rank+M+1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                rightDownCorner=*sub4;
                delete sub4;
                MPI_Send(&tempZ[row-1][row-1], 1, MPI_INT, rank+M+1, 0, MPI_COMM_WORLD);
            }
            if(rank%M!=1 && (rank-1)/M!=0 ){
                MPI_Send(&tempZ[0][0], 1, MPI_INT, rank-M-1, 0, MPI_COMM_WORLD);
                int* sub5 = NULL;
                sub5 = (int *)malloc(sizeof(int));
                MPI_Recv(sub5, 1, MPI_INT, rank-M-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                leftUpCorner=*sub5;
                delete sub5;
            }
            //Diagonal communication(from right upper to left bottom corner)
            if(rank%M!=1 && (rank-1)/M!=(M-1) ){
                int* sub6 = NULL;
                sub6 = (int *)malloc(sizeof(int));
                MPI_Recv(sub6, 1, MPI_INT, rank+M-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                leftDownCorner=*sub6;
                delete sub6;
                MPI_Send(&tempZ[row-1][0], 1, MPI_INT, rank+M-1, 0, MPI_COMM_WORLD);
            }
            if(rank%M!=0 && (rank-1)/M!=0){
                MPI_Send(&tempZ[0][row-1], 1, MPI_INT, rank-M+1, 0, MPI_COMM_WORLD);
                int* sub7 = NULL;
                sub7 = (int *)malloc(sizeof(int));
                MPI_Recv(sub7, 1, MPI_INT, rank-M+1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                rightUpCorner=*sub7;
                delete sub7;
            }
            //I classified slave processor into 9 categories and calculated sum accordingly
            if(rank==1){
                
                int i = rand() % row;
                int j= rand() % row;
                int sum=0;
                
                if(i==0 && j==0){
                    sum+=tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1];
                }
                else if(i==0 && j==row-1){
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + right[i+1][0] + right[i][0];
                }
                else if(i==row-1 && j==0){
                    sum+=down[j] + down[j+1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i][j];
                }
                else if(i==row-1 && j==row-1){
                    sum+=tempZ[i][j-1] + down[j-1] + down[j] + rightDownCorner + right[i][0] + right[i-1][0] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                else if(i==0){
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1];
                }
                else if(j==0){
                    sum+=tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j];
                }
                else if(j==row-1){
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + right[i+1][0] + right[i][0] + right[i-1][0] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                else if(i==row-1){
                    sum+=tempZ[i][j-1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + tempZ[i-1][j-1] + down[j-1] + down[j] + down[j+1];
                }
                else{
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                double alfa = min(1.0 ,exp((-2 * gamma * tempX[i][j] * tempZ[i][j]) + (-2 * beta * tempZ[i][j] * sum)));
                double random=((double)rand()/(double)RAND_MAX);
                if(random < alfa){
                    tempZ[i][j] *= -1;
                }
            }
            else if(rank / M == 0){
                
                int i = rand() % row;
                int j= rand() % row;
                int sum=0;
                
                if(i==0 && j==0){
                    sum+= left[i][j] + left[i+1][j] + tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1];
                }
                else if(i==0 && j==row-1){
                    sum+= tempZ[i][j-1] +tempZ[i+1][j-1] + tempZ[i+1][j] + right[i+1][0] + right[i][0];
                }
                else if(i==row-1 && j==0){
                    sum+=left[i][j] + leftDownCorner + down[j] + down[j+1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + left[i-1][0];
                }
                else if(i==row-1 && j==row-1){
                    sum+=tempZ[i][j-1] + down[j-1] + down[j] + rightDownCorner + right[i][0] + right[i-1][0] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                else if(i==0){
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1];
                }
                else if(j==0){
                    sum+=left[i][0] + left[i+1][0] + tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + left[i-1][0];
                }
                else if(j==row-1){
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + right[i+1][0] + right[i][0] + right[i-1][0] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                else if(i==row-1){
                    sum+=tempZ[i][j-1] + down[j-1] + down[j] + down[j+1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                else{
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                double alfa = min(1.0 ,exp((-2 * gamma * tempX[i][j] * tempZ[i][j]) + (-2 * beta * tempZ[i][j] * sum)));
                double random=((double)rand()/(double)RAND_MAX);
                if(random < alfa){
                    tempZ[i][j] *= -1;
                }
            }
            else if(rank == M){
                
                int i = rand() % row;
                int j= rand() % row;
                int sum=0;
                
                if(i==0 && j==0){
                    sum+=left[i][0] + left[i+1][0] + tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1];
                }
                else if(i==0 && j==row-1){
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j];
                }
                else if(i==row-1 && j==0){
                    sum+=left[i][0] + leftDownCorner + down[j] + down[j+1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + left[i-1][0];
                }
                else if(i==row-1 && j==row-1){
                    sum+=tempZ[i][j-1] + down[j-1] + down[j] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                else if(i==0){
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1];
                }
                else if(j==0){
                    sum+=left[i][0] +left[i+1][0]+ tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + left[i-1][0];
                }
                else if(j==row-1){
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                else if(i==row-1){
                    sum+=tempZ[i][j-1] + down[j-1] + down[j] + down[j+1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                else{
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                double alfa = min(1.0 ,exp((-2 * gamma * tempX[i][j] * tempZ[i][j]) + (-2 * beta * tempZ[i][j] * sum)));
                double random=((double)rand()/(double)RAND_MAX);
                if(random < alfa){
                    tempZ[i][j] *= -1;
                }
                
            }
            else if(1<=(rank/M) && (rank/M)< M-1 && rank%M == 1 ){
                
                int i = rand() % row;
                int j= rand() % row;
                int sum=0;
                
                if(i==0 && j==0){
                    sum+=tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + up[j+1] + up[j];
                }
                else if(i==0 && j==row-1){
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + right[i+1][0] + right[i][0] + rightUpCorner + up[j] + up[j-1];
                }
                else if(i==row-1 && j==0){
                    sum+=down[j] + down[j+1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j];
                }
                else if(i==row-1 && j==row-1){
                    sum+=tempZ[i][j-1] + down[j-1] + down[j] + rightDownCorner + right[i][0] + right[i-1][0] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                else if(i==0){
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + up[j+1] + up[j] + up[j-1];
                }
                else if(j==0){
                    sum+=tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j];
                }
                else if(j==row-1){
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + right[i+1][0] + right[i][0] + right[i-1][0] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                else if(i==row-1){
                    sum+=tempZ[i][j-1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + tempZ[i-1][j-1] + down[j-1] + down[j] + down[j+1];
                }
                else{
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                double alfa = min(1.0 ,exp((-2 * gamma * tempX[i][j] * tempZ[i][j]) + (-2 * beta * tempZ[i][j] * sum)));
                double random=((double)rand()/(double)RAND_MAX);
                if(random < alfa){
                    tempZ[i][j] *= -1;
                }
                
            }
            else if(1<=(rank/M) && (rank/M)< M && rank%M == 0){
                
                int i = rand() % row;
                int j= rand() % row;
                int sum=0;
                
                if(i==0 && j==0){
                    sum+=left[i][0] + left[i+1][0] + tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + up[j+1] + up[j] +leftUpCorner;
                }
                else if(i==0 && j==row-1){
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + up[j] + up[j-1];
                }
                else if(i==row-1 && j==0){
                    sum+=left[i][0] + leftDownCorner + down[j] + down[j+1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + left[i-1][0];
                }
                else if(i==row-1 && j==row-1){
                    sum+=tempZ[i][j-1] + down[j-1] + down[j] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                else if(i==0){
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + up[j+1] + up[j] +up[j-1];
                }
                else if(j==0){
                    sum+= left[i][0] + left[i+1][0] + tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + left[i-1][0] ;
                }
                else if(j==row-1){
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                else if(i==row-1){
                    sum+=tempZ[i][j-1] + down[j-1] + down[j] + down[j+1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                else{
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                double alfa = min(1.0 ,exp((-2 * gamma * tempX[i][j] * tempZ[i][j]) + (-2 * beta * tempZ[i][j] * sum)));
                double random=((double)rand()/(double)RAND_MAX);
                if(random < alfa){
                    tempZ[i][j] *= -1;
                }
            }
            else if(rank == M * (M-1) +1){
                
                int i = rand() % row;
                int j= rand() % row;
                int sum=0;
                
                if(i==0 && j==0){
                    sum+=tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + up[j+1] + up[j];
                }
                else if(i==0 && j==row-1){
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + right[i+1][0] + right[i][0] + rightUpCorner + up[j] + up[j-1];
                }
                else if(i==row-1 && j==0){
                    sum+=tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j];
                }
                else if(i==row-1 && j==row-1){
                    sum+=tempZ[i][j-1] + right[i][0] + right[i-1][0] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                else if(i==0){
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + up[j+1] + up[j] + up[j-1];
                }
                else if(j==0){
                    sum+=tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j];
                }
                else if(j==row-1){
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + right[i+1][0] + right[i][0] + right[i-1][0] +  tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                else if(i==row-1){
                    sum+=tempZ[i][j-1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                else{
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                double alfa = min(1.0 ,exp((-2 * gamma * tempX[i][j] * tempZ[i][j]) + (-2 * beta * tempZ[i][j] * sum)));
                double random=((double)rand()/(double)RAND_MAX);
                if(random < alfa){
                    tempZ[i][j] *= -1;
                }
            }
            else if(rank/M == M-1){
                
                int i = rand() % row;
                int j= rand() % row;
                int sum=0;
                
                if(i==0 && j==0){
                    sum+= left[i][0] + left[i+1][0] + tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + up[j+1] + up[j] + leftUpCorner;
                }
                else if(i==0 && j==row-1){
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + right[i+1][0] + right[i][0] + rightUpCorner + up[j] + up[j-1];
                }
                else if(i==row-1 && j==0){
                    sum+=left[i][0] + left[i-1][0] + tempZ[i-1][j] + tempZ[i-1][j+1] + tempZ[i][j+1];
                }
                else if(i==row-1 && j==row-1){
                    sum+=tempZ[i][j-1] + tempZ[i-1][j-1] + tempZ[i-1][j] + right[i-1][0] + right[i][0];
                }
                else if(i==0){
                    sum+= tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + up[j+1] + up[j] +up[j-1];
                }
                else if(j==0){
                    sum+=left[i][0] +left[i+1][0]+ tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + left[i-1][0];
                }
                else if(j==row-1){
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + right[i+1][0] + right[i][0] + right[i-1][0] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                else if(i==row-1){
                    sum+=tempZ[i][j-1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                else{
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                double alfa = min(1.0 ,exp((-2 * gamma * tempX[i][j] * tempZ[i][j]) + (-2 * beta * tempZ[i][j] * sum)));
                double random=((double)rand()/(double)RAND_MAX);
                if(random < alfa){
                    tempZ[i][j] *= -1;
                }
            }
            else if(rank == M*M){
                
                int i = rand() % row;
                int j= rand() % row;
                int sum=0;
                
                if(i==0 && j==0){
                    sum+=left[i][0] + left[i+1][0] + tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + up[j+1] + up[j] +leftUpCorner;
                }
                else if(i==0 && j==row-1){
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + up[j] + up[j-1];
                }
                else if(i==row-1 && j==0){
                    sum+=left[i][0] + left[i-1][0] + tempZ[i-1][j] + tempZ[i-1][j+1] + tempZ[i][j+1];
                }
                else if(i==row-1 && j==row-1){
                    sum+=tempZ[i][j-1] + tempZ[i-1][j-1] + tempZ[i-1][j];
                }
                else if(i==0){
                    sum+= tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + up[j+1] + up[j] +up[j-1];
                }
                else if(j==0){
                    sum+=left[i][0] +left[i+1][0]+ tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + left[i-1][0];
                }
                else if(j==row-1){
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                else if(i==row-1){
                    sum+=tempZ[i][j-1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                else{
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                double alfa = min(1.0 ,exp((-2 * gamma * tempX[i][j] * tempZ[i][j]) + (-2 * beta * tempZ[i][j] * sum)));
                double random=((double)rand()/(double)RAND_MAX);
                if(random < alfa){
                    tempZ[i][j] *= -1;
                }
                
            }
            else{
                
                int i = rand() % row;
                int j= rand() % row;
                int sum=0;
                
                if(i==0 && j==0){
                    sum+=left[i][0] + left[i+1][0] + tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + up[j+1] + up[j] +leftUpCorner;
                }
                else if(i==0 && j==row-1){
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + right[i+1][0] + right[i][0] + rightUpCorner + up[j] + up[j-1];
                }
                else if(i==row-1 && j==0){
                    sum+=left[i][0] + leftDownCorner + down[j] + down[j+1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + left[i-1][0];
                }
                else if(i==row-1 && j==row-1){
                    sum+=tempZ[i][j-1] + down[j-1] + down[j] + rightDownCorner + right[i][0] + right[i-1][0] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                else if(i==0){
                    sum+= tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + up[j+1] + up[j] +up[j-1];
                }
                else if(j==0){
                    sum+=left[i][0] +left[i+1][0]+ tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + left[i-1][0];
                }
                else if(j==row-1){
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + right[i+1][0] + right[i][0] + right[i-1][0] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                else if(i==row-1){
                    sum+=tempZ[i][j-1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + tempZ[i-1][j-1] + down[j-1] + down[j] + down[j+1];
                }
                else{
                    sum+=tempZ[i][j-1] + tempZ[i+1][j-1] + tempZ[i+1][j] + tempZ[i+1][j+1] + tempZ[i][j+1] + tempZ[i-1][j+1] + tempZ[i-1][j] + tempZ[i-1][j-1];
                }
                double alfa = min(1.0 ,exp((-2 * gamma * tempX[i][j] * tempZ[i][j]) + (-2 * beta * tempZ[i][j] * sum)));
                double random=((double)rand()/(double)RAND_MAX);
                if(random < alfa){
                    tempZ[i][j] *= -1;
                }
                
                
            }
            
        }
        for(int u=0;u<row;u++){
            MPI_Send(&tempZ[u][0], row, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
        
    }
    MPI_Finalize();
    
    return 0;
}

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
    //How many row each slave processor will process
    int row= 200/N;
    //In total how many pixels each slave processor will process
    int data = 200 * row;
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
        for(int i = 1 ; i <= N ; i++){
            MPI_Send(xPicture[row*(i-1)], data, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        //Receives from each processor in order and place them into result array
        for(int t=1;t<=N;t++){
            int* subarr1 = NULL;
            subarr1 = (int *)malloc(sizeof(int) * data);
            MPI_Recv(subarr1, data, MPI_INT, t, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for(int i=0;i<row;i++){
                for(int j=0;j<200;j++){
                    result[i+(t-1)*row][j] = subarr1[i*200 + j];
                }
            }
            delete subarr1;
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
    //Represents the slave processor at the top
    else if(rank == 1){
        //At first receive from master processor and replace each pixel temporary X image array and temporary Z image array
        int* subarr = NULL;
        subarr = (int *)malloc(sizeof(int) * data);
        MPI_Recv(subarr, data, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        int tempX[row][200];
        int tempZ[row][200];
        int lower[200];
        for(int i=0;i<data;i++){
            tempX[i/200][i%200]=subarr[i];
            tempZ[i/200][i%200]=subarr[i];
        }
        delete subarr;
        //Start to iterate
        for(int a=0;a<(T/N);a++){
            //Firstly receives from the processor below it and then sends to it
            if(N!=1){
                int* sub = NULL;
                sub = (int *)malloc(sizeof(int) * 200);
                MPI_Recv(sub, 200, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                for(int s=0;s<200;s++){
                    lower[s]=sub[s];
                }
                delete sub;
                MPI_Send(tempZ[row-1], 200, MPI_INT, 2, 0, MPI_COMM_WORLD);
            }
            //Chooses a random pixel
            int i = rand() % row;
            int j= rand() % 200;
            int sum=0;
            //Calculates the sum of neighbor cells
            for(int e=i-1;e<=i+1;e++){
                for(int f=j-1;f<=j+1;f++){
                    if(i!=row-1 && e>=0 && e<=row-1 && f>=0 && f<=199){
                        sum+=tempZ[e][f];
                    }
                    if(i==row-1 && e<=row-1 && f>=0 && f<=199){
                        sum+=tempZ[e][f];
                    }
                    if(i==row-1 && e==row && f>=0 && f<=199 && N!=1){
                        sum+=lower[f];
                    }
                }
            }
            sum-=tempZ[i][j];
            double alfa = min(1.0 ,exp((-2 * gamma * tempX[i][j] * tempZ[i][j]) + (-2 * beta * tempZ[i][j] * sum)));
            double random=((double)rand()/(double)RAND_MAX);
            if(random < alfa){
                tempZ[i][j] *= -1;
            }
        }
        //After finishing all iterations sends the final Z image to the master processor
        MPI_Send(tempZ, data, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    //Represents the slave processor at the down
    else if(rank == N && N!=1){
        //At first receive from master processor and replace each pixel temporary X image array and temporary Z image array
        int* subarr = NULL;
        subarr = (int *)malloc(sizeof(int) * data);
        MPI_Recv(subarr, data, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        int tempX[row][200];
        int tempZ[row][200];
        int upper[200];
        for(int i=0;i<data;i++){
            tempX[i/200][i%200]=subarr[i];
            tempZ[i/200][i%200]=subarr[i];
        }
        delete subarr;
        //Start to iterate
        for(int a=0;a<(T/N);a++){
            //Firstly sends to the processor above it and then receives from it
            MPI_Send(tempZ[0], 200, MPI_INT, N-1, 0, MPI_COMM_WORLD);
            int* sub = NULL;
            sub = (int *)malloc(sizeof(int) * 200);
            MPI_Recv(sub, 200, MPI_INT, N-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for(int s=0;s<200;s++){
                upper[s]=sub[s];
            }
            delete sub;
            //Chooses a random pixel
            int i = rand() % row;
            int j= rand() % 200;
            int sum=0;
            //Calculates the sum of neighbor cells
            for(int e=i-1;e<=i+1;e++){
                for(int f=j-1;f<=j+1;f++){
                    if(i!=0 && e>=0 && e<=row-1 && f>=0 && f<=199){
                        sum+=tempZ[e][f];
                    }
                    if(i==0 && e>=0 && f>=0 && f<=199){
                        sum+=tempZ[e][f];
                    }
                    if(i==0 && e==-1 && f>=0 && f<=199){
                        sum+=upper[f];
                    }
                }
            }
            sum-=tempZ[i][j];
            double alfa = min(1.0 ,exp((-2 * gamma * tempX[i][j] * tempZ[i][j]) + (-2 * beta * tempZ[i][j] * sum)));
            double random=((double)rand()/(double)RAND_MAX);
            if(random < alfa){
                tempZ[i][j] *= -1;
            }
        }
        //After finishing all iterations sends the final Z image to the master processor
        MPI_Send(tempZ, data, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    //Represents the slave processors between the first and the last one
    else if(N!=1 && rank!=1 && rank!=N){
        //At first receive from master processor and replace each pixel temporary X image array and temporary Z image array
        int* subarr = NULL;
        subarr = (int *)malloc(sizeof(int) * data);
        MPI_Recv(subarr, data, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        int tempX[row][200];
        int tempZ[row][200];
        int upper[200];
        int lower[200];
        for(int i=0;i<data;i++){
            tempX[i/200][i%200]=subarr[i];
            tempZ[i/200][i%200]=subarr[i];
        }
        delete subarr;
        //Start to iterate
        for(int a=0;a<(T/N);a++){
            //Firstly sends to the processor above it and then receives from it
            MPI_Send(tempZ[0], 200, MPI_INT, rank-1, 0, MPI_COMM_WORLD);
            int* sub = NULL;
            sub = (int *)malloc(sizeof(int) * 200);
            MPI_Recv(sub, 200, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for(int s=0;s<200;s++){
                upper[s]=sub[s];
            }
            delete sub;
            //Secondly receives from the processor below it and then sends to it
            int* subb = NULL;
            subb = (int *)malloc(sizeof(int) * 200);
            MPI_Recv(subb, 200, MPI_INT, rank+1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for(int s=0;s<200;s++){
                lower[s]=subb[s];
            }
            delete subb;
            MPI_Send(tempZ[row-1], 200, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
            //Chooses a random pixel
            int i = rand() % row;
            int j= rand() % 200;
            int sum=0;
            //Calculates the sum of neighbor cells
            for(int e=i-1;e<=i+1;e++){
                for(int f=j-1;f<=j+1;f++){
                    if(i!=row-1 && i!=0 && e>=0 && e<=row-1 && f>=0 && f<=199){
                        sum+=tempZ[e][f];
                    }
                    if(i==row-1 && e<=row-1 && f>=0 && f<=199){
                        sum+=tempZ[e][f];
                    }
                    if(i==row-1 && e==row && f>=0 && f<=199){
                        sum+=lower[f];
                    }
                    if(i==0 && e>=0 && f>=0 && f<=199){
                        sum+=tempZ[e][f];
                    }
                    if(i==0 && e==-1 && f>=0 && f<=199){
                        sum+=upper[f];
                    }
                }
            }
            sum-=tempZ[i][j];
            double alfa = min(1.0 ,exp((-2 * gamma * tempX[i][j] * tempZ[i][j]) + (-2 * beta * tempZ[i][j] * sum)));
            double random=((double)rand()/(double)RAND_MAX);
            if(random < alfa){
                tempZ[i][j] *= -1;
            }
        }
        //After finishing all iterations sends the final Z image to the master processor
        MPI_Send(tempZ, data, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    
    return 0;
}

#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <iterator>
#include <stdlib.h>
#include <string>
using namespace std;

//A struct for instruction wiht ID and process time of instruction
struct Instruction{
    string ID;
    int processTime;

    Instruction(string id,int time){
        this->ID=id;
        this->processTime=time;
    }
};
//A struct for process with necessary fields such as ID, arrival time, priority etc.
struct Process{
    string ID;
    int priority;
    int arrivalTime;
    int counter;
    string filename;
    int waitTime;
    int turnaround;
    int lastActive;
    int location;
    vector<Instruction> instructions;
    Process(string id,int _priority, string file, int arrTime, int location){
        this->ID=id;
        this->arrivalTime=arrTime;
        this->priority=_priority;
        this->counter=1;
        this->filename=file;
        this->waitTime=0;
        this->turnaround=0;
        this->lastActive=arrTime;
        this->location=location;
    }

};
//This one is used to form a vector with respect to priority and arrival time of processes
bool myComparator(Process &p1, Process &p2){

    if(p1.priority==p2.priority){
        return p1.arrivalTime < p2.arrivalTime;
    }

    return p1.priority < p2.priority;
}

template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}

int main(int argc,char* argv[]) {

    ifstream infile("./definition.txt");
    //A vector to hold all processes at the beginning
    vector<Process> process;
    string line;
    int lin=0;
    //Reading all processes from the definition file
    while(getline(infile,line)){
        vector<string> words;
        split1(line,words);
        Process newOne(words[0].c_str(),atoi(words[1].c_str()),words[2].c_str(),atoi(words[3].c_str()), lin);
        process.push_back(newOne);
        lin++;
    }
    //Reading correct code file to add instructions of each process to itself
    for(int i=0;i<process.size();i++){
        Process current=process[i];
        ifstream file(("./"+current.filename+".txt").c_str());
        string instructionLine;
        while(getline(file,instructionLine)){
            vector<string> word;
            split1(instructionLine,word);
            Instruction newOne(word[0].c_str(),atoi(word[1].c_str()));
            current.instructions.push_back(newOne);
        }
        process[i]=current;
    }

    ofstream myfile;
    myfile.open("./output.txt");
    //The general time
    int time=0;
    //Readyqueue that holds the processes waiting to be processed in the system including the one in the CPU at that moment
    vector<Process> readyQueue;
    //A vector that holds processes finished being executed
    vector<Process> finishedQueue=process;
    myfile << time << ":HEAD--TAIL" << endl;
    readyQueue.push_back(process[0]);
    time=process[0].arrivalTime;
    process.erase(process.begin());

    while(!readyQueue.empty()){
        //if there are multiple processes that have the same arrival time
        if(!process.empty() && time==process[0].arrivalTime){
            readyQueue.push_back(process[0]);
            process.erase(process.begin());
        }
        else{
            //sorts readyqueue and prints it
            sort(readyQueue.begin(),readyQueue.end(),myComparator);
            myfile << time << ":HEAD-" ;
            for(int i=0;i<readyQueue.size();i++){
                myfile << readyQueue[i].ID << "[" << readyQueue[i].counter << "]-" ;
            }
            myfile << "TAIL" << endl;

            Process current = readyQueue[0];

            //Updates the waiting time of the process in the CPU currently
            current.waitTime+= (time-current.lastActive);

            //If all processes haven't arrived to readyqueue yet
            if(!process.empty()){
                //Executes instructions of current process until it finishes or next process comes to the system
                while(time < process[0].arrivalTime){
                    //en son instructionsa turnaround hesaplayıp yeni processese geçmeli
                    if(current.instructions[current.counter-1].ID=="exit"){
                        time += current.instructions[current.counter-1].processTime;
                        current.turnaround=time-current.arrivalTime;
                        current.counter++;
                        readyQueue.erase(readyQueue.begin());
                        finishedQueue[current.location]=current;
                        break;
                    }
                    else{
                        time += current.instructions[current.counter-1].processTime;
                        current.counter++;
                        current.lastActive=time;
                    }
                }
                //If current process hasn't finished yet, updates it
                if(current.counter<=current.instructions.size()){
                    readyQueue[0]=current;
                }
                //If current process is finished, readyqueue is empty and the arrival time of next process hasn't come yet then
                //we add the next process to the readyqueue and makes the general time equal to arrival time of next process
                if(current.counter > current.instructions.size()  && readyQueue.empty() && time < process[0].arrivalTime){
                    myfile << time << ":HEAD--TAIL" << endl;
                    readyQueue.push_back(process[0]);
                    time=process[0].arrivalTime;
                    process.erase(process.begin());
                }
                    //Otherwise it adds processes that have already come to system at that moment or before
                else{
                    while(!process.empty() && time>=process[0].arrivalTime){
                        readyQueue.push_back(process[0]);
                        process.erase(process.begin());
                    }
                }

            }
                //If all processes is available in the readyqueue if they are not finished of course
            else if(process.empty()){
                while(current.counter<current.instructions.size()){
                    time += current.instructions[current.counter-1].processTime;
                    current.counter++;
                    current.lastActive=time;
                }
                time += current.instructions[current.counter-1].processTime;
                current.turnaround=time-current.arrivalTime;
                current.counter++;
                readyQueue.erase(readyQueue.begin());
                finishedQueue[current.location]=current;

            }

        }

    }

    sort(readyQueue.begin(),readyQueue.end(),myComparator);
    myfile << time << ":HEAD-" ;
    for(int i=0;i<readyQueue.size();i++){
        myfile << readyQueue[i].ID << "[" << readyQueue[i].counter << "]-" ;
    }

    myfile << "-TAIL" << endl;
    myfile << endl;
    //Writes turnaround time and waiting time of each process to the output file
    for(int i=0;i<finishedQueue.size();i++){
        myfile << "Turnaround time for " << finishedQueue[i].ID << " = " << finishedQueue[i].turnaround << " ms" << endl;
        myfile << "Waiting time for " << finishedQueue[i].ID << " = " << finishedQueue[i].waitTime << endl;
    }
    return 0;
}
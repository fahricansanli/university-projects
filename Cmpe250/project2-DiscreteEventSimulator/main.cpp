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
// A struct for customer
struct Customer{
    int line;  // specify the the number of the customer according to their arrival time
    double arr;
    double time;
    double ordTime;
    double brewTime;
    double price;
    int location;  // holds the at which process customer is
    Customer(double time_,double ordTime_,double brewTime_,double price_,int location_,int line_){
        this->time=time_;
        this->ordTime=ordTime_;
        this->brewTime=brewTime_;
        this->price=price_;
        this->location=location_;
        this->line=line_;
        this->arr=time_;
    }
    Customer(){

    }

};
// this one is used to form a priority queue with respect to arrival time
struct myComparator {
    bool operator()(Customer &c1, Customer &c2) {
        return c1.time > c2.time;
    }
};
//this one is used to form a priority queue with respect to price of order
struct compare{
    bool operator()(Customer &c1, Customer &c2) {
        return c1.price < c2.price;
    }
};
// struct for cashier
struct Cashier{
    bool empty;
    double activityTime;
    double time; // it holds the time that cashier will be available


    Cashier(){
        this->empty=true;
        this->activityTime=0;
        this->time=0;
    }


};
//struct for barista
struct Barista{
    bool empty;
    double activityTime;
    double time; // it holds the time that barista will be available

    Barista(){
        this->empty=true;
        this->activityTime=0;
        this->time=0;
    }
};
// a struct to form an priority queue where I can easily reach the max length
struct baristaQ{
    int max_length; //max length of priority queue
    int length; // its dinamic length
    std::priority_queue<Customer, std::vector<Customer>, compare > baristaQueue;
    baristaQ(){
        max_length = 0;
        length = 0;
    }
    void push(Customer e){
        baristaQueue.push(e);
        length++;
        if(length>max_length){
            max_length = length;
        }
    }
    const Customer& top() const{
        baristaQueue.top();
    }
    void pop(){
        baristaQueue.pop();
        length--;
    }
    bool empty(){
        return baristaQueue.empty();
    }
};
//struct to form a queue
struct cashierQ{
    int max_length; //its max length
    int length;
    std::queue<Customer> cashierQueue;
    cashierQ(){
        max_length = 0;
        length = 0;
    }
    void push(Customer e){
        cashierQueue.push(e);
        length++;
        if(length>max_length){
            max_length = length;
        }
    }
    const Customer& top() const{
        cashierQueue.front();
    }
    void pop(){
        cashierQueue.pop();
        length--;
    }
    bool empty(){
        return cashierQueue.empty();
    }
};


template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}

int main(int argc,char* argv[]) {
    if (argc != 3) {
        cout << "Run the code with the following command: ./project1 [input_file] [output_file]" << endl;
        return 1;
    }

    cout << "input file: " << argv[1] << endl;
    cout << "output file: " << argv[2] << endl;

    ifstream infile(argv[1]);
    //cout << clock() << endl;
    //ifstream infile("large-input.txt");
    int a; // number of cashier
    int b; // number of orders

    string line;
    getline(infile, line);
    a = stoi(line);
    vector<Cashier> cashier; //cashier vector for model 1
    vector<Cashier> cashier2; //cashier vector for model 2
    for(int i=0;i<a;i++){
        cashier.push_back(Cashier());
        cashier2.push_back(Cashier());
    }

    vector<Barista> barista; //barista vector for model 1
    vector<Barista> barista2; //barista vector for model 2
    for(int i=0;i<a/3;i++){
        barista.push_back(Barista());
        barista2.push_back(Barista());
    }

    getline(infile, line);
    b =stoi(line);
    Customer processedCustomer[b]; // an array of customer that is going to leave the system for model 1
    Customer processedCustomer2[b]; // an array of customer that is going to leave the system for model 2
    priority_queue <Customer, vector<Customer>,myComparator  > pq; // for model 1
    priority_queue <Customer, vector<Customer>,myComparator  > pq2; //for model 2
    for(int i=0;i<b;i++){
        getline(infile, line);

        vector<string> words;
        split1(line,words);
        Customer order(atof(words[0].c_str()),atof(words[1].c_str()),atof(words[2].c_str()),atof(words[3].c_str()),1,i+1);
        pq.push(order);
        pq2.push(order);
    }

    cashierQ cashierQueue; //for model 1
    baristaQ baristaQueue; //for model 1
    cashierQ cashierQueue2; //for model 2
    vector<baristaQ> baristaQueue2; //for model 2
    for(int i=0;i<a/3;i++){
        baristaQueue2.push_back(baristaQ());
    }
    double time=0;
    while(!pq.empty()){
        Customer current=pq.top(); // process each event with respect to timeline
        pq.pop();
        time=current.time;
        //if the customer wants to go to cashier
        if(current.location==1){
            for(int i=0;i<a;i++){
                if(cashier[i].empty){
                    cashier[i].empty=false;
                    cashier[i].activityTime+=current.ordTime;
                    current.time+=current.ordTime;
                    cashier[i].time=current.time;
                    current.location=3;
                    pq.push(current);
                    break;
                }
                else if(i==(a-1)){
                    cashierQueue.push(current);
                    break;
                }
            }
        }
            //if the customer finished with customer and wants to go to barista
        else if(current.location==3){
            if(!cashierQueue.empty()){
                Customer next=cashierQueue.top();
                cashierQueue.pop();
                for(int i=0;i<a;i++){
                    if(cashier[i].time==current.time){
                        next.location=3;
                        next.time=cashier[i].time+next.ordTime;
                        cashier[i].time=next.time;
                        cashier[i].activityTime+=next.ordTime;
                        pq.push(next);
                        break;
                    }
                }
                for(int i=0;i<(a/3);i++){
                    if(barista[i].empty){
                        barista[i].empty=false;
                        barista[i].activityTime+=current.brewTime;
                        current.time+=current.brewTime;
                        barista[i].time=current.time;
                        current.location=5;
                        pq.push(current);
                        break;

                    }
                    else if(i==(a/3)-1){
                        baristaQueue.push(current);
                        break;
                    }
                }
            }
            else if(cashierQueue.empty()){
                for (int i = 0; i < a; i++) {
                    if (cashier[i].time == current.time) {
                        cashier[i].empty = true;
                        break;
                    }
                }
                for (int i = 0; i < (a / 3); i++) {
                    if (barista[i].empty) {
                        barista[i].empty = false;
                        barista[i].activityTime += current.brewTime;
                        current.time += current.brewTime;
                        barista[i].time = current.time;
                        current.location = 5;
                        pq.push(current);
                        break;

                    } else if (i == (a / 3) - 1) {
                        baristaQueue.push(current);
                        break;
                    }
                }
            }

        }
            //if the customer finished with barista
        else if(current.location==5){
            if(!baristaQueue.empty()){
                Customer next=baristaQueue.top();
                baristaQueue.pop();
                for(int i=0;i<(a/3);i++){
                    if(current.time==barista[i].time){
                        next.time=barista[i].time+next.brewTime;
                        barista[i].time=next.time;
                        barista[i].activityTime+=next.brewTime;
                        next.location=5;
                        pq.push(next);
                        break;
                    }
                }
                //processedCustomer.push_back(current);
                processedCustomer[current.line-1]=current;
            }
            else if(baristaQueue.empty()) {
                for (int i = 0; i < (a / 3); i++) {
                    if (current.time == barista[i].time) {
                        barista[i].empty = true;
                        break;
                    }
                }
                processedCustomer[current.line-1]=current;
            }
        }

    }
    double time2=0;
    while(!pq2.empty()){
        Customer current=pq2.top(); //process each event for model 2 with respect to timeline
        pq2.pop();
        time2=current.time;
        //customer is now arriving
        if(current.location==1){
            for(int i=0;i<a;i++){
                if(cashier2[i].empty){
                    cashier2[i].empty=false;
                    cashier2[i].activityTime+=current.ordTime;
                    current.time+=current.ordTime;
                    cashier2[i].time=current.time;
                    current.location=3;
                    pq2.push(current);
                    break;

                }
                else if(i==a-1){
                    cashierQueue2.push(current);
                    break;
                }
            }
        }
            //customer gave his/her order and goes to barista
        else if(current.location==3){
            if(!cashierQueue2.empty()){
                int numberCashier;
                Customer next=cashierQueue2.top();
                cashierQueue2.pop();
                for(int i=0;i<a;i++){
                    if(cashier2[i].time==current.time){
                        numberCashier=i/3;
                        next.location=3;
                        next.time=cashier2[i].time+next.ordTime;
                        cashier2[i].time=next.time;
                        cashier2[i].activityTime+=next.ordTime;
                        pq2.push(next);
                        break;
                    }
                }
                if(barista2[numberCashier].empty){
                    barista2[numberCashier].empty=false;
                    barista2[numberCashier].activityTime+=current.brewTime;
                    current.time+=current.brewTime;
                    barista2[numberCashier].time=current.time;
                    current.location=5;
                    pq2.push(current);
                }
                else if(!barista2[numberCashier].empty){
                    baristaQueue2[numberCashier].push(current);
                }

            }
            else if(cashierQueue2.empty()){
                int numberCashier;
                for(int i=0;i<a;i++){
                    if(cashier2[i].time==current.time){
                        numberCashier=i/3;
                        cashier2[i].empty=true;
                        break;
                    }
                }
                if(barista2[numberCashier].empty){
                    barista2[numberCashier].empty=false;
                    barista2[numberCashier].activityTime+=current.brewTime;
                    current.time+=current.brewTime;
                    barista2[numberCashier].time=current.time;
                    current.location=5;
                    pq2.push(current);
                }
                else if(!barista2[numberCashier].empty){
                    baristaQueue2[numberCashier].push(current);
                }

            }
        }
            //customer took his drink
        else if(current.location==5){
            int whichBarista;
            for(int i=0;i<a/3;i++){
                if(barista2[i].time==current.time){
                    whichBarista=i;
                }
            }
            if(!baristaQueue2[whichBarista].empty()){
                Customer next=baristaQueue2[whichBarista].top();
                baristaQueue2[whichBarista].pop();
                next.time=barista2[whichBarista].time+next.brewTime;
                barista2[whichBarista].time=next.time;
                barista2[whichBarista].activityTime+=next.brewTime;
                next.location=5;
                pq2.push(next);
                //processedCustomer2.push_back(current);
                processedCustomer2[current.line-1]=current;

            }
            else if(baristaQueue2[whichBarista].empty()){
                barista2[whichBarista].empty=true;
                //processedCustomer2.push_back(current);
                processedCustomer2[current.line-1]=current;
            }
        }
    }

    ofstream myfile;
    //myfile.open ("outputttttt.txt");
    myfile.open (argv[2]);


    myfile << std::fixed;
    myfile << std::setprecision(2);

    myfile << time << endl;
    myfile << cashierQueue.max_length << endl;
    myfile << baristaQueue.max_length << endl;
    for(int i=0;i<cashier.size();i++){
        myfile << cashier[i].activityTime/time << endl;
    }
    for(int i=0;i<barista.size();i++){
        myfile << barista[i].activityTime/time << endl;
    }
    for(int i=0;i<b;i++){

        myfile << processedCustomer[i].time-processedCustomer[i].arr << endl;


    }

    myfile << endl;

    myfile << time2 << endl;
    myfile << cashierQueue2.max_length << endl;
    for(int i=0;i<a/3;i++){
        myfile << baristaQueue2[i].max_length << endl;
    }
    for(int i=0;i<cashier2.size();i++){
        myfile << cashier2[i].activityTime/time2 << endl;
    }
    for(int i=0;i<barista2.size();i++){
        myfile << barista2[i].activityTime/time2 << endl;
    }
    for(int i=0;i<b-1;i++){

        myfile << processedCustomer2[i].time-processedCustomer2[i].arr << endl;

    }
    myfile << processedCustomer2[b-1].time-processedCustomer2[b-1].arr;

    myfile.close();
    //cout << clock();


    return 0;
}
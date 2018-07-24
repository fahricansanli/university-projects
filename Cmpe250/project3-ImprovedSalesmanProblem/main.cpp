#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <queue>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iterator>
#include <map>
using namespace std;

struct State{
    int currentVertex;
    int timePassed;
    int coins[13];
    string path;
    map<vector<int>,int> visit;
    State(int currentVertex,int timePassed,string path){
        this->currentVertex=currentVertex;
        this->path=path;
        this->timePassed=timePassed;
        for(int i=0;i<13;i++){
            coins[i]=0;
        }
    }
};

struct Edge{
    int n1;
    int n2;
    int weight;
    int numberOfThief;
    vector<int> Thief;
    Edge(int n1,int n2,int weight,int thief){
        this->n1=n1;
        this->n2=n2;
        this->weight=weight;
        this->numberOfThief=thief;
    }
};
struct Vertex{
    bool visited;
    int coins[13];
    int withCoins[13]; /// EMİN DEĞİLİM YİNEEE
    Vertex(){
        this->visited=false;
        for(int i=0;i<13;i++){
            coins[i]=0;
        }
        for(int i=0;i<13;i++){
            withCoins[i]=0;
        }
    }
};
struct compare{
    bool operator()(State &s1, State &s2) {
        return s1.timePassed > s2.timePassed;
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
    int n; // number of cities
    int m; // number of roads
    int p; // number of different thief group
    int k; // number of jewelers
    ifstream infile(argv[1]);
    string line;
    getline(infile, line);
    vector<string> words;
    split1(line,words);
    n=stoi(words[0]);
    m=stoi(words[1]);
    p=stoi(words[2]);
    k=stoi(words[3]);
    vector<Edge> adjaceny[n];
    Vertex array[n];
    array[0].visited=true; // EMİN DEĞİLİM BURDANNNNNN !!!!!!!!!!!!!!!!!!!!!!!!!!!!
    for(int i=0;i<k;i++){
        getline(infile,line);
        vector<string> words1;
        split1(line,words1);
        int id;
        int amount;
        id=stoi(words1[0]);
        amount=stoi(words1[1]);
        for(int j=0;j<amount;j++){
            int x=stoi(words1[j+2]);
            array[id-1].coins[x-1]=1;
        }
    }
    for(int i=0;i<m;i++){
        int a,b,c,d;
        getline(infile,line);
        vector<string> words2;
        split1(line,words2);
        a=stoi(words2[0]);
        b=stoi(words2[1]);
        c=stoi(words2[2]);
        d=stoi(words2[3]);
        Edge add(a,b,c,d);
        Edge add2(b,a,c,d);
        for(int j=0;j<d;j++){
            int e=stoi(words2[j+4]);
            add.Thief.push_back(e);
            add2.Thief.push_back(e);
        }
        adjaceny[a-1].push_back(add);
        adjaceny[b-1].push_back(add2);
    }
    string shortestPath="-1";
    int shortestTime=0;
    priority_queue <State,vector<State>,compare> state;
    State statee(1,0,"1"); // sonradan eklemeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
    for(int g=0;g<13;g++){
        statee.coins[g]=array[0].coins[g];
    }
    state.push(statee);
    //state.push(State(1,0,"1")); // 1. vertex o saniye geçti yolum 1
    while(!state.empty()){
        State current=state.top();
        state.pop();
        if(current.currentVertex==n){
            shortestPath=current.path;
            shortestTime=current.timePassed;
            break;
        }
        int vertex=current.currentVertex-1; // şu anda olduğum şehir 1 eksiğiği çünkü 1.şehir mesela arrayde 0 da
        for(int i=0;i<adjaceny[vertex].size();i++){
            int next=adjaceny[vertex][i].n2; // gidilebilecek şehirlerin numarası
                bool canGo=true;
                for(int a=0;a<adjaceny[vertex][i].numberOfThief;a++){  /////////!!!!!!!!!!!!!!
                    if(current.coins[adjaceny[vertex][i].Thief[a]-1]==0){
                        canGo=false;
                    }
                }
            /*bool isSame=true;
            for(int a=0;a<13;a++){
                if(current.coins[a]==1&&array[next-1].withCoins[a]==0){
                    isSame=false;
                    array[next-1].withCoins[a]=1;
                }
            }*/
            vector<int> road={vertex,next-1};
                if(canGo){
                    bool notExist=true;
                    if(current.visit.count(road)==1){
                        notExist=false;
                    }
                    if(notExist) {
                        current.visit.insert(pair<vector<int>,int>(road,1));
                        State newest(next, current.timePassed + adjaceny[vertex][i].weight, current.path + " " + to_string(next));
                        for (int a = 0; a < 13; a++) {
                            if (current.coins[a] == 1) {
                                newest.coins[a] = 1;
                            }
                        }
                        bool newAdd=false;
                        for (int a = 0; a < 13; a++) {
                            if (array[next - 1].coins[a] == 1&&newest.coins[a]==0) {
                                newest.coins[a] = 1;
                                newAdd=true;
                            }
                        }
                        if(!newAdd)
                        newest.visit.insert(current.visit.begin(),current.visit.end());
                        else
                            newest.visit.clear();
                        state.push(newest);
                    }
                }


        }
    }
    ofstream myfile;
    myfile.open (argv[2]);
    if(shortestPath!="-1"){
        myfile << shortestPath << endl;
    }
    else if(shortestPath=="-1"){
        myfile << "-1" << endl;
    }
    myfile.close();

    return 0;

}
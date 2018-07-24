#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include "graph.h"
#include "variable.h"
#include "function.h"
#include <queue>
#include <iterator>
#include <cmath>
#include <sstream>

using namespace std;

// helper function that checks whether the given string is number or not.
bool isNumber(const string& s)
{
    char* end = 0;
    double val = strtod(s.c_str(), &end);
    return end != s.c_str() && val != HUGE_VAL;
}

int Graph::getVariable(string inp){
    int res;
    if( isNumber(inp) ){
        double val = stod(inp.c_str());
        idCount++;
        name[idCount] = inp;
        vars[idCount] = new Variable(idCount, inp, val);
        res = idCount;
        type[idCount] = VARIABLE;
        ids.push_back(idCount);
    }
    else{
        if(id.find(inp)==id.end()){
            idCount++;
            id[inp] = idCount;
            name[idCount] = inp;
            vars[idCount] = new Variable(idCount, inp);
            res = idCount;
            type[idCount] = VARIABLE;
        }
        else{
            res = id[inp];
        }
    }
    // printf("%s -> %d\n",inp.c_str(), res);
    return res;
}

int Graph::getFunction(string fnc){
    idCount++;
    name[idCount] = fnc;
    type[idCount] = FUNCTION;
    Function *f;
    // cout << "new Function: " << fnc << endl;
    if(fnc.compare("mult")==0)
        f = new Multiplication(idCount, fnc);
    else if(fnc.compare("add")==0)
        f = new Addition(idCount, fnc);
    else if(fnc.compare("subs")==0)
        f = new Subtraction(idCount, fnc);
    else if(fnc.compare("divide")==0)
        f = new Division(idCount, fnc);

    else if(fnc.compare("sin")==0)
        f = new Sine(idCount, fnc);
    else if(fnc.compare("cos")==0)
        f = new Cosine(idCount, fnc);
    else if(fnc.compare("identity")==0)
        f = new Identity(idCount, fnc);
    else if(fnc.compare("tan")==0)
        f = new Tangent(idCount, fnc);
    else if(fnc.compare("acos")==0)
        f = new ArcCosine(idCount, fnc);
    else if(fnc.compare("asin")==0)
        f = new ArcSine(idCount, fnc);
    else if(fnc.compare("atan")==0)
        f = new ArcTangent(idCount, fnc);
    else if(fnc.compare("exp")==0)
        f = new Exponential(idCount, fnc);
    else if(fnc.compare("log")==0)
        f = new Log(idCount, fnc);
    else if(fnc.compare("log10")==0)
        f = new Log10(idCount, fnc);
    else if(fnc.compare("pow")==0)
        f = new Power(idCount, fnc);
    else if(fnc.compare("sqrt")==0)
        f = new Sqrt(idCount, fnc);
    fncs[idCount] = f;
    return idCount;
}
template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}
void Graph::addAssignment(string lvalue, string rvalue) {
    vector<string> words;
    split1(rvalue,words);
    if(words[0].compare("add")==0){
        addBinaryFunction(words[0],words[1],words[2],lvalue);
    }
    else if(words[0].compare("mult")==0){
        addBinaryFunction(words[0],words[1],words[2],lvalue);
    }
    else if(words[0].compare("subs")==0){
        addBinaryFunction(words[0],words[1],words[2],lvalue);
    }
    else if(words[0].compare("divide")==0){
        addBinaryFunction(words[0],words[1],words[2],lvalue);
    }
    else if(words[0].compare("pow")==0){
        addBinaryFunction(words[0],words[1],words[2],lvalue);
    }
    else if(words.size()==1){
        addUnaryFunction("identity",words[0],lvalue);
    }
    else{
        addUnaryFunction(words[0],words[1],lvalue);
    }


}

void Graph::addUnaryFunction(string fnc, string inp, string out){

    int fId = getFunction(fnc);
    int inpId = getVariable(inp);
    int outId = getVariable(out);
    fncs[fId]->addInput(vars[inpId]);
    fncs[fId]->setOutput(vars[outId]);

    vars[inpId]->addTo(fncs[fId]);
    vars[outId]->setFrom(fncs[fId]);

}

void Graph::addBinaryFunction(string fnc, string inp1, string inp2, string out){

    int fId = getFunction(fnc);
    int inpId = getVariable(inp1);
    int inpId2 = getVariable(inp2);
    int outId = getVariable(out);
    fncs[fId]->addInput(vars[inpId]);
    fncs[fId]->addInput(vars[inpId2]);
    fncs[fId]->setOutput(vars[outId]);

    vars[inpId]->addTo(fncs[fId]);
    vars[inpId2]->addTo(fncs[fId]);
    vars[outId]->setFrom(fncs[fId]);

}


void Graph::readGraph(string fileName){
    ifstream infile(fileName);
    string line;
    getline(infile, line);
    vector<string> words;
    split1(line,words);
    while(words.size()!=0){
        if(words[0].compare("input")==0){
            int id=getVariable(words[1]);
            this->inputNodes.push_back(id);
            this->inputNames.push_back(vars[id]->name); // sonradannnnnnnnnnnnnnnnnnnnnnn
        }
        else if(words[0].compare("output")==0){
            int id=getVariable(words[1]);
            this->outputNode=id;
        }
        else{
            string right="";
            for(int i=2;i<words.size();i++){
                right=right+" "+words[i];
            }
            addAssignment(words[0],right);
        }
        getline(infile, line);
        words.clear();
        split1(line,words);
    }

}

void Graph::initTopologicalOrder(queue<Node *> &q, int *incSizes){
    for(int i=0;i<ids.size();i++){
        q.push(vars[ids[i]]);
    }
    for(int i=0;i<inputNodes.size();i++){
            q.push((Node*)vars[inputNodes[i]]);
    }
}

bool Graph::isCyclic(){
    queue<Node *> temp;
    initTopologicalOrder(temp,0);
    Node * current;
    while(!temp.empty()){
        current=temp.front();
        temp.pop();
        vector<Node*> out=current->getOutgoings();
        for(int i=0;i<out.size();i++){
            if(out[i]->numberOfIncoming==1){
                out[i]->numberOfIncoming--;
                temp.push(out[i]);
            }
            else{
                out[i]->numberOfIncoming--;
            }
        }
    }
    if(current->id==outputNode){
        return false;
    }
    else{
        return true;
    }
}

double Graph::forwardPass(vector<double> inputValues){
    queue<Variable *> temp;
    for(int i=0;i<ids.size();i++){
        temp.push(vars[ids[i]]);
    }
    for(int i=0;i<this->inputNodes.size();i++){
        this->vars[this->inputNodes[i]]->value=inputValues[i];
        temp.push(vars[inputNodes[i]]);
    }

    while(!temp.empty()){
        Variable * x=temp.front();
        temp.pop();
        for(int i=0;i<x->to.size();i++){
            x->to[i]->numberOfIncoming2--;
            x->to[i]->doForward();
            if(x->to[i]->numberOfIncoming2==0) {
                x->to[i]->output->numberOfIncoming2--;
                temp.push(x->to[i]->output);
                this->reversed.push(x->to[i]);
                //this->reverse.push_back(x->to[i]);
            }
        }
        if(temp.empty()){
            return x->value;

        }
    }

}

vector<double> Graph::backwardPass(){
    vars[outputNode]->derivative=1;
    /*vector<Function*> newest;
    for(int i=this->reverse.size()-1;i>=0;i--){
        newest.push_back(reverse[i]);
    }
    for(int i=0;i<newest.size();i++){
        newest[i]->doBackward();
    }
    vector<double> derivative;
    for(int i=0;i<this->inputNodes.size();i++){
        derivative.push_back(vars[inputNodes[i]]->derivative);
    }*/
    vector<double> derivative;
    while(!reversed.empty()){
        Function* temp=reversed.top();
        reversed.pop();
        temp->doBackward();
    }
    for(int i=0;i<this->inputNodes.size();i++){
        derivative.push_back(vars[inputNodes[i]]->derivative);
    }
    return derivative;
};
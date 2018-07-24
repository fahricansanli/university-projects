#include "variable.h"
#include <vector>
using namespace std;
Variable :: Variable(){
    this->value=0;
    this->derivative=0;
    this->from= nullptr;
    this->id=0;
    this->name="";
}
Variable::Variable(int _id, string _name, double _value) {
    this->id=_id;
    this->name=_name;
    this->value=_value;
}
void Variable::setFrom(Function *_from) {
    this->from=_from;
    this->numberOfIncoming++;
    this->numberOfIncoming2++;
}
void Variable::addTo(Function *_to) {
    this->to.push_back(_to);
}
vector<Node *> Variable::getOutgoings() {
    vector<Node*> temp;
    for(int i=0;i<to.size();i++){
        temp.push_back((Node*)(to[i]));
    }
    return temp;
}
vector<Node *> Variable::getIncomings() {
    vector<Node*> temp;
    temp.push_back((Node*)(from));
    return temp;
}
/*Variable::~Variable() {
    delete this->from;
    delete[] this->to;
}*/
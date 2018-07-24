#include "function.h"
#include <math.h>

Function::Function(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}
void Function::setOutput(Variable *_output) {
    this->output=_output;
}
void Function::addInput(Variable *input) {
    this->inputs.push_back(input);
    this->numberOfIncoming++;
    this->numberOfIncoming2++;
}
vector<Node *> Function::getOutgoings() {
    vector<Node*> temp;
    temp.push_back((Node*)(output));
    return temp;
}
vector<Node *> Function::getIncomings() {
    vector<Node*> temp;
    for(int i=0;i<this->inputs.size();i++){
        temp.push_back((Node*)(this->inputs[i]));
    }
    return temp;
}
/*Function::~Function() {
    delete this->inputs;
    delete this->output;
}*/

Function::Function() {

}

Addition::Addition(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}
void Addition::doForward() {
    this->output->value=this->inputs[0]->value+this->inputs[1]->value;
}
void Addition::doBackward() {
    this->inputs[0]->derivative+=this->output->derivative;
    this->inputs[1]->derivative+=this->output->derivative;
}
Sine::Sine(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}
void Sine::doForward() {
    this->output->value=sin(this->inputs[0]->value);
}
void Sine::doBackward() {
    this->inputs[0]->derivative+=(this->output->derivative)*(cos(this->inputs[0]->value));
}
Multiplication::Multiplication(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}
void Multiplication::doForward() {
    this->output->value=(this->inputs[0]->value)*(this->inputs[1]->value);
}
void Multiplication::doBackward() {
    this->inputs[0]->derivative+=(this->output->derivative)*(this->inputs[1]->value);
    this->inputs[1]->derivative+=(this->output->derivative)*(this->inputs[0]->value);
}
Subtraction::Subtraction(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}
void Subtraction::doForward() {
    this->output->value=(this->inputs[0]->value)-(this->inputs[1]->value);
}
void Subtraction::doBackward() {
    this->inputs[0]->derivative+=this->output->derivative;
    this->inputs[1]->derivative+=(-1)*this->output->derivative;
}
Division::Division(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}
void Division::doForward() {
    this->output->value=(this->inputs[0]->value)/(this->inputs[1]->value);

}
void Division::doBackward() {
    this->inputs[0]->derivative+=(this->output->derivative)*(1.0/this->inputs[1]->value);
    this->inputs[1]->derivative+=(this->output->derivative)*(-1.0*this->inputs[0]->value/pow(this->inputs[1]->value,2));
}
Cosine::Cosine(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}
void Cosine::doForward() {
    this->output->value=cos(this->inputs[0]->value);
}
void Cosine::doBackward() {
    this->inputs[0]->derivative+=(this->output->derivative)*((-1.0)*sin(this->inputs[0]->value));
}
Identity::Identity(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}
void Identity::doForward() {
    this->output->value=this->inputs[0]->value;
}
void Identity::doBackward() {
    this->inputs[0]->derivative+=(this->output->derivative);
}
Tangent::Tangent(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}
void Tangent::doForward() {
    this->output->value=tan(this->inputs[0]->value);
}
void Tangent::doBackward() {
    this->inputs[0]->derivative+=(this->output->derivative)*(1.0/(cos(inputs[0]->value)*cos(inputs[0]->value)));
}
ArcCosine::ArcCosine(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}
void ArcCosine::doForward() {
    this->output->value=acos(this->inputs[0]->value);
}
void ArcCosine::doBackward() {
    this->inputs[0]->derivative+=(this->output->derivative)*(-1.0/(sqrt(1-pow(this->inputs[0]->value,2))));
}
ArcSine::ArcSine(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}
void ArcSine::doForward() {
    this->output->value=asin(this->inputs[0]->value);
}
void ArcSine::doBackward() {
    this->inputs[0]->derivative+=(this->output->derivative)*(1.0/(sqrt(1-pow(this->inputs[0]->value,2))));
}
ArcTangent::ArcTangent(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}
void ArcTangent::doForward() {
    this->output->value=atan(this->inputs[0]->value);
}
void ArcTangent::doBackward() {
    inputs[0]->derivative += 1.0 / (1 + pow(inputs[0]->value,2)) * output->derivative;
}
Exponential::Exponential(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}
void Exponential::doForward() {
    this->output->value=exp(this->inputs[0]->value);
}
void Exponential::doBackward() {
    this->inputs[0]->derivative+=(this->output->derivative)*(exp(this->inputs[0]->value));
}
Log::Log(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}
void Log::doForward() {
    this->output->value=log(this->inputs[0]->value);
}
void Log::doBackward() {
    this->inputs[0]->derivative+=(this->output->derivative)*(1.0/(this->inputs[0]->value));
}
Log10::Log10(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}
void Log10::doForward() {
    this->output->value=log10(this->inputs[0]->value);
}
void Log10::doBackward() {
    this->inputs[0]->derivative+=(this->output->derivative)*(1.0/this->inputs[0]->value)*log10(exp(1));
}
Power::Power(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}
void Power::doForward() {
    this->output->value=pow(this->inputs[0]->value,this->inputs[1]->value);
}
void Power::doBackward() {
    this->inputs[0]->derivative+=(this->output->derivative)*((this->inputs[1]->value)*(pow(this->inputs[0]->value,this->inputs[1]->value-1)));
    this->inputs[1]->derivative+=(this->output->derivative)*pow(inputs[0]->value,inputs[1]->value)*(log(this->inputs[0]->value));
}
Sqrt::Sqrt(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}
void Sqrt::doForward() {
    this->output->value=sqrt(this->inputs[0]->value);
}
void Sqrt::doBackward() {
    this->inputs[0]->derivative+=(this->output->derivative)*(1.0/(2*sqrt(this->inputs[0]->value)));
}

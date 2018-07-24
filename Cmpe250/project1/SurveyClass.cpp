#include "SurveyClass.h"
#include <map>

SurveyClass::SurveyClass() {

    this->members=new LinkedList;
}
SurveyClass::SurveyClass(const SurveyClass &other) {

    this->members=new LinkedList;
    if(other.members==NULL)
        return;
    Node *temp=other.members->head; // to iterate list of other survey
    while(temp){
        this->members->pushTail(temp->data);
        temp=temp->next;
    }
}
SurveyClass& SurveyClass::operator=(const SurveyClass &list) {


    if(this->members){
        delete members;
    }
    this->members=new LinkedList;
    members->head=0;
    members->tail=0;
    members->length=0;
    if(list.members!=NULL){
        Node *temp=list.members->head; // to iterate list of other survey
        while(temp){
            this->members->pushTail(temp->data);
            temp=temp->next;

        }
    }
    return *this;

}
void SurveyClass::addMember(const Member &newMember) {

    this->members->pushTail(newMember);

}
float SurveyClass::calculateAverageAge() {
    int a=this->members->length;  // length of list
    double sum = 0;   // to hold sum of ages
    Node *temp=this->members->head;  // to iterate list
    for(int i=0;i<a;i++) {
        sum = sum + temp->data.age;
        if (temp->next) {
            temp = temp->next;
        }
    }
    float average=sum/a;
    float rounded=((int)(average*100+.5)/100.0);
    return rounded ;
}

string SurveyClass::findMostFavouriteColor() {

    int number=this->members->length;  // length of list
    Node *temp=this->members->head;   // to iterate list
    string favorite="";
    map<string,int> map;
    for(int i=0;i<number;i++){
        if(map.count(temp->data.color)==0){
            map.insert(pair<string,int>(temp->data.color,1));
        }
        else{
            int x=map.at(temp->data.color);
            //map.at(temp->data.color)++;
            map.erase(temp->data.color);
            map.insert(pair<string,int>(temp->data.color,(x+1)));

        }
        temp=temp->next;
    }
    Node *temp1=this->members->head; // to iterate list
    favorite=temp1->data.color;
    if(temp1->next!= nullptr)
    temp1=temp1->next;
    for(int i=0;i<number-1;i++){
        if(map.at(temp1->data.color)>map.at(favorite)){
            favorite=temp1->data.color;
        }
        //if(temp1->next!= nullptr)
        temp1=temp1->next;
    }
    return favorite;




}
SurveyClass::~SurveyClass() {
    if(this->members){
        delete members;
    }
}



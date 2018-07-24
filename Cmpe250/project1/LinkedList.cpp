#include "LinkedList.h"

LinkedList::LinkedList() {
    this->length=0;
}
LinkedList::LinkedList(const LinkedList &list) {
    if(list.head== nullptr){
        this->head= nullptr;
        this->tail= nullptr;
        this->length=0;
        return;
    }
    Node *temp=list.head; // to iterate list
    this->length=0;
    for(int i=0;i<list.length;i++){
        this->pushTail(temp->data);
        temp=temp->next;
    }
}
LinkedList::~LinkedList() {
    if(head){
        delete head;
    }
}
LinkedList& LinkedList::operator=(const LinkedList &list) {
    if(this->head){
        delete this->head;
    }
    this->head=0;
    this->tail=0;
    if(list.head!= nullptr) {
        head = new Node(list.head->data);
        tail = head;
        Node *temp = list.head->next; // to iterate list
        while (temp) {
            this->pushTail(temp->data);
            temp = temp->next;
        }
    }
    return *this;

}
void LinkedList::pushTail(Member data) {
    this->length++;
    if(!head){
        this->head=new Node(data);
        this->tail=head;

    }
    else {
        this->tail->next = new Node(data);
        this->tail = this->tail->next;
    }


}



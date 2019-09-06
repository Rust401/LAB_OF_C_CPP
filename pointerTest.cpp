#include<stdio.h>
#include<iostream>

struct Node
{
    int value;
    Node* next;
    Node(int value):value(value),next(nullptr){}
};

void changeNodeValue(Node* dude,int value){
    dude->value=value;
    dude->next=nullptr;
}

Node* buildLinkList(int length){
    Node* dummy=new Node(0);
    Node* cur=dummy;
    while(length--){
        cur->next=new Node(0);
        cur=cur->next;
    }
    return dummy->next;
}


void display(Node* dude){
    Node* cur=dude;
    while(dude!=nullptr){
        std::cout<<dude->value<<" ";
        dude=dude->next;
    }
    std::cout<<std::endl;
    return;
}


int main()
{
    Node* dude=buildLinkList(10);
    display(dude);
    changeNodeValue(dude,1);
    display(dude);
}
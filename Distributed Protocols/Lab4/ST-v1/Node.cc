/*
 * Node.cc
 *
 *  Created on: 3 dec. 2019
 *      Author: Fethi Ourghi
 */
#include "SimpleMessage_m.h"
#define Answer_NO 0
#define Answer_YES 1
#define Question 2
#define IDLE 0
#define ACTIVE 1
#define DONE 2
using namespace omnetpp;
void displaySet(std::set<int> input);
std::set<int> set_union(std::set<int> input1, std::set<int> input2);
std::set<int> set_intersection(std::set<int> input1, std::set<int> input2);
std::set<int> set_difference(std::set<int> input1, std::set<int> input2);
class Node : public cSimpleModule{
private:
    int state=IDLE;
    bool root=false;
    int sender,next,typeMsg,index,counter=0,parent=-1;
    std::set<int> neighbors,ST,Nx_minus_sender;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    int gateForNode(int k);
    int NeighbourInGate(int k);
    std::set<int> getNeighbours();
    bool isQuestion(int type);
    bool isYES(int type);
    bool isNO(int type);
    SimpleMessage* prepareMsg(int msgType,int Src,int Dst,char msgName[]);
};
Define_Module(Node);
void Node::initialize(){
    index=getIndex();
    neighbors=getNeighbours();
    if(index==0){
        root=true;
        for(int i=0;i<gateSize("gate$o");i++){
            SimpleMessage *Q=prepareMsg(Question, index, NeighbourInGate(i), "Question");
            send(Q,"gate$o",i);
        }
        state=ACTIVE;
    }
}
void Node::handleMessage(cMessage *msg){
    SimpleMessage *Q=check_and_cast<SimpleMessage *>(msg);
    sender=Q->getSource();
    typeMsg=Q->getType();
    switch(state){
    case IDLE:{
        root=false;
        parent=sender;
        ST.insert(sender);

        counter=1;
        if(counter==neighbors.size()){
            SimpleMessage *YES=prepareMsg(Answer_YES, index, sender, "YES");
            gate("gate$o",gateForNode(sender))->setDisplayString("ls=green,4");
            send(YES,"gate$o",gateForNode(sender));
            state=DONE;}
        else{
            Nx_minus_sender=neighbors;Nx_minus_sender.erase(sender);
            std::set<int>::iterator it=Nx_minus_sender.begin();
            for(;it!=Nx_minus_sender.end();it++){
                SimpleMessage *Q=prepareMsg(Question, index, *it, "Question");
                send(Q,"gate$o",gateForNode(*it));
            }
            state=ACTIVE;
        }
        break;}
    case ACTIVE:{
        if(isQuestion(typeMsg)){
            SimpleMessage *NO=prepareMsg(Answer_NO, index, sender, "NO");
            send(NO,"gate$o",gateForNode(sender));
        }
        else{
            counter++;
            if(isYES(typeMsg)){
                ST.insert(sender);
                gate("gate$o",gateForNode(sender))->setDisplayString("ls=green,4");
            }
            if(counter==neighbors.size()){
                if(!root){
                SimpleMessage *YES=prepareMsg(Answer_YES, index, parent, "YES");
                gate("gate$o",gateForNode(parent))->setDisplayString("ls=green,4");
                send(YES,"gate$o",gateForNode(parent));
                }
                else{EV<<"global termination"<<endl;}
                state=DONE;}
        }
        break;}
    case DONE:break;
    }
}

std::set<int> Node::getNeighbours(){
    int n=0;
    std::set<int> s;
    for(int k=0;k<gateSize("gate");k++){
        n=NeighbourInGate(k);
        s.insert(n);
    }
    return s;
}
int Node::NeighbourInGate(int k){
    return gate("gate$o",k)->getPathEndGate()->getOwnerModule()->getIndex();
}
int Node::gateForNode(int k){
    for(int i=0;i<gateSize("gate$o");i++){
        if(NeighbourInGate(gate("gate$o",i)->getIndex())==k)
            return i;
    }
    return -1;
}
bool Node::isQuestion(int type){return type==Question;}
bool Node::isYES(int type){return type==Answer_YES;}
bool Node::isNO(int type){return type==Answer_NO;}
SimpleMessage* Node::prepareMsg(int msgType,int Src,int Dst,char msgName[]){
    SimpleMessage *msg=new SimpleMessage(msgName);
    msg->setType(msgType);
    msg->setSource(Src);
    msg->setDestination(Dst);
    return msg;
}
std::set<int> set_union(std::set<int> input1, std::set<int> input2) {
    std::set<int> output=input1;
    std::set<int>::iterator it;
    for (it = input2.begin(); it != input2.end(); it++) output.insert(*it);
    return output;
}
std::set<int> set_intersection(std::set<int> input1, std::set<int> input2) {
    std::set<int> output;
    output=set_difference(input1, input2);
    output=set_difference(input1, output);
    return output;
}
std::set<int> set_difference(std::set<int> input1, std::set<int> input2) {
    std::set<int> output=input1;
    std::set<int>::iterator it;
    for (it = input2.begin(); it != input2.end(); it++) output.erase(*it);
    return output;
}
void displaySet(std::set<int> input){
    std::set<int>::iterator it;
    EV<<"set={";
    for(it=input.begin();it!=input.end();it++){
        EV<<*it<<", ";
    }
    EV<<"}"<<endl;
}


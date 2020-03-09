/*
 * Node.cc
 *
 *  Created on: 20 nov. 2019
 *      Author: Fethi Ourghi
 */
#include "SimpleMessage_m.h"
#define Token 0
#define Return 1
#define Backedge 2
#define Visited 3
#define IDLE 0
#define AVAILABLE 1
#define VISITED 2
#define DONE 3
using namespace omnetpp;
void displaySet(std::set<int> input);
class Node : public cSimpleModule{
private:
    int state=IDLE;
    bool initiator=false;
    int entry,sender,next,typeMsg,index;
    std::set<int> unvisited;
    SimpleMessage *MSG;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    int gateForNode(int k);
    int NeighbourInGate(int k);
    std::set<int> getNeighbours();
    void Visit();
    bool isToken(int k);
    bool isReturn(int k);
    bool isBackedge(int k);
    bool isVisited(int k);
    void First_Visit();
    SimpleMessage* prepareMsg(int msgType,int Src,int Dst,char msgName[]);
};
Define_Module(Node);
void Node::initialize(){
    index=getIndex();
    unvisited=getNeighbours();
    if(index==0){
        initiator=true;
        MSG=new SimpleMessage("DFT");
        for(int i=0;i<gateSize("gate$o");i++){
            if(i==gateForNode(*(unvisited.begin()))) continue;
            SimpleMessage *msg=prepareMsg(Visited, index, NeighbourInGate(i), "visited");
            send(msg,"gate$o",i);
        }
        Visit();
        state=VISITED;
    }
}
void Node::handleMessage(cMessage *msg){
    MSG=check_and_cast<SimpleMessage *>(msg);
    sender=MSG->getSource();
    //displaySet(unvisited);
    typeMsg=MSG->getType();
    switch(state){
    case IDLE:{
        if(isVisited(typeMsg)){
            unvisited.erase(sender);
            state=AVAILABLE;
        }
        if(isToken(typeMsg)){
            First_Visit();
        }
        break;
    }
    case VISITED:{
        if(isToken(typeMsg)){
            unvisited.erase(sender);
            if(*(unvisited.begin())==sender)
                Visit();
        }
        else if(isReturn(typeMsg)) Visit();
        else if(isBackedge(typeMsg)) Visit();
        else if(isVisited(typeMsg)){
            unvisited.erase(sender);
            if(*(unvisited.begin())==sender) Visit();
        }
        break;
    }
    case AVAILABLE:{
        if(isVisited(typeMsg)) unvisited.erase(sender);
        else if(isToken(typeMsg)) First_Visit();
        break;
    }
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
void Node::Visit(){
    if(!unvisited.empty()){
        next=*(unvisited.begin());  unvisited.erase(next);
        MSG=prepareMsg(Token, index, next, "Token");
        next=gateForNode(next);//the gate of next node in the unvisited list
        send(MSG,"gate$o",next);
    }
    else{
        if(!initiator){
            unvisited.erase(entry);
            MSG=prepareMsg(Return, index, entry, "Return");
            send(MSG,"gate$o",gateForNode(entry));
        }
        state=DONE;
    }
}
bool Node::isToken(int k){
    return(k==0);
}
bool Node::isReturn(int k){
    return(k==1);
}
bool Node::isBackedge(int k){
    return(k==2);
}
bool Node::isVisited(int k){
    return(k==3);
}
void Node::First_Visit(){
    initiator=false;
    entry=sender;
    unvisited.erase(sender);
    if(!unvisited.empty()){
        next=*(unvisited.begin());  unvisited.erase(next);
        MSG=prepareMsg(Token, index, next, "Token");
        next=gateForNode(next);//the gate of next node in the unvisited list
        send(MSG,"gate$o",next);
        for(int i=0;i<gateSize("gate$o");i++){
            if(i==gateForNode(entry) || i==next) continue;
            SimpleMessage *msg=prepareMsg(Visited, index, NeighbourInGate(i), "visited");
            send(msg,"gate$o",i);
        }
        state=VISITED;
    }
    else{
        MSG=prepareMsg(Return, index, entry, "Return");
        send(MSG,"gate$o",gateForNode(entry));
        for(int i=0;i<gateSize("gate$o");i++){
            if(i==gateForNode(entry)) continue;
            SimpleMessage *msg=prepareMsg(Visited, index, NeighbourInGate(i), "visited");
            send(msg,"gate$o",i);
        }
        state=DONE;
    }
}

SimpleMessage* Node::prepareMsg(int msgType,int Src,int Dst,char msgName[]){
    SimpleMessage *msg=new SimpleMessage(msgName);
    msg->setType(msgType);
    msg->setSource(Src);
    msg->setDestination(Dst);
    return msg;
}

void displaySet(std::set<int> input){
    std::set<int>::iterator it;
    EV<<"set={";
    for(it=input.begin();it!=input.end();it++){
        EV<<*it<<", ";
    }
    EV<<"}"<<endl;
}


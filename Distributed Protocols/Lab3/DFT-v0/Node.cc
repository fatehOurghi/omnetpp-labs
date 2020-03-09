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
#define IDLE 0
#define VISITED 1
#define DONE 2
using namespace omnetpp;
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
    SimpleMessage* prepareMsg(int msgType,int Src,int Dst,char* msgName);
};
Define_Module(Node);
void Node::initialize(){
    index=getIndex();
    unvisited=getNeighbours();
    if(index==0){
        initiator=true;
        MSG=new SimpleMessage();
        Visit();
    }
}
void Node::handleMessage(cMessage *msg){
    MSG=check_and_cast<SimpleMessage *>(msg);
    sender=MSG->getSource();
    unvisited.erase(sender);
    typeMsg=MSG->getType();
    switch(state){
    case IDLE:{
        entry=MSG->getArrivalGate()->getIndex();//save just the arrival gate index
        unvisited.erase(sender);
        Visit();
        break;
    }
    case VISITED:{
        if(isToken(typeMsg)){
            unvisited.erase(sender);
            MSG=prepareMsg(Backedge, index, sender, "Backedge");
            send(MSG,"gate$o",gateForNode(sender));
        }
        if(isReturn(typeMsg))Visit();
        if(isBackedge(typeMsg))Visit();
        break;
    }
    }
}

bool Node::isToken(int k){return(k==0);}
bool Node::isReturn(int k){return(k==1);}
bool Node::isBackedge(int k){return(k==2);}
SimpleMessage* Node::prepareMsg(int msgType,int Src,int Dst,char* msgName){
    SimpleMessage *msg=new SimpleMessage(msgName);
    msg->setType(msgType);
    msg->setSource(Src);
    msg->setDestination(Dst);
    return msg;
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
        state=VISITED;
    }
    else{
        if(!initiator){
            unvisited.erase(NeighbourInGate(entry));
            MSG=prepareMsg(Return, index, NeighbourInGate(entry), "Return");
            send(MSG,"gate$o",entry);
        }
        state=DONE;
    }
}




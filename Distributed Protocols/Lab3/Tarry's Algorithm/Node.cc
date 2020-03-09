/*
 * Node.cc
 *
 *  Created on: 20 nov. 2019
 *      Author: Fethi Ourghi
 */
#include "SimpleMessage_m.h"
#define Token 0
#define Return 1
#define IDLE 0
#define VISITED 1
#define DONE 2
using namespace omnetpp;
void displaySet(std::set<int>input);
class Node : public cSimpleModule{
private:
    int state=IDLE;
    bool initiator=false;
    int sender,next,index,parent=-1;
    std::set<int> neighbors;
    SimpleMessage *MSG;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    int gateForNode(int k);
    int NeighbourInGate(int k);
    std::set<int> getNeighbours();
    SimpleMessage* prepareMsg(int msgType,int Src,int Dst,char* msgName);
};
Define_Module(Node);
void Node::initialize(){
    index=getIndex();
    neighbors=getNeighbours();
    if(index==0){
        initiator=true;
        parent=index;
        MSG=new SimpleMessage();
        next=*(neighbors.begin());  neighbors.erase(next);
        MSG=prepareMsg(Token, index, next, "Token");
        send(MSG,"gate$o",gateForNode(next));
        state=VISITED;
    }
}
void Node::handleMessage(cMessage *msg){
    MSG=check_and_cast<SimpleMessage *>(msg);
    sender=MSG->getSource();
    switch(state){
    case IDLE:{
        parent=sender;
        neighbors.erase(sender);
        next=*(neighbors.begin());  neighbors.erase(next);
        MSG=prepareMsg(Token, index, next, "Token");
        send(MSG,"gate$o",gateForNode(next));
        state=VISITED;
        break;
    }
    case VISITED:{
        if(!neighbors.empty()){
            next=*(neighbors.begin());  neighbors.erase(next);
            MSG=prepareMsg(Token, index, next, "Token");
            send(MSG,"gate$o",gateForNode(next));
        }
        else{
            if(!initiator){
                MSG=prepareMsg(Return, index,parent, "Return");
                send(MSG,"gate$o",gateForNode(parent));
            }
            state=DONE;
        }
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
SimpleMessage* Node::prepareMsg(int msgType,int Src,int Dst,char* msgName){
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


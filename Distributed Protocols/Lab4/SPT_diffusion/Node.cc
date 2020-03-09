/*
 * Node.cc
 *
 *  Created on: 20 sept. 2019
 *      Author: Fethi Ourghi
 */
#include <omnetpp.h>
#include <time.h>
#include "SimpleMessage_m.h"
#define VISITED 0
#define DONE 1
#define WAIT 2
#define IDLE 3
#define QUESTION 0
#define YES 1
#define NO 2
using namespace omnetpp;
std::set<int> set_union(std::set<int> input1, std::set<int> input2);
std::set<int> set_intersection(std::set<int> input1, std::set<int> input2);
std::set<int> set_difference(std::set<int> input1, std::set<int> input2);
void displaySet(std::set<int> input){
    std::set<int>::iterator it;
    EV<<"set={";
    for(it=input.begin();it!=input.end();it++){
        EV<<*it<<", ";
    }
    EV<<"}"<<endl;
}
class Node : public cSimpleModule
{
private:

    std::set<int> N_x,Y,Z,YUZ,ST;
    int index,parent,sender,counter=0;
    bool root=false;
    int state=IDLE;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    int gateForNode(int k);
    int NeighbourInGate(int k);
    bool isVisited(){return state==VISITED;};
    bool isWait(){return state==WAIT;};
    bool isIdle(){return state==IDLE;};
    bool isQuestion(int type){return type==QUESTION;};
    bool isYes(int type){return type==YES;};
    bool isNo(int type){return type==NO;};
    std::set<int> getNeighbours();
    SimpleMessage* prepareMsg(int msgType,int Src,int Dst,char msgName[]);
};
Define_Module(Node);
void Node::initialize(){
    N_x=getNeighbours();
    index=getIndex();
    if(index==0){
        root=true;
        Y=N_x;
        N_x.insert(index);                      //N(x)+x
        for(int i=0;i<gateSize("gate$o");i++){
            SimpleMessage *msg=new SimpleMessage("Question");
            msg->setDestination(NeighbourInGate(i));
            msg->setSource(index);
            msg->setZ(N_x);
            msg->setType(QUESTION);
            send(msg,"gate$o",i);
        }
        state=WAIT;
    }
}
void Node::handleMessage(cMessage *msg){
    SimpleMessage *rmsg=check_and_cast<SimpleMessage *>(msg);
    int MsgType=rmsg->getType();
    sender=rmsg->getSource();
    switch(state){
    case IDLE:
    {
        parent=sender;
        Z=rmsg->getZ();
        Y=set_difference(N_x, Z);
        SimpleMessage *Yes=prepareMsg(YES, index, parent, "YES");
        send(Yes,"gate$o",gateForNode(parent));
        gate("gate$o",gateForNode(parent))->setDisplayString("ls=green,4");
        ST.insert(parent);
        if(!Y.empty()){
            state=WAIT;
            YUZ=set_union(Y, Z);
            std::set<int>::iterator it;
            for(it=Y.begin();it!=Y.end();it++){
                SimpleMessage *MSG=new SimpleMessage("Question");
                MSG->setDestination(*it);
                MSG->setSource(index);
                MSG->setZ(YUZ);
                send(MSG,"gate$o",gateForNode(*it));
            }
        }
        else{
            state=DONE;
        }
        break;}
    case WAIT:
    {
        if(isYes(MsgType)){
            counter++;
            gate("gate$o",gateForNode(sender))->setDisplayString("ls=green,4");
            ST.insert(sender);
        }
        if(isQuestion(MsgType)){
            SimpleMessage *Yes=prepareMsg(NO, index, sender, "NO");
            send(Yes,"gate$o",gateForNode(sender));
        }
        if(isNo(MsgType))counter++;
        if(counter==Y.size()){state=DONE;}
        break;}
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




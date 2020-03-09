/*
 * Node.cc
 *
 *  Created on: 20 sept. 2019
 *      Author: Fethi Ourghi
 */
#include <omnetpp.h>
#include <time.h>
#include "SimpleMessage_m.h"
using namespace omnetpp;
std::set<int> set_union(std::set<int> input1, std::set<int> input2);
std::set<int> set_intersection(std::set<int> input1, std::set<int> input2);
std::set<int> set_difference(std::set<int> input1, std::set<int> input2);
class Node : public cSimpleModule
{
private:
    bool done=false;
    std::set<int> N_x,Y,Z,YUZ;
    int index;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    int gateForNode(int k);
    int NeighbourInGate(int k);
    std::set<int> getNeighbours();
};
Define_Module(Node);
void Node::initialize(){
    N_x=getNeighbours();
    index=getIndex();
    if(index==0){
        N_x.insert(index);                      //N(x)+x
        for(int i=0;i<gateSize("gate$o");i++){
            SimpleMessage *msg=new SimpleMessage("Broadcasting");
            msg->setDestination(NeighbourInGate(i));
            msg->setSource(index);
            msg->setZ(N_x);
            send(msg,"gate$o",i);
        }
        done=true;
    }
}
void Node::handleMessage(cMessage *msg){
    if(!done){
        SimpleMessage *rmsg=check_and_cast<SimpleMessage *>(msg);
        done=true;
        Z=rmsg->getZ();
        Y=set_difference(N_x, Z);
        if(!Y.empty()){
            YUZ=set_union(Y, Z);
            std::set<int>::iterator it;
            for(it=Y.begin();it!=Y.end();it++){
                SimpleMessage *MSG=new SimpleMessage("Broadcasting");
                MSG->setDestination(*it);
                MSG->setSource(index);
                MSG->setZ(YUZ);
                send(MSG,"gate$o",gateForNode(*it));
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




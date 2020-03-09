/*
 * Node.cc
 *
 *  Created on: 20 nov. 2019
 *      Author: Fethi Ourghi
 */
#include "SimpleMessage_m.h"
using namespace omnetpp;
std::set<int> set_union(std::set<int> input1, std::set<int> input2);
std::set<int> set_intersection(std::set<int> input1, std::set<int> input2);
std::set<int> set_difference(std::set<int> input1, std::set<int> input2);
class Node : public cSimpleModule{
private:
    int bp=0;
    bool black=false;
    int index;
    std::set<int> bl,Z;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    int NeighbourInGate(int k);
};
Define_Module(Node);
void Node::initialize(){
    black=false;
    index=getIndex();
    WATCH(bp);
    bool noir=rand()%2;
    if(noir){// I choose random nodes to be black processes
        setDisplayString("i=,black");
        black=true;
        bl.insert(index);
        bp=bl.size();
        for(int k=0;k<gateSize("gate$o");k++){
            SimpleMessage *msg=new SimpleMessage("I am black process");
            msg->setDestination(NeighbourInGate(k));
            msg->setSource(index);
            msg->setZ(bl);
            send(msg,"gate$o",k);
        }
    }
}
void Node::handleMessage(cMessage *msg){
    SimpleMessage *rmsg=check_and_cast<SimpleMessage *>(msg);
    Z=rmsg->getZ();
    if(bl!=Z){
        bl=set_union(bl, Z);
        bp=bl.size();
        for(int k=0;k<gateSize("gate$o");k++){
            SimpleMessage *msg=new SimpleMessage("liste of bps");
            msg->setDestination(NeighbourInGate(k));
            msg->setSource(getIndex());
            msg->setZ(bl);
            send(msg,"gate$o",k);
        }
    }
}
int Node::NeighbourInGate(int k){
    return gate("gate$o",k)->getPathEndGate()->getOwnerModule()->getIndex();
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

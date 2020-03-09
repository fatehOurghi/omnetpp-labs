/*
 * Node.cc
 *
 *  Created on: 20 sept. 2019
 *      Author: Fethi Ourghi
 */
#include <string.h>
#include <omnetpp.h>
#include <time.h>
#include <set>
using namespace omnetpp;

std::set<int> list={0,1,5,7,9};
class Node : public cSimpleModule
{
private:
    bool awake=false;
    int index;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};
Define_Module(Node);
void Node::initialize()
{
    index=getIndex();
    if(list.find(index)!=list.end()){
        for(int k=0;k<gateSize("gate$o");k++)
        {
            cMessage *msg=new cMessage("Broadcasting");
            send(msg,"gate$o",k);
        }
        awake=true;
    }
}
void Node::handleMessage(cMessage *msg)
{
    int sender=msg->getArrivalGate()->getIndex();//getting the sender gate
    if(!awake)
    {
        for(int k=0;k<gateSize("gate$o");k++)
        {
            if(k!=sender)
            {
                cMessage *msg=new cMessage("Broadcasting");
                send(msg,"gate$o",k);
            }
        }
        awake=true;
    }
}


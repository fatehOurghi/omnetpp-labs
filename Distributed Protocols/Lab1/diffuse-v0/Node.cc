/*
 * Node.cc
 *
 *  Created on: 20 sept. 2019
 *      Author: Fethi Ourghi
 */
#include <string.h>
#include <omnetpp.h>
using namespace omnetpp;
class Node : public cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};
Define_Module(Node);
void Node::initialize()
{
    if (getIndex() == 0) {
        for(int i=0;i<gateSize("gate$o");i++)
        {
            cMessage *msg=new cMessage("Broadcasting");
            send(msg,"gate$o",i);
        }
    }
}
void Node::handleMessage(cMessage *msg)
{
    if (getIndex() != 0)
    {
        for (int i = 0; i < gateSize("gate$o"); i++) {
            cMessage *msg = new cMessage("Broadcasting");
            send(msg, "gate$o", i);
        }
    }
}



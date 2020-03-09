/*
 * Node.cc
 *
 *  Created on: 20 dec. 2019
 *      Author: Fethi Ourghi
 */
#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
using namespace omnetpp;
#include "SimpleMessage_m.h"
class Node : public cSimpleModule
{
private:
    simsignal_t arrivalSignal;

protected:
    virtual SimpleMessage *generateMessage();
    virtual void forwardMessage(SimpleMessage *msg);
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void finish();
    cLongHistogram hopCountStates;
    cOutVector hopCountVector;
};
Define_Module(Node);
void Node::initialize()
{
    hopCountStates.setName("hopCountStats");
    hopCountStates.setRangeAutoUpper(0, 10, 1.5);
    hopCountVector.setName("HopCount");
    arrivalSignal = registerSignal("arrival");
    // Module 0 sends the first message
    if (getIndex() == 0) {
        // Boot the process scheduling the initial message as a self-message.
        SimpleMessage *msg = generateMessage();
        scheduleAt(0.0, msg);
    }
}
void Node::handleMessage(cMessage *msg)
{
    SimpleMessage *ttmsg = check_and_cast<SimpleMessage *>(msg);
    if (ttmsg->getDestination() == getIndex()) {
        emit(arrivalSignal, ttmsg->getHopCount());
        // Message arrived.
        EV << "Message " << ttmsg << " arrived after " << ttmsg->getHopCount()<< " hops.\n";
        bubble("ARRIVED, starting new one!");
        hopCountVector.record(ttmsg->getHopCount());
        hopCountStates.collect(ttmsg->getHopCount());
        delete ttmsg;
        // Generate another one.
        EV << "Generating another message: ";
        SimpleMessage *newmsg = generateMessage();
        EV << newmsg << endl;
        forwardMessage(newmsg);
    }
    else {
        // We need to forward the message.
        forwardMessage(ttmsg);
        hopCountVector.record(ttmsg->getHopCount());
        hopCountStates.collect(ttmsg->getHopCount());
    }
}
SimpleMessage *Node::generateMessage()
{
    // Produce source and destination addresses.
    int src = getIndex(); // our module index
    int n = getVectorSize(); // module vector size
    int dest = intuniform(0, n-2);
    if (dest >= src)
        dest++;
    char msgname[20];
    sprintf(msgname, "from-%d-to-%d", src, dest);
    // Create message object and set source and destination field.
    SimpleMessage *msg = new SimpleMessage(msgname);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}
void Node::forwardMessage(SimpleMessage *msg)
{
    // Increment hop count.
    msg->setHopCount(msg->getHopCount()+1);
    // Same routing as before: random gate.
    int n = gateSize("gate");
    int k=intuniform(0, n-1);
    if(msg->getArrivalGate()!=NULL && n > 1)
    {

        while(msg->getArrivalGate()->getIndex()==k){
            k = intuniform(0, n-1);
        }
    }
    EV << "Forwarding message " << msg << " on gate[" << k << "]\n";
    send(msg, "gate$o", k);
}
void Node::finish()
{
    // This function is called by OMNeT++ at the end of the simulation.
    //EV << "Hop count, min:    " << hopCountStates.getMin() << endl;
    //EV << "Hop count, max:    " << hopCountStates.getMax() << endl;
    EV << "Hop count, mean:   " << hopCountStates.getMean() << endl;
    //EV << "Hop count, stddev: " << hopCountStates.getStddev() << endl;

    hopCountStates.recordAs("hop count");
}

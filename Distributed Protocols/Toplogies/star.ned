//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

// Created: 2019-10-29 for project diffuse-v1

import Node;

import Node;

import ned.DelayChannel;

//
// A generated network with star topology.
//
network Star
{
    submodules:
        node[21]:Node;
    connections:
        node[0].gate++ <--> DelayChannel <--> node[1].gate++;
        node[0].gate++ <--> DelayChannel <--> node[2].gate++;
        node[0].gate++ <--> DelayChannel <--> node[3].gate++;
        node[0].gate++ <--> DelayChannel <--> node[4].gate++;
        node[0].gate++ <--> DelayChannel <--> node[5].gate++;
        node[0].gate++ <--> DelayChannel <--> node[6].gate++;
        node[0].gate++ <--> DelayChannel <--> node[7].gate++;
        node[0].gate++ <--> DelayChannel <--> node[8].gate++;
        node[0].gate++ <--> DelayChannel <--> node[9].gate++;
        node[0].gate++ <--> DelayChannel <--> node[10].gate++;
        node[0].gate++ <--> DelayChannel <--> node[11].gate++;
        node[0].gate++ <--> DelayChannel <--> node[12].gate++;
        node[0].gate++ <--> DelayChannel <--> node[13].gate++;
        node[0].gate++ <--> DelayChannel <--> node[14].gate++;
        node[0].gate++ <--> DelayChannel <--> node[15].gate++;
        node[0].gate++ <--> DelayChannel <--> node[16].gate++;
        node[0].gate++ <--> DelayChannel <--> node[17].gate++;
        node[0].gate++ <--> DelayChannel <--> node[18].gate++;
        node[0].gate++ <--> DelayChannel <--> node[19].gate++;
        node[0].gate++ <--> DelayChannel <--> node[20].gate++;
}

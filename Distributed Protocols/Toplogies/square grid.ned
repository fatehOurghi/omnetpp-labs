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

// Created: 2019-10-1 for project lab0

import Node;

import ned.DelayChannel;

//
// A generated network with grid topology.
//
//number of msgs=59 for n=30 nodes------>  2*n-1
network Rnd2
{
    submodules:
        node[30]: Node ;

    connections:
        node[0].gate++ <--> DelayChannel <--> node[1].gate++;
        node[1].gate++ <--> DelayChannel <--> node[2].gate++;
        node[2].gate++ <--> DelayChannel <--> node[3].gate++;
        node[3].gate++ <--> DelayChannel <--> node[4].gate++;
        
        node[5].gate++ <--> DelayChannel <--> node[6].gate++;
        node[6].gate++ <--> DelayChannel <--> node[7].gate++;
        node[7].gate++ <--> DelayChannel <--> node[8].gate++;
        node[8].gate++ <--> DelayChannel <--> node[9].gate++;
        
        node[10].gate++ <--> DelayChannel <--> node[11].gate++;
        node[11].gate++ <--> DelayChannel <--> node[12].gate++;
        node[12].gate++ <--> DelayChannel <--> node[13].gate++;
        node[13].gate++ <--> DelayChannel <--> node[14].gate++;
        
        node[15].gate++ <--> DelayChannel <--> node[16].gate++;
        node[16].gate++ <--> DelayChannel <--> node[17].gate++;
        node[17].gate++ <--> DelayChannel <--> node[18].gate++;
        node[18].gate++ <--> DelayChannel <--> node[19].gate++;
        
        node[20].gate++ <--> DelayChannel <--> node[21].gate++;
        node[21].gate++ <--> DelayChannel <--> node[22].gate++;
        node[22].gate++ <--> DelayChannel <--> node[23].gate++;
        node[23].gate++ <--> DelayChannel <--> node[24].gate++;
        
        node[25].gate++ <--> DelayChannel <--> node[26].gate++;
        node[26].gate++ <--> DelayChannel <--> node[27].gate++;
        node[27].gate++ <--> DelayChannel <--> node[28].gate++;
        node[28].gate++ <--> DelayChannel <--> node[29].gate++;
        
        node[0].gate++ <--> DelayChannel <--> node[5].gate++;
        node[5].gate++ <--> DelayChannel <--> node[10].gate++;
        node[10].gate++ <--> DelayChannel <--> node[15].gate++;
        node[15].gate++ <--> DelayChannel <--> node[20].gate++;
        node[20].gate++ <--> DelayChannel <--> node[25].gate++;
        
        node[1].gate++ <--> DelayChannel <--> node[6].gate++;
        node[6].gate++ <--> DelayChannel <--> node[11].gate++;
        node[11].gate++ <--> DelayChannel <--> node[16].gate++;
        node[16].gate++ <--> DelayChannel <--> node[21].gate++;
        node[21].gate++ <--> DelayChannel <--> node[26].gate++;
        
        node[2].gate++ <--> DelayChannel <--> node[7].gate++;
        node[7].gate++ <--> DelayChannel <--> node[12].gate++;
        node[12].gate++ <--> DelayChannel <--> node[17].gate++;
        node[17].gate++ <--> DelayChannel <--> node[22].gate++;
        node[22].gate++ <--> DelayChannel <--> node[27].gate++;
        
        node[3].gate++ <--> DelayChannel <--> node[8].gate++;
        node[8].gate++ <--> DelayChannel <--> node[13].gate++;
        node[13].gate++ <--> DelayChannel <--> node[18].gate++;
        node[18].gate++ <--> DelayChannel <--> node[23].gate++;
        node[23].gate++ <--> DelayChannel <--> node[28].gate++;
        
        node[4].gate++ <--> DelayChannel <--> node[9].gate++;
        node[9].gate++ <--> DelayChannel <--> node[14].gate++;
        node[14].gate++ <--> DelayChannel <--> node[19].gate++;
        node[19].gate++ <--> DelayChannel <--> node[24].gate++;
        node[24].gate++ <--> DelayChannel <--> node[29].gate++;
       
        
        
}

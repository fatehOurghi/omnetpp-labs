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

import Node;

network rnd {
    submodules:
        node[13] : Node;
    connections:
        node[0].gate++ <-->  {delay=100ms;} <--> node[1].gate++;
        node[0].gate++ <-->  {delay=100ms;} <--> node[3].gate++;
        node[1].gate++ <-->  {delay=100ms;} <--> node[2].gate++;
        node[1].gate++ <-->  {delay=100ms;} <--> node[4].gate++;
        node[2].gate++ <-->  {delay=100ms;} <--> node[5].gate++;
        node[2].gate++ <-->  {delay=100ms;} <--> node[6].gate++;
        node[3].gate++ <-->  {delay=100ms;} <--> node[4].gate++;
        node[3].gate++ <-->  {delay=100ms;} <--> node[9].gate++;
        node[4].gate++ <-->  {delay=100ms;} <--> node[5].gate++;
        node[4].gate++ <-->  {delay=100ms;} <--> node[8].gate++;
        node[5].gate++ <-->  {delay=100ms;} <--> node[6].gate++;
        node[5].gate++ <-->  {delay=100ms;} <--> node[7].gate++;
        node[6].gate++ <-->  {delay=100ms;} <--> node[7].gate++;
        node[6].gate++ <-->  {delay=100ms;} <--> node[12].gate++;
        node[7].gate++ <-->  {delay=100ms;} <--> node[11].gate++;
        node[7].gate++ <-->  {delay=100ms;} <--> node[12].gate++;
        node[7].gate++ <-->  {delay=100ms;} <--> node[8].gate++;
        node[8].gate++ <-->  {delay=100ms;} <--> node[11].gate++;
        node[8].gate++ <-->  {delay=100ms;} <--> node[10].gate++;
        node[8].gate++ <-->  {delay=100ms;} <--> node[9].gate++;
        node[9].gate++ <-->  {delay=100ms;} <--> node[10].gate++;
        node[10].gate++ <-->  {delay=100ms;} <--> node[11].gate++;
        node[11].gate++ <-->  {delay=100ms;} <--> node[12].gate++;
        
}

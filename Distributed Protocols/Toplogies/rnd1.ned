import Node;

network rnd1 {
    submodules:
        node[16] : Node;
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
        
        node[13].gate++ <-->  {delay=100ms;} <--> node[14].gate++;
        node[14].gate++ <-->  {delay=100ms;} <--> node[1].gate++;
        node[15].gate++ <-->  {delay=100ms;} <--> node[11].gate++;
        node[13].gate++ <-->  {delay=100ms;} <--> node[5].gate++;
}

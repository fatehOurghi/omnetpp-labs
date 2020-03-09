simple Node
{
    gates:
        inout gate[];
}
network Network
{
    submodules:
        node[10]: Node;
    connections:
       node[0].gate++ <--> {  delay = 1ms; } <-->  node[1].gate++;
       node[0].gate++ <--> {  delay = 1ms; } <-->  node[2].gate++;
       node[0].gate++ <--> {  delay = 1ms; }  <--> node[3].gate++;
       node[1].gate++ <--> {  delay = 1ms; }  <--> node[2].gate++;
       
       node[2].gate++ <--> {  delay = 1ms; }  <--> node[4].gate++;
       node[3].gate++ <--> {  delay = 1ms; }  <--> node[4].gate++;
     
        
       
}

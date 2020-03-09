cplusplus{{
        #include <set>
        typedef std::set<int> Set;
}};
class noncobject Set;

message SimpleMessage
{
        int source;
        int destination;
        int hopCount = 0;
        int type;
        Set Z;
}

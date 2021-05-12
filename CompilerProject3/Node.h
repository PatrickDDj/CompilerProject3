//
//  Node.h
//  CompilerProject3
//
//  Created by PatrickDD on 2021/5/10.
//

#ifndef Node_h
#define Node_h

class Node{
public:
    string Component;
    vector<Node> sons;
    
    int id;
    
    static int cur_id;
    static const int format_length = 2;
    
    Node(string Component){
        this->Component = Component;
        id = ++cur_id;
    }
    
    void add_son(Node son){
        sons.push_back(son);
    }
    
    bool is_terminal() const {
        return sons.size() == 0;
    }
    
    string format_Component() const {
        string f_Component = Component;
        while(f_Component.length() < 4*format_length){
            f_Component += is_terminal()?" ":"-";
        }
        return f_Component;
    }
    
    
};

int Node::cur_id = 0;

#endif /* Node_h */

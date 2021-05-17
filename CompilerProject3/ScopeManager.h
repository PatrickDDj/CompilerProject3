//
//  ScopeManager.h
//  CompilerProject3
//
//  Created by PatrickDD on 2021/5/17.
//

#ifndef ScopeManager_h
#define ScopeManager_h


class ScopeManager{
private:
    vector<int> usable_scopes;
    
    int HEADER_scope;
    int cur_scope;

public:
    ScopeManager(){}
    
    void set_cur_scope(int scope){
        cur_scope = scope;
    }
    
    void set_HEADER_scope(int HEADER_scope){
        this->HEADER_scope = HEADER_scope;
    }
    
    const vector<int>& get_cur_usable_scopes(){
        return usable_scopes;
    }
    
    int get_cur_scope(){
        return cur_scope;
    }
    
    int get_HEADER_scope(){
        return HEADER_scope;
    }
    
    void jump_into_Block(int Block_id){
        set_cur_scope(Block_id);
        usable_scopes.push_back(Block_id);
    }
    
    void jump_out_Block(){
        usable_scopes.pop_back();
        set_cur_scope(get_cur_usable_scopes().back());
    }
};

#endif /* ScopeManager_h */

#include<iostream>
#include<map>
#include<stack>
//function  to reverse a string
std::string reverse(std::string str){
    for(int i=0;i<str.length()/2;i++){
        char temp = str[i] ;
        str[i] = str[str.length() - i - 1];
        str[str.length() - i - 1] =  temp;
    }
    return str;
}

//function to convert infix to postfix 
std::string infixToPostfix(std::stack<char> s, std::string infix){
    std::map < char, int> precedence = {
        {'+',1},
        {'-',1},
        {'*',2},
        {'/',2},
        {'^',3},
        {'(',0},
        {')',0}
    };
    std::string  postfix =  "";
    for(int i=0;i<infix.length();i++){
        if((infix[i]>= 'a' && infix[i] <='z') || (infix[i] >='A' && infix[i] <='Z')){
            postfix +=  infix[i];
        }
        else if(infix[i] == '('){
            s.push(infix[i]);
        }
        else if(infix[i] == ')'){
            while(!s.empty() && s.top()!='('){
                postfix += s.top();
                s.pop();
            }
            if(!s.empty() && s.top() == '('){
                s.pop();
            }
        }
        else{
            if(s.empty()){
                s.push(infix[i]);
            }
            else if(precedence[infix[i]] > precedence[s.top()]){
                s.push(infix[i]);
            }
            else if(precedence[infix[i]] ==  precedence[s.top()] && infix[i] == '^'){
                s.push(infix[i]);
            }
            else{
                while(precedence[infix[i]] <= precedence[s.top()] && !s.empty()){
                    postfix += s.top();
                    s.pop();
                }
                s.push(infix[i]);
            }
        }
    }
    while(!s.empty()){
        postfix += s.top();
        s.pop();
    }
    return postfix;
}

//function to convert infix to prefix 
std::string infixToPrefix(std::stack <char> s,std::string infix){
    std::map <char, int> precedence = {
        {'+',1},
        {'-',1},
        {'*',2},
        {'/',2},
        {'^',3},
        {'(',0},
        {')',0}
    };
    infix =  reverse(infix);
    for(int i=0;i<infix.length();i++){
        if(infix[i] == '('){
            infix[i] = ')';
        }
        else if(infix[i] == ')'){
            infix[i] = '(';
        }
    }
    std::string prefix = "";
    for(int i=0;i<infix.length();i++){
        if((infix[i] >= 'a' && infix[i] <= 'z') || (infix[i] >= 'A' && infix[i] <= 'Z')){
            prefix += infix[i];
        }
        else if(infix[i] == '('){
            s.push(infix[i]);
        }
        else if(infix[i] == ')'){
            while(!s.empty() && s.top() != '('){
                prefix += s.top();
                s.pop();
            }
            if(!s.empty() && s.top() == '('){
                s.pop();
            }
        }
        else{
            if(s.empty()){
                s.push(infix[i]);
            }
            else if(precedence[infix[i]] > precedence[s.top()]){
                s.push(infix[i]);
            }
            else if(precedence[infix[i]] ==  precedence[s.top()] && infix[i] == '^'){
                while(precedence[infix[i]] == precedence[s.top()] && infix[i] == '^'){
                    prefix += s.top();
                    s.pop();
                }
                s.push(infix[i]);
            }
            else if(precedence[infix[i]] == precedence[s.top()]){
                s.push(infix[i]);
            }
            else{
                while(!s.empty() && precedence[infix[i]] < precedence[s.top()]){
                    prefix += s.top();
                    s.pop();
                }
                s.push(infix[i]);
            }
        }
    }
    while(!s.empty()){
        prefix += s.top();
        s.pop();
    }
    prefix = reverse( prefix);
    return prefix;
}

//function to convert postfix to infix
std::string postfixToInfix(std::stack<std::string> s, std::string postfix){
    for(int i=0;i<postfix.length() ;i++){
        if((postfix[i] >='a' && postfix[i] <= 'z') || (postfix[i] >='A' && postfix[i] <='Z')){
            std::string temp = std::string("") + postfix[i];
            s.push(temp);
        }
        else{
            if(s.size() >= 2){
                std::string op1 = s.top();
                s.pop();
                std::string op2 =  s.top();
                s.pop();
                std::string temp = "("+ op1 + postfix[i] + op2 +")";
                s.push(temp);
            }
        }
    }
    s.top() = reverse(s.top());
    for(int i=0;i<s.top().length();i++){
        if(s.top()[i] == '('){
            s.top()[i] = ')';
        }
        else if(s.top()[i] == ')'){
            s.top()[i] = '(';
        }
    }
    return s.top();
}


//function to convert prefix to infix
std::string prefixToInfix(std::stack <std::string> s, std::string prefix){
    prefix = reverse(prefix);
    for(int i=0;i<prefix.length() ;i++){
        if((prefix[i] >= 'a' && prefix[i] <='z') || (prefix[i] >='A' &&  prefix[i] <= 'Z')){
            std::string temp = std::string("") + prefix[i];
            s.push(temp);
        }
        else{
            if(s.size() >= 2){
                std::string op1 =  s.top();
                s.pop();
                std::string op2 = s.top();
                s.pop();
                std::string temp = "(" + op1 + prefix[i] + op2 + ")";
                s.push(temp);
            }
        }
    }
    
    return s.top();
}

//function to convert postfix to prefix
std::string postfixToPrefix(std::stack <std::string> s, std::string postfix){
    for(int i=0;i<postfix.length();i++){
        if((postfix[i]>='a' && postfix[i]<='z') || (postfix[i]>='A' && postfix[i] <='Z')){
            std::string temp = std::string("") + postfix[i];
            s.push(temp);
        }
        else{
            if(s.size()>=2){
                std::string op2 = s.top();
                s.pop();
                std::string op1 = s.top();
                s.pop();
                std::string temp = postfix[i] + op1 + op2 ;
                s.push(temp);
            }
        }
    }
    return s.top();
}
//function to convert prefix to postfix
std::string prefixToPostfix(std::stack <std::string> s, std::string prefix){
    prefix = reverse(prefix);
    for(int i=0;i<prefix.length() ;i++){
        if((prefix[i] >='a' && prefix[i] <='z') || (prefix[i]<='A' && prefix[i] >= 'Z')){
            std::string temp = std::string("") + prefix[i];
            s.push(temp);
        }
        else{
            if(s.size() >= 2){
                std::string op1 = s.top();
                s.pop();
                std::string op2 = s.top();
                s.pop();
                std::string temp =op1 + op2 + prefix[i];
                s.push(temp);
            }
        }
    }
    return s.top();
}


int main(){
    std::stack <char> s;
    std::stack <std::string> s2;
    //infix expression
    std::string infix = "((a+b-c)*d^e^f)/g";
    
    //postfix expression 
    std::string postfix = "ab+c-def^^*g/";
    
    //prefix expression 
    std::string prefix = "/*-+abc^d^efg";
    
    //variable to contain the results in 
    std::string result;
    
    //convert infix to postfix 
    result = infixToPostfix(s,infix);
    std::cout<< "Infix: "<<infix<<std::endl;
    std::cout<<"Infix to Postfix: "<<result <<std::endl;
    
    //convert infix to prefix 
    result  = infixToPrefix(s,infix);
    std::cout<< "Infix: "<<infix <<std::endl;
    std::cout<< "Infix to Prefix: "<<result<<std::endl;
    
    //convert postfix to infix
    result =  postfixToInfix(s2,postfix);
    std::cout<< "Postfix: "<<postfix<<std::endl;
    std::cout<< "Postfix to Infix: "<<result <<std::endl;
    
    //convert postfix to prefix
    result = postfixToPrefix(s2,postfix);
    std::cout<< "Postfix: "<<postfix<<std::endl;
    std::cout<< "Postfix to Prefix: "<<result <<std::endl;
    
    //convert prefix to infix
    result = prefixToInfix(s2,prefix);
    std::cout<< "Prefix: "<<prefix<<std::endl;
    std::cout<< "Prefix to Infix: "<<result<<std::endl;
    
    //convert prefix to postfix
    result = prefixToPostfix(s2,prefix);
    std::cout<< "Prefix: "<<prefix <<std::endl;
    std::cout<< "Prefix to Postfix: "<<result <<std::endl;
    return 0;
}


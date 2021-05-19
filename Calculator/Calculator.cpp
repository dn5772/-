#include "List.h"
#include "String.h"
#include "Stack.h"
#include <iostream>

using namespace std;

class Calculator 
{
    private : 

    List<String> tokens;
    int errCode;
    int value;
    String postfix;

    int makePostFix();
    int evaluation();

    public : 
    
    Calculator();
    ~Calculator();
    int getErrorCode();
    int setExpression(const char* expr);
    String getPostFix();
    int getValue();

};

Calculator::Calculator(){
    
}

int Calculator::makePostFix(){

}

int Calculator::evaluation(){

}

int Calculator::getErrorCode(){

}

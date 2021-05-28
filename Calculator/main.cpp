#include "Calculator.cpp"
#include <iostream>

using namespace std;

int main(void){

    char expr[1000];

    Calculator c;

    cout << "수식을 입력하세요" << endl;
    cin.getline(expr, 10);

    String posfix;
    c.setExpression(expr);
    
    posfix = c.getPostFix();
    

    cout << "중위표기식 : " << expr << " 후위표기식 :" << posfix << "." << endl;
/*
    if (!c.setExpression(expr)){
        String posfix = c.getPostFix();
        
        try {
            cout << "후위표기식 : " << posfix << "결과값 : " << c.getValue() << endl;
        }
        catch (const char* errmsg){
            cout << errmsg << endl;
        }
    }
    */

    return 0;
}

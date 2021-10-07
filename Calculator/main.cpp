#include "Calculator.cpp"
#include <iostream>

using namespace std;

int main(void){


    char expr[1000];

    Calculator c;

    cout << "수식을 입력하세요" << endl;
    cin.getline(expr, 1000);

    String posfix;
    c.setExpression(expr);
    
    posfix = c.getPostFix();


    if (!c.setExpression(expr)){
        String posfix = c.getPostFix();
        
        try {
            cout << "중위표기식 : " << expr << "\n후위표기식 :" << posfix << "\n결과값 : " << c.getValue() << endl;
        }
        catch (const char* errmsg){
            cout << errmsg << endl;
        }
    }
    

    return 0;
}

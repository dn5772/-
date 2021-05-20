#include "Calculator.cpp"
#include <iostream>

using namespace std;

int main(void){

    char expr[1000];

    Calculator c;

    cout << "수식을 입력하세요" << endl;
    cin.getline(expr, 1000);

    if (!c.setExpression(expr)){
        String posfix = c.getPostFix();
        
        try {
            cout << "후위표기식 : " << posfix << "결과값 : " << c.getValue() << endl;
        }
        catch (const char* errmsg){
            cout << errmsg << endl;
        }
    }

    return 0;
}

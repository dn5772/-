#include "List.cpp"
#include "String.cpp"
#include "Stack.cpp"
#include <iostream>

using namespace std;

class Calculator 
{
    private : 

    List<String> tokens;
    List<String> op;
    int errCode;
    int value;
    String postfix;

    int makePostFix(); //후위 표기식 만들기
    int evaluation();  //

    public : 
    
    Calculator();
    ~Calculator();
    String makeToken(const char* expr, int num);
    int getErrorCode();
    int setExpression(const char* expr);
    String getPostFix();
    int getValue();

};

Calculator::Calculator(){

    String nu((char*)"\0", 1);
    String sp((char*)" ", 1);
    String pl((char *)"+", 1), mi((char *)"-", 1), mu((char *)"*", 1), di((char *)"/", 1), pal((char *)"(", 1), par((char *)")", 1);

    errCode = 0;
    value = 0;
    postfix = sp;

    op.addItem(nu);op.addItem(pl);op.addItem(mi);op.addItem(mu);op.addItem(di);op.addItem(pal);op.addItem(par);op.addItem(sp);

}

Calculator::~Calculator(){

}

String Calculator::makeToken(const char* expr, int num){
    char tmp[num+1];

    for (int i=0; i<num+1; i++){
        tmp[i] = expr[i];
    }
    
    String token(tmp, num+1);
    //token.print();
    return token;
}

int Calculator::setExpression(const char* expr){
    for (int i=0; i<1000; i++){

        char* tmp = (char*) expr;
        tmp += i;
        String token;
        

        if (expr[i]==' ')
        continue;

        if (expr[i]=='\0')
        break;

        if ('/' <= expr[i] && expr[i] <= ':'){
            int j;
            for (j=i; j<i+10; j++){
                if (j < 1000){
                    if (('/' >= expr[j] || expr[j] >= ':')){
                        break;
                    }
                }
            }
            j--;
            token = makeToken(tmp, j-i);
            i = j;
        }
        else {
        token = makeToken(tmp, 0);
        }

        tokens.addItem(token);
        
    }
    String nu;
    nu = op.getItem(0);
    tokens.addItem(nu);

    //tokens.print();
    //cout<<tokens.getItemCount()<<endl;

    makePostFix();
    
    return 0;
}

int Calculator::makePostFix(){
    Stack<String> stack;
    String nu((char*)"\0", 1);
    String sp;
    sp = op.getItem(7);
    stack.Push(nu);

    if (tokens.getItemCount()){
        

        while (tokens.getItemCount() > 0) {

            //cout << " 1. makePostFix " << endl;

            String c;
            c = tokens.removeAt(0);
                
            String s;
            s = stack.Top();
            int tokenCase = 8, stackCase = 0;

            for (int j=0; j<7; j++){
                if (c == op.getItem(j))
                    tokenCase = j;
                }

            for (int j=0; j<8; j++){
                if (s == op.getItem(j))
                    stackCase = j;
                }
            cout << " tokenCase = " << tokenCase << " stackCase = " << stackCase << endl;

                switch (tokenCase) {
                    case 1 :
                    if (stackCase == 1 || stackCase == 2){
                        postfix = postfix.Concat(s); //스텍에서 출력
                        stack.Pop();     //
                        stack.Push(c);   // 스택에 넣기
                        break;
                    }
                    else if (stackCase == 0 || stackCase == 5 || stackCase == 3 || stackCase == 4){
                        stack.Push(c);
                        break;
                    }

                    case 2 :
                    if (stackCase == 1 || stackCase == 2){
                        postfix = postfix.Concat(s);
                        stack.Pop();
                        stack.Push(c);   
                        break;
                    }
                    else if (stackCase == 0 || stackCase == 5 || stackCase == 3 || stackCase == 4){
                        stack.Push(c);
                        break;
                    }
                    
                    case 3 :
                    if ( stackCase == 3 || stackCase == 4){
                        stack.Pop();     //
                        stack.Push(c);   // 스택에 넣기
                        postfix = postfix.Concat(s); //스텍에서 출력

                        break;
                    }
                    else if (stackCase == 0 || stackCase == 5 || stackCase == 1 || stackCase == 2){
                        stack.Push(c);
                        break;
                    }

                    case 4 :
                    if (stackCase == 3 || stackCase == 4){
                        postfix = postfix.Concat(s); //스텍에서 출력
                        stack.Pop();     //
                        stack.Push(c);   // 스택에 넣기
                        break;
                    }
                    else if (stackCase == 1 || stackCase == 2 || stackCase == 0 || stackCase == 5){
                        stack.Push(c);
                        break;
                    }

                    case 5 :
                        stack.Push(c);
                        break;
                    
                    case 6 :
                    while (!(stack.Top() == op.getItem(5))){
                        postfix = postfix.Concat(stack.Top());
                        stack.Pop();
                    }
                    stack.Pop();
                    break;
                    
                    case 0 :
                    while (!stack.IsEmpty()){
                        postfix = postfix.Concat(stack.Top());
                        stack.Pop();
                    }
                    break;

                    default :
                        postfix = postfix.Concat(c);
                }
                postfix = postfix.Concat(sp);
                
                cout << " 2. postfix is = " << postfix << endl;
        }
    }

    return 0;
}

int Calculator::evaluation(){

return 0;
}

int Calculator::getErrorCode(){

return 0;
}

String Calculator::getPostFix(){ return postfix;}

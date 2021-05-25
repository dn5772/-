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
    tokens.addItem(nu);

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
    cout << tmp << num << " *" << endl;

    return token;
}

int Calculator::setExpression(const char* expr){
    for (int i=0; i<10; i++){

        char* tmp = (char*) expr;
        tmp += i;
        String token;

        if (*tmp=='\0' || *tmp==' ')
        continue;

        if ('0' <= expr[i] || expr[i] <= '9'){
            int j;
            for (j=i; j<11; j++){
                if (j < 10){
                    if (('0' >= expr[j] || expr[j] >= '9')){
                        break;
                    }
                }
            }
            j--;
            token = makeToken(tmp, j-i);
        }
        else {
        token = makeToken(tmp, 0);
        }

        tokens.addItem(token);
        
    }
    
    return 0;
}

int Calculator::makePostFix(){
    //cout << "1 " << endl;
    Stack<String> stack;
    String nu((char*)"\0", 1);
    stack.Push(nu);

    if (tokens.getItemCount()){
        int i = 0;
        

        while (1) {
            if(tokens.getItemCount() > i){
                String c, c_c;
                c = tokens.getItem(i);
                
                String s, s_c;
                s = stack.Top();
                int tokenCase = 0, stackCase = 0;

                for (int j=0; j<7; j++){
                    if (c == op.getItem(j))
                        tokenCase = j;
                }

                for (int j=0; j<7; j++){
                    if (s == op.getItem(j))
                        stackCase = j;
                }

                switch (tokenCase) {
                    case 1 :
                    if (stackCase == 1 || stackCase == 2){
                        postfix.Concat(stack.Top()); //스텍에서 출력
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
                        postfix.Concat(stack.Top()); 
                        stack.Pop();    
                        stack.Push(c);   
                        break;
                    }
                    else if (stackCase == 0 || stackCase == 5 || stackCase == 3 || stackCase == 4){
                        stack.Push(c);
                        break;
                    }
                    
                    case 3 :
                    if (stackCase == 1 || stackCase == 2 || stackCase == 3 || stackCase == 4){
                        postfix.Concat(stack.Top()); //스텍에서 출력
                        stack.Pop();     //
                        stack.Push(c);   // 스택에 넣기
                        break;
                    }
                    else if (stackCase == 0 || stackCase == 5){
                        stack.Push(c);
                        break;
                    }

                    case 4 :
                    if (stackCase == 1 || stackCase == 2 || stackCase == 3 || stackCase == 4){
                        postfix.Concat(stack.Top()); //스텍에서 출력
                        stack.Pop();     //
                        stack.Push(c);   // 스택에 넣기
                        break;
                    }
                    else if (stackCase == 0 || stackCase == 5){
                        stack.Push(c);
                        break;
                    }

                    case 5 :
                        stack.Push(c);
                        break;
                    
                    case 6 :
                    while (!stack.IsEmpty() && !(stack.Top() == op.getItem(5)))
                        postfix.Concat(stack.Top());
                    
                    case 0 :
                    while (!stack.IsEmpty())
                        postfix.Concat(stack.Top());

                    default :
                        postfix.Concat(c);
                }
                
                i++;
                continue;
            }

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

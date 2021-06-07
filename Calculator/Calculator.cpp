#include "List.cpp"
#include "String.cpp"
#include "Stack.cpp"
#include <iostream>

using namespace std;

class Calculator 
{
    private : 

    List<String> tokens;
    List<String> postfixToken;
    List<String> op;
    int errCode;
    int value;
    String postfix;
    Stack<String> tokenStack;

    int makePostFix(); //후위 표기식 만들기
    int evaluation();  //

    public : 
    
    Calculator();
    ~Calculator();
    String makeToken(const char* expr, int num);
    void conToken(String); 
    int getErrorCode();
    int setExpression(const char* expr);
    int stoint(String);
    int getValue();
    String getPostFix();
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

        if (('/' <= expr[i]) && (expr[i] <= ':')){
            int j;
            for (j=i; j<i+10; j++){
                if (j < 1000){
                    if (('/' > expr[j]) || (expr[j] > ':')){
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

inline void Calculator::conToken(String s){
    String sp;
    sp = op.getItem(7);
    postfix = postfix.Concat(s);
    postfix = postfix.Concat(sp);
    postfixToken.addItem(s);
}

int Calculator::makePostFix(){
    Stack<String> stack;
    String nu((char*)"\0", 1);
    String sp;
    sp = op.getItem(7);
    stack.Push(nu);
    int error = 0;

    if (tokens.getItemCount()){
        while (tokens.getItemCount() > 0) {
            
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
            // cout << " tokenCase = " << tokenCase << " stackCase = " << stackCase << endl;


                switch (tokenCase) {
                    case 1 :
                    if (stackCase == 1 || stackCase == 2){
                        conToken(s);
                        stack.Pop();     
                        stack.Push(c);   
                        break;
                    }
                    else if (stackCase == 0 || stackCase == 5 || stackCase == 3 || stackCase == 4){
                        stack.Push(c);
                        break;
                    }

                    case 2 :
                    if (stackCase == 1 || stackCase == 2){
                        conToken(s);
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
                        stack.Pop();     // 빼고
                        stack.Push(c);   // 스택에 넣기
                        conToken(s); //문자열에 출에

                        break;
                    }
                    else if (stackCase == 0 || stackCase == 5 || stackCase == 1 || stackCase == 2){
                        stack.Push(c);
                        break;
                    }

                    case 4 :
                    if (stackCase == 3 || stackCase == 4){
                        conToken(s); //스텍에서 출력
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
                        conToken(stack.Top());
                        stack.Pop();
                    }
                    stack.Pop();
                    break;
                    
                    case 0 :
                    while (!stack.IsEmpty()){
                        conToken(stack.Top());
                        stack.Pop();
                    }
                    break;

                    default :
                        conToken(c);
                }
                //postfix = postfix.Concat(sp);
                // cout << " 2. postfix is = " << postfix << endl;
        }
    }
    //postfixToken.removeAt(postfixToken.getItemCount()-1);
    evaluation();
    // postfixToken.print();
    // cout << "item count is : " << postfixToken.getItemCount() << endl;
    return error;
}

int Calculator::evaluation(){
    int tokenCount = postfixToken.getItemCount();
    Stack<int> stack;

    int num1 = 0, num2 = 0, val = 0;

    for (int i=0; i<tokenCount; i++){
        // cout << " 3. evaluation is = " << endl;

        String t;
        t = postfixToken.removeAt(0);

        int tokenCase = 8;

        for (int j=0; j<6; j++){
            if (t == op.getItem(j))
                tokenCase = j;
        }

        switch (tokenCase){

            case 0 :
            val = stack.Top();
            break;

            case 1 :
            num1 = stack.Top(); stack.Pop();
            num2 = stack.Top(); stack.Pop();
            val = num2 + num1;
            stack.Push(val);
            break;

            case 2 :
            num1 = stack.Top(); stack.Pop();
            num2 = stack.Top(); stack.Pop();
            val = num2 - num1;
            stack.Push(val);
            break;

            case 3 :
            num1 = stack.Top(); stack.Pop();
            num2 = stack.Top(); stack.Pop();
            val = num2 * num1;
            stack.Push(val);
            break;

            case 4 :
            num1 = stack.Top(); stack.Pop();
            num2 = stack.Top(); stack.Pop();
            val = num2 / num1;
            stack.Push(val);
            break;

            case 8 :
            val = t.stoint();
            stack.Push(val);
            break;
        }
    }

    // cout << " 6. val is = " << val << endl;
    value = val;

return 0;
}


// int Calculator::stoint(String s){
//     s.buffer

// }

int Calculator::getErrorCode(){return errCode;}
String Calculator::getPostFix(){ return postfix;}
int Calculator::getValue(){return value;}

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
    int getErrorCode();
    int setExpression(const char* expr);
    String getPostFix();
    int getValue();
    

};

Calculator::Calculator(){

    String nu((char*)"\0", 1);
    String pl((char *)"+", 1), mi((char *)"-", 1), mu((char *)"*", 1), di((char *)"/", 1), pal((char *)"(", 1), par((char *)")", 1);

    errCode = 0;
    value = 0;
    postfix = nu;
    tokens.addItem(nu);

    op.addItem(pl);op.addItem(mi);op.addItem(mu);op.addItem(di);op.addItem(pal);op.addItem(par);

}

int setExpression(const char* expr){
    
}

int Calculator::makePostFix(){
    Stack<String> stack;
    String nu((char*)"\0", 1);
    stack.Push(nu);

    if (tokens.getItemCount()){
        int i = 0;
        while (1) {
            String c = tokens.getItem(i);
            String s = stack.Top();
            if(tokens.getItemCount() > i){
                int tokenCase = 0, stackCase = 0;

                for (int j=0; j<6; j++){
                    if (c == op.getItem(j))
                        tokenCase = j+1;
                }
                for (int j=0; j<6; j++){
                    if (s == op.getItem(j))
                        stackCase = j+1;
                }

                switch (tokenCase) {
                    case 1 :
                    if (stackCase == 1 || stackCase == 2){
                        

                    }

                    
                }
                

                i++;
                continue;
            }

        }
    }

    return 0;
}

int Calculator::evaluation(){

}

int Calculator::getErrorCode(){

}

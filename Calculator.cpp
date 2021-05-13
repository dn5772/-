#include "List.h"
#include "String.h"

using namespace std;

class Calculator 

{
    private : 

    List<String> tokens; 
    int errCode;                  // 발생된 오류코드 값 : 0 -> 오류 없음 , 다른 값 -> 오류 있음
    int value;                     // 계산된 값
    String postfix;             // 후위표기식 = 최초 공백으로 초기화
    int makePostFix();         // postfix 로 변경하는 함수 :
    int a;

                                       // 오류 없는경우, 0, 오류가 있는 경우, 1을 반환 

                                       // 변경결과는 postfix 변수에 저장, 오류시 적절한 코드를 errCode 에 저장 (오류코드는 각자가 정의)

    int evaluation();            // postfix 를 계산하는 함수 : 

                                       // 계산된 값을 구함, 오류 없는경우 0, 오류가 있는 경우, 1을 반환

                                       // 계산된 값은 value 에 저장, 오류시 적절한 코드를 errCode 에 저장 (오류코드는 각자가 정의)

    public : 
    
    int getErrorCode();                             

    int setExpression(const char* expr);           

                                                            //    오류 없는경우, 0, 오류가 있는 경우, 1을 반환 
    String getPostFix();                            
    int getValue();                                   // 수식 오류있음 --> 예외발생
                                                     
};


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
    
    int getErrorCode();                             // 오류코드 반환

    int setExpression(const char* expr);       // expr에 전달된 수식(중위표기식)을 postfix로 변경하고 계산하는 함수      

                                                            //    오류 없는경우, 0, 오류가 있는 경우, 1을 반환 
    String getPostFix();                            // 변환된 후위표기식을 반환   --> 오류가 있을경우 최초값인 공백이 리턴
    int getValue();                                   // 수식 오류있음 --> 예외발생
                                                      // 수식 오류없음 --> 결과값 리턴
};


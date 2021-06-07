#include <iostream> 

using namespace std;

class String { 
    private:
        char* buffer; 
        int length;
        int size;

    public: 
        ~String();
        String Concat(String t);
        String();
        String(int m);
        String(String&);
        String(char* init, int m);

        String& operator=(const String&);
        bool operator==(const String& t);
        bool operator!();
        int Length();
        String Substr(int i, int j);
        int Find(String pat);
        int stoint();
        void print();

    friend ostream& operator<< (ostream& os, String& s);
    //friend istream& operator>> (istream& is, String& s);
};

String::String():String(10) {}

String::~String() {
    delete[] buffer;
}

String::String(int m) {
    size = m;
    buffer = new char[m];
    length = 0; 
}

String::String(String& s) : String(s.length + 1) { 
    for (int i = 0; i < s.length; i++)
        buffer[i] = s.buffer[i]; 
    buffer[s.length] = '\0'; 
    length = s.length;
}

String& String::operator=(const String& s) {
    delete[] buffer;
    buffer = new char[s.length + 1];
    for (int i = 0; i < s.length; i++)
        buffer[i] = s.buffer[i]; 
    buffer[s.length] = '\0'; 
    length = s.length;
    return *this;
}


String::String(char* init, int m) : String(m + 1) { 
    for (int i = 0; i < m; i++)
        buffer[i] = init[i]; 
    buffer[m] = '\0'; 
    length = m;
}

String String::Concat(String t) {
    //cout << " 3. Concat" << endl;

    String result(length + t.length + 1); 
    for (int i = 0; i < length; i++)
        result.buffer[i] = buffer[i];
    

    for (int i = 0; i < t.length; i++)
        result.buffer[length + i] = t.buffer[i];

    result.buffer[length + t.length] = '\0';
    result.length = length + t.length;

    return result;
}

bool String::operator==(const String& t) { 
    for (int i = 0; i < length; i++) {
        if (buffer[i] != t.buffer[i]) 
            return false;
    }
    return true; 
}

bool String::operator!() { 
    if (length == 0)
        return true; 
    else
        return false;
}

int String::Length() { 
    return length;
}

String String::Substr(int i, int j) {
    String Alpha(j - i+2);
    Alpha.length = (j - i+2);
    for (int a = 0; a <= (j - i+1); a++)
        Alpha.buffer[a] = buffer[a+i]; 
    Alpha.buffer[j - i+1] = '\0'; 
    return Alpha;
}

int String::Find(String pat) {
    for (int start = 0; start <= Length() - pat.Length(); start++) {
        for (int j = 0; j < pat.Length() && buffer[start + j] == pat.buffer[j]; j++) 
            if (j == pat.Length()-1)
                return start;
    }
    return -1;
}

int String::stoint(){
    int tmp=0;

    for (int i=0; i<length; i++){
        tmp += (buffer[i] - '0') * pow(10, (length-i-1));
    }
    
    return tmp;
}


void String::print() {
    cout << buffer << endl;
}

ostream& operator<< (ostream& os, String& s){
    os << s.buffer;
    return os;
}
/*
int main() {

    bool alpha, beta;

    String a((char*)"177", 3); 
    String b((char*)"world!", 6); 
    String c = a;
    String d;
    
    // cout << a << endl;
    // a.print(); 

    int aa = a.stoint();
    int bb = a.Length();

    cout << " int = " << aa << " Length = "<< bb << endl;
    
    // cout << boolalpha << alpha << " : a == c ? (true여야함)" << endl;

    // beta = (! c); 

    // cout << boolalpha << beta << " : ! c (c= \"hello\", 공백아니므로 false)"<<endl;

    // d = b.Substr(1, 3);

    // d.print();


    // printf("위는 b의 1~3 추출 값 orl. \n");
    // printf("%d : a의 길이, 5여야 함\n", a.Length()); 
    // //printf("%d : b에서 ld의 시작 위치, 3이어야 함", b.Find(f)); 


    return 0; 
}
*/

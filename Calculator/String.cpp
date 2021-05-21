#include <iostream> 

using namespace std;

class String { 
    private:
        char* buffer; 
        int length;
        int size; 
        String(int m);

    public: 
        ~String();
        String(char* init, int m); 
        String Concat(String t);
        String();
        String(String&);
        String& operator=(const String&);
        bool operator==(String t); 
        bool operator!(); 
        int Length(); 
        String Substr(int i, int j); 
        int Find(String pat); 
        void print(); 
};

String::String() : String(10) {}

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
    String result(length + t.length + 1); 
    for (int i = 0; i < length; i++)
        result.buffer[i] = buffer[i];
    

    for (int i = 0; i < t.length; i++)
        result.buffer[length + i] = t.buffer[i];

    result.buffer[length + t.length] = '\0';
    result.length = length + t.length;

    return result; 
}

bool String::operator==(String t) { 
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

void String::print() {
    for (int i = 0; i < length; i++)
        cout << buffer[i] << endl;
    //printf("%c", buffer[i]); printf(" : 출력값\n");
}

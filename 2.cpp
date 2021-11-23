#include <iostream>

using namespace std;

class Rectangle {
    public:

    Rectangle();
    ~Rectangle();

    void read();
    void print();


    int getArea();
    

    Rectangle operator + (Rectangle & r);
    Rectangle operator/(Rectangle& r);
    bool operator==(Rectangle& r);

    int x, y, height, width;

};
    Rectangle::Rectangle(){
        x = 0;
        y = 0;
        width = 0;
        height = 0;
    }
Rectangle::~Rectangle(){

}

void Rectangle::print()
{
    cout << "\n시작점의 좌표 : (" << x << ","<< y <<")" << endl;
    cout << "길이 : " << width << endl;
    cout << "높이 : " << height << endl;
}

void Rectangle::read()
{
    cout << "\nx 좌표 : ";
    cin >> x;
    cout << "\ny 좌표 : ";
    cin >> y;
    cout << "\n길이 : ";
    cin >> width;
    cout << "\n높이 : ";
    cin >> height;
}

int Rectangle::getArea(){
    return height * width;
}

Rectangle Rectangle::operator+(Rectangle & r)
{
    int x1_f = x, x2_f = x + width, x1_s = r.x, x2_s = r.x + r.width;
    int y1_f = y, y2_f = y + height, y1_s = r.y, y2_s = r.y + r.height;
    Rectangle rect;

    if (((x1_f > x1_s)&&(x2_f < x2_s))||((x1_f < x1_s)&&(x2_f > x2_s))){
        if ((x1_f < x1_s)&&(x2_f < x2_s)){
            rect.width = r.width;
            rect.x = r.x;
        }
        else {
            rect.width = width;
            rect.x = x;
        }
    }
    else if ((x2_f-x1_s)>(x2_s-x1_f)){
        rect.width = x2_f-x1_s;
        rect.x = x1_s;
    }
    else {
        rect.width = x2_s - x1_f;
        rect.x = x1_f;
    }


    if (((y1_f > y1_s)&&(y2_f < y2_s))||((y1_f < y1_s)&&(y2_f > y2_s))){
        if ((y1_f < y1_s)&&(y2_f < y2_s)){
            rect.height = r.height;
            rect.y = r.y;
        }
        else {
            rect.height = height;
            rect.y = y;
        }
    }
    else if ((y2_f-y1_s)>(y2_s-y1_f)){
        rect.height = y2_f-y1_s;
        rect.y = y1_s;
    }
    else {
        rect.height = y2_s - y1_f;
        rect.y = y1_f;
    }
    

    return rect;
}

Rectangle Rectangle::operator/(Rectangle& r){
    int x1_f = x, x2_f = x + width, x1_s = r.x, x2_s = r.x + r.width;
    int y1_f = y, y2_f = y + height, y1_s = r.y, y2_s = r.y + r.height;
    Rectangle rect;

    if (((x2_f - x1_s)<0)&&((x2_s-x1_f)<0)&&((y2_f-y1_s)<0)&&((y2_s-y1_f)<0))
        return rect;

    if (((x1_f > x1_s)&&(x2_f < x2_s))||((x1_f < x1_s)&&(x2_f > x2_s))){
        if ((x1_f < x1_s)&&(x2_f < x2_s)){
            rect.width = width;
            rect.x = x;
        }
        else {
            rect.width = r.width;
            rect.x = r.x;
        }
    }
    else if ((x2_f-x1_s)>(x2_s-x1_f)){
        rect.width = x2_s-x1_f;
        rect.x = x1_f;
    }
    else {
        rect.width = x2_f - x1_s;
        rect.x = x1_s;
    }

    if (((y1_f > y1_s)&&(y2_f < y2_s))||((y1_f < y1_s)&&(y2_f > y2_s))){
        if ((y1_f < y1_s)&&(y2_f < y2_s)){
            rect.height = height;
            rect.y = y;
        }
        else {
            rect.height = r.height;
            rect.y = r.y;
        }
    }
    else if ((y2_f-y1_s)>(y2_s-y1_f)){
        rect.height = y2_s-y1_f;
        rect.y = y1_f;
    }
    else {
        rect.height = y2_f - y1_s;
        rect.y = y1_s;
    }

    return rect;
}

bool Rectangle::operator==(Rectangle& r){
    if (this == &r) 
        return true;
    if ((x == r.x) && (y == r.y) && (height == r.height) && (width == r.width))
        return true; 
    else 
        return false;
}

ostream& operator<<(ostream& os, Rectangle& r){
    os << "사각형의 넓이 : " << r.getArea() << "\n입니다.\n" << endl;

    return os;
}


int main(void){
    Rectangle rect_f, rect_s, rect_a;

    cout << "첫번째 사각형의 시작점과 길이, 높이를 입력해 주세요\n";
    rect_f.read();
    rect_f.print();
    cout << rect_f;
    
    cout << "두번째 사각형의 시작점과 길이, 높이를 입력해 주세요\n";
    rect_s.read();
    rect_s.print();
    cout << rect_s;

    if (rect_s == rect_f)
        cout << "두 사각형은 같습니다.\n";
    else
        cout << "두 사각형은 같지않습니다.\n";

    cout << "두 사각형의 합집합 사각형은\n";
    rect_a = rect_f + rect_s;
    rect_a.print();
    cout << rect_a;
    
    cout << "두 사각형의 교집합 사각형은\n";
    rect_a = rect_f / rect_s;
    rect_a.print();
    cout << rect_a;
    

    return 0;
}

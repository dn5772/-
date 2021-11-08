#include <iostream>
using namespace std;

class List {
    private :

    int* items;
    int itemCount;
    int size;

    
    public :

    List();
    ~List();

    int getItem(int index);
    void addItem(int itm);
    void insertItem(int index, int itm);
    int removeAt(int index);
    int removeItem(int itm);
    void concat(List& list);
    void print();
    
};

class OrderedList {
    private :

    int *items;
    int itemCount;
    int size;

    public :

    OrderedList();
    ~OrderedList();

    int getItem(int index);
    void addItem(int itm);
    int removeAt(int index);
    int removeItem(int itm);
    void concat(OrderedList& olist);
    void print();

};

List::List(){
    itemCount = 0;
    size = 5;
    items = new int[size];
}

List::~List(){
    delete[] items;
}

int List::getItem(int index){
    if (0 <= index && index < itemCount)
        return items[index];
    else
        return -99999;
}

void List::addItem(int itm){
    if (itemCount < size){
        items[itemCount] = itm;
        itemCount++;
        //cout << itemCount;
    }
    else {
        int *newItems = new int[size*2];
        for (int i=0; i<itemCount; i++)
            newItems[i] = items[i];
        newItems[itemCount] = itm;
        itemCount++;
        delete[] items;
        items = newItems;
        size = size * 2;
    }
}

void List::insertItem(int index, int itm){
    if (itemCount == size){
        int *newItems = new int[size*2];
        for (int i=0; i<itemCount; i++)
            newItems[i] = items[i];
        itemCount++;
        delete[] items;
        items = newItems;
        size = size * 2;
    }
    else
        itemCount++;
    for (int i=itemCount; i>index; i--){
        items[i] = items[i-1];
    }

    items[index] = itm;
}

int List::removeAt(int index){

    if (0 <= index && index < itemCount){
        int tmp = items[index];
        for (int i=index; i<itemCount; i++){
            items[i] = items[i+1];
        }
        itemCount--;
        return tmp;
    }

    else
        return -99999;

}

int List::removeItem(int itm){
    for (int i=0; i<itemCount; i++){
        if (items[i]==itm){
            int tmp = items[i];
            for (int j=i; j<itemCount; j++){
                items[j] = items[j+1];
            }
            itemCount--;
            return tmp;
        }
    }
    return -99999;
}

void List::concat(List& list){
    for (int i=0; i<list.itemCount; i++){
        addItem(list.items[i]);
    }
}

void List::print(){
    for (int i=0; i<itemCount; i++)
        cout << items[i] << endl;
}

// OrderedList
OrderedList::OrderedList(){
    itemCount = 0;
    size = 5;
    items = new int[size];
}

OrderedList::~OrderedList(){
    delete[] items;
}

int OrderedList::getItem(int index){
    if (0 <= index && index < itemCount)
        return items[index];
    
    return -99999;
}

void OrderedList::addItem(int itm){
    if (itemCount < size){
        items[itemCount] = itm;
        itemCount++;
    }

    else {
        int *newItems = new int[size*2];
        for (int i=0; i<itemCount; i++)
            newItems[i] = items[i];
        newItems[itemCount] = itm;
        itemCount++;
        delete[] items;
        items = newItems;
        size = size * 2;
    }

    int tmp;
    for (int i=0; i<itemCount-1; i++){
        for (int j=0; j<itemCount-i-1; j++){
            if (items[j] > items[j+1]){
                tmp = items[j];
                items[j] = items[j+1];
                items[j+1] = tmp;
            }
        }
    }
}

int OrderedList::removeAt(int index){
    if (0 <= index && index < itemCount){
        int tmp = items[index];
        for (int i=index; i<itemCount; i++){
            items[i] = items[i+1];
        }
        itemCount--;
        return tmp;
    }

    else
        return -99999;
}

int OrderedList::removeItem(int itm){
    for (int i=0; i<itemCount; i++){
        if (items[i]==itm){
            int tmp = items[i];
            for (int j=i; j<itemCount; j++){
                items[j] = items[j+1];
            }
            itemCount--;
            return tmp;
        }
    }
    return -99999;
}

void OrderedList::concat(OrderedList& olist){
    for (int i=0; i<olist.itemCount; i++){
        addItem(olist.items[i]);
    }
}

void OrderedList::print(){
    for (int i=0; i<itemCount; i++)
        cout << items[i] << endl;
}

int main(){
    char list, c;
    bool loop = 1;

    cout << "1 : List\n2 : OrderedList" << endl;

    cin >> list;

    List list_a, list_b;

    if (list == '1'){
        while (loop){
            int lindex=0, litm=0;
            
            cout << "1 : getItem \n2 : addItem \n3 : insertItem \n4 : removeAt \n5 : removeItem \n6 : concat \n7 : print \n8 : END"<< endl;

            cin >> c;            

            switch (c){
                case '1' : 
                cout << "index :";
                cin >> lindex;
                cout << list_a.getItem(lindex) << endl;
                break;

                case '2' :
                cout << "itm :";
                cin >> litm;
                list_a.addItem(litm);
                break;

                case '3' :
                cout << "index itm :";
                cin >> lindex >> litm;
                list_a.insertItem(lindex, litm);
                break;

                case '4' :
                cout << "index :";
                cin >> lindex;
                cout << "REMOVE : " << list_a.removeAt(lindex) << endl;
                break;

                case '5' :
                cout << "itm :";
                cin >> litm;
                cout << "REMOVE : " << list_a.removeItem(litm) << endl;
                break;

                case '6' :
                for (int i=0; i<20; i++){
                    list_b.addItem(i);
                }
                list_a.concat(list_b);
                break;

                case '7' :
                list_a.print();
                break;

                case '8' :
                loop = 0;
                break;
            }
       }
    }

    OrderedList olist_a, olist_b;

    if (list == '2'){
        while (loop){
            int lindex=0, litm=0;
            
            cout << "1 : getItem \n2 : addItem \n3 : removeAt \n4 : removeItem\n5 : concat \n6 : print \n7 : END"<< endl;

            cin >> c;            

            switch (c){
                case '1' : 
                cout << "index :";
                cin >> lindex;
                cout << olist_a.getItem(lindex) << endl;
                break;

                case '2' :
                cout << "itm :";
                cin >> litm;
                olist_a.addItem(litm);
                break;

                case '3' :
                cout << "index :";
                cin >> lindex;
                cout << "REMOVE : " << olist_a.removeAt(lindex) << endl;
                break;

                case '4' :
                cout << "itm :";
                cin >> litm;
                cout << "REMOVE : " << olist_a.removeItem(litm) << endl;
                break;

                case '5' :
                for (int i=0; i<20; i++){
                    olist_b.addItem(i);
                }
                olist_a.concat(olist_b);
                break;

                case '6' :
                olist_a.print();
                break;

                case '7' :
                loop = 0;
                break;
            }
       }
    }

    return 0;
}

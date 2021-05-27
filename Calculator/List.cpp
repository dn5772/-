#include <iostream>
//#include "String.cpp"
using namespace std;

template <typename T>
class List {
    private :

    T* items;
    int itemCount;
    int size;

    public :

    List();
    ~List();

    T getItem(int index);
    int getItemCount();
    void addItem(T itm);
    void insertItem(int index,T itm);
    T removeAt(int index);
    T removeItem(T itm);
    void concat(List& list);
    void print();

};

template <typename T> 
List<T>::List(){
    itemCount = 0;
    size = 5;
    items = new T[size];
}

template <typename T> 
List<T>::~List(){
    delete[] items;
}

template <typename T> 
T List<T>::getItem(int index){
    if (0 > index && index >= itemCount)
        throw "Index Err";
    return items[index];
}

template <typename T> 
void List<T>::addItem(T itm){
    if (itemCount < size){
        items[itemCount] = itm;
        itemCount++;
    }
    else {
        T *newItems = new T[size*2];
        for (int i=0; i<itemCount; i++)
            newItems[i] = items[i];
        newItems[itemCount] = itm;
        itemCount++;
        delete[] items;
        items = newItems;
        size = size * 2;
    }

    //cout << itm << "add itme $" << endl;
}

template <typename T>
int List<T>::getItemCount(){ return itemCount; }

template <typename T> 
void List<T>::insertItem(int index,T itm){
    if (itemCount == size){
        T *newItems = new T[size*2];
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

template <typename T> 
T List<T>::removeAt(int index){
    if (!itemCount){
        throw "List is empty. Cannot delete";
    }
        T tmp = items[index];
        for (int i=index; i<itemCount; i++){
            items[i] = items[i+1];
        }
        itemCount--;
        return tmp;
}

template <typename T>
T List<T>::removeItem(T itm){
    for (int i=0; i<itemCount; i++){
        if (items[i]==itm){
            T tmp = items[i];
            for (int j=i; j<itemCount; j++){
                items[j] = items[j+1];
            }
            itemCount--;
            return tmp;
        }
    }
}

template <typename T> 
void List<T>::concat(List<T>& list){
    for (int i=0; i<list.itemCount; i++){
        addItem(list.items[i]);
    }
}

template <typename T> 
void List<T>::print(){
    for (int i=0; i<itemCount; i++)
        cout << items[i] << endl;
}

/*
int main(){
    char list, c;
    bool loop = 1;

    List<String> op;
    String a, b;
    String nu((char*)"\0", 1);
    String sp((char*)" ", 1);
    String pl((char *)"+", 1), mi((char *)"-", 1), mu((char *)"*", 1), di((char *)"/", 1), pal((char *)"(", 1), par((char *)")", 1);

    op.addItem(nu);op.addItem(pl);op.addItem(mi);op.addItem(mu);op.addItem(di);op.addItem(pal);op.addItem(par);op.addItem(sp);

    a = op.getItem(1);

    a.print();
    b = op.getItem(1);

    if (a == b)
    a.print();
    

    if (list == '1'){
        while (loop){
            int lindex=0; 
            String litm;
            
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

    return 0;
}
*/

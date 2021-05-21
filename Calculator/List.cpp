#include <iostream>
using namespace std;

template <typename T>
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


template <typename T> 
List<T>::List(){
    itemCount = 0;
    size = 5;
    items = new int[size];
}

template <typename T> 
List<T>::~List(){
    delete[] items;
}

template <typename T> 
int List<T>::getItem(int index){
    if (0 <= index && index < itemCount)
        return items[index];
    else
        return -99999;
}

template <typename T> 
void List<T>::addItem(int itm){
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

template <typename T> 
void List<T>::insertItem(int index, int itm){
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

template <typename T> 
int List<T>::removeAt(int index){
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

template <typename T> 
int List<T>::removeItem(int itm){
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

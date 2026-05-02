#include "circular_list.h"
#include <iostream>
#include "clocale"

using namespace std;

int main() {

    setlocale(LC_ALL, "Russian_Russia.1251");

    CircularList<CircularList<int>> listOfLists;


    CircularList<int> list3;
    list3.insertAfter(195);

    CircularList<int> list1;
    list1.insertAfter(2);
    list1.insertAfter(5);
    list1.insertAfter(3);

    CircularList<int> list2;
    list2.insertAfter(89);
    list2.insertAfter(45);

    try {
        listOfLists.insertAfter(list1);
        listOfLists.insertAfter(list2);
        listOfLists.insertAfter(list3);

        for (int i = 0; i < listOfLists.getSize(); i++) {
            cout << *listOfLists.getCurrent() << endl;
            listOfLists.next();
        }
    }
    catch (const runtime_error& e) {
        cerr << "Исключение: " << e.what() << endl;
    }


    CircularList<int> emptyList;

    try {
        emptyList.getCurrent();
    }
    catch (const runtime_error& e) {
        cerr << "Перехвачено: " << e.what() << endl;
    }

    try {
        emptyList.removeCurrent();
    }
    catch (const runtime_error& e) {
        cerr << "Перехвачено: " << e.what() << endl;
    }

    try {
        emptyList.prev();
    }
    catch (const runtime_error& e) {
        cerr << "Перехвачено: " << e.what() << endl;
    }

    try{
        emptyList.next();
    }
    catch (const runtime_error& e) {
        cerr << "Перехвачено: " << e.what() << endl;
    }
    try{
        const CircularList<int> constEmptyList;
        constEmptyList.getCurrent();
    }
    catch (const runtime_error& e) {
        cerr << "Перехвачено: " << e.what() << endl;
    }
    return 0;
}

#include "circular_list.h"
#include <iostream>
#include "clocale"

using namespace std;

void printList(CircularList<int>& list, string name) {
    if (list.isEmpty()) {
        cout << name << ": пуст" << endl;
        return;
    }

    cout << name << ": ";

    int firstValue = *list.getCurrent();

    do {
        cout << *list.getCurrent() << " ";
        list.next();
    } while (*list.getCurrent() != firstValue);

    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian_Russia.1251");

    CircularList<int> list1;
    CircularList<int> list2;
    CircularList<int> list3;

    int choice, listChoice, value;

    cout << "Программа для работы с 3 списками" << endl;
    cout << "Список 1, Список 2, Список 3" << endl;


    list1.insertAfter(10);
    list1.insertAfter(20);
    list1.insertAfter(30);

    list2.insertAfter(5);
    list2.insertAfter(15);

    list3.insertAfter(100);

    do {
        cout << "\n  Главное меню  " << endl;
        cout << "1. Показать все списки" << endl;
        cout << "2. Работа со списком" << endl;
        cout << "3. Скопировать список в другой" << endl;
        cout << "0. Выход" << endl;
        cout << "Выбор: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nТекущее состояние:" << endl;
                printList(list1, "Список 1");
                printList(list2, "Список 2");
                printList(list3, "Список 3");
                break;

            case 2: {
                cout << "\nВыберите список (1, 2 или 3): ";
                cin >> listChoice;

                CircularList<int>* currentList = nullptr;
                string listName;

                if (listChoice == 1) {
                    currentList = &list1;
                    listName = "Список 1";
                } else if (listChoice == 2) {
                    currentList = &list2;
                    listName = "Список 2";
                } else if (listChoice == 3) {
                    currentList = &list3;
                    listName = "Список 3";
                } else {
                    cout << "Неверный номер!" << endl;
                    break;
                }

                int subChoice;
                do {
                    cout << "\n--- Работа с " << listName << " ---" << endl;
                    cout << "1. Добавить число" << endl;
                    cout << "2. Удалить текущее число" << endl;
                    cout << "3. Перейти к следующему" << endl;
                    cout << "4. Перейти к предыдущему" << endl;
                    cout << "5. Показать текущее число" << endl;
                    cout << "6. Показать весь список" << endl;
                    cout << "7. Очистить список" << endl;
                    cout << "0. Назад" << endl;
                    cout << "Выбор: ";
                    cin >> subChoice;

                    try {
                        switch (subChoice) {
                            case 1:
                                cout << "Введите число: ";
                                cin >> value;
                                currentList->insertAfter(value);
                                cout << "Число " << value << " добавлено!" << endl;
                                break;

                            case 2:
                                if (!currentList->isEmpty()) {
                                    value = *currentList->getCurrent();
                                    currentList->removeCurrent();
                                    cout << "Число " << value << " удалено!" << endl;
                                } else {
                                    cout << "Список пуст!" << endl;
                                }
                                break;

                            case 3:
                                if (!currentList->isEmpty()) {
                                    currentList->next();
                                    cout << "Текущее число: " << *currentList->getCurrent() << endl;
                                } else {
                                    cout << "Список пуст!" << endl;
                                }
                                break;

                            case 4:
                                if (!currentList->isEmpty()) {
                                    currentList->prev();
                                    cout << "Текущее число: " << *currentList->getCurrent() << endl;
                                } else {
                                    cout << "Список пуст!" << endl;
                                }
                                break;

                            case 5:
                                if (!currentList->isEmpty()) {
                                    cout << "Текущее число: " << *currentList->getCurrent() << endl;
                                } else {
                                    cout << "Список пуст!" << endl;
                                }
                                break;

                            case 6:
                                printList(*currentList, listName);
                                break;

                            case 7:
                                currentList->clear();
                                cout << "Список очищен!" << endl;
                                break;

                            case 0:
                                cout << "Возврат в главное меню..." << endl;
                                break;

                            default:
                                cout << "Неверный выбор!" << endl;
                        }
                    } catch (const runtime_error& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                } while (subChoice != 0);
                break;
            }

            case 3: {
                int from, to;
                cout << "\nИз какого списка копировать (1, 2, 3): ";
                cin >> from;
                cout << "В какой список копировать (1, 2, 3): ";
                cin >> to;

                CircularList<int>* fromList = nullptr;
                CircularList<int>* toList = nullptr;

                if (from == 1) fromList = &list1;
                else if (from == 2) fromList = &list2;
                else if (from == 3) fromList = &list3;

                if (to == 1) toList = &list1;
                else if (to == 2) toList = &list2;
                else if (to == 3) toList = &list3;

                if (fromList && toList) {
                    *toList = *fromList;
                    cout << "Список " << from << " скопирован в список " << to << endl;
                } else {
                    cout << "Неверный номер списка!" << endl;
                }
                break;
            }

            case 0:
                cout << "Программа завершена!" << endl;
                break;

            default:
                cout << "Неверный выбор!" << endl;
        }
    } while (choice != 0);

    return 0;
}

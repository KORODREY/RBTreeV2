#include <iostream>
#include <fstream>
#include "RBTree.hpp"

using namespace std;

// main для интового дерева
// вывод дерева 
void PrintTree(RBTree<int> &tree) {
    if (tree.GetSize() == 0) {
        cout << "(empty)" << endl;
        return;
    }

    cout << tree;
    cout << endl << "PreOrder: ";
    tree.PreOrder(cout);

    cout << endl << "InOrder: ";
    tree.InOrder(cout);

    cout << endl << "PostOrder: ";
    tree.PostOrder(cout);
    cout << endl;
}

// ввод дерева
void ReadTree(RBTree<int> &tree) {
    cout << "Введите значения: ";
    cin >> tree; // считываем дерево
    cin.clear();
}

// вставка в дерево
void InsertTree(RBTree<int> &tree) {
    int value;
    cout << "Введите значение: ";
    cin >> value;

    tree.Insert(value);
    cout << "Готово!" << endl;
}

// поиск в дереве
void FindInTree(RBTree<int> &tree) {
    int value;
    cout << "Число для поиска: ";
    cin >> value;

    if (tree.Find(value)) { 
        cout << "Нашли!" << endl;
    }
    else {
        cout << "Не нашли число " << value << " в дереве:(" << endl;
    }
}

// удаление элемента
void RemoveInTree(RBTree<int> &tree) {
    int value;
    cout << "Число для удаления: ";
    cin >> value;

    if (tree.Remove(value)) {
        cout << "Готово!" << endl; //
    }
    else {
        cout << "Не нашли число " << value << " в дереве:(" << endl;
    }
}

void SaveToFile(RBTree<int> &tree) {
    char path[100]; // путь к файлу
    cout << "Путь к файлу: ";
    cin >> path;

    ofstream f(path); // создаём файл
    f << tree; // выводим дерево
    f.close();
}

void LoadFromFile(RBTree<int> &tree) {
    char path[100]; // путь к файлу
    cout << "Путь к файлу: ";
    cin >> path;

    ifstream f(path); // создаём файл

    if (!f) {
        cout << "Какие-то проблемы с файлом '" << path << "'" << endl;
        return;
    }

    f >> tree; // считываем дерево
    f.close();
}

int main() {

    setlocale(LC_ALL, "Russian");

    int item;
    RBTree<int> tree; // создаём интовое дерево

    do {
        cout << endl << "Что будем делать?" << endl;
        cout << "1. Напечатать" << endl;
        cout << "2. Считать" << endl;
        cout << "3. Вставить" << endl;
        cout << "4. Найти" << endl;
        cout << "5. Удалить" << endl;
        cout << "6. Получить размер" << endl;
        cout << "7. Сохранить в файл" << endl;
        cout << "8. Загрузить из файла" << endl;
        cout << "9. Выход" << endl;
        cout << ">";
        cin >> item;

        while (item < 1 || item > 9) {
            cout << "Попробуйте еще раз: ";
            cin >> item;
        }

        switch (item) {
            case 1:
                PrintTree(tree);
                break;

            case 2:
                ReadTree(tree);
                break;

            case 3:
                InsertTree(tree);
                break;

            case 4:
                FindInTree(tree);
                break;

            case 5:
                RemoveInTree(tree);
                break;

            case 6:
                cout << "Размер: " << tree.GetSize() << endl;
                break;

            case 7:
                SaveToFile(tree);
                break;

            case 8:
                LoadFromFile(tree);
                break;
        }
    } while (item != 9);

    return 0;
}

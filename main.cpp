#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <string>

using namespace std;

struct graph {
    int pathCount;//количество путей
    int* lenghtPathPtr;//массив длины путей
    int* pathTo;//массив путей, куда идём
};
int countOfString;

void printGraphMatrix(int** matrix, int row);

void printGraphList(struct graph* list, int row);

int weight;

int main() {
    int nodeA, nodeB;
    system("chcp 1251");
    int b, numberOfCities;
    int big_num(10000);
    char fileName[50];
    char menu;
    cout << "Введите имя файла: " << endl;
    cin >> fileName;
    ifstream in(fileName);

    if (in.is_open()) {
        int countOfNumbers = 0, temp, countOfSpace = 0;
        int selector;
        char* str = new char[256];

        while (!in.eof())//считываем количество чисел
        {
            in.getline(str, 256, '\n');
            countOfString++;
        }
        in.seekg(0, ios_base::beg);
        in.clear();
        delete []str;
        //matrix
        int** originalMatrix;
        originalMatrix = new int* [countOfString];
        for (int i = 0; i < countOfString; i++) {
            originalMatrix[i] = new int[countOfString];
        }

        int** matrix;
        matrix = new int* [countOfString];
        for (int i = 0; i < countOfString; i++) {
            matrix[i] = new int[countOfString];
        }

        //list
        graph* list;
        list = new struct graph[countOfString];

        for (int i = 0; i < countOfString; i++)//обнуление элементов
        {
            list[i].lenghtPathPtr = NULL;
            list[i].pathTo = NULL;
            list[i].pathCount = 0;
        }


        for (int i = 0; i < countOfString; i++) { //тут параллельно заолняются
            int havePathTo = 0;//путь до вершины

            for (int j = 0; j < countOfString; j++) {
                in >> temp;
                matrix[i][j] = temp;
                originalMatrix[i][j] = temp;

                if (originalMatrix[i][j] != 0)//если буфер не равен нулю, считаем количество смежных вершин
                {
                    list[i].pathCount++;
                    if (havePathTo <
                        list[i].pathCount) //если есть путь, перевыделяем память и записываем вершину, куда идём и значение
                    {
                        list[i].lenghtPathPtr = (int*)realloc(list[i].lenghtPathPtr,
                                                              list[i].pathCount * sizeof(int));
                        list[i].pathTo = (int*)realloc(list[i].pathTo, list[i].pathCount * sizeof(int));

                        list[i].pathTo[havePathTo] = j;
                        list[i].lenghtPathPtr[havePathTo] = originalMatrix[i][j];
                    }
                    havePathTo++;
                }
            }
        }
        cout << "Выберите" << endl;
        cout << "1. Матрица смежности" << endl;
        cout << "2. Список смежности" << endl;
        cin >> selector;
        switch (selector) {
            case 1: {
                cout << "Вывод матрицы смежности:" << endl;
                printGraphMatrix(originalMatrix, countOfString);
                cout << "Введите город А: ";
                cin >> nodeA;
                cout << "Введите город B: ";
                cin >> nodeB;
                cout << "Введите количество городов, которые нужно обойти: " << endl;
                cin >> numberOfCities;
                cout << "Введите города, через которые не должен проходить заданный маршрут: " << endl;
                for (int i = 0; i < numberOfCities; i++) {
                    cin >> b;
                    for (int j = 0; j < countOfString; j++) {
                        matrix[j][b] = 0;
                    }
                }
                int* pos = new int[countOfString];
                int* node = new int[countOfString];
                cout << "Вывод матрицы смежности:" << endl;
                printGraphMatrix(matrix, countOfString);
                int min, index_min(0);
                for (int i = 0; i < countOfString; ++i) {     // заполняем путь к вершине большими числами, желательно взять биг_нам ещё больше, но и так ок.
                    pos[i] = big_num;       // а все вершины помечаем как "непройденные"
                    node[i] = 0;
                }
                pos[nodeA] = 0;                // назначаем какую-то вершину началом алгоритма, узлом ( или так не говорят, хз)
                for (int i = 0; i < countOfString - 1; ++i) {    // основной цикл
                    min = big_num;
                    for (int j = 0; j <
                                    countOfString; ++j) {     // находим вершину с минимальным к ней расстоянием, на первом шаге это будет узел
                        if (!node[j] && pos[j] < min) {
                            min = pos[j];
                            index_min = j;
                        }
                    }
                    node[index_min] = true;   // помечаем выбранную вершину как пройденную
                    for (int j = 0; j <
                                    countOfString; ++j) {   // цикл, в котором мы даем всем вершинам, смежным с выбранной вес пути к ней
                        if (!node[j] && matrix[index_min][j] > 0 && pos[index_min] != big_num &&
                            pos[index_min] + matrix[index_min][j] < pos[j]) {
                            pos[j] = pos[index_min] + matrix[index_min][j];
                        } // условие такое, если эта вершина не пройденная и она смежна с выбранной и если сумма веса выбранной вершины и ребра к текущей будет меньше, чем
                    }     // вес текущей на данный момент, то  - меняем значение веса текущей вершины.
                }
                cout << "\nКратчайший путь из города A в город B = " << pos[nodeB] << endl;
                break;
                delete[]pos;
                delete[]node;
            }
            case 2: {
                cout << "Вывод списка смежности:" << endl;
                printGraphList(list, countOfString);
                cout << "Введите город А: ";
                cin >> nodeA;
                cout << "Введите город B: ";
                cin >> nodeB;
                cout << "Введите количество городов, которые нужно обойти: " << endl;
                cin >> numberOfCities;
                if (numberOfCities > 0) {
                    cout << "Введите города, через которые не должен проходить заданный маршрут: " << endl;
                    cin >> b;
                    for (int i = 0; i < numberOfCities; i++) {
                        for (int j = 0; j < countOfString; j++) {
                            if (list[i].pathTo[j] == b) {
                                list[i].lenghtPathPtr[j] = 0;
                            }
                        }
                    }
                }
                int* pos = new int[countOfString];
                int* node = new int[countOfString];
                int min, index_min(0);
                for (int i = 0; i < countOfString; ++i) {
                    pos[i] = big_num;
                    node[i] = 0;
                }
                for (int j = 0; j < countOfString; j++) {
                    matrix[j][b] = 0;
                }
                pos[nodeA] = 0;
                for (int i = 0; i < countOfString - 1; ++i) {
                    min = big_num;
                    for (int j = 0; j < countOfString; ++j) {
                        if (!node[j] && pos[j] < min) {
                            min = pos[j];
                            index_min = j;
                        }
                    }
                    node[index_min] = true;
                    for (int j = 0; j < countOfString; ++j) {
                        if (!node[j] && matrix[index_min][j] > 0 && pos[index_min] != big_num &&
                            pos[index_min] + matrix[index_min][j] < pos[j]) {
                            pos[j] = pos[index_min] + matrix[index_min][j];
                            weight = pos[j];
                        }
                    }
                }
                cout << "Список смежности" << endl;
                printGraphList(list, countOfString);
                cout << "\nКратчайший путь из города A в город B = " << pos[nodeB] << endl;

                free(list);
                break;
            }
            default: {
                cout << "Данный пункт меню отсутствует, повторите попытку" << endl;
                break;
            }
        }
        for (int i = 0; i < countOfString; i++)
            delete[] originalMatrix[i];
        delete[]originalMatrix;
        for (int i = 0; i < countOfString; i++)
            delete[] matrix[i];
        delete[]matrix;
    }
    else {
        cout << "Файл не найден" << endl;
    }
    cout << endl;
    return 0;
}

void printGraphMatrix(int** matrix, int row) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < row; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void printGraphList(struct graph* list, int row) {
    for (int i = 0; i < row; i++) {
        cout << i << ": ";
        for (int j = 0; j < list[i].pathCount; j++) {
            cout << list[i].pathTo[j] << " (" << list[i].lenghtPathPtr[j] << "); ";
        }
        cout << endl;
    }
}
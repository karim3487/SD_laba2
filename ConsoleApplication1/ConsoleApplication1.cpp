#include <iostream>
#include <iomanip>
#include <windows.h>
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
        int tem;
        for (int i = 0; i < countOfString; i++) {
            for (int j = 0; j < countOfString; j++) {
                in >> tem;
                matrix[i][j] = tem;
                originalMatrix[i][j] = tem;
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
            cout << "Введите количество городов, которые нужно обойти: " << endl;
            cin >> numberOfCities;
            cout << "Введите города, через которые не должен проходить заданный маршрут: " << endl;
            for (size_t i = 0; i < numberOfCities; i++) {
                cin >> b;
                for (size_t j = 0; j < countOfString; j++) {
                    matrix[j][b] = 0;
                }
            }
            int* pos = new int[countOfString];
            int* node = new int[countOfString];
            cout << "Вывод матрицы смежности:" << endl;
            printGraphMatrix(matrix, countOfString);
            int min, index_min(0);
            for (int i = 0; i <
                countOfString; ++i) {     // заполняем путь к вершине большими числами, желательно взять биг_нам ещё больше, но и так ок.
                pos[i] = big_num;       // а все вершины помечаем как "непройденные"
                node[i] = 0;
            }
            pos[0] = 0;                // назначаем какую-то вершину началом алгоритма, узлом ( или так не говорят, хз)
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
                        weight = pos[j];
                    } // условие такое, если эта вершина не пройденная и она смежна с выбранной и если сумма веса выбранной вершины и ребра к текущей будет меньше, чем
                }     // вес текущей на данный момент, то  - меняем значение веса текущей вершины.
            }
            int* ver = new int[countOfString];
            int end = countOfString - 1;
            ver[0] = end + 1;
            int k = 1;
            while (end != 0) {
                for (int i = 0; i < countOfString; i++)
                    if (matrix[i][end] != 0) {
                        int temp = weight - matrix[i][end];
                        if (temp == pos[i]) {
                            weight = temp;
                            end = i;
                            ver[k] = i + 1;
                            k++;
                        }
                    }
            }
            printf("\nВывод кратчайшего пути\n");
            for (int i = k - 1; i >= 0; i--)
                printf("%3d ", ver[i]);
            cout << "\nКратчайший путь из города 1 в город 6 = " << pos[countOfString - 1] << endl;
            break;
            delete[]pos;
            delete[]node;
            delete[]ver;
        }
        case 2: {

            struct graph* list;
            list = new struct graph[countOfString];

            for (int i = 0; i < countOfString; i++)//обнуление элементов
            {
                list[i].lenghtPathPtr = NULL;
                list[i].pathTo = NULL;
                list[i].pathCount = 0;
            }

            int buff;//буфер для считывания
            ifstream in(fileName);
            while (!in.eof()) {
                for (int i = 0; i < countOfString; i++) {
                    int havePathTo = 0;//путь до вершины
                    for (int j = 0, k = 0; j < countOfString; j++) {
                        in >> buff; // заполнение матрицы
                        matrix[i][j] = buff;
                        if (buff != 0)//если буфер не равен нулю, считаем количество смежных вершин
                        {
                            list[i].pathCount++;
                            if (havePathTo <
                                list[i].pathCount) //если есть путь, перевыделяем память и записываем вершину, куда идём и значение
                            {
                                list[i].lenghtPathPtr = (int*)realloc(list[i].lenghtPathPtr,
                                    list[i].pathCount * sizeof(int));
                                list[i].pathTo = (int*)realloc(list[i].pathTo, list[i].pathCount * sizeof(int));

                                list[i].pathTo[havePathTo] = j;
                                list[i].lenghtPathPtr[havePathTo] = buff;
                            }
                            havePathTo++;
                        }

                    }
                }
            }
            cout << "Вывод списка смежности:" << endl;
            printGraphList(list, countOfString);
            cout << "Введите количество городов, которые нужно обойти: " << endl;
            cin >> numberOfCities;
            cout << "Введите города, через которые не должен проходить заданный маршрут: " << endl;
            for (size_t i = 0; i < numberOfCities; i++) {
                cin >> b;
                for (size_t j = 0; j < countOfString; j++) {
                    matrix[j][b] = 0;
                }
            }
            int* pos = new int[countOfString];
            int* node = new int[countOfString];

            cout << "Вывод списка смежности:" << endl;
            int min, index_min(0);
            for (int i = 0; i < countOfString; ++i) {
                pos[i] = big_num;
                node[i] = 0;
            }
            pos[0] = 0;
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
            int* ver = new int[countOfString];
            int end = countOfString - 1;
            ver[0] = end + 1;
            int k = 1;
            while (end != 0) {
                for (int i = 0; i < countOfString; i++)
                    if (matrix[i][end] != 0) {
                        int temp = weight - matrix[i][end];
                        if (temp == pos[i]) {
                            weight = temp;
                            end = i;
                            ver[k] = i + 1;
                            k++;
                        }
                    }
            }
            printf("\nВывод кратчайшего пути\n");
            for (int i = k - 1; i >= 0; i--)
                printf("%3d ", ver[i]);
            cout << "\nКратчайший путь из города 1 в город 6 = " << pos[countOfString - 1] << endl;
            break;
            delete[] pos; delete[] node; delete[] ver, delete[] list;
        }
        default: {
            cout << "Данный пункт меню отсутствует, повторите попытку" << endl;
            break;
        }
        }
        delete[]originalMatrix;
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
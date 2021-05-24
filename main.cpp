#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <string>

using namespace std;

struct graph {
    int pathCount;//���������� �����
    int* lenghtPathPtr;//������ ����� �����
    int* pathTo;//������ �����, ���� ���
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
    cout << "������� ��� �����: " << endl;
    cin >> fileName;
    ifstream in(fileName);

    if (in.is_open()) {
        int countOfNumbers = 0, temp, countOfSpace = 0;
        int selector;
        char* str = new char[256];

        while (!in.eof())//��������� ���������� �����
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
        cout << "��������" << endl;
        cout << "1. ������� ���������" << endl;
        cout << "2. ������ ���������" << endl;
        cin >> selector;
        switch (selector) {
            case 1: {
                cout << "����� ������� ���������:" << endl;
                printGraphMatrix(originalMatrix, countOfString);
                cout << "������� ����� �: ";
                cin >> nodeA;
                cout << "������� ����� B: ";
                cin >> nodeB;
                cout << "������� ���������� �������, ������� ����� ������: " << endl;
                cin >> numberOfCities;
                cout << "������� ������, ����� ������� �� ������ ��������� �������� �������: " << endl;
                for (int i = 0; i < numberOfCities; i++) {
                    cin >> b;
                    for (int j = 0; j < countOfString; j++) {
                        matrix[j][b] = 0;
                    }
                }
                int* pos = new int[countOfString];
                int* node = new int[countOfString];
                cout << "����� ������� ���������:" << endl;
                printGraphMatrix(matrix, countOfString);
                int min, index_min(0);
                for (int i = 0; i <
                                countOfString; ++i) {     // ��������� ���� � ������� �������� �������, ���������� ����� ���_��� ��� ������, �� � ��� ��.
                    pos[i] = big_num;       // � ��� ������� �������� ��� "������������"
                    node[i] = 0;
                }
                pos[nodeA] = 0;                // ��������� �����-�� ������� ������� ���������, ����� ( ��� ��� �� �������, ��)
                for (int i = 0; i < countOfString - 1; ++i) {    // �������� ����
                    min = big_num;
                    for (int j = 0; j <
                                    countOfString; ++j) {     // ������� ������� � ����������� � ��� �����������, �� ������ ���� ��� ����� ����
                        if (!node[j] && pos[j] < min) {
                            min = pos[j];
                            index_min = j;
                        }
                    }
                    node[index_min] = true;   // �������� ��������� ������� ��� ����������
                    for (int j = 0; j <
                                    countOfString; ++j) {   // ����, � ������� �� ���� ���� ��������, ������� � ��������� ��� ���� � ���
                        if (!node[j] && matrix[index_min][j] > 0 && pos[index_min] != big_num &&
                            pos[index_min] + matrix[index_min][j] < pos[j]) {
                            pos[j] = pos[index_min] + matrix[index_min][j];
                            //weight = pos[j];
                        } // ������� �����, ���� ��� ������� �� ���������� � ��� ������ � ��������� � ���� ����� ���� ��������� ������� � ����� � ������� ����� ������, ���
                    }     // ��� ������� �� ������ ������, ��  - ������ �������� ���� ������� �������.
                }
                /*int* ver = new int[countOfString];
                int end = nodeB;
                ver[0] = end + 1;
                int k = 1;
                cout << "\n\n\n" << weight << "\n\n\n";

                while (end != nodeA) {
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
                printf("\n����� ����������� ����\n");
                for (int i = k - 1; i >= 0; i--)
                    printf("%3d ", ver[i]);*/
                cout << "\n���������� ���� �� ������ A � ����� B = " << pos[nodeB] << endl;
                break;
                delete[]pos;
                delete[]node;
                //delete[]ver;
            }
            case 2: {

                struct graph* list;
                list = new struct graph[countOfString];

                for (int i = 0; i < countOfString; i++)//��������� ���������
                {
                    list[i].lenghtPathPtr = NULL;
                    list[i].pathTo = NULL;
                    list[i].pathCount = 0;
                }

                int buff;//����� ��� ����������
                ifstream in(fileName);
                while (!in.eof()) {
                    for (int i = 0; i < countOfString; i++) {
                        int havePathTo = 0;//���� �� �������
                        for (int j = 0, k = 0; j < countOfString; j++) {
                            in >> buff; // ���������� �������
                            matrix[i][j] = buff;
                            if (buff != 0)//���� ����� �� ����� ����, ������� ���������� ������� ������
                            {
                                list[i].pathCount++;
                                if (havePathTo <
                                    list[i].pathCount) //���� ���� ����, ������������ ������ � ���������� �������, ���� ��� � ��������
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
                cout << "����� ������ ���������:" << endl;
                printGraphList(list, countOfString);
                cout << "������� ���������� �������, ������� ����� ������: " << endl;
                cin >> numberOfCities;
                cout << "������� ������, ����� ������� �� ������ ��������� �������� �������: " << endl;
                for (int i = 0; i < numberOfCities; i++) {
                    cin >> b;
                    for (int j = 0; j < countOfString; j++) {
                        matrix[j][b] = 0;
                    }
                }
                int* pos = new int[countOfString];
                int* node = new int[countOfString];

                cout << "����� ������ ���������:" << endl;
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
                printf("\n����� ����������� ����\n");
                for (int i = k - 1; i >= 0; i--)
                    printf("%3d ", ver[i]);
                cout << "\n���������� ���� �� ������ 1 � ����� 6 = " << pos[countOfString - 1] << endl;
                break;
                delete[] pos; delete[] node; delete[] ver, delete[] list;
            }
            default: {
                cout << "������ ����� ���� �����������, ��������� �������" << endl;
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
        cout << "���� �� ������" << endl;
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
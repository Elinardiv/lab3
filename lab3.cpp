#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>

using namespace std;

void partA() {
    string folds;
    int rib_num;

    cout << "\n--- Способ А ---" << endl;
    cout << "Введите строку сгибаний (P/Z): ";
    cin >> folds;
    cout << "Введите номер ребра: ";
    cin >> rib_num;

    vector<char> edges;

    if (folds[0] == 'P') {
        edges.push_back('K');
    } else {
        edges.push_back('O');
    }

    for (int i = 1; i < folds.length(); i++) {
        char new_edge = (folds[i] == 'P') ? 'K' : 'O';

        vector<char> new_edges;

        for (int j = 0; j < edges.size(); j++) {
            new_edges.push_back(edges[j]);

            if (j == edges.size() - 1) {
                new_edges.push_back(new_edge);

                for (int k = edges.size() - 1; k >= 0; k--) {
                    if (edges[k] == 'K') {
                        new_edges.push_back('O');
                    } else {
                        new_edges.push_back('K');
                    }
                }
                break;
            }
        }
        edges = new_edges;
    }

    cout << "Тип ребра: " << edges[rib_num - 1] << endl;
}

bool recover(string& edges, int l, int r, string& folds) {
    if (l == r) {
        if (edges[l] == 'K') folds.push_back('P');
        else folds.push_back('Z');
        return true;
    }

    int len = r - l + 1;
    int mid = l + len / 2;

    if (edges[mid] == 'K') {
        folds.push_back('P');
    } else {
        folds.push_back('Z');
    }

    int half_len = len / 2;
    for (int i = 0; i < half_len; i++) {
        char left_char = edges[l + i];
        char right_char = edges[mid + 1 + i];

        char expected_right = (left_char == 'K') ? 'O' : 'K';

        if (right_char != expected_right) {
            return false;
        }
    }

    return recover(edges, l, mid - 1, folds);
}

void partB() {
    string edges;
    cout << "\n--- Способ Б ---" << endl;
    cout << "Введите последовательность рёбер (O/K): ";
    cin >> edges;

    int len = edges.length();

    int x = len + 1;
    if ((x & (x - 1)) != 0) {
        cout << "Такой последовательности не существует" << endl;
        return;
    }

    string folds = "";

    if (recover(edges, 0, len - 1, folds)) {
        reverse(folds.begin(), folds.end());
        cout << "Последовательность сгибаний: " << folds << endl;
    } else {
        cout << "Такой последовательности не существует" << endl;
    }
}


int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    int choice;

    cout << "------ Выберите способ: ------" << endl;
    cout << "1 - Способ А" << endl;
    cout << "2 - способ Б" << endl;
    cout << "Выбран: ";
    cin >> choice;

    if (choice == 1) {
        partA();
    } else if (choice == 2) {
        partB();
    } else {
        cout << "Нету такого способа" << endl;
    }

    return 0;
}

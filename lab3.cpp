#include <iostream>
#include <windows.h>

using namespace std;

char* vvodStroki() {
    char* str = new char[1];
    int dlina = 0;
    int razmer = 1;

    char ch;
    while (cin.get(ch) && ch != '\n') {
        if (dlina + 1 >= razmer) {
            razmer *= 2;
            char* novayaStr = new char[razmer];
            for (int i = 0; i < dlina; i++) novayaStr[i] = str[i];
            delete[] str;
            str = novayaStr;
        }
        str[dlina++] = ch;
    }
    str[dlina] = '\0';
    return str;
}

void zadanieA() {
    cout << "\n--- Способ А ---" << endl;
    cout << "Введите строку сгибаний (P/Z): ";
    cin.ignore();
    char* str = vvodStroki();

    cout << "Введите номер ребра: ";
    int nomer;
    cin >> nomer;

    int razmerRebra = 1;
    char* rebra = new char[razmerRebra];

    if (str[0] == 'P') rebra[0] = 'K';
    else rebra[0] = 'O';

    for (int i = 1; str[i] != '\0'; i++) {
        int noviyRazmer = razmerRebra * 2 + 1;
        char* novieRebra = new char[noviyRazmer];

        // Копируем левую
        for (int j = 0; j < razmerRebra; j++) {
            novieRebra[j] = rebra[j];
        }

        if (str[i] == 'P') novieRebra[razmerRebra] = 'K';
        else novieRebra[razmerRebra] = 'O';

        // инвертированная правая
        for (int j = 0; j < razmerRebra; j++) {
            if (rebra[razmerRebra - 1 - j] == 'K') {
                novieRebra[razmerRebra + 1 + j] = 'O';
            } else {
                novieRebra[razmerRebra + 1 + j] = 'K';
            }
        }

        delete[] rebra;
        rebra = novieRebra;
        razmerRebra = noviyRazmer;
    }

    cout << "Тип ребра: " << rebra[nomer - 1] << endl;

    delete[] str;
    delete[] rebra;
}

bool vosstanovit(char* rebra, int levo, int pravo, char*& rez, int& index, int& obem) {
    if (levo == pravo) {
        if (index + 1 >= obem) {
            obem *= 2;
            char* noviyRez = new char[obem];
            for (int i = 0; i < index; i++) noviyRez[i] = rez[i];
            delete[] rez;
            rez = noviyRez;
        }

        if (rebra[levo] == 'K') rez[index++] = 'P';
        else rez[index++] = 'Z';

        return true;
    }

    int seredina = levo + (pravo - levo + 1) / 2;

    if (index + 1 >= obem) {
        obem *= 2;
        char* noviyRez = new char[obem];
        for (int i = 0; i < index; i++) noviyRez[i] = rez[i];
        delete[] rez;
        rez = noviyRez;
    }

    if (rebra[seredina] == 'K') rez[index++] = 'P';
    else rez[index++] = 'Z';

    int polovina = (pravo - levo + 1) / 2;
    for (int i = 0; i < polovina; i++) {
        char ozhidaemyy;
        if (rebra[levo + i] == 'K') ozhidaemyy = 'O';
        else ozhidaemyy = 'K';

        if (rebra[seredina + 1 + i] != ozhidaemyy) return false;
    }

    return vosstanovit(rebra, levo, seredina - 1, rez, index, obem);
}

void zadanieB() {
    cout << "\n--- Способ Б ---" << endl;
    cout << "Введите последовательность рёбер (O/K): ";
    cin.ignore();
    char* rebra = vvodStroki();

    int dlina = 0;
    while (rebra[dlina] != '\0') dlina++;

    int proverka = dlina + 1;
    if (proverka <= 0 || (proverka & (proverka - 1)) != 0) {
        cout << "Такой последовательности не существует" << endl;
        delete[] rebra;
        return;
    }

    int obem = 10;
    char* rezultat = new char[obem];
    int index = 0;

    if (vosstanovit(rebra, 0, dlina - 1, rezultat, index, obem)) {
        for (int i = 0; i < index / 2; i++) {
            char temp = rezultat[i];
            rezultat[i] = rezultat[index - 1 - i];
            rezultat[index - 1 - i] = temp;
        }
        rezultat[index] = '\0';
        cout << "Последовательность сгибаний: " << rezultat << endl;
    } else {
        cout << "Такой последовательности не существует" << endl;
    }

    delete[] rebra;
    delete[] rezultat;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int vibor;
    cout << "------ Выберите способ: ------" << endl;
    cout << "1 - Способ А" << endl;
    cout << "2 - Способ Б" << endl;
    cout << "Выбран: ";
    cin >> vibor;

    if (vibor == 1) zadanieA();
    else if (vibor == 2) zadanieB();
    else cout << "Нету такого способа" << endl;

    return 0;
}

#include <iostream>
#include "windows.h"
#include <stdio.h>
#include <thread>
#include <math.h>



using namespace std;
using namespace chrono;

void setCursorPosition(int x, int y)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}
// фукция заполнения
void fill(int* (p), int* (e), const int DEGREE) {
    int hight = 0, count = 0, countD = 0, color = 14;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << endl;
    while (true && p <= e + DEGREE - 1) {

        if (p > e - DEGREE * DEGREE / 2 + DEGREE) {
            if (p == e - DEGREE * DEGREE + DEGREE + (DEGREE / 2 - 1) + (DEGREE / 2) * countD) {

                if (color == 3) color = 13; else color = 3;
                count++;
                countD++;
            }
            else {
                SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | color));
                count = -1;
            }
        }
        else if (p == e - DEGREE * DEGREE / 2 + DEGREE) { color = 3; SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | color)); }
        else {
            if (p == e - DEGREE * DEGREE + DEGREE + (DEGREE / 2 - 1) + (DEGREE / 2) * countD) {


                if (color == 14) color = 7; else color = 14;
                count++;
                countD++;
            }
            else {
                SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | color));
                count = -1;
            }
        }

        if (p != e - DEGREE * DEGREE + DEGREE * 2 - 1 + hight) {

            cout << *p << "\t";
            p += 1;
        }
        else {

            cout << *p << "\t";
            p += 1;
            hight += DEGREE;
            cout << endl;
        }
        count++;
    }
    SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
}
// способ заполнения
void shellFill(int* (p), int* (e), int* (pp), int* (ee), const int DEGREE) {
    int count = 0, * border = e + DEGREE - 1, * d = p, step = DEGREE - 1;

    while (p <= e + DEGREE - 1) {

        *p = 0;
        p += 1;
    }
    p -= DEGREE * DEGREE;

    while (true) {
        system("cls");
        while (p != e - DEGREE * DEGREE / 2 + DEGREE + DEGREE / 2 - 1) {

            if (p == e - DEGREE * (DEGREE - 1) + DEGREE * count + step || p == e + step) {

                *p = abs(1 + rand() % (DEGREE * DEGREE));
                *pp = *p;
                if (p == border) {

                    if (step / abs(step) != 1) {
                        // после прохода вверх
                        count += 1;
                        border = e - count * DEGREE + (DEGREE - count - 1);
                        step = DEGREE - (count + 1);
                        p += 1;
                        pp++;

                    }
                    else {
                        // после прохода вниз
                        if (count == 0) {
                            border = e - DEGREE * (DEGREE - 2);
                        }
                        else {
                            border = e - DEGREE * (DEGREE - 2) + DEGREE * count + count;
                        }

                        p -= 1;
                        pp--;
                        if (step == 35) step = 0; else step = 0 - DEGREE * count + count;
                    }
                }
                else {
                    // Подъем
                    if (step == 0 || step / abs(step) != 1) {

                        step -= DEGREE;
                        p -= DEGREE;
                        pp -= DEGREE;
                    }
                    //Спуск
                    else {

                        step += DEGREE;
                        p += DEGREE;
                        pp += DEGREE;
                    }
                }
            }

            else if (p < e - DEGREE * DEGREE / 2 + DEGREE + DEGREE / 2 - 1) {

                *p = abs(1 + rand() % (DEGREE * DEGREE));
                *pp = *p;
                p += 1;
                pp++;

            }
            else if (p > e - DEGREE * DEGREE / 2 + DEGREE + DEGREE / 2 - 1) {

                *p = abs(1 + rand() % (DEGREE * DEGREE));
                *pp = *p;
                p -= 1;
                pp--;
            }
            fill(d, e, DEGREE);
            Sleep(50);
            setCursorPosition(0, 0);
            if (p == e - DEGREE * DEGREE / 2 + DEGREE + DEGREE / 2 - 1) {
                *p = abs(1 + rand() % (DEGREE * DEGREE));
                *pp = *p;
            }
        }
        fill(d, e, DEGREE);
        break;
    }

}
void snakeFill(int* (p), int* (e), int* (pp), int* (ee), const int DEGREE) {
    int count = 0, * border = e, * d = p, step = DEGREE;

    while (p <= e + DEGREE - 1) {

        *p = 0;
        p += 1;
    }
    p -= DEGREE * DEGREE;

    while (true) {
        system("cls");
        while (p != d + DEGREE - 1) {
            if (step / abs(step) == 1) {
                if (p != border) {
                    *p = abs(1 + rand() % (DEGREE * DEGREE));
                    *pp = *p;
                    p += step;  // сложение
                    pp += step;
                }
                else {
                    *p = abs(1 + rand() % (DEGREE * DEGREE)); // нижняя прорисовка
                    *pp = *p;
                    count += 1;
                    border = d + count;
                    step = -DEGREE;
                    pp++;
                    p += 1;
                }
            }
            else {
                if (p != border) {
                    *p = abs(1 + rand() % (DEGREE * DEGREE));
                    *pp = *p;
                    pp += step;
                    p += step; // вычитание
                }
                else {
                    *p = abs(1 + rand() % (DEGREE * DEGREE)); // верхяя прорисовка
                    *pp = *p;
                    count += 1;
                    border = e + count;
                    step = DEGREE;
                    pp++;
                    p += 1;
                }
            }

            fill(d, e, DEGREE);
            Sleep(50);
            setCursorPosition(0, 0);
        }
        *p = abs(1 + rand() % (DEGREE * DEGREE));
        *pp = *p;
        fill(d, e, DEGREE);
        break;
    }
}
// способ замены
void clockWise(const int DEGREE, int* p, int* e, int* pp, int* ee) {
    int* dd = pp, * d = p, * border = e - DEGREE * DEGREE / 2 + DEGREE / 2 - 1;
    int count = 0, circle = 1;

    pp = dd + DEGREE / 2;

    while (true) {

        while (circle != 0) {

            if (count != DEGREE / 2 - 1) {

                *pp = *p;
                pp++;
                p++;
                count++;
            }
            else {
                *pp = *p;
                if (p != border) {

                    count = 0;
                    pp += DEGREE / 2 + 1;
                    p += DEGREE / 2 + 1;
                }
                else {

                    if (circle == 1) {
                        // из первого во второй
                        *pp = *p;
                        border += DEGREE / 2;
                        p = d + DEGREE / 2;
                        pp = dd + DEGREE * DEGREE / 2 + DEGREE / 2;
                        circle++;
                        count = 0;
                    }
                    else if (circle == 2) {
                        // из второго в четвертый
                        *pp = *p;
                        border += DEGREE * DEGREE / 2;
                        p = d + DEGREE * DEGREE / 2 + DEGREE / 2;
                        pp = dd + DEGREE * DEGREE / 2;
                        circle++;
                        count = 0;
                    }
                    else if (circle == 3) {
                        // из четвертого в третий
                        *pp = *p;
                        border -= DEGREE / 2;
                        p = d + DEGREE * DEGREE / 2;
                        pp = dd;
                        circle++;
                        count = 0;
                    }
                    else {
                        // из третьего в первый
                        *pp = *p;
                        border -= DEGREE * DEGREE / 2;
                        p = d;
                        pp = dd + DEGREE / 2;
                        circle = 0;
                        count = 0;
                    }
                }
            }
        }
        pp = dd;
        p = d;
        while (pp <= ee) {
            *p = *pp;
            pp++;
            p++;
        }
        fill(dd, ee, DEGREE);
        break;
    }
}
void crissCross(const int DEGREE, int* p, int* e, int* pp, int* ee) {
    int* dd = pp, * d = p, * border = e - DEGREE * DEGREE / 2 + DEGREE / 2 - 1;
    int count = 0, circle = 1;

    pp = dd + DEGREE * DEGREE / 2 + DEGREE / 2;

    while (true) {

        while (circle != 0) {

            if (count != DEGREE / 2 - 1) {

                *pp = *p;
                pp++;
                p++;
                count++;
            }
            else {
                *pp = *p;
                if (p != border) {

                    count = 0;
                    pp += DEGREE / 2 + 1;
                    p += DEGREE / 2 + 1;
                }
                else {

                    if (circle == 1) {
                        // из второго в третий
                        *pp = *p;
                        border += DEGREE / 2;
                        p = d + DEGREE / 2;
                        pp = dd + DEGREE * DEGREE / 2;
                        circle++;
                        count = 0;
                    }
                    else if (circle == 2) {
                        // из третьего во второй
                        *pp = *p;
                        border = d + DEGREE * DEGREE - DEGREE / 2 - 1;
                        p = d + DEGREE * DEGREE / 2;
                        pp = dd + DEGREE / 2;
                        circle++;
                        count = 0;
                    }
                    else if (circle == 3) {
                        // из четвертого в первый
                        *pp = *p;
                        border += DEGREE / 2;
                        p = d + DEGREE * DEGREE / 2 + DEGREE / 2;
                        pp = dd;
                        circle++;
                        count = 0;

                    }
                    else { circle = 0; }
                }
            }
        }
        pp = dd;
        p = d;
        while (pp <= ee) {
            *p = *pp;
            pp++;
            p++;
        }
        fill(dd, ee, DEGREE);
        break;
    }
}
void verticaSwap(const int DEGREE, int* p, int* e, int* pp, int* ee) {
    int* dd = pp, * d = p, * border = e - DEGREE * DEGREE / 2 + DEGREE / 2 - 1;
    int count = 0, circle = 1;

    pp = dd + DEGREE * DEGREE / 2;

    while (true) {

        while (circle != 0) {

            if (count != DEGREE / 2 - 1) {

                *pp = *p;
                pp++;
                p++;
                count++;
            }
            else {
                *pp = *p;
                if (p != border) {

                    count = 0;
                    pp += DEGREE / 2 + 1;
                    p += DEGREE / 2 + 1;
                }
                else {

                    if (circle == 1) {
                        // из второго в четвертый
                        *pp = *p;
                        border += DEGREE / 2;
                        p = d + DEGREE / 2;
                        pp = dd + DEGREE * DEGREE / 2 + DEGREE / 2;
                        circle++;
                        count = 0;
                    }
                    else if (circle == 2) {
                        // из третьего в первый
                        *pp = *p;
                        border = e + DEGREE / 2 - 1;
                        p = d + DEGREE * DEGREE / 2;
                        pp = dd;
                        circle++;
                        count = 0;
                    }
                    else if (circle == 3) {
                        // из четвертого в первый
                        *pp = *p;
                        border += DEGREE / 2;
                        p = d + DEGREE * DEGREE / 2 + DEGREE / 2;
                        pp = dd + DEGREE / 2;
                        circle++;
                        count = 0;

                    }
                    else { circle = 0; }
                }
            }
        }
        pp = dd;
        p = d;
        while (pp <= ee) {
            *p = *pp;
            pp++;
            p++;
        }
        fill(dd, ee, DEGREE);
        break;
    }


}
void horizontalSwap(const int DEGREE, int* p, int* e, int* pp, int* ee) {
    int* dd = pp, * d = p, * border = d + DEGREE * DEGREE / 2 - DEGREE / 2 - 1;
    int count = 0, circle = 1;

    pp = dd + DEGREE / 2;

    while (true) {

        while (circle != 0) {

            if (count != DEGREE / 2 - 1) {

                *pp = *p;
                pp++;
                p++;
                count++;
            }
            else {
                *pp = *p;
                if (p != border) {

                    count = 0;
                    pp += DEGREE / 2 + 1;
                    p += DEGREE / 2 + 1;
                }
                else {

                    if (circle == 1) {
                        // из второго в первый
                        *pp = *p;
                        border += DEGREE / 2;
                        p = d + DEGREE / 2;
                        pp = dd;
                        circle++;
                        count = 0;
                    }
                    else if (circle == 2) {
                        // из третьего в четвертый
                        *pp = *p;
                        border = e + DEGREE / 2 - 1;
                        p = d + DEGREE * DEGREE / 2;
                        pp = dd + DEGREE * DEGREE / 2 + DEGREE / 2;
                        circle++;
                        count = 0;
                    }
                    else if (circle == 3) {
                        // из четвертого в третий
                        *pp = *p;
                        border += DEGREE / 2;
                        p = d + DEGREE * DEGREE / 2 + DEGREE / 2;
                        pp = dd + DEGREE * DEGREE / 2;
                        circle++;
                        count = 0;
                    }
                    else { circle = 0; }
                }
            }
        }
        pp = dd;
        p = d;
        while (pp <= ee) {
            *p = *pp;
            pp++;
            p++;
        }
        fill(dd, ee, DEGREE);
        break;
    }
}
// сортировка, операции и 
void insertSort(int* p, int* e, const int DEGREE, int* pp) {
    int arr[10] = { 13, 35, 89, 1, 1, 1, 1, 1, 1, 1};
    int* d = p, * ee = e;
    for (p; p <= d + DEGREE * DEGREE - 1; p++) {
        for (ee = p; ee > d; ee--) {
            if (*ee < *(ee - 1)) swap(*ee, *(ee - 1));
        }
    }
    p = d;
    while (p <= e) {
        *pp = *p;
        pp++;
        p++;
    }
    fill(d, e, DEGREE);
}
void calculator(int* p, int* e, int* pp, int* ee) {
    char action;
    int numb, * d = p;
    cout << "Выберите опаерацию (+, -, *, /)\n" << endl;
    cin >> action;
    cout << "Введите число\n" << endl;
    cin >> numb;
    while (p <= e) {
        switch (action) {
        case  '+': {
            *p += numb;
            break;
        }
        case  '-': {
            *p -= numb;
            break;
        }
        case  '*': {
            *p *= numb;
            break;
        }
        case  '/': {
            *p /= numb;
            break;
        }
        }
        p++;
    }
    p = d;
    while (p <= e) {
        *pp = *p;
        pp++;
        p++;
    }
}
void transpose(const int DEGREE, int* p, int* e, int* pp, int* ee) {
    int* d = p + DEGREE, * border = p + DEGREE - 1, * start = p;
    int count = 2;
    p += 1;
    while (p <= e - 1) {
        if (p != border) {
            swap(*d, *p);
            p++;
            d += DEGREE;
        }
        else {
            swap(*d, *p);
            count += 1;
            border += DEGREE;
            p += count;
            d += 1 - DEGREE * DEGREE + DEGREE + DEGREE * (count - 1);
        }



    }
    p = start;
    while (p <= e) {
        *pp = *p;
        pp++;
        p++;
    }
    fill(start, e, DEGREE);

}
int selectOption(int option, int deep, int* p, int* e, int* pp, int* ee, int degree) {
    auto coutDegree = "\nСоздать массив и отобразить его ввиде квадратичной матрицы\n1. Из 6^2 элементов\n2. Из 8^2 элементов\n3. Из 10^2 элементов\n\n";
    auto coutFill = "\n1. Заполнить Ракушкой\n2. Заполнить змейкой\n";
    auto coutSwap = "\n1. Замена по часовой стрелке\n2. Замена крест-накрест\n3. Вертикальная замена\n4. Горизонтальная замена\n5. Отсортировать\n6. Операция над элементами массива\n7. Транспонировать\n";

    switch (option) {
    case 1: {
        if (deep == 1) {
            // степень матрицы
            int arrF[6][6], arrS[6][6], option, degree = 6;
            int* p = arrF[0], * e = arrF[5];
            int* pp = arrS[0], * ee = arrS[5];
            cout << coutFill << "\nВыберите действие\n" << endl;
            cin >> option;
            selectOption(option, 2, p, e, pp, ee, degree);
        }
        // метод заполнения
        else if (deep == 2) {
            shellFill(p, e, pp, ee, degree);
            cout << coutSwap << "\nВыберите действие\n" << endl;
            cin >> option;
            selectOption(option, 3, p, e, pp, ee, degree);
        }
        else if (deep == 3) {
            clockWise(degree, p, e, pp, ee);
            cout << "\n1. Отсортировать\n2. Пересоздать массив\n3. Операция над элементами массива\n4. Транспонировать\n" << endl;
            cin >> option;
            selectOption(option, 4, p, e, pp, ee, degree);
        }
        else if (deep == 4) {
            insertSort(p, e, degree, pp);
            cout << coutSwap << "\nВыберите действие\n" << endl;
            cin >> option;
            selectOption(option, 3, p, e, pp, ee, degree);
        }
        break;
    }
    case 2: {
        if (deep == 1) {
            int arrF[8][8], arrS[8][8], option, degree = 8;
            int* p = arrF[0], * e = arrF[8 - 1];
            int* pp = arrS[0], * ee = arrS[7];
            cout << coutFill << "\nВыберите действие\n" << endl;
            cin >> option;
            selectOption(option, 2, p, e, pp, ee, degree);
        }
        else if (deep == 2) {
            snakeFill(p, e, pp, ee, degree);
            cout << coutSwap << "\nВыберите действие\n" << endl;
            cin >> option;
            selectOption(option, 3, p, e, pp, ee, degree);
        }
        else if (deep == 3) {
            crissCross(degree, p, e, pp, ee);
            cout << "\n1. Отсортировать\n2. Пересоздать массив\n3. Операция над элементами массива\n4. Транспонировать\n" << endl;
            cin >> option;
            selectOption(option, 4, p, e, pp, ee, degree);
        }
        else if (deep == 4) {
            cout << coutDegree << "\nВыберите действие\n" << endl;
            cin >> option;
            selectOption(option, 1, 0, 0, 0, 0, 0);
        }
        break;
    }
    case 3: {
        if (deep == 1) {
            int arrF[10][10], arrS[10][10], option, degree = 10;
            int* p = arrF[0], * e = arrF[10 - 1];
            int* pp = arrS[0], * ee = arrS[9];
            cout << coutFill << "\nВыберите действие\n" << endl;
            cin >> option;
            selectOption(option, 2, p, e, pp, ee, degree);
        }
        else if (deep == 3) {
            verticaSwap(degree, p, e, pp, ee);
            cout << "\n1. Отсортировать\n2. Пересоздать массив\n3. Операция над элементами массива\n4. Транспонировать\n" << endl;
            cin >> option;
            selectOption(option, 4, p, e, pp, ee, degree);
        }
        else if (deep == 4) {
            calculator(pp, (ee + degree - 1), p, (e + degree - 1));
            fill(pp, ee, degree);
            cout << coutSwap << endl;
            cin >> option;
            selectOption(option, 3, p, e, pp, ee, degree);
        }

        break;
    }
    case 4: {
        if (deep == 3) {
            horizontalSwap(degree, p, e, pp, ee);
            cout << "\n1. Отсортировать\n2. Пересоздать массив\n3. Операция над элементами массива\n4. Транспонировать\n" << endl;
            cin >> option;
            selectOption(option, 4, p, e, pp, ee, degree);
        }
        if (deep == 4) {
            transpose(degree, pp, ee, p, e);
            cout << "\n1. Отсортировать\n2. Пересоздать массив\n3. Операция над элементами массива\n4. Транспонировать\n" << endl;
            cin >> option;
            selectOption(option, 4, p, e, pp, ee, degree);
        }
    }
    case 5: {
        insertSort(p, e, degree, pp);
        cout << coutSwap << endl;
        cin >> option;
        selectOption(option, 3, p, e, pp, ee, degree);
    }
    case 6: {
        calculator(p, (e + degree - 1), pp, (ee + degree - 1));
        fill(p, e, degree);
        cout << coutSwap << endl;
        cin >> option;
        selectOption(option, 3, p, e, pp, ee, degree);
    }
    case 7: {
        transpose(degree, p, e, pp, ee);
        cout << "\n1. Отсортировать\n2. Пересоздать массив\n3. Операция над элементами массива\n4. Транспонировать\n" << endl;
        cin >> option;
        selectOption(option, 4, p, e, pp, ee, degree);
    }
    }
    return 0;
}





int arr[10], reserve, deep = 0, state = false;
void arrShow() {
    cout << endl;
    for (int i = 0; i <= sizeof(arr) / sizeof(arr[0]) - 1; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n" << endl;
}
void filler() {
    // Заполнение массива
    cout << "\nВаш массив";
    for (int i = 0; i <= sizeof(arr) / sizeof(arr[0]) - 1; i++) {
        if (1 + rand() % 2 == 2) {
            arr[i] = -1 * (rand() % 100);
        }
        else arr[i] = rand() % 100;
    }
    arrShow();
}
// false - неотсортированный true-остортированный
void minMaxSearch(bool state) {
    float minimum = 100, maximum = -100, average;
    // Начало поиска минимумов и максимумов в массиве
    auto start = high_resolution_clock::now();
    for (int i = 0; i <= sizeof(arr) / sizeof(arr[0]) - 1; i++) {
        if (arr[i] > maximum) {
            maximum = arr[i];
        }
        if (arr[i] < minimum) {
            minimum = arr[i];
        }
    }
    // Конец поиска минимумов и максимумов в массиве
    auto end = high_resolution_clock::now();
    if (state) {
        // Вывод времени поиска минимумов и максимумов в массиве
        cout << "Поиск максимумов и минимумов в отсортированном массиве шел: " << duration_cast<nanoseconds>(end - start).count() << " наносекунд" << "\n"
            << "минимум: " << minimum << "\n"
            << "максимум: " << maximum << "\n" << endl;
    }
    else {
        // Вывод времени поиска минимумов и максимумов в неотсортированном массиве
        cout << "Поиск максимумов и минимумов в неотсортированном массиве шел: " << duration_cast<nanoseconds>(end - start).count() << " наносекунд" << "\n"
            << "минимум: " << minimum << "\n"
            << "максимум: " << maximum << "\n" << endl;
    }

    // Вывод среднего значения минимума и максимума
    average = round((minimum + maximum) / 2);
    cout << "Среднее значение: " << average << "\n" << endl;
}
void quanityA() {
    int c = 0, a;
    cout << "\nВведте первое число" << "\n" << endl;
    cin >> a;
    // Вывод количества элементов равных инициализированному числу a
    cout << "\nиндексы элементов, больше инициализированного числа " << a << ": ";
    for (int i = 0; i <= sizeof(arr) / sizeof(arr[0]) - 1; i++) {
        if (arr[i] > a) {
            cout << i << " индекс ";
            c++;
        }
    }
    cout << "\n\nколичество элементов в массиве, равных инициализированному числу " << a << ": " << c << "\n" << endl;
}
void quanityB() {
    int c = 0, b;
    cout << "Введте второе число" << "\n" << endl;
    cin >> b;
    // Вывод количества элементов равных инициализированному числу b
    cout << "индексы элементов, меньше инициализированного числа " << b << " ";
    for (int i = 0; i <= sizeof(arr) / sizeof(arr[0]) - 1; i++) {
        if (arr[i] < b) {
            cout << i << " индекс ";
            c++;
        }
    }
    cout << "\n\nколичество элементов в массиве, равных инициализированному числу " << b << ": " << c << "\n" << endl;
}
int binarySearch() {
    int reserve;
    cout << "Введите число для поиска\n";
    cin >> reserve;
    int size = sizeof(arr) / sizeof(arr[0]);
    int low = 0, hight = size - 1;
    while (low <= hight) {
        int mid = (low + hight) / 2;

        if (reserve == arr[mid]) {
            cout << "идекс нужно числа " << mid << endl;
            return 0;
        }
        else if (reserve > arr[mid]) {
            low = mid + 1;
        }
        else hight = mid - 1;
    }
    return 0;
}
int defaultSearch() {
    int reserve;
    cout << "Введите число для поиска\n";
    cin >> reserve;
    for (int i = 0; i <= sizeof(arr) / sizeof(arr[0]) - 1; i++) {
        if (arr[i] == reserve) {
            cout << "идекс нужно числа " << i << endl;
            return 0;
        }
    }

    return 0;
}
void numbReplace(int indexF, int indexS) {
    int space;
    space = arr[indexF];
    arr[indexF] = arr[indexS];
    arr[indexS] = space;
}
void task() {
    const int size = sizeof(arr) / sizeof(arr[0]);
    int j = size / 2;
    int arrF[size / 2], arrS[size / 2 + 1], i = 0;

    //разделеие массива
    {
        do {
            arrF[i] = arr[i];
            arrS[i] = arr[j];
            i += 1;
            j += 1;
        } while (i < size / 2);

        if (size % 2 == 1) {
            arrS[i + 1] = arr[j];
        }
    }
    //результат разделеия
    {
        cout << "\nЛевая часть\n";
        for (i = 0; i <= size / 2 - 1; i++) {
            cout << arrF[i] << " ";
        }
        cout << "\n" << endl;

        cout << "\nПравая часть\n";
        for (i = 0; i <= size / 2 - 1; i++) {
            cout << arrS[i] << " ";
        }

        if (size % 2 == 1) {
            cout << arrS[i + 1] << " ";
        }
        cout << "\n" << endl;
    }
    //замена всех нечетных первого, четными второго массива
    {
        j = 0;
        i = 0;
        do {
            if (abs(arrF[i] % 2) == 1) {

                if (abs(arrS[j] % 2) == 0) {
                    swap(arrF[i], arrS[j]);
                    i += 1;
                    j += 1;
                }
                else j += 1;
            }
            else i += 1;

        } while (i <= size / 2 && j < size);
    }
    //результат замены
    {
        cout << "\nЛевая часть\n";
        for (i = 0; i <= size / 2 - 1; i++) {
            cout << arrF[i] << " ";
        }
        cout << "\n" << endl;

        cout << "\nПравая часть\n";
        for (i = 0; i <= size / 2 - 1; i++) {
            cout << arrS[i] << " ";
        }

        if (size % 2 == 1) {
            cout << arrS[i + 1] << " ";
        }
        cout << "\n" << endl;
    }
    //преобразовани всех нечетных второго массива в четные
    {
        for (i = 0; i < size / 2; i++) {
            if (arrS[i] % 2 == 1) arrS[i] += 1;
        }
    }
    //результат преобразования
    {
        cout << "\nЛевая часть\n";
        for (i = 0; i <= size / 2 - 1; i++) {
            cout << arrF[i] << " ";
        }
        cout << "\n" << endl;

        cout << "\nПравая часть\n";
        for (i = 0; i <= size / 2 - 1; i++) {
            cout << arrS[i] << " ";
        }

        if (size % 2 == 1) {
            cout << arrS[i + 1] << " ";
        }
        cout << "\n" << endl;
    }
    //попарное сравнение значений двух массивов 
    {
        int quantityF = 0;
        int quantityS = 0;
        i = 0;
        do {
            if (arrF[i] > arrS[i]) {
                quantityF += 1;
            }
            if (arrF[i] < arrS[i]) {
                quantityS += 1;
            }
            i += 1;
        } while (i < size / 2);

        cout << "Количество значений первого массива больше второго: " << quantityF << endl;
        cout << "Количество значений второго массива больше первого: " << quantityS << endl;
    }

}
// Сортировки
void bubbleSort() {
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]) - 1; i++) {
        for (int j = 0; j < sizeof(arr) / sizeof(arr[0]) - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                reserve = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = reserve;
            }
        }
    }
}
void shakerSort() {
    int count = 2;
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]) - count + 1; i++) {
        for (int j = count - 2; j < sizeof(arr) / sizeof(arr[0]) - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                reserve = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = reserve;
            }
        }
        for (int j = sizeof(arr) / sizeof(arr[0]) - i - 2; j >= i + 1; j--) {
            if (arr[j] < arr[j - 1]) {
                reserve = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = reserve;
            }
        }
        count++;
    }
}
void insertSort() {
    for (int i = 1; i < sizeof(arr) / sizeof(arr[0]); i++) {
        for (int j = i; j > 0; j--) {
            if (arr[j] < arr[j - 1]) {
                reserve = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = reserve;
            }
        }
    }
}
void quickSort(int* arr, int size) {
    //Указатели в начало и в конец массива
    int i = 0;
    int j = size - 1;

    //Центральный элемент массива
    int mid = arr[size / 2];

    //Делим массив
    do {
        //Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
        //В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
        while (arr[i] < mid) {
            i++;
        }
        //В правой части пропускаем элементы, которые больше центрального
        while (arr[j] > mid) {
            j--;
        }

        //Меняем элементы местами
        if (i <= j) {
            int reserve = arr[i];
            arr[i] = arr[j];
            arr[j] = reserve;

            i++;
            j--;
        }
    } while (i <= j);


    //Рекурсивные вызовы, если осталось, что сортировать
    if (j > 0) {
        //"Левый кусок"
        quickSort(arr, j + 1);
    }
    if (i < size) {
        //"Првый кусок"
        quickSort(&arr[i], size - i);
    }
    state = true;
}
void combSort() {
    int step = sizeof(arr) / sizeof(arr[0]) - 1, count = 0, reserve;
    while (step >= 2 || (step > 1 || count > 0)) {
        count = 0;
        for (int i = 0; i + step < sizeof(arr) / sizeof(arr[0]); i++) {
            if (arr[i] > arr[step + i]) {
                reserve = arr[i];
                arr[i] = arr[step + i];
                arr[step + i] = reserve;
                count++;
            }
        }
        if (step > 1) step = ceil(step - 1.247);
    }
}
void shellSort(int* arr, int size) {
    double step = ceil(size / 2);
    do {
        if (step <= 2) {
            if (step == 1) {
                int i = step, j = step;

                while (i < size) {
                    if (arr[j] < arr[j - 1]) {
                        swap(arr[j], arr[j - 1]);
                        j -= 1;
                    }
                    if (j == 0 || (arr[j] >= arr[j - 1])) {
                        i++;
                        j = i;
                    }
                }
            }
            else if (step == 2) {
                int i = step, j = step;
                while (i < size) {
                    if (arr[j] < arr[j - 2]) {
                        swap(arr[j], arr[j - 2]);
                        j -= 2;
                    }
                    if (j == 0 || (arr[j] >= arr[j - 2])) {
                        i += 2;
                        j = i;
                    }

                }

                i = step + 1;
                j = i;

                while (i < size) {
                    if (arr[j] < arr[j - 2]) {
                        swap(arr[j], arr[j - 2]);
                        j -= 2;
                    }
                    if (j == 1 || (arr[j] >= arr[j - 2])) {
                        i += 2;
                        j = i;
                    }
                }
            }
        }
        else {
            int i = 0, j = step;
            while (j < size) {
                if (arr[j] < arr[i]) swap(arr[i], arr[j]);
                i++;
                j++;
            }
        }
        if (step == 1) step = step / 2;
        else step = ceil(step / 2);
    } while (step >= 1);
}
int selectOptione(int option) {
    auto coutSort = "1. Пересоздать массив\n2. Отсортировать пузырьком\n3. Отсортировать шейкером\n4. Отсортировать вставками\n5. Отсортировать расческой\n6. Отсоритровать быстро\n7. Отсортировать сортировкой Шелла\n";
    auto coutBasic = "1. Пересоздать массив\n2. Отсортировать\n3. Найти минимум и максимум\n4. Найти кол-во элементов больше инициальзируемого\n5. Найти кол-во элементов меньше инициальзируемого\n6. Найти число перебором\n7. Найти число посредством бинарного поиска\n8. Поменять местами элементы массива\n9. Выполнить 3-е задание\n";
    switch (option) {
    case 1: {
        filler();
        deep = 1;
        cout << coutBasic;
        break;
    }
    case 2: {
        if (deep == 2) {
            auto start = high_resolution_clock::now();
            bubbleSort();
            auto end = high_resolution_clock::now();
            arrShow();
            cout << "\nСортировка пузырьком производилась: " << duration_cast<nanoseconds>(end - start).count() << " наносекунд" << "\n" << endl;
            state = true;
            deep = 0;
            cout << coutBasic;
        }
        else {
            deep = 2;
            cout << coutSort;
        }
        break;
    }
    case 3: {
        if (deep == 2) {
            auto start = high_resolution_clock::now();
            shakerSort();
            auto end = high_resolution_clock::now();
            arrShow();
            state = true;
            cout << "\nСортировка шейкером производилась: " << duration_cast<nanoseconds>(end - start).count() << " наносекунд" << "\n" << endl;
            deep = 0;
            cout << coutBasic;
        }
        else { minMaxSearch(state); deep = 0; cout << coutBasic; }
        break;
    }
    case 4: {
        if (deep == 2) {
            auto start = high_resolution_clock::now();
            insertSort();
            cout << coutBasic;
            auto end = high_resolution_clock::now();
            arrShow();
            state = true;
            cout << "\nСортировка вставками производилась: " << duration_cast<nanoseconds>(end - start).count() << " наносекунд" << "\n" << endl;
            deep = 0;
            cout << coutBasic;
        }
        else { quanityA(); cout << coutBasic; }
        break;
    }
    case 5: {
        if (deep == 2) {
            auto start = high_resolution_clock::now();
            combSort();
            auto end = high_resolution_clock::now();
            arrShow();
            state = true;
            cout << "\nСортировка расческой производилась: " << duration_cast<nanoseconds>(end - start).count() << " наносекунд" << "\n" << endl;
            deep = 0;
            cout << coutBasic;
        }
        else { quanityB(); cout << coutBasic; }
        break;
    }
    case 6: {
        if (deep == 2) {
            auto start = high_resolution_clock::now();
            quickSort(arr, sizeof(arr) / sizeof(arr[0]));
            auto end = high_resolution_clock::now();
            arrShow();
            state = true;
            cout << "\nБыстрая сортировка производилась: " << duration_cast<nanoseconds>(end - start).count() << " наносекунд" << "\n" << endl;
            deep = 0;
            cout << coutBasic;
        }
        else {
            auto start = high_resolution_clock::now();
            defaultSearch();
            auto end = high_resolution_clock::now();
            cout << "поиск производился " << duration_cast<nanoseconds>(end - start).count() << " наносекунд\n\n";
            cout << coutBasic;
            break;
        }
        break;
    }
    case 7: {
        if (deep == 2) {
            auto start = high_resolution_clock::now();
            shellSort(arr, sizeof(arr) / sizeof(arr[0]));
            auto end = high_resolution_clock::now();
            arrShow();
            state = true;
            cout << "\nСортировка Шелла производилась: " << duration_cast<nanoseconds>(end - start).count() << " наносекунд" << "\n" << endl;
            deep = 0;
            cout << coutBasic;
        }
        else {
            auto start = high_resolution_clock::now();
            binarySearch();
            auto end = high_resolution_clock::now();
            cout << "поиск производился " << duration_cast<nanoseconds>(end - start).count() << " наносекунд\n\n";
            cout << coutBasic;
            break;
        }
        break;
    }
    case 8: {
        int indexF, indexS;
        cout << "\nВведите перый индекс\n";
        cin >> indexF;
        cout << "\nВведите второй индекс\n";
        cin >> indexS;

        auto start = high_resolution_clock::now();
        numbReplace(indexF, indexS);
        auto end = high_resolution_clock::now();
        arrShow();
        cout << "\nЗамена заняла " << duration_cast<nanoseconds>(end - start).count() << " наносекунд\n\n";
        cout << coutBasic;
        break;
    }
    case 9: {
        task();
        break;
    }
    }
    return 0;
}

void taskTwo() {
    int arr[10], reserve, deep = 0, state = false;
    srand(time(0));
    cout << "\n1. Заполнить массив\n" << endl;
    do {
        int option;
        cout << "\nВыберите действие\n" << endl;
        cin >> option;
        selectOptione(option);
    } while (true);
}

void taskThree() {
    cout << "\nСоздать массив и отобразить его ввиде квадратичной матрицы\n1. Из 6^2 элементов\n2. Из 8^2 элементов\n3. Из 10^2 элементов\n\n" << endl;
    do {
        int option;
        cout << "\nВыберите действие\n" << endl;
        cin >> option;
        selectOption(option, 1, 0, 0, 0, 0, 0);
    } while (true);
}
void mainOption(int option) {
    switch (option) {
    case 1: {
        taskTwo();
    }
    case 2: {
        taskThree();
    }
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int option;
    cout << "Выберите задание\n\n1. Task 2\n2. Task 3\n";
    cin >> option;
    mainOption(option);
    return 0;
}

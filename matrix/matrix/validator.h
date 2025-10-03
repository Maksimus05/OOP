#pragma once
#include <iostream>
#include <string>
#include <limits>
using namespace std;

class Validator {
public:
    // Валидация скорости
    static bool validateVelocity(int velocity) {
        return velocity > 0 && velocity <= 30;
    }

    // Валидация длины
    static bool validateLength(int length) {
        return length > 0 && length <= 30;
    }

    // Валидация режима эпилепсии
    static bool validateEpilepsy(char epilepsy) {
        epilepsy = toupper(epilepsy);
        return epilepsy == 'Y' || epilepsy == 'N';
    }

    // Получить валидную скорость с защитой от дурака
    static int getValidVelocity() {
        int velocity;
        while (true) {
            cout << "Скорость линии 1-30 (символов в секунду) ";
            if (cin >> velocity && validateVelocity(velocity)) {
                return velocity;
            }
            cout << "Ошибка: скорость должна быть в диапазоне от 1 до 30.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Получить валидную длину с защитой от дурака
    static int getValidLength() {
        int length;
        while (true) {
            cout << "Длина линии 1-30 (символов) ";
            if (cin >> length && validateLength(length)) {
                return length;
            }
            cout << "Ошибка: длина должна быть в диапазоне от 1 до 30.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Получить валидный режим эпилепсии с защитой от дурака
    static bool getValidEpilepsy() {
        char epilepsy;
        while (true) {
            cout << "Режим эпилепсии Y/N (вкл/выкл) ";
            if (cin >> epilepsy && validateEpilepsy(epilepsy)) {
                return (toupper(epilepsy) == 'Y');
            }
            cout << "Ошибка: необходимо ввести букву Y/N\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Валидация всех аргументов командной строки
    static bool validateAllArguments(int velocity, int length, char epilepsy) {
        return validateVelocity(velocity) &&
            validateLength(length) &&
            validateEpilepsy(epilepsy);
    }
};
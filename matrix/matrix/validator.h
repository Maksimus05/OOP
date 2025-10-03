#pragma once
#include <iostream>
#include <string>
#include <limits>
using namespace std;

class Validator {
public:
    // ��������� ��������
    static bool validateVelocity(int velocity) {
        return velocity > 0 && velocity <= 30;
    }

    // ��������� �����
    static bool validateLength(int length) {
        return length > 0 && length <= 30;
    }

    // ��������� ������ ���������
    static bool validateEpilepsy(char epilepsy) {
        epilepsy = toupper(epilepsy);
        return epilepsy == 'Y' || epilepsy == 'N';
    }

    // �������� �������� �������� � ������� �� ������
    static int getValidVelocity() {
        int velocity;
        while (true) {
            cout << "�������� ����� 1-30 (�������� � �������) ";
            if (cin >> velocity && validateVelocity(velocity)) {
                return velocity;
            }
            cout << "������: �������� ������ ���� � ��������� �� 1 �� 30.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // �������� �������� ����� � ������� �� ������
    static int getValidLength() {
        int length;
        while (true) {
            cout << "����� ����� 1-30 (��������) ";
            if (cin >> length && validateLength(length)) {
                return length;
            }
            cout << "������: ����� ������ ���� � ��������� �� 1 �� 30.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // �������� �������� ����� ��������� � ������� �� ������
    static bool getValidEpilepsy() {
        char epilepsy;
        while (true) {
            cout << "����� ��������� Y/N (���/����) ";
            if (cin >> epilepsy && validateEpilepsy(epilepsy)) {
                return (toupper(epilepsy) == 'Y');
            }
            cout << "������: ���������� ������ ����� Y/N\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // ��������� ���� ���������� ��������� ������
    static bool validateAllArguments(int velocity, int length, char epilepsy) {
        return validateVelocity(velocity) &&
            validateLength(length) &&
            validateEpilepsy(epilepsy);
    }
};
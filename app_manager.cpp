#include "app_manager.h"

void app_manager::showHelp() {
    cout << "�������������: matrix.exe [�������� ����� �����_���������]" << endl;
    cout << "���������:" << endl;
    cout << "  ��������          �������� ����� 1-30 (�������� � �������)" << endl;
    cout << "  �����             ����� ����� 1-30 (��������)" << endl;
    cout << "  �����_���������   Y/N (���/����)" << endl;
    cout << endl;
    cout << "�������:" << endl;
    cout << "  matrix.exe 23 8 Y    - ������ � �����������" << endl;
    cout << "  matrix.exe --help    - �������� �������" << endl;
    cout << "  matrix.exe /?        - �������� �������" << endl;
    cout << "  matrix.exe           - ���������� �����" << endl;
}

int app_manager::generateY() {
    return rand() % (this->consoleHeight);
}

void app_manager::getArguments() {
    bool flagVel = false;
    bool flagLength = false;
    bool flagEpilepsy = false;

    // ���� ��������
    while (!flagVel) {
        cout << "�������� ����� 1-30 (�������� � �������) ";
        int velocity;
        try {
            cin >> velocity;
            if (cin.fail()) {
                throw invalid_argument("������: ������������ ����. ��������� ����� �����.");
            }
            if (velocity > 0 && velocity <= 30) {
                this->velocity = velocity;
                flagVel = true;
            }
            else {
                cout << "������: �������� ������ ���� � ��������� �� 1 �� 30.\n";
            }
        }
        catch (const invalid_argument& e) {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // ���� �����
    while (!flagLength) {
        cout << "����� ����� 1-30 (��������) ";
        int length;
        try {
            cin >> length;
            if (cin.fail()) {
                throw invalid_argument("������: ������������ ����. ��������� ����� �����.");
            }
            if (length > 0 && length <= 30) {
                this->length = length;
                flagLength = true;
            }
            else {
                cout << "������: ����� ������ ���� � ��������� �� 1 �� 30.\n";
            }
        }
        catch (const invalid_argument& e) {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // ���� ������ ���������
    while (!flagEpilepsy) {
        cout << "����� ��������� Y/N (���/����) ";
        char epilepsy;
        try {
            cin >> epilepsy;
            if (cin.fail()) {
                throw invalid_argument("������: ������������ ����.");
            }
            epilepsy = toupper(epilepsy);
            if (epilepsy == 'Y' || epilepsy == 'N') {
                this->epilepsy = (epilepsy == 'Y');
                flagEpilepsy = true;
            }
            else {
                cout << "������: ���������� ������ ����� Y/N \n";
            }
        }
        catch (const invalid_argument& e) {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void app_manager::startMove() {
    srand(static_cast<unsigned int>(time(nullptr)));
    bool flag = true;

    while (flag) {
        // �������� ����� ����� �� ���������� �����������
        myLine line(this->consoleWidth, generateY(), this->length, this->velocity, this->epilepsy);
        flag = line.moveLine();
    }
}

// ����������� ��� ����������� ������
app_manager::app_manager() {
    setlocale(0, "");
    winFunc functional;

    // ��������� ���������� �� ������������
    getArguments();

    // ��������� �������
    functional.cleanConsole();
    functional.changeCursor(); //�������� ������
    functional.setConsoleSize();

    // ��������� �������� �������
    this->consoleHeight = functional.getCsHeight();
    this->consoleWidth = functional.getCsWidth();

    // ������ ��������
    startMove();
}

// ����������� ��� ������ ��������� ������
app_manager::app_manager(int argc, char* argv[]) {
    setlocale(0, "");

    // �������� �� ������ �������
    if (argc == 2) {
        string arg = argv[1];
        if (arg == "--help" || arg == "/?") {
            showHelp();
            exit(0);
        }
    }

    // �������� ���������� ����������
    if (argc != 4) {
        cout << "������: �������� ���������� ����������." << endl;
        cout << "����������� matrix.exe --help ��� ��������� �������." << endl;
        exit(1);
    }

    try {
        // ������� ����������
        this->velocity = atoi(argv[1]);
        this->length = atoi(argv[2]);
        string epilepsyStr = argv[3];

        // ��������� ����������
        if (velocity < 1 || velocity > 30) {
            throw invalid_argument("�������� ������ ���� � ��������� 1-30");
        }
        if (length < 1 || length > 30) {
            throw invalid_argument("����� ������ ���� � ��������� 1-30");
        }
        if (epilepsyStr.length() != 1 || (toupper(epilepsyStr[0]) != 'Y' && toupper(epilepsyStr[0]) != 'N')) {
            throw invalid_argument("����� ��������� ������ ���� Y ��� N");
        }

        this->epilepsy = (toupper(epilepsyStr[0]) == 'Y');

    }
    catch (const exception& e) {
        cout << "������ � ����������: " << e.what() << endl;
        cout << "����������� matrix.exe --help ��� ��������� �������." << endl;
        exit(1);
    }

    winFunc functional;
    functional.cleanConsole();
    functional.changeCursor();
    functional.setConsoleSize();

    this->consoleHeight = functional.getCsHeight();
    this->consoleWidth = functional.getCsWidth();

    startMove();
}
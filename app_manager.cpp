#include "app_manager.h"

void app_manager::showHelp() {
    cout << "Использование: matrix.exe [СКОРОСТЬ ДЛИНА РЕЖИМ_ЭПИЛЕПСИИ]" << endl;
    cout << "Параметры:" << endl;
    cout << "  СКОРОСТЬ          Скорость линии 1-30 (символов в секунду)" << endl;
    cout << "  ДЛИНА             Длина линии 1-30 (символов)" << endl;
    cout << "  РЕЖИМ_ЭПИЛЕПСИИ   Y/N (вкл/выкл)" << endl;
    cout << endl;
    cout << "Примеры:" << endl;
    cout << "  matrix.exe 23 8 Y    - запуск с параметрами" << endl;
    cout << "  matrix.exe --help    - показать справку" << endl;
    cout << "  matrix.exe /?        - показать справку" << endl;
    cout << "  matrix.exe           - диалоговый режим" << endl;
}

int app_manager::generateY() {
    return rand() % (this->consoleHeight);
}

void app_manager::getArguments() {
    bool flagVel = false;
    bool flagLength = false;
    bool flagEpilepsy = false;

    // Ввод скорости
    while (!flagVel) {
        cout << "Скорость линии 1-30 (символов в секунду) ";
        int velocity;
        try {
            cin >> velocity;
            if (cin.fail()) {
                throw invalid_argument("Ошибка: некорректный ввод. Ожидалось целое число.");
            }
            if (velocity > 0 && velocity <= 30) {
                this->velocity = velocity;
                flagVel = true;
            }
            else {
                cout << "Ошибка: скорость должна быть в диапазоне от 1 до 30.\n";
            }
        }
        catch (const invalid_argument& e) {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Ввод длины
    while (!flagLength) {
        cout << "Длина линии 1-30 (символов) ";
        int length;
        try {
            cin >> length;
            if (cin.fail()) {
                throw invalid_argument("Ошибка: некорректный ввод. Ожидалось целое число.");
            }
            if (length > 0 && length <= 30) {
                this->length = length;
                flagLength = true;
            }
            else {
                cout << "Ошибка: длина должна быть в диапазоне от 1 до 30.\n";
            }
        }
        catch (const invalid_argument& e) {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Ввод режима эпилепсии
    while (!flagEpilepsy) {
        cout << "Режим эпилепсии Y/N (вкл/выкл) ";
        char epilepsy;
        try {
            cin >> epilepsy;
            if (cin.fail()) {
                throw invalid_argument("Ошибка: некорректный ввод.");
            }
            epilepsy = toupper(epilepsy);
            if (epilepsy == 'Y' || epilepsy == 'N') {
                this->epilepsy = (epilepsy == 'Y');
                flagEpilepsy = true;
            }
            else {
                cout << "Ошибка: необходимо ввести букву Y/N \n";
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
        // Создание новой линии со случайными параметрами
        myLine line(this->consoleWidth, generateY(), this->length, this->velocity, this->epilepsy);
        flag = line.moveLine();
    }
}

// Конструктор для диалогового режима
app_manager::app_manager() {
    setlocale(0, "");
    winFunc functional;

    // Получение параметров от пользователя
    getArguments();

    // Настройка консоли
    functional.cleanConsole();
    functional.changeCursor(); //спрятали курсор
    functional.setConsoleSize();

    // Получение размеров консоли
    this->consoleHeight = functional.getCsHeight();
    this->consoleWidth = functional.getCsWidth();

    // Запуск анимации
    startMove();
}

// Конструктор для режима командной строки
app_manager::app_manager(int argc, char* argv[]) {
    setlocale(0, "");

    // Проверка на запрос справки
    if (argc == 2) {
        string arg = argv[1];
        if (arg == "--help" || arg == "/?") {
            showHelp();
            exit(0);
        }
    }

    // Проверка количества аргументов
    if (argc != 4) {
        cout << "Ошибка: неверное количество аргументов." << endl;
        cout << "Используйте matrix.exe --help для получения справки." << endl;
        exit(1);
    }

    try {
        // Парсинг аргументов
        this->velocity = atoi(argv[1]);
        this->length = atoi(argv[2]);
        string epilepsyStr = argv[3];

        // Валидация параметров
        if (velocity < 1 || velocity > 30) {
            throw invalid_argument("Скорость должна быть в диапазоне 1-30");
        }
        if (length < 1 || length > 30) {
            throw invalid_argument("Длина должна быть в диапазоне 1-30");
        }
        if (epilepsyStr.length() != 1 || (toupper(epilepsyStr[0]) != 'Y' && toupper(epilepsyStr[0]) != 'N')) {
            throw invalid_argument("Режим эпилепсии должен быть Y или N");
        }

        this->epilepsy = (toupper(epilepsyStr[0]) == 'Y');

    }
    catch (const exception& e) {
        cout << "Ошибка в параметрах: " << e.what() << endl;
        cout << "Используйте matrix.exe --help для получения справки." << endl;
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
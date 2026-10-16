#include <iostream>
#include <math.h>
#include <string>
#include <format>
#include <windows.h>
#include <regex>
#include <chrono>

enum class ValidationError {
    None,
    EmptyInput,
    NegativeNum,
    InvalidChars,
    LeadingZeros,
    EmptyDot,
    NegativeZero,
    PositiveZero,
    FloatNum,
    NotInt
};

ValidationError validate(const std::string& input) {
    if (input.empty()) {
        return ValidationError::EmptyInput;
    }
    if (input.back() == '.' || input.back() == ',') {
        return ValidationError::EmptyDot;
    }
    if (input.find('.') != std::string::npos || input.find(',') != std::string::npos) {
        return ValidationError::FloatNum;
    }
    if (std::regex_match(input, std::regex(R"(^-\d+$)"))) {
        return ValidationError::NegativeNum;
    }
    if (!std::regex_match(input, std::regex(R"(^\d+$)"))) {
        return ValidationError::InvalidChars;
    }
    if (std::regex_match(input, std::regex(R"(^-0+$)"))) {
        return ValidationError::NegativeZero;
    }
    if (std::regex_match(input, std::regex(R"(^\+0+$)"))) {
        return ValidationError::PositiveZero;
    }
    if (std::regex_match(input, std::regex(R"(^0\d+$)"))) {
        return ValidationError::LeadingZeros;
    }
    if (!std::regex_match(input, std::regex(R"(^(0|[1-9]\d*)$)"))) {
        return ValidationError::InvalidChars;
    }
    try {
        int value = std::stoi(input);
        (void)value;
    }
    catch(const std::out_of_range& e) {
        return ValidationError::NotInt;
    }


    return ValidationError::None;
}

std::string returnValidation(const std::string& input) {
    switch (validate(input)) {
    case ValidationError::None:
        return "Valid";
    case ValidationError::EmptyInput:
        return "Введена пустая строка. Пожалуйста, не будьте динозавром и введите число в формате <положительное число>";
    case ValidationError::InvalidChars:
        return "Во вводе присутствуют буквы, специальные символы, пустые пробелы или ввод в целом некорректен.  Пожалуйста, не будьте динозавром и введите целое число в формате <положительное число>";
    case ValidationError::EmptyDot:
        return "Число не может оканчиваться на точку.  Пожалуйста, не будьте динозавром и введите целое число в формате <нположительное число>";
    case ValidationError::NegativeZero:
        return "Введен отрицательный ноль, это недопустимо.  Пожалуйста, не будьте динозавром и введите целое число в формате <положительное число>";
    case ValidationError::PositiveZero:
        return "Введен положительный ноль, это недопустимо.  Пожалуйста, не будьте динозавром и введите целое число в формате <положительное число>";
    case ValidationError::LeadingZeros:
        return "Введено число с ведущими нулями.  Пожалуйста, не будьте динозавром и введите целое число в формате положительное число>";
    case ValidationError::NotInt:
        return "Введенное число является слишком большим. Пожалуйста, введите число меньше.";
    case ValidationError::FloatNum:
        return "Введенное число не является целым. Пожалуйста, не будьте динозавром и введите целое число в формате <положительное число>";
    case ValidationError::NegativeNum:
        return "Введенное число является отрицательным. Пожалуйста, не будьте динозавром и введите целое число в формате <положительное число>";
    }
    return "Неизвестная ошибка. Поздравляю, вы динозавр";
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main()
{
    setlocale(LC_ALL, "ru");
    std::setlocale(LC_NUMERIC, "C");

    int N = 0;
    int M = 0;
    int S = 0;
    int mode = 1;
    std::string input;

    std::cin.clear();

    std::cout << std::format("{:=^80}", " ЛЯГУШКА.exe ") << std::endl;

    while (true)
    {

        std::cout << "Введите длину прыжка вверх N: ";

        if (!std::getline(std::cin, input)) {
            break;
        }

        std::string validResult = returnValidation(input);

        if (validResult != "Valid") {
            std::cout << validResult << std::endl << std::endl;
            continue;
        }

        N = std::stoi(input);
        break;
    }

    std::cin.clear();

    while (true)
    {

        std::cout << "Введите длину отскока M: ";

        if (!std::getline(std::cin, input)) {
            break;
        }

        std::string validResult = returnValidation(input);

        if (validResult != "Valid") {
            std::cout << validResult << std::endl << std::endl;
            continue;
        }

        M = std::stoi(input);
        if (M > N) {
            std::cout << "Длина отскока не должна превышать длину прыжка" << std::endl << std::endl;
        }
        else {
            break;
        }
    }

    std::cin.clear();

    while (true)
    {

        std::cout << "Выберите на какой ступеньке S остановиться: ";

        if (!std::getline(std::cin, input)) {
            break;
        }

        std::string validResult = returnValidation(input);

        if (validResult != "Valid") {
            std::cout << validResult << std::endl << std::endl;
            continue;
        }

        S = std::stoi(input);
        break;
    }

    while (true) {
        std::cout << "\nВыберите режим расчета:\n1. Пошагово\n2. Быстро\nВаш выбор: ";
        if (!std::getline(std::cin, input)) return 0;
        if (input == "1" || input == "2") {
            mode = std::stoi(input);
            break;
        }
        std::cout << "Неверный выбор. Введите 1 или 2.\n";
    }

    std::cout << std::endl;

    int c = 1;
    int stairNo = 0;
    bool _completed = false;

    auto start = std::chrono::high_resolution_clock::now();

    std::string reason;

    if (S == 0) {
        c = 0;
        _completed = true;
    }
    else if (N == M) {
        c = 0;
        _completed = false;
        reason = "Лягушка двигается на 0 ступенек за каждое действие.";
    }
    else
    {
        if (mode == 2) {
            int toGoal = S - N;
            int diff = N - M;
            c = 1 + std::ceil((double)toGoal / diff);
            _completed = true;
        }
        else {

            while (true) {
                c++;
                stairNo += (N - M);
                std::cout << std::format("Попытка {}: Лягушка прыгает на +{} вверх, соскальзывает на -{} вниз и приземляется на ступеньку {}.\n", c, N, M, stairNo) << std::endl;

                if (stairNo == S) {
                    _completed = true;
                    break;
                }
                else if (stairNo > S) {
                    reason = "Лягушка перепрыгнула указанную ступеньку.";
                    _completed = false;
                    break;
                }
            }
        }
    }


    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);


    std::string toInsert = _completed ? "ПОБЕДА" : "ПОРАЖЕНИЕ";
    std::string movesC = _completed ? std::to_string(c) : "Невозможно";

    if (!_completed) {
        std::cout << std::format("Остановиться на указанной ступеньке при заданных условиях невозможно. Причина: {}\n\n", reason);
    }

    std::cout << std::format("{:=^80}\n{:^80}\nЗаданные условия: Длина прыжка - {}, Отскок - {}, Номер ступеньки - {}\nПотребуется ходов: {}\nВремя вычисления: {} ms\n",
        " ИГРА ОКОНЧЕНА ", toInsert, N, M, S, movesC, duration.count());

    return 0;
}

//Глупая лягушка поднимается по лестнице. 
//Лягушка делает прыжок вверх на N ступенек, при этом у нее получается отскок от достигнутого результата на M ступенек вниз. 
//Сколько потребуется сделать прыжков лягушке, 
//чтобы остановится на ступеньке с номером S?
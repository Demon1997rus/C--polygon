#include <algorithm>
#include <bitset>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

// Функция проверки корректности числа в заданной системе счисления
bool isValidNumber(const string &num, int base)
{
    for (char c : num) {
        if (c == '-' || c == '+')
            continue;
        int val = (isdigit(c) ? c - '0' : toupper(c) - 'A' + 10);
        if (val < 0 || val >= base)
            return false;
    }
    return true;
}

// Функция перевода числа из заданной системы счисления в десятичную
int toDecimal(const string &num, int base)
{
    int result = 0;
    bool isNegative = num[0] == '-';
    size_t start = (isNegative || num[0] == '+') ? 1 : 0;

    for (size_t i = start; i < num.size(); ++i) {
        char c = toupper(num[i]);
        int digit = isdigit(c) ? c - '0' : c - 'A' + 10;
        result = result * base + digit;
    }

    return isNegative ? -result : result;
}

// Функция перевода числа из десятичной системы в заданную систему счисления
string fromDecimal(int num, int base)
{
    if (num == 0)
        return "0";

    bool isNegative = num < 0;
    num = abs(num);
    string result;

    while (num > 0) {
        int remainder = num % base;
        char digit = (remainder < 10) ? remainder + '0' : remainder - 10 + 'A';
        result += digit;
        num /= base;
    }

    if (isNegative)
        result += '-';
    reverse(result.begin(), result.end());
    return result;
}

// Функция формирования двоичного представления числа в виде прямого кода
string toDirectCode(int num)
{
    if (num == 0)
        return "0000"; // Для 0 минимальная ширина - 4 бита

    num = abs(num); // Работаем с модулем числа

    // Определение минимальной ширины для прямого кода
    int bitWidth = 4;
    if (num >= 8)
        bitWidth = 8;
    if (num >= 128)
        bitWidth = 16;
    if (num >= 32768)
        bitWidth = 32;

    // Генерация двоичной строки фиксированной ширины
    string binary = bitset<32>(num).to_string();
    binary = binary.substr(32 - bitWidth);

    return binary;
}

int main()
{
    try {
        // Ввод систем счисления
        int fromBase, toBase;
        cout << "Введите исходную систему счисления (2-16): ";
        cin >> fromBase;
        if (fromBase < 2 || fromBase > 16) {
            throw invalid_argument("Ошибка: Неверная исходная система счисления!");
        }

        cout << "Введите конечную систему счисления (2-16): ";
        cin >> toBase;
        if (toBase < 2 || toBase > 16) {
            throw invalid_argument("Ошибка: Неверная конечная система счисления!");
        }

        // Ввод числа
        string num;
        cout << "Введите число в исходной системе счисления: ";
        cin >> num;

        if (!isValidNumber(num, fromBase)) {
            throw invalid_argument("Ошибка: Введено некорректное число!");
        }

        // Перевод в десятичную систему
        int decimal = toDecimal(num, fromBase);

        // Перевод в целевую систему
        string result = fromDecimal(decimal, toBase);

        // Вывод результата
        cout << "Число в конечной системе счисления: " << result << endl;

        // Дополнительный вывод для двоичной системы (прямой код)
        if (toBase == 2) {
            cout << "Представление в виде прямого кода (ПК): " << toDirectCode(decimal) << endl;
        }
    } catch (const invalid_argument &e) {
        cerr << e.what() << endl;
    } catch (const exception &e) {
        cerr << "Ошибка: " << e.what() << endl;
    }

    return 0;
}

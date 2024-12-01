#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

// Функция для проверки корректности введенного числа
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

// Функция для перевода числа из любой системы счисления в десятичную (основание от 2 до 16)
int toDecimal(const string &num, int base)
{
    int result = 0;
    bool isNegative = num[0] == '-';
    int start = isNegative || num[0] == '+' ? 1 : 0;

    for (size_t i = start; i < num.size(); ++i) {
        char c = toupper(num[i]);
        int digit = isdigit(c) ? c - '0' : c - 'A' + 10;
        result = result * base + digit;
    }
    return isNegative ? -result : result;
}

// Функция для перевода числа из десятичной системы счисления в произвольную (основание от 2 до
// 16)
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

// Функция для вывода прямого кода
string toDirectCode(int num)
{
    if (num == 0)
        return "0000"; // Для 0 просто вернуть 4 бита

    bool isNegative = num < 0;
    num = abs(num);

    // Перевод числа в двоичную строку
    string binary = bitset<32>(num).to_string();

    // Сократить ведущие нули
    size_t firstOne = binary.find('1');
    binary = binary.substr(firstOne);

    // Приведение к кратной 4 длине
    while (binary.size() % 4 != 0) {
        binary = '0' + binary;
    }

    // Для отрицательных чисел возвращаем прямой код
    string directCode = (isNegative ? "ПК " : "") + binary;
    return directCode;
}

int main()
{
    try {
        // Ввод исходной и конечной систем счисления
        int fromBase, toBase;
        cout << "Введите исходную систему счисления (2-16): ";
        cin >> fromBase;
        if (fromBase < 2 || fromBase > 16)
            throw invalid_argument("Неверная исходная система счисления!");

        cout << "Введите конечную систему счисления (2-16): ";
        cin >> toBase;
        if (toBase < 2 || toBase > 16)
            throw invalid_argument("Неверная конечная система счисления!");

        // Ввод числа в исходной системе счисления
        string num;
        cout << "Введите число в исходной системе счисления: ";
        cin >> num;

        if (!isValidNumber(num, fromBase))
            throw invalid_argument("Введено некорректное число!");

        // Перевод числа в десятичную систему счисления
        int decimal = toDecimal(num, fromBase);

        // Перевод числа из десятичной системы счисления в заданную
        string result = fromDecimal(decimal, toBase);

        cout << "Число в конечной системе счисления: " << result << endl;

        // Дополнительный вывод для двоичной системы счисления
        if (toBase == 2) {
            cout << "Представление в виде прямого кода (ПК): " << toDirectCode(decimal) << endl;
        }

    } catch (const invalid_argument &e) {
        cerr << "Ошибка: " << e.what() << endl;
    } catch (const exception &e) {
        cerr << "Непредвиденная ошибка: " << e.what() << endl;
    }

    return 0;
}

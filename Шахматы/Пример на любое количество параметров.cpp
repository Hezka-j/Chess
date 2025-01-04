#include <iostream>
#include <cstdarg>
using namespace std;

void printArgs(int count, ...) { // Первым параметром передается количество аргументов
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; ++i) {
        cout << va_arg(args, int) << " "; // Извлечение аргумента
    }

    va_end(args);
    cout << endl;
}

//int main() {
//    printArgs(5, 1, 2, 3, 4, 5); // Пример вызова
//    return 0;
//}
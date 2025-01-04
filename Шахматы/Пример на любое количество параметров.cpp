#include <iostream>
#include <cstdarg>
using namespace std;

void printArgs(int count, ...) { // ������ ���������� ���������� ���������� ����������
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; ++i) {
        cout << va_arg(args, int) << " "; // ���������� ���������
    }

    va_end(args);
    cout << endl;
}

//int main() {
//    printArgs(5, 1, 2, 3, 4, 5); // ������ ������
//    return 0;
//}
#include <iostream>
#include <stdexcept>
#include <string>
 
using namespace std;

/*
* \brief пустой класс
*/
class except1 {};
 
/**
* \brief независимый класс с полями-параметрами функции
*/
class except2 {
    string msg;
public:
    except2(const string &s) : msg(s) {}
    const char *message() const { return msg.c_str(); }
};

/*
* \brief Класс наследник от стандартного исключения с полем
*/
class except3 : public invalid_argument {
    double num;
public:
    except3(const string msg, double n) : invalid_argument(msg), num(n) {}
    double arg() const { return num; }
};

/**
* \brief без спецификации исключений
*/
double root1(double a, double b) {
    return -b/a;
}
 
/**
* \brief со спецификацией throw()
*/
double root2(double a, double b) throw() {
    return -b/a;
}
 
/**
* \brief с конкретной спецификацией с подходящим стандартным исключением
*/
double root3(double a, double b) throw(invalid_argument) {
    if (a = 0.0)
        throw invalid_argument("a равно 0");
    return -b/a;
}
 
/**
* \brief Спецификация с собственным реализованным исключением
*/
double root4_1(double a, double b) throw(except1) {
    if (a = 0.0)
        throw except1();
    return -b/a;
}

/**
* \brief Спецификация с собственным реализованным исключением
*/
double root4_2(double a, double b) throw(except2) {
    if (a = 0.0)
        throw except2("a равно 0");
    return -b/a;
}

/**
* \brief Спецификация с собственным реализованным исключением
*/
double root4_3(double a, double b) throw(except3) {
    if (a <= 0.0)
        throw except3("Неверный аргумент", a);
    return -b/a;
}
 
void helper(double (*func)(double, double)) {
    double a, b;
    cout << "Введите a= ";
    cin >> a;
    cout << "Введите b= ";
    cin >> b;
    cout << "Корень уравнения: " << func(a, b) << endl;
}
 
int main() {
    setlocale(LC_ALL, "rus");
    cout << "Программа считает уравнение ax+b=0 \n";
 
    try {
        helper(root1);
    }
    catch (...) {
        cout << "Произошло исключение в функции root1" << endl;
    }
 
    try {
        helper(root2);
    }
    catch (...) {
        cout << "Произошло исключение в функции root2" << endl;
    }
 
    try {
        helper(root3);
    }
    catch (invalid_argument &e) {
        cout << e.what() << endl;
    }
 
    try {
        helper(root4_1);
    }
    catch (except1) {
        cout << "Произошло исключение except1 в функции root4_1" << endl;
    }
 
    try {
        helper(root4_2);
    }
    catch (except2 &e) {
        cout << e.message() << endl;
    }
 
    try {
        helper(root4_3);
    }
    catch (except3 &e) {
        cout << e.what() << " " << e.arg() << endl;
    }
}
#include <iostream>
#include <cmath>
using namespace std;

// Project Description:
// This program implements a Scientific Calculator using Object Oriented Programming.
// It supports basic arithmetic, trigonometric, logarithmic and power operations.
// It also handles invalid inputs such as division by zero.

class Calculator {
public:
    // Basic operations
    double add(double a, double b) {
        return a + b;
    }

    double subtract(double a, double b) {
        return a - b;
    }

    double multiply(double a, double b) {
        return a * b;
    }

    double divide(double a, double b) {
        if (b == 0) {
            cout << "Error: Division by zero not allowed!\n";
            return 0;
        }
        return a / b;
    }

    int modulo(int a, int b) {
        if (b == 0) {
            cout << "Error: Modulo by zero not allowed!\n";
            return 0;
        }
        return a % b;
    }

    // Scientific operations
    double power(double a, double b) {
        return pow(a, b);
    }

    double squareroot(double a) {
        if (a < 0) {
            cout << "Error: Square root of negative number not possible!\n";
            return 0;
        }
        return sqrt(a);
    }

    double sine(double a) {
        return sin(a);
    }

    double cosine(double a) {
        return cos(a);
    }

    double tangent(double a) {
        return tan(a);
    }

    double logarithm(double a) {
        if (a <= 0) {
            cout << "Error: Log of zero or negative number not allowed!\n";
            return 0;
        }
        return log(a);
    }
};

int main() {
    Calculator calc;
    int choice;
    double x, y;

    cout << "------ Scientific Calculator ------\n";

    do {
        cout << "\nChoose Operation:\n";
        cout << "1. Addition\n";
        cout << "2. Subtraction\n";
        cout << "3. Multiplication\n";
        cout << "4. Division\n";
        cout << "5. Modulo\n";
        cout << "6. Power\n";
        cout << "7. Square Root\n";
        cout << "8. Sin\n";
        cout << "9. Cos\n";
        cout << "10. Tan\n";
        cout << "11. Log\n";
        cout << "0. Exit\n";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter two numbers: ";
            cin >> x >> y;
            cout << "Result = " << calc.add(x, y);
            break;

        case 2:
            cout << "Enter two numbers: ";
            cin >> x >> y;
            cout << "Result = " << calc.subtract(x, y);
            break;

        case 3:
            cout << "Enter two numbers: ";
            cin >> x >> y;
            cout << "Result = " << calc.multiply(x, y);
            break;

        case 4:
            cout << "Enter two numbers: ";
            cin >> x >> y;
            cout << "Result = " << calc.divide(x, y);
            break;

        case 5:
            int a, b;
            cout << "Enter two integers: ";
            cin >> a >> b;
            cout << "Result = " << calc.modulo(a, b);
            break;

        case 6:
            cout << "Enter base and power: ";
            cin >> x >> y;
            cout << "Result = " << calc.power(x, y);
            break;

        case 7:
            cout << "Enter a number: ";
            cin >> x;
            cout << "Result = " << calc.squareroot(x);
            break;

        case 8:
            cout << "Enter angle (in radians): ";
            cin >> x;
            cout << "Result = " << calc.sine(x);
            break;

        case 9:
            cout << "Enter angle (in radians): ";
            cin >> x;
            cout << "Result = " << calc.cosine(x);
            break;

        case 10:
            cout << "Enter angle (in radians): ";
            cin >> x;
            cout << "Result = " << calc.tangent(x);
            break;

        case 11:
            cout << "Enter a number: ";
            cin >> x;
            cout << "Result = " << calc.logarithm(x);
            break;

        case 0:
            cout << "Exiting Calculator...\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 0);

    return 0;
}

#include <algorithm>
#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <cctype>
#include <stdexcept>

class Calculator {
public:
    std::stack<double> values;
    std::stack<char> operators;
    std::stack<char> operators_old;

    void processExpression(const std::string& expression) {
        size_t idx = 0;
        while (idx < expression.size()) {
            char ch = expression[idx];

            if (std::isdigit(ch)) {
                double number = ch - '0';
                while (idx + 1 < expression.size() && std::isdigit(expression[idx + 1])) {
                    number = number * 10 + (expression[++idx] - '0');
                }
                values.push(number);
                idx++;
            } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                while (!operators.empty() && priority(operators.top()) >= priority(ch)) {
                    executePendingOperation();
                }

                operators.push(ch);
                idx++;


            } else if (ch == '(') {
                operators.push(ch);
                idx++;
            } else if (ch == ')') {

                while (!operators.empty() && operators.top() != '(') {
                    executePendingOperation();
                }

                if (!operators.empty() && operators.top() == '(') {
                    operators.pop();
                }

                idx++;
            } else {
                std::cout << "Unsupported character in expression\n";
                idx = expression.size();
            }
        }

        while (!operators.empty()) {
            executePendingOperation();
        }

        if (!values.empty()) {
            std::cout << "Result: " << values.top() << "\n";
            values.pop();
        }
    }

    double performOperation(double num1, double num2, char op) {
        switch (op) {
            case '+':
                return num1 + num2;
            case '-':
                return num1 - num2;
            case '*':
                return num1 * num2;
            case '/':
                if (num2 != 0) {
                    return num1 / num2;
                }
            default:
                throw std::invalid_argument("Unsupported operation");
        }
    }

    void executePendingOperation() {
        if (!operators.empty()) {

            char op = operators.top();
            operators.pop();


            double num2 = values.top();
            values.pop();
            double num1 = values.top();
            values.pop();
            double result = performOperation(num1, num2, op);
            values.push(result);
        }
    }

    int priority(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }
};

class MinMax {
public:
    void theMin(double num1, double num2) {
        double print = std::min(num1, num2);
        std::cout << "min:" << print<< std::endl;;

    }
    void theMax(double num1, double num2) {
        double print = std::max(num1, num2);
        std::cout << "max:" << print<< std::endl;;

    }
};

class TextEditor {
public:
    void text(std::string& expression, Calculator& calc) {

        std::cout << "expression: ";
        std::getline(std::cin, expression);

        MinMax minMax;
        size_t idx = 0;

        if (expression.compare(0, 3, "min") == 0) {

            idx = 4;
            double num1, num2 = 0;
            bool foundComma = false;

            while (idx < expression.size()) {

                char ch = expression[idx];

                if (std::isdigit(ch)) {

                    double number = ch - '0';
                    while (idx + 1 < expression.size() && std::isdigit(expression[idx + 1])) {
                        number = number * 10 + (expression[++idx] - '0');
                    }

                    if (!foundComma) {
                        num1 = number;
                    } else {
                        num2 = number;
                    }

                } else if (ch == ',') {
                    foundComma = true;
                }

                idx++;
            }
            minMax.theMin(num1, num2);


        } else if (expression.compare(0, 3, "max") == 0) {
            idx = 4;
            double num1 = 0, num2 = 0;
            bool foundComma = false;

            while (idx < expression.size() && expression[idx] != ')') {
                 char ch = expression[idx];

                if (std::isdigit(ch)) {
                    double number = ch - '0';
                    while (idx + 1 < expression.size() && std::isdigit(expression[idx + 1])) {
                        number = number * 10 + (expression[++idx] - '0');
                    }

                    if (!foundComma) {
                        num1 = number;
                    } else {
                        num2 = number;
                    }
                } else if (ch == ',') {
                    foundComma = true;
                }

                idx++;
            } minMax.theMax(num1, num2);

        } else {
            calc.processExpression(expression);
        }


    }
};

int main() {
    TextEditor editor;
    Calculator calc;
    std::string operation;
    editor.text(operation, calc);

    return 0;
}

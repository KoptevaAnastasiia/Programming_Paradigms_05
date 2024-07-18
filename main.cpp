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

                if (operators.empty() && operators_old.empty()) {
                    values.push(number);
                } else if (!operators_old.empty()) {
                    double num1 = values.top();
                    values.pop();
                    char op = operators_old.top();
                    operators_old.pop();
                    double result = performOperation(num1, number, op);
                    values.push(result);
                } else if (!operators.empty()) {
                    values.push(number);
                }

                idx++;
            } else if (ch == '+' || ch == '-') {
                while (!operators_old.empty()) {
                    executePendingOperation();
                }
                operators.push(ch);
                idx++;
            } else if (ch == '*' || ch == '/') {
                operators_old.push(ch);
                idx++;
            } else {
                std::cout << "no";
                idx = expression.size();


            }

        }

        while (!operators_old.empty()) {
            executePendingOperation();
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
                return num1 / num2;
            default:
                throw std::invalid_argument("Unsupported operation");
        }
    }

    void executePendingOperation() {
        if (!operators_old.empty()) {
            double num2 = values.top();
            values.pop();
            double num1 = values.top();
            values.pop();
            char op = operators_old.top();
            operators_old.pop();
            double result = performOperation(num1, num2, op);
            values.push(result);
        } else if (!operators.empty()) {
            double num2 = values.top();
            values.pop();
            double num1 = values.top();
            values.pop();
            char op = operators.top();
            operators.pop();
            double result = performOperation(num1, num2, op);
            values.push(result);
        }
    }
};

class TextEditor {
public:
    void text(std::string& expression, Calculator& calc) {
        std::cout << "expression: ";
        std::cin >> expression;

        calc.processExpression(expression);
    }
};

int main() {
    TextEditor editor;
    Calculator calc;
    std::string operation;
    editor.text(operation, calc);

    return 0;
}

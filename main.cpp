#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <float.h>

class TextEditor {
public:
    void text(std::string& expression) {
        std::cout << "expression: ";
        std::cin >> expression;


        int i = 0;
        Valid(expression, i);

        if (i != 0) {
            std::cout << "Invalid expression with error count: " << i << "\n";
            return;
        }

        std::cout << "The expression is valid.\n";

    }

private:
  void Valid(const std::string& expression, int& i) {

        std::stack<char> brackets;


        for (char ch : expression) {

            if (!isdigit(ch)) {
                if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                    if (expression[ch-1] == (isdigit(ch)) ) {
                        i++; }
                }



            }



             if (ch == '(') {
                brackets.push(ch);
             }

            if (ch == ')') {
                if (brackets.empty() )

                    i++;

                brackets.pop();
             }


        }

     }
};

int main() {
    TextEditor editor;
    std::string operation;
    editor.text(operation);


    return 0;
}

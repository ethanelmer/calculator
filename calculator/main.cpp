#include <iostream>
#include <string>
#include <vector>

struct token{
    char kind;
    double value;

    token(char ch) : kind(ch), value(0) {}
    token(double val) : kind('n'), value(val) {}  
    token() : kind('n'), value(0) {}
};

int expressionParsing(){
    return 0;
};

char tokenize(char ch){
    switch(ch){
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
        case '=':
        case '.':
            return ch;
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': 
            return 'n';
        case 'q':
            return 'q';
        default:
            return 's';
    }
};

char tokenize_value(char ch){
    double value = 0;
    std::string str(1, ch);
    switch(ch){
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
        case '=':
        case '.':
        case '^':
            return value;
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': 
            value = std::stod(str);
            return value;
        default:
            return value;
    }
};

float evaluateExpression(std::vector<token>& tokens){
    for (int i = 0; i<tokens.size(); i++){
        if (tokens[i].kind == 'n'){
            bool previousNum = true;
            while(previousNum && i > 0){
                if(tokens[i - 1].kind == 'n'){
                    tokens[i - 1].value = tokens[i - 1].value * 10 + tokens[i].value;
                    tokens.erase(tokens.begin() + i);
                    i--;
                } 
                else {
                    previousNum = false;
                }
            }
        }
    if (tokens[i].kind == '.') {
        // Check if there's a number before the decimal point
        if (i > 0 && tokens[i - 1].kind == 'n') {
            // Combine the decimal part with the previous number
            double decimalValue = 0.1;
            size_t j = i + 1; // Start from the digit after the decimal point
            while (j < tokens.size() && tokens[j].kind == 'n') {
                tokens[i - 1].value += tokens[j].value * decimalValue;
                decimalValue *= 0.1; // Move to the next decimal place
                j++;
            }
            // Erase the tokens for the decimal point and the digits after it
            tokens.erase(tokens.begin() + i, tokens.begin() + j);
        } else {
            // Handle case where the decimal point is not preceded by a number
            std::cerr << "Error: Invalid input format" << std::endl;
            // Add error handling as needed
        }
    }
}
    for(int i = 0; i<tokens.size(); i++){
        if(tokens[i].kind == '+'){
            double answer = tokens[i-1].value + tokens[i+1].value;
            tokens[i-1].value = answer;
            tokens.erase(tokens.begin() + i, tokens.begin() + i + 2);
            i--;
        }
        if(tokens[i].kind == '-'){
            double answer = tokens[i-1].value - tokens[i+1].value;
            tokens[i-1].value = answer;
            tokens.erase(tokens.begin() + i, tokens.begin() + i + 2);
            i--;
        }
        if(tokens[i].kind == '*'){
            double answer = tokens[i-1].value * tokens[i+1].value;
            tokens[i-1].value = answer;
            tokens.erase(tokens.begin() + i, tokens.begin() + i + 2);
            i--;
        }
        if(tokens[i].kind == '/'){
            if(tokens[i+1].value == 0){
                std::cout << "Error: Division by zero" << std::endl;
                return 0;
            }
            else{
                double answer = tokens[i-1].value / tokens[i+1].value;
                tokens[i-1].value = answer;
                tokens.erase(tokens.begin() + i, tokens.begin() + i + 2);
                i--;
            }
        }
    }
    for(int i = 0; i<tokens.size(); i++){
        std::cout << "Answer: " << tokens[i].value << std::endl;
    }
    return 0;
};

int main() {
    std::cout << "Enter q at any time to stop the program." << std::endl;
    std::cout << "Please enter an expression:" << std::endl;
    std::string expression;
    std::getline(std::cin, expression);
    while (expression[0] != 'q'){
        std::vector<token> tokens;
        for(int i = 0; i<expression.length(); i++){
            token t;
            char ch = expression[i];
            t.kind = tokenize(ch); 
            if (t.kind != 's'){
                t.value = tokenize_value(ch);
                tokens.push_back(t);
            }
        }
        evaluateExpression(tokens);
        std::cout << "Enter a new expression or q to quit the program: " << std::endl;
        std::getline(std::cin, expression);
    }
    return 0;
}


//TODO : Add functionality for parentheses, negative numbers, remainder, and exponents, pre-defined symbolic values, and variables
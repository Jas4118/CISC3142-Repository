#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
using namespace std;

vector<string> Tokenize(string &expression, unordered_map<string, int> &operationsMap)
{
    // Will read the expression the user submits and tokenize it into infix form
    vector<string> tokens = {};
    string temp = "";

    for (char c : expression)
    {
        // This will loop through the entire expression that the user passes
        if (c == ' ')
        {
            // If an empty space is detected, the for loop will continue
            continue;
        }
        // Checks if the current token contains any of the values in the operationsMap. If it does, the token is an operation
        else if (operationsMap.find(string(1, c)) != operationsMap.end())
        {
            if (temp != "")
            {
                // If the temp string is not empty, push it into the vector before resetting and pushing the operator
                tokens.push_back(temp);
            }

            // Reset the temp variable and put the operator into the vector
            temp = "";
            tokens.push_back(string(1, c));
        }
        else
        {
            // If it is not an empty space and not an operator, then the character is a number. In this case, we add the character to the temp string
            temp += c;
        }
    }

    // If, by the end of the loop, the temp variable is not empty, we must clear it and push the contents into the vector
    if (temp != "")
    {
        tokens.push_back(temp);
    }

    return tokens;
}

vector<string> InfixToPostfix(vector<string> &infix, unordered_map<string, int> &operationsMap)
{
    // Will taken the tokenized infix expression and convert to postfix
    vector<string> postfix = {};
    vector<string> stack = {"("};

    infix.push_back(")");

    // Loops through all of the infix tokens
    for (string token : infix)
    {
        if (operationsMap.find(token) == operationsMap.end())
        {
            // If the token is not in the operationsMap, that means it is not an operation, but an operand. We check this condition first.
            postfix.push_back(token);
        }
        else if (token == "(")
        {
            // If the token is an open parentheses, the open parentheses will be put into the stack
            stack.push_back(token);
        }
        else if (token == ")")
        {
            // If the token is a close parentheses, while the top of the stack is not an open parentheses, all the values in the stack
            // will be put into the postfix vector.
            while (stack.back() != "(")
            {
                postfix.push_back(stack.back());
                stack.pop_back();
            }

            // Remove the open parentheses
            stack.pop_back();
        }
        // If the token is not an operand and is not a parentheses, then it must be an operation
        else
        {
            // There must still be items in the stack. Additionally, the token must exist in the operations make and the current token should have
            // a high priority (order of operations wise) than the top of the stack
            while (stack.size() > 0 && operationsMap[token] <= operationsMap[stack.back()])
            {
                // Put the top of the stack into the post fix and then pop the stack
                postfix.push_back(stack.back());
                stack.pop_back();
            }

            stack.push_back(token);
        }
    }

    return postfix;
}

float CalculatePostfix(vector<string> &postfix, unordered_map<string, int> &operationsMap)
{
    // Calculate the postfix vector and does the calculations
    vector<float> evaluationStack = {};

    // This will loop through all of the tokens in the now converted postfix expression
    for (string token : postfix)
    {
        // If the token is in the operationsMap, then it is an operator
        if (operationsMap.find(token) != operationsMap.end())
        {
            //Creates two floats, one for the closest operand, and one for the second closest
            float n1 = evaluationStack[evaluationStack.size() - 1];
            float n2 = evaluationStack[evaluationStack.size() - 2];

            float result = 0.0;

            // Utilize the appropriate operator and save it into the result
            switch (token[0])
            {
            case '+':
                result = n2 + n1;
                break;
            case '-':
                result = n2 - n1;
                break;
            case '*':
                result = n2 * n1;
                break;
            case '/':
                result = n2 / n1;
                break;
            case '^':
                result = pow(n2, n1);
                break;
            }

            evaluationStack.pop_back();
            evaluationStack.pop_back();

            // Put the sum into the evaluation stack
            evaluationStack.push_back(result);
        }
        // Otherwise, it was an operand
        else
        {
            // We need to convert the operand into a number (convert string to float)
            evaluationStack.push_back(atof(token.c_str()));
        }
    }

    // Finally, the evaluation stack will only have one value, which will be the final result. We return this.
    return evaluationStack[0];
}

int main()
{
    // The main function that will allows the user to enter the expression

    unordered_map<string, int> operationsMap = {
        // The operation map that deals with order of operations. The lower the value, the higher the precedence. Parentheses come first, then
        // addition and subtraction, then multiplication and division.

        {"*", 2},
        {"/", 2},
        {"^", 2},
        {"+", 1},
        {"-", 1},
        {"(", -1},
        {")", -1},
    };

    string expression;

    cout << "\nThe supported operations are parentheses, addition, subtraction, multiplication, division, and exponents/square root (do x ^ (1/2) for square root).\n";
    cout << "If you would like to quit, type 'quit' in all lowercase.\n";

    while (true)
    {
        cout << "Please enter your expression.\n";

        getline(cin, expression);

        if (expression == "quit")
        {
            break;
        }

        // Tokenizes the user's line into infix form
        vector<string> tokens = Tokenize(expression, operationsMap);

        // Converts to infix form to postfix form
        tokens = InfixToPostfix(tokens, operationsMap);

        float result = CalculatePostfix(tokens, operationsMap);

        cout << result << "\n" << endl;
    }
}

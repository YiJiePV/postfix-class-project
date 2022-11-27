/*
 * Title:		Evaluator Function Definition
 * Purpose:		Implements the function Evaluate, which evaluates a postfix expression
 * Author:		Karena Qian
 * Date:		May 20, 2022
 */
#include "evaluator.h"
#include <stack>
#include <sstream>
#include <cmath>
#include <limits>
#include<algorithm>

using std::stack;
using std::isdigit;
using std::istringstream;
using std::numeric_limits;
using std::streamsize;
using std::all_of;

/**
 * Check
 * Checks if given character is a digit or decimal point
 * @param c character to be checked
 * @return true if character is digit or decimal point, false otherwise
 * */
bool Check(char c){
    return !(!isdigit(c) && c != '.');
}
/**
 * IsValid
 * Checks if given string is a real number
 * @param num string to be checked
 * @return true if string is a real number, false otherwise
 * */
bool IsValid(const string& num){
    bool l = all_of(num.cbegin(), num.cend(), Check);
    return l;
}
/**
 * Evaluate
 * Evaluates the given postfix expression. It sets error to false and returns the result if expression is correct,
 * otherwise it sets error to true and return -1
 * @param postfix expression to be evaluated
 * @param error true if expression can be evaluated, false otherwise
 * @return the result of postfix if solvable, -1 otherwise
 * */
double Evaluate(const string& postfix, bool& error){
    //error if string does not start with a number
    if(!isdigit(postfix.at(0))){
        error = true;
        return -1;
    }
    stack<double> num;
    //Read each part of the postfix
    istringstream ss(postfix);
    while(!ss.eof()){
        string part;
        ss >> part;
        istringstream ss2(part);
        //adds part to stack if part is a real number
        if(IsValid(part)){
            double value;
            ss2 >> value;
            num.push(value);
        }
        //if part is a char:
        else if(part.length() == 1){
            //returns error if stack has only one number left
            if(num.size() == 1){
                error = true;
                return -1;
            }
            char optr;
            double n2 = num.top();
            num.pop();
            double n1 = num.top();
            num.pop();
            ss2 >> optr;
            //evaluates and adds expression to stack if optr is +, -, *, /, or ^
            if(optr == '+'){
                double total = n1 + n2;
                num.push(total);
            }
            else if(optr == '-'){
                double total = n1 - n2;
                num.push(total);
            }
            else if(optr == '*'){
                double total = n1 * n2;
                num.push(total);
            }
            else if(optr == '/'){
                double total = n1 / n2;
                num.push(total);
            }
            else if(optr == '^'){
                double total = pow(n1, n2);
                num.push(total);
            }
            //returns error if char is not a valid operator
            else{
                error = true;
                return -1;
            }
        }
        //returns error if part is neither a real number nor a valid char
        else{
            error = true;
            return -1;
        }
    }
    error = false;
    return num.top();
}

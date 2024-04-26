#include <stdio.h> 
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
using namespace std;
class TableDrivenDFSA{
    public:
        // Function to determine the type of input symbol
        int getInputSymbol(char c) {
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') {
                return 5;
            } else if (c >= '0' && c <= '9') {
                return 3;
            } else if (c == '*' ){
                return 2;
            } else if (c == '/') {
                return 7;
            } else if (c == '='){
                return 11;
            } else if (c == '<'){
                return 14;
            } else if (c == '>'){
                return 17;
            } else if (c == '+'){
                return 20;
            } else if (c == '-'){
                return 21;
            } else if (c == '('){
                return 22;
            } else if (c == ')'){
                return 23;
            } else if (c == '{'){
                return 24;
            } else if (c == '}'){
                return 25;
            } else if (c == '!'){
                return 26;
            } else if (c == ';'){
                return 30;
            } else if (c == ','){
                return 29;
            } else {
                return 1; // error
            }
        }
        // Transition table for the finite automata
        int stateTable[31][31] = {
            // ROW 0 - Initial state
            {1, 1, 2, 3, 1, 5, 1, 7, 1, 1, 1, 11, 1, 1, 14, 1, 1, 17, 1, 1, 20, 21, 22, 23, 24, 25, 26, 1, 1, 29, 30},
            // ROW 1 - Error state
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            // ROW 2 - Multiplication
            {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
            // ROW 3 - Number
            {4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
            // ROW 4 - Number
            {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
            // ROW 5 - LETTER
            {6, 6, 6, 5, 6, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
            // ROW 6 - Identifier
            {6, 6, 6, 6, 6, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
            // ROW 7 - Division
            {10,10,8,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
            // ROW 8 - Comment
            {8, 8, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
            // ROW 9 - Comment
            {8, 8, 8, 8, 8, 8, 8, 0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
            // ROW 10 - Division
            {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
            // ROW 11 - Assignment
            {12,12,12,12,12,12,12,12,12,12,12,13,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
            // ROW 12 - Assignment
            {12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
            // ROW 13 - Assignment
            {13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13},
            // ROW 14 - Less than
            {15,15,15,15,15,15,15,15,15,15,15,16,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
            // ROW 15 - Less than
            {15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
            // ROW 16 - Less than or equal
            {16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16},
            // ROW 17 - Greater than
            {18,18,18,18,18,18,18,18,18,18,18,19,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18},
            // ROW 18 - Greater than
            {18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18},
            // ROW 19 - Greater than or equal
            {19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19},
            // ROW 20 - Addition
            {20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20},
            // ROW 21 - Subtraction
            {21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},
            // ROW 22 - Left parenthesis
            {22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22},
            // ROW 23 - Right parenthesis
            {23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23},
            // ROW 24 - Left curly brace
            {24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24},
            // ROW 25 - Right curly brace
            {25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25},
            // ROW 26 - Exclamation
            {27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,28,27,27,27,27},
            // ROW 27 - Exclamation
            {27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27},
            // ROW 28 - Not equal
            {28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28},
            // ROW 29 - Comma
            {29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29},
            // ROW 30 - Semicolon
            {30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30}
        };
        int nextState(int currentState, int inputSymbol){
            // this function returns the next state of the finite automata
            for (int i = 0; i < 32; i++){
                if (stateTable[currentState][i] == inputSymbol){
                    // cout << "Next state: " << stateTable[currentState][i] << endl;
                    return stateTable[currentState][i];
                }
            }
            return 1; // error
        }
        int nexxtState(int currentState, int inputSymbol){
            // this function returns the next state of the finite automata
            for (int i = 0; i < 32; i++){
                if (stateTable[currentState][i] == stateTable[currentState][inputSymbol]){
                    // cout << "Next state: " << stateTable[currentState][i] << endl;
                    return stateTable[currentState][i];
                }
            }
            return 1; // error
        }
};
class SymbolTableDFSA{
    public:
        int InputSymbolTable(string type) {
            if (type == "$CLASS" || type == "$PROCEDURE" || type == "$CALL"){
                return 1;
            }
            else if (type == "$CLASS_NAME" || type == "$PROCEDURE_NAME" || type == "$CALL_NAME"){
                return 2;
            }
            else if (type == "$SEMICOLON" || type == "$LEFT_CURLY_BRACE") { 
                return 3;
            }
            else if (type == "$CONSTANT"){
                return 4;
            }
            else if (type == "$IDENTIFIER"){
                return 5;
            }
            else if (type == "$ASSIGNMENT"){
                return 6;
            }
            else if (type == "$NUMBER"){
                return 7;
            }
            else if (type == "$VARIABLE"){
                return 8;
            }
            else if (type == "$BEGIN" || type == "$END" || type == "$IF" || type == "$THEN" || type == "$ELSE" || type == "$WHILE" || type == "$DO" || type == "$ODD" || type == "$CALL" || type == "$IN" || type == "$OUT"){
                return 10;
            }
            else {
                return 3;
            }

        }
        // Transition table for the finite automata
        int symboltablestates[13][13] = {
            // state 0: Initial state
            {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //
            // state 1: class
            {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //
            // state 2: program name
            {0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //
            // state 3: '{' or ';' add to symbol table
            {3, 1, 3, 3, 4, 3, 3, 3, 8, 3, 10, 3, 3}, //
            // state 4: const
            {0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0}, //
            // state 5: const name
            {0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0}, //
            // state 6: '='
            {0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0}, //
            // state 7: add constant to symbol table
            {0, 0, 0, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0}, //
            // state 8: var
            {0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0}, //
            // state 9: add var to symbol table
            {0, 0, 0, 3, 0, 0, 0, 0, 8, 0, 0, 0, 0}, //
            // state 10: 
            {10, 10, 10, 10, 10, 10, 10, 11, 10, 10, 10, 10, 12}, //
            // state 11: add numbers to symbol table
            {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 12}, //
            // state 12 : end of pass 1
            {12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12} //
        };
        int nextState(int currentState, int inputSymbol){
            return symboltablestates[currentState][inputSymbol];
        }
};
class PushdownAutomata {
public:
    // STACK ALPHABETS (STACK SYMBOLS) THAT CAN BE PUSHED ONTO THE STACK
    int InputsforPDA(string type) {
        if (type == "$IDENTIFIER" || type == "$NUMBER" || type == "$ASSIGNMENT" || type == "$CLASS_NAME" || type == "$PROCEDURE_NAME" || type == "$CALL_NAME") return 0;
        else if (type == "$SEMICOLON") return 1;
        else if (type == "$ADDITION" || type == "$SUBTRACTION") return 2;
        else if (type == "$MULTIPLICATION" || type == "$DIVISION") return 3; 
        else if (type == "$LEFT_PARENTHESIS" || type == "$RIGHT_PARENTHESIS") return 4;
        else if (type == "$LESS_THAN" || type == "$GREATER_THAN" || type == "$EQUAL" || type == "$NOT_EQUAL" || type == "$LESS_THAN_OR_EQUAL" || type == "$GREATER_THAN_OR_EQUAL") return 5;
        else if (type == "$IF") return 6;
        else if (type == "$THEN") return 7;
        else if (type == "$WHILE") return 8;
        else if (type == "$DO") return 9;
        else if (type == "$LEFT_CURLY_BRACE" || type == "$RIGHT_CURLY_BRACE") return 10;
        else if (type == "$CALL" || type == "$PROCEDURE" || type == "$CLASS") return 11;
        else return 999;
    }
    // Q FINITE SET OF STATES
    int QSTATES[19][12] = {
        // stmt
        {2,7,7,7,7,7,8,7,9,7,6,3},
        // empty
        {17,17,17,17,17,17,17,17,17,17,17,17},
        // simple stmt
        {12,12,12,12,12,12,12,12,12,12,12,12},
        // call stmt
        {4,17,17,17,17,17,17,17,17,17,17,17},
        // parm list
        {17,17,17,17,5,17,17,17,17,17,6,17},
        // ident list
        {17,17,17,17,4,17,17,17,17,17,17,17},
        // compound stmt
        {7,7,7,7,7,7,8,7,9,7,7,3},
        // stmt list
        {0,0,7,7,7,7,7,7,7,7,6,7},
        // if stmt
        {10,17,17,17,10,17,17,17,17,17,17,17},
        // while stmt
        {10,17,17,17,10,17,17,17,17,17,17,17},
        // be
        {12,17,12,12,12,11,17,0,17,0,17,17},
        // relop
        {12,17,17,17,17,10,17,17,17,17,17,17},
        // exp
        {12,18,13,15,16,11,0,0,17,0,17,17},
        // addop
        {14,17,14,17,11,17,17,17,17,17,17,17},
        // term
        {14,18,13,15,16,17,17,17,17,17,17,17},
        // mop
        {16,17,17,17,16,17,17,17,17,17,17,17},
        // factor
        {12,18,12,12,12,12,17,12,17,12,17,17},
        // ERROR
        {17,17,17,17,17,17,17,17,17,17,17,17},
        // HALT
        {18,18,18,18,18,18,18,18,18,18,18,18}  
    };
    // TRANSITION FUNCTION FOR THE Q STATES
    int QTransitionFunction(int currentState, int inputSymbol) {return QSTATES[currentState][inputSymbol];}
    int operatorinputs(string Type) {
        if (Type == "$") {
            return 0;
        } else if (Type == "$ASSIGNMENT" || Type == "=") {
            return 1;
        } else if (Type == "$ADDITION" || Type == "+"){
            return 2;
        } else if (Type == "$SUBTRACTION" || Type == "-") {
            return 3;
        } else if (Type == "$LEFT_PARENTHESIS" || Type == "(") {
            return 4;
        } else if (Type == "$RIGHT_PARENTHESIS" || Type == ")") {
            return 5;
        } else if (Type == "$MULTIPLICATION" || Type == "*") {
            return 6;
        } else if (Type == "$DIVISION" || Type == "/") {
            return 7;
        } else if (Type == "$SEMICOLON" || Type == "$COMMA" || Type == ";" || Type == ",") {
            return 8;
        } else if (Type == "$EQUAL" || Type == "==") {
            return 9;
        } else if (Type == "$NOT_EQUAL" || Type == "!=") {
            return 10;
        } else if (Type == "$GREATER_THAN" || Type == ">") {
            return 11;
        } else if (Type == "$LESS_THAN" || Type == "<") {
            return 12;
        } else if (Type == "$GREATER_THAN_OR_EQUAL" || Type == ">=") {
            return 13;
        } else if (Type == "$LESS_THAN_OR_EQUAL" || Type == "<=") {
            return 14;
        } else if (Type == "$IF" || Type == "IF") {
            return 15;
        } else if (Type == "$THEN" || Type == "THEN") {
            return 16;
        } else if (Type == "$WHILE" || Type == "WHILE") {
            return 17;
        } else if (Type == "$DO" || Type == "DO") {
            return 18;
        } else if (Type == "$LEFT_CURLY_BRACE" || Type == "{") {
            return 19;
        } else if (Type == "$RIGHT_CURLY_BRACE" || Type == "}") {
            return 20;
        } else if (Type == "$PROCEDURE" || Type == "PROCEDURE") {
            return 21;
        } else if (Type == "$CALL" || Type == "CALL") {
            return 22;
        } else {
            return 999;
        }
    }
    // OPERATOR PRECEDENCE TABLE
    string OperatorPrecedence[23][23] ={
    //     $    =    +    -    (    )    *    /    ;  ==  !=    >    <    >=    <=  IF THEN  WHILE  DO   {    }  PROC
        // $
        {"0", "<", "<", "<", "<", "0", "<", "<", "0", "<", "<", "<", "<", "<", "<", "<", "0", "<", "0", "<", "0", "0", "0"},
        // =
        {">", "<", "<", "<", "<", "0", "<", "<", ">", "<", "<", "<", "<", "<", "<", "0", "0", "0", "0", "<", "0", "0", "0"},
        // +
        {">", "0", ">", ">", "<", ">", "<", "<", ">", ">", ">", ">", ">", ">", ">", "0", ">", "0", "0", "0", "0", "0", "0"},
        // -
        {">", "0", ">", ">", "<", ">", "<", "<", ">", ">", ">", ">", ">", ">", ">", "0", ">", "0", "0", "0", "0", "0", "0"},
        // (
        {"0", "0", "<", "<", "<", "=", "<", "<", "0", "<", "<", "<", "<", "<", "<", "0", "0", "0", "0", "0", "0", "0", "0"},
        // )
        {">", "0", ">", ">", "0", ">", ">", ">", ">", ">", ">", ">", ">", ">", ">", "0", "0", "0", "0", "0", "0", "0", "0"},
        // *
        {">", "0", ">", ">", "<", ">", ">", ">", ">", ">", ">", ">", ">", ">", ">", "0", ">", "0", "0", "0", "0", "0", "0"},
        // /
        {">", "0", ">", ">", "<", ">", ">", ">", ">", ">", ">", ">", ">", ">", ">", "0", ">", "0", "0", "0", "0", "0", "0"},
        // ;
        {"0", "<", "<", "<", "<", "0", "<", "<", "0", "<", "<", "<", "<", "<", "<", "<", "0", "<", "0", "0", ">", "0", "0"},
        // ==
        {"0", "0", "<", "<", "<", ">", "<", "<", ">", "0", "0", "0", "0", "0", "0", "0", ">", "0", ">", "0", "0", "0", "0"},
        // !=
        {"0", "0", "<", "<", "<", ">", "<", "<", ">", "0", "0", "0", "0", "0", "0", "0", ">", "0", ">", "0", "0", "0", "0"},
        // >
        {"0", "0", "<", "<", "<", ">", "<", "<", ">", "0", "0", "0", "0", "0", "0", "0", ">", "0", ">", "0", "0", "0", "0"},
        // <
        {"0", "0", "<", "<", "<", ">", "<", "<", ">", "0", "0", "0", "0", "0", "0", "0", ">", "0", ">", "0", "0", "0", "0"},
        // >=
        {"0", "0", "<", "<", "<", ">", "<", "<", ">", "0", "0", "0", "0", "0", "0", "0", ">", "0", ">", "0", "0", "0", "0"},
        // <=
        {"0", "0", "<", "<", "<", ">", "<", "<", ">", "0", "0", "0", "0", "0", "0", "0", ">", "0", ">", "0", "0", "0", "0"},
        // IF
        {"<", "0", "<", "<", "<", "0", "<", "<", "<", "<", "<", "<", "<", "<", "<", "0", "=", "0", "0", "<", "0", "0", "0"},
        // THEN
        {">", "<", "0", "0", "0", "0", "0", "0", ">", "0", "0", "0", "0", "0", "0", "<", "0", "<", "0", "<", ">", "0", "0"},
        // WHILE
        {"<", "0", "<", "<", "<", "0", "<", "<", "<", "<", "<", "<", "<", "<", "<", "0", "0", "0", "=", "<", "0", "0", "0"},
        // DO
        {">", "<", "0", "0", "0", "0", "0", "0", ">", "0", "0", "0", "0", "0", "0", "<", "0", "<", "0", "<", ">", "0", "0"},
        // {
        {"0", "<", "<", "<", "<", "0", "<", "<", "=", "0", "0", "0", "0", "0", "0", "<", "<", "<", "<", "<", "=", "<", "<"},
        // }
        {"0", "0", "0", "0", "0", "0", "0", "0", ">", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", ">", "<", "0"},
        // PROCEDURE
        {"<", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "<", ">", "<", "0"},
        // CALL
        {"0", "0", "0", "0", "0", "0", "0", "0", ">", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "<", "0", "0", "0"}
    };
    // FUNCTION TO RETURN THE OPERATOR PRECEDENCE
    string Operatorstate(int& lastoperator, int currentoperator, string& lastoperatorstring, string& currentoperatorstring) {
        lastoperator = operatorinputs(lastoperatorstring);
        cout << "comparing " << lastoperatorstring << " with " << currentoperatorstring << " " << OperatorPrecedence[lastoperator][currentoperator] << endl;
        lastoperatorstring = currentoperatorstring;
        return OperatorPrecedence[lastoperator][currentoperator];
    }
    // function to pop quads from the stack:
    void popQuads(stack<string>& stack1, string currentoperator, ofstream &quadfile, stack<string>& labelstack, int& i, int& l, int& j, stack<string>& whilestack) {
         string temp; string haha;
        string precedence = ">"; string label;
        while (precedence == ">" || precedence == "=") { 
            string operand1, operand2, op;
            if (stack1.empty()) {
                stack1.push("$");
                break;
            }
            operand2 = stack1.top(); stack1.pop();
            if (operand2 == "$"){
                stack1.push(operand2);
                break;
            }
            cout << "operand2: " << operand2 << endl;
            op = stack1.top(); stack1.pop();
            cout << "op: " << op << endl;
            if (op == "IF" && operand2 == "THEN"){
                haha = op;
                op = operand2;
                operand2 = haha;
            }
            if (op == "WHILE" && operand2 == "DO"){
                haha = op;
                op = operand2;
                operand2 = haha;
            }
            if (op[0] == 'T' && (operand2 == "IF" || operand2 == "WHILE")){
                haha = op;
                op = operand2;
                operand2 = haha;
            }
            //cout << operatorinputs(op) << " " << operatorinputs(currentoperator)<< " " << currentoperator << endl;
            precedence = OperatorPrecedence[operatorinputs(op)][operatorinputs(currentoperator)];
            cout  << op << " " << precedence << " " << currentoperator << endl;
            if (precedence == "0") {   
                stack1.push(op);     
                break;  
            }
            if (precedence != "="){ // this is for when the presedence is = to not over pop the stack
                operand1 = stack1.top(); stack1.pop();
                cout << "operand1: " << operand1 << endl;
                //cout << op << " " << operand1 << " " << operand2 << endl;
            }
            if (precedence == ">") { // good to go
                if (currentoperator == "}" && (op == "DO" || op == "THEN")){
                    if (op == "DO"){
                        cout << "jmp " << whilestack.top() <<" ?" << " ?" << endl;
                        quadfile << "jmp " << whilestack.top() <<" ?" << " ?" << endl;
                        whilestack.pop();
                    }
                    //cout << labelstack.top() << " ?" <<" ?" << " ?" << endl;
                    quadfile << labelstack.top()<< " ?" <<" ?" << " ?" << endl;
                    labelstack.pop();   
                    break;
                }
                if (op == "THEN" || op == "ELSE" || op == "DO"){
                    // popping the label into the label stack
                    //cout << "popped " << "L" << j << " to the stack" << endl;
                    if (op == "DO"){
                        //cout << whilestack.top() << " ?" <<" ?" << " ?" << endl;
                        quadfile << whilestack.top() << " ?" <<" ?" << " ?" << endl;
                        whilestack.pop(); 
                    }
                    //cout << labelstack.top() << " ?" <<" ?" << " ?" << endl;
                    quadfile << labelstack.top()<< " ?" <<" ?" << " ?" << endl;
                    labelstack.pop();  
                    if (operand1 == "$"){
                        break;
                    }
                    //stack1.push(op);    
                }   else if (op == ">" || op == "<" || op == ">=" || op == "<=" || op == "!=" || op == "=="){
                    // this is for the THEN QUAD
                                    if (op == ">") label = "JLE";
                                    else if (op == "<") label = "JGE";
                                    else if (op == ">=") label = "JL";
                                    else if (op == "<=") label = "JG";
                                    else if (op == "!=") label = "JE";
                                    else if (op == "==") label = "JNE";
                        //cout << op << " " << operand1 << " " << operand2 << " " << "L" << j << endl;
                        quadfile << op << " " << operand1 << " " << operand2 << " " << "L" << j << endl;
                        // pushing the label into the label stack
                        //cout << "pushed " << "L" << j << " to the stack" << endl;
                        labelstack.push("L" + to_string(j));
                        // this creates the THEN and DO quad label
                        if (currentoperator == "THEN" || "DO"){
                            //cout << currentoperator << " L" << j << " " << label << " ?" << endl;
                            quadfile << currentoperator << " L" << j << " " << label << " ?" << endl;
                        }
                    }
                    else { // this outputs the traditional quads
                        //cout << op << " " << operand1 << " " << operand2 << " " << "T" << i << endl;
                        quadfile << op << " " << operand1 << " " << operand2 << " " << "T" << i << endl;
                        if (operand2 == "CIN" || operand2 == "PRINT" || operand1 == "CIN" || operand1 == "PRINT" || operand1 == "FUNCTIONCALL" || operand2 == "FUNCTIONCALL"){
                            if (operand1 == "FUNCTIONCALL" || operand2 == "FUNCTIONCALL"){
                                quadfile << "exit " << "end: " << " ?" << " ?" << endl; 
                            } else {
                                ; // do nothing
                            }
                        } else {
                            stack1.push("T" + to_string(i));
                            i++;
                        }
                    }
                    if (operand2 == "{" && op == "THEN" && currentoperator == ";"){
                        stack1.push(operand1);
                        stack1.push(op);
                        stack1.push(operand2);
                        break;
                    }
                    // for nested if statements
                    while (precedence == ">" && currentoperator == ";" && op == "THEN"){
                        operand2 = stack1.top(); stack1.pop();
                        op = stack1.top(); stack1.pop();
                        if (op == "IF" && operand2 == "THEN"){
                            haha = op;
                            op = operand2;
                            operand2 = haha;
                        }
                        precedence = OperatorPrecedence[operatorinputs(op)][operatorinputs(currentoperator)];
                        //cout << operand2 << " " << op << " " << precedence << " " << currentoperator << endl;
                        // popping the label into the label stack
                        //cout << labelstack.top() << " ?" <<" ?" << " ?" << endl;
                        quadfile << labelstack.top() << " ?" <<" ?" << " ?" << endl;
                        labelstack.pop();
                    }
                    // for nested while statements
                    while (precedence == ">" && currentoperator == ";" && op == "DO"){
                        operand2 = stack1.top(); stack1.pop();
                        op = stack1.top(); stack1.pop();
                        if (op == "WHILE" && operand2 == "DO"){
                            haha = op;
                            op = operand2;
                            operand2 = haha;
                        }
                        precedence = OperatorPrecedence[operatorinputs(op)][operatorinputs(currentoperator)];
                        //cout << operand2 << " " << op << " " << precedence << " " << currentoperator << endl;
                        //cout << whilestack.top() << " ?" <<" ?" << " ?" << endl;
                        quadfile << whilestack.top() << " ?" <<" ?" << " ?" << endl;
                        whilestack.pop();
                        // popping the label into the label stack
                        //cout << labelstack.top() << " ?" <<" ?" << " ?" << endl;
                        quadfile << "L" << labelstack.top() << " ?" <<" ?" << " ?" << endl;
                        labelstack.pop();
                    }
                } 
                else if (precedence == "="){ // this sets the top of the stack to the current operator and pushes the popped element back to the stack
                    //cout << "here---" << endl;
                    op = stack1.top();
                    stack1.push(operand2);
                    //cout << "operand2: " << operand2 << endl;
                    //cout << "op: " << op << endl;
                    if (currentoperator == ")"){
                        break;
                    }
                }
                else { // good to go
                    if (currentoperator == ";" && op == "{"){
                        stack1.push(operand1);
                        stack1.push(op);
                    } else {
                        // push the popped elements back to the stack
                        stack1.push(operand1);
                        stack1.push(op);
                        stack1.push(operand2);
                    }   
                }
               // this prints the stack in a temporary stack to se what is happening
                cout << "--------------------------------------" << endl;
                stack<string> tempstack = stack1;
                cout << "Stack: ";
                    while (!tempstack.empty()){
                        cout << tempstack.top() << " ";
                        tempstack.pop();
                    }
                    cout << endl;
                // print the label stack
                stack<string> tempstack2 = labelstack;
                cout << "Label Stack: ";
                    while (!tempstack2.empty()){
                        cout << tempstack2.top() << " ";
                        tempstack2.pop();
                    }
                    cout << endl;
                // print the while stack
                stack<string> tempstack3 = whilestack;
                cout << "While Stack: ";
                    while (!tempstack3.empty()){
                        cout << tempstack3.top() << " ";
                        tempstack3.pop();
                    }
                    cout << endl;
                    cout << "--------------------------------------" << endl;
        }
    }
    // function to generate assembly code from the quads
    void generateAssemblyCode() {
        // reading the symbol table file
        ifstream symboltablefile("symboltable.txt");
        string word, type, value, address, segment;
        ofstream assemblyfile("assemblycode.asm");
        string line; char c = 'L';
        assemblyfile <<"sys_exit	equ	1\n"
                        "sys_read	equ	3\n"
                        "sys_write	equ	4\n"
                        "stdin		equ	0 ; default keyboard\n"
                        "stdout		equ	1 ; default terminal screen\n"
                        "stderr		equ	3" << endl;
        assemblyfile << "\n\tsection .data\n" << endl;
        assemblyfile << "\tuserMsg		db      'Enter an integer(less than 32,765): '\n"
                        "\tlenUserMsg	equ	$-userMsg\n"
                        "\tdisplayMsg	db	'You entered: '\n"
                        "\tlenDisplayMsg	equ	$-displayMsg\n"
                        "\tnewline		db	0xA 	; 0xA 0xD is ASCII <LF><CR>\n\n"
                        "\tTen             DW      10  ;Used in converting to base ten.\n\n"
                        "\tprintTempchar	db	'Tempchar = : '\n"
                        "\tlenprintTempchar	equ 	$-printTempchar\n\n"
                        "\tResult          db      'Ans = '\n"
                        "\tResultValue	db	'aaaaa'\n"
                        "\tdb	0xA\n"		
                        "\tResultEnd       equ 	$-Result    ; $=> here, subtract address Result\n\n"
                        "\tnum		times 6 db 'ABCDEF'\n"
                        "\tnumEnd		equ	$-num" << endl;
        while (symboltablefile >> word >> type >> value >> address >> segment) {
            if (type != "CLASS" && type != "PROCEDURE" && type != "CALL"){
                if (type == "CONST" || type == "$NUMBER"){
                    assemblyfile << "\t" << word << " DW " << value << endl;
                }
            }
        }
        // this is for the .BSS section of the assembly code
        assemblyfile << "\n\tsection .bss" << endl;
        symboltablefile.clear();
        symboltablefile.seekg(0, ios::beg);
        assemblyfile << " \n\tTempChar        RESB       1              ;temp space for use by GetNextChar\n"
                         "\ttestchar        RESB       1\n"	
                         "\tReadInt         RESW       1              ;Temporary storage GetAnInteger.\n"	
                         "\ttempint         RESW	   1              ;Used in converting to base ten.\n"
                         "\tnegflag         RESB       1              ;P=positive, N=negative\n" << endl;
        while (symboltablefile >> word >> type >> value >> address >> segment) {
            if (type != "CLASS" && type != "PROCEDURE" && type != "CALL"){
                if (type == "VAR" || type == "$IDENTIFIER" || type == "$TEMPORARY" ){
                    assemblyfile << "\t" << word << " resw 1" << endl;
                }
            }
        }
        // this is for the .TEXT section of the assembly code
        assemblyfile << "\tglobal _start\n" << endl;
        assemblyfile << "\tsection .text\n" << endl;
        assemblyfile << "\t_start:	nop\n" << endl;
        assemblyfile << "\t\tAgain:\n" << endl;
        // reading the quads file
        ifstream quadfile("quads.txt");
        while (getline(quadfile, line)) {
            stringstream ss(line);
            string op, operand1, operand2, result;
            string nextop, nextoperand1, nextoperand2, nextresult;
            ss >> op >> operand1 >> operand2 >> result;
            if (operand1 == "CIN" || operand1 == "IN"){
                // this TO INPUT A NUMBER FROM THE USER
                assemblyfile << "\t\tcall PrintString" << endl;
                assemblyfile << "\t\tcall GetAnInteger"<< endl;
                assemblyfile << "\t\tmov ax, [ReadInt]" << endl;
                assemblyfile << "\t\tmov [" << operand2 << "], ax\n" << endl;
            }
            else if (op == "FUNCTIONCALL"){
                assemblyfile << "\t\tcall " << operand1 << endl;
                assemblyfile << "\t\tcall exitpgm" << endl;
            }
            else if (op == "PROCEDURE"){
                assemblyfile << "\t\tfini" << endl;
            }
            else if (op == "WHILE"){
                assemblyfile << "\t\t" << operand1 << ": nop" << endl;
            }
            else if (op[0] == 'W' && op != "WHILE"){
                assemblyfile << "\t\tjmp " << op << endl;
            }
            else if (op == "jmp"){
                assemblyfile << "\t\tjmp " << operand1 << endl;
            }
            else if (operand1 == "PRINT" || operand1 == "OUT"){
                // this TO OUTPUT A NUMBER TO THE USER
                assemblyfile << "\n\t\tmov ax,["<<operand2<<"]\n"
                                    "\t\tcall ConvertIntegerToString\n"      
                                    "\t\tmov eax, 4	;write   ; 'Ans = value <newline>\n"
                                    "\t\tmov ebx, 1	; default sys_out\n"
                                    "\t\tmov ecx, Result   	;start address for print\n"
                                    "\t\tmov edx, ResultEnd ;Length to write.\n"
                                    "\t\tint 80h\n" << endl;
            } else if (op == "+") {
                assemblyfile << "\t\tmov ax, [" << operand1 << "]" << endl;
                assemblyfile << "\t\tadd ax, ["<< operand2 << "]"<< endl;
                assemblyfile << "\t\tmov [" << result << "], ax" << endl;
            } else if (op == "-") {
                assemblyfile << "\t\tmov ax, [" << operand1 <<"]"<< endl;
                assemblyfile << "\t\tsub ax, ["<< operand2 << "]"<<endl;
                assemblyfile << "\t\tmov [" << result << "], ax" << endl;
            } else if (op == "*") {
                assemblyfile << "\t\tmov ax, [" << operand1 <<"]"<< endl;
                assemblyfile << "\t\tmul word ["<< operand2 <<"]"<< endl;
                assemblyfile << "\t\tmov [" << result << "], ax" << endl;
            } else if (op == "/") {
                assemblyfile << "\t\tmov dx, 0" << endl;
                assemblyfile << "\t\tmov ax, [" << operand1<< "]" << endl;
                assemblyfile << "\t\tmov bx, [" << operand2<< "]" << endl;
                assemblyfile << "\t\tdiv word bx" << endl;
                assemblyfile << "\t\tmov [" << result << "], ax" << endl;
            } else if (op == "=") {
                assemblyfile << "\t\tmov ax, [" << operand2<< "]" << endl;
                assemblyfile << "\t\tmov [" << operand1 << "], ax" << endl;
            } else if (op == "<"){
                assemblyfile << "\t\tmov ax, [" << operand1<< "]" << endl;
                assemblyfile << "\t\tcmp ax, [" << operand2<< "]" << endl;
                assemblyfile << "\t\tjge " << result << endl;
            } else if (op == ">"){
                assemblyfile << "\t\tmov ax, [" << operand1<< "]" << endl;
                assemblyfile << "\t\tcmp ax, [" << operand2<< "]" << endl;
                assemblyfile << "\t\tjle " << result << endl;
            } else if (op == "<="){
                assemblyfile << "\t\tmov ax, [" << operand1<< "]" << endl;
                assemblyfile << "\t\tcmp ax, [" << operand2<< "]" << endl;
                assemblyfile << "\t\tjg " << result << endl;
            } else if (op == ">="){
                assemblyfile << "\t\tmov ax, [" << operand1<< "]" << endl;
                assemblyfile << "\t\tcmp ax, [" << operand2<< "]" << endl;
                assemblyfile << "\t\tjl " << result << endl;
            } else if (op == "!="){
                assemblyfile << "\t\tmov ax, [" << operand1<< "]" << endl;
                assemblyfile << "\t\tcmp ax, [" << operand2<< "]" << endl;
                assemblyfile << "\t\tje " << result << endl;
            } else if (op == "=="){
                assemblyfile << "\t\tmov ax, [" << operand1<< "]" << endl;
                assemblyfile << "\t\tcmp ax, [" << operand2<< "]" << endl;
                assemblyfile << "\t\tjne " << result << endl;
            } else if (op[0] == c){
                assemblyfile << "\t\t" << op << ": nop" << endl;
            } 
        }
        assemblyfile << "\n\t\t;jmp     Again\n"
                        "\n\t; exit code" << endl;
        assemblyfile << "fini:\n"
                        "\tmov eax,sys_exit ;terminate, sys_exit = 1 \n"
                        "\txor ebx,ebx	      ;zero in ebx indicates success\n"
                        "\tint 80h\n" << endl;
        assemblyfile << "\n\t; subpgm to print a string\n"
        // printstring
                        "\tPrintString:\n"
                        "\tpush    ax              ;Save registers\n"
                        "\tpush    dx\n"
                        "\tmov eax, 4		;Linux print device register\n"
                        "\tmov ebx, 1		; print default output device\n"
                        "\tmov ecx, userMsg	; pointer to string\n"
                        "\tmov edx, lenUserMsg\n"
                        "\tint	80h		; interrupt 80 hex, call kernel\n"
                        "\tpop     dx              ;Restore registers\n"
                        "\tpop     ax\n"
                        "\tret\n" << endl;
        assemblyfile << "\n\t; subpgm to get an integer\n"
        // getaninteger
                        "\tGetAnInteger:\n"
                        "\tmov eax,3	;read\n"
                        "\tmov ebx,2	;device\n"
                        "\tmov ecx, num	;buffer address\n"
                        "\tmov edx,6	;max characters\n"
                        "\tint 0x80\n"
                        "\tmov edx,eax 	; eax contains the number of character read including <lf>\n"
                        "\tmov eax, 4\n"
                        "\tmov ebx, 1\n"
                        "\tmov ecx, num\n"
                        "\tint 80h\n"<< endl;
        assemblyfile << "\n\t; subpgm to convert a string to an integer\n"
        // convertstringtointeger
                        "\tConvertStringToInteger:\n"
                        "\tmov ax,0	;hold integer\n"
                        "\tmov [ReadInt],ax ;initialize 16 bit number to zero\n"
                        "\tmov ecx,num	;pt - 1st or next digit of number as a string terminated by <lf>\n"
                        "\tmov bx,0\n"
                        "\tmov bl, byte [ecx] ;contains first or next digit\n"
                        "Next:\n"
                        "\tsub bl,'0'	;convert character to number\n"
                        "\tmov ax,[ReadInt]\n"
                        "\tmov dx,10\n"
                        "\tmul dx		;eax = eax * 10\n"
                        "\tadd ax,bx\n"
                        "\tmov [ReadInt], ax\n"
                        "\tmov bx,0\n"
                        "\tadd ecx,1 	;pt = pt + 1\n"
                        "\tmov bl, byte[ecx]\n"
                        "\tcmp bl,0xA	;is it a <lf>\n"
                        "\tjne Next	; get next digit\n"
                        "\tret\n" << endl;
        assemblyfile << "\n\t; subpgm to convert an integer to a string\n"
        // convertintegertostring
                        "\tConvertIntegerToString:\n"
                        "\tmov ebx, ResultValue + 4   ;Store the integer as a five digit char string at Result for printing\n"
                        "ConvertLoop:\n"
                        "\tsub dx,dx  ; repeatedly divide dx:ax by 10 to obtain last digit of number\n"
                        "\t; to obtain last digit of number\n"
                        "\tmov cx,10  ; as the remainder in the DX register.  Quotient in AX.\n"
                        "\tdiv cx\n"
                        "\tadd dl,'0' ; Add '0' to dl to convert from binary to character.\n"
                        "\tmov [ebx], dl\n"
                        "\tdec ebx\n"
                        "\tcmp ebx,ResultValue\n"
                        "\tjge ConvertLoop\n"
                        "\tret\n" << endl;
        // closing the files
        symboltablefile.close();
        assemblyfile.close();
    }
};
void processWord(ifstream& file, string& word, TableDrivenDFSA& table, int& currentState, ofstream& tokenizedfile, const string& toPrint) {
    char c;
    while (file.get(c)) {
        if (c == ' ' || c == '\n' || c == '\t') {
            continue;
        } else {
            int inputSymbol = table.getInputSymbol(c);
            currentState = table.nexxtState(currentState, inputSymbol);
            if (toPrint == "$CALL_NAME"){
                if (inputSymbol == 30){
                    file.unget();
                    tokenizedfile << word << " " << toPrint << endl;
                    word.clear();
                    break;
                } else {word += c;}
            } else {
                if (inputSymbol == 24) {
                    file.unget();
                    tokenizedfile << word << " " << toPrint << endl;
                    word.clear();
                    break;
                } else {
                    word += c;
                }   }   }   }   }
void lexicalAnalyzer(TableDrivenDFSA& table, const string& filename) {
    ifstream file(filename);
    ofstream tokenizedfile("tokenizedfile.txt");
    char c; string word;
    int currentState = 0; // Start at initial state
    bool finished = false;
    while (file.get(c)){
        if (c == ' ' || c == '\n' || c == '\t') {continue;}
        finished = false;
        currentState = 0;
        int inputSymbol = table.getInputSymbol(c);
        currentState = table.nextState(currentState, inputSymbol);

        while (!finished){
            switch (currentState) {
                    case 0:
                        tokenizedfile << word << " $COMMENT" << endl;
                        word.clear();
                        finished = true;
                        break;
                    case 1:
                        finished = true;
                        break;
                    case 2:
                        tokenizedfile << c << " $MULTIPLICATION" << endl;
                        finished = true;
                        break;
                    case 3:
                        // if the next character does not equal to , ; or space then keep concatenating else print the word and type 
                        if (file.peek() != ',' && file.peek() != ';' && file.peek() != ' ' && file.peek() != '+' && file.peek() != '-' && file.peek() != '*' && file.peek() != '/' && file.peek() != '=' && file.peek() != '<' && file.peek() != '>' && file.peek() != '!' && file.peek() != '(' && file.peek() != ')' && file.peek() != '{' && file.peek() != '}'){
                            word += c;
                            file.get(c);
                        } else{
                            word += c;
                            file.get(c);
                            inputSymbol = table.getInputSymbol(c);
                            currentState = table.nexxtState(currentState, inputSymbol);
                            file.unget();
                        }
                    break;
                    case 4:
                        tokenizedfile << "LIT"+word << " $NUMBER" << endl;
                        word.clear();
                        finished = true;
                        break;
                    case 5:
                        if (file.peek() != ',' && file.peek() != ';' && file.peek() != ' ' && file.peek() != '+' && file.peek() != '-' && file.peek() != '*' && file.peek() != '/' && file.peek() != '=' && file.peek() != '<' && file.peek() != '>' && file.peek() != '!' && file.peek() != '(' && file.peek() != ')' && file.peek() != '{' && file.peek() != '}' && file.peek() != '\n' && file.peek() != '\t'){
                            word += c;
                            file.get(c);
                        } else{
                            word += c;
                            file.get(c);
                            inputSymbol = table.getInputSymbol(c);
                            currentState = table.nexxtState(currentState, inputSymbol);
                            file.unget();
                        }
                        break;
                    case 6:
                        if (word == "CONST"){
                            tokenizedfile << word << " $CONSTANT" << endl; word.clear();
                        } else if (word == "VAR"){
                            tokenizedfile << word << " $VARIABLE" << endl; word.clear();
                        } else if (word == "BEGIN"){
                            tokenizedfile << word << " $BEGIN" << endl; word.clear();
                        } else if (word == "END"){
                            tokenizedfile << word << " $END" << endl; word.clear();
                        } else if (word == "IF"){
                            tokenizedfile << word << " $IF" << endl; word.clear();
                        } else if (word == "THEN"){
                            tokenizedfile << word << " $THEN" << endl; word.clear();
                        } else if (word == "ELSE"){
                            tokenizedfile << word << " $ELSE" << endl; word.clear();
                        } else if (word == "IN") {
                            tokenizedfile << word << " $IN" << endl; word.clear();
                        }else if (word == "OUT") {
                            tokenizedfile << word << " $OUT" << endl; word.clear();
                        } else if (word == "WHILE"){
                            tokenizedfile << word << " $WHILE" << endl; word.clear();
                        } else if (word == "DO"){
                            tokenizedfile << word << " $DO" << endl; word.clear();
                        } else if (word == "PROCEDURE"){
                            tokenizedfile << word << " $PROCEDURE" << endl; word.clear();
                            processWord(file, word, table, currentState, tokenizedfile, "$PROCEDURE_NAME");
                        } else if (word == "CALL"){
                            tokenizedfile << word << " $CALL" << endl; word.clear();
                            processWord(file, word, table, currentState, tokenizedfile, "$CALL_NAME");
                        } else if (word == "ODD"){tokenizedfile << word << " $ODD" << endl; word.clear();} 
                          else if (word == "CLASS"){
                            tokenizedfile << word << " $CLASS" << endl; 
                            word.clear();
                            processWord(file, word, table, currentState, tokenizedfile, "$CLASS_NAME");
                        } else {tokenizedfile << word << " $IDENTIFIER" << endl; word.clear(); finished = true;}
                        finished = true;
                        break;
                    case 7:
                        word += c;
                        if (file.peek() == '*'){
                            file.get(c);
                            word += c;
                            inputSymbol = table.getInputSymbol(c);
                            currentState = table.nexxtState(currentState, inputSymbol);
                        }
                        else {
                            file.get(c);
                            inputSymbol = table.getInputSymbol(c);
                            currentState = table.nexxtState(currentState, inputSymbol);
                            file.unget();
                        }
                        break;
                    case 8:
                        if (file.peek() == '*'){
                            file.get(c);
                            word += c;
                            inputSymbol = table.getInputSymbol(c);
                            currentState = table.nexxtState(currentState, inputSymbol);
                        }
                        else {
                            file.get(c);
                            inputSymbol = table.getInputSymbol(c);
                            currentState = table.nexxtState(currentState, inputSymbol);
                        }
                        break;
                    case 9:
                        if (file.peek() == '/'){
                            file.get(c);
                            word += c;
                            inputSymbol = table.getInputSymbol(c);
                            currentState = table.nexxtState(currentState, inputSymbol);
                        }
                        else {
                            file.get(c);
                            inputSymbol = table.getInputSymbol(c);
                            currentState = table.nexxtState(currentState, inputSymbol);
                        }
                        break;
                    case 10:
                        tokenizedfile << word << " $DIVISION" << endl;
                        word.clear();
                        finished = true;
                        break;
                    case 11:
                        word += c;
                        if (file.peek() == '='){
                            file.get(c);
                            word += c;
                            inputSymbol = table.getInputSymbol(c);
                            currentState = table.nexxtState(currentState, inputSymbol);
                        }
                        else {
                            file.get(c);
                            inputSymbol = table.getInputSymbol(c);
                            currentState = table.nexxtState(currentState, inputSymbol);
                            file.unget();
                        }
                        break;
                    case 12:
                        tokenizedfile << word << " $ASSIGNMENT" << endl;
                        word.clear();
                        finished = true;
                        break;
                    case 13:
                        tokenizedfile << word << " $EQUAL" << endl;
                        word.clear();
                        finished = true;
                        break;
                    case 14:
                        word += c;
                        if (file.peek() == '='){
                            file.get(c);
                            word += c;
                            inputSymbol = table.getInputSymbol(c);
                            currentState = table.nexxtState(currentState, inputSymbol);
                        }
                        else {
                            file.get(c);
                            inputSymbol = table.getInputSymbol(c);
                            currentState = table.nexxtState(currentState, inputSymbol);
                            file.unget();
                        }
                        break;
                    case 15:
                        tokenizedfile << word << " $LESS_THAN" << endl;
                        word.clear();
                        finished = true;
                        break;
                    case 16:
                        tokenizedfile << word << " $LESS_THAN_OR_EQUAL" << endl;
                        word.clear();
                        finished = true;
                        break;
                    case 17:
                        word += c;
                        if (file.peek() == '='){
                            file.get(c);
                            word += c;
                            inputSymbol = table.getInputSymbol(c);
                            currentState = table.nexxtState(currentState, inputSymbol);
                        }
                        else {
                            file.get(c);
                            inputSymbol = table.getInputSymbol(c);
                            currentState = table.nexxtState(currentState, inputSymbol);
                            file.unget();
                        }
                        break;
                    case 18:
                        tokenizedfile << word << " $GREATER_THAN" << endl;
                        word.clear();
                        finished = true;
                        break;
                    case 19:
                        tokenizedfile << word << " $GREATER_THAN_OR_EQUAL" << endl;
                        word.clear();
                        finished = true;
                        break;
                    case 20:
                        tokenizedfile << c << " $ADDITION" << endl;
                        finished = true;
                        break;
                    case 21:
                        tokenizedfile << c << " $SUBTRACTION" << endl;
                        finished = true;
                        break;
                    case 22:
                        tokenizedfile << c << " $LEFT_PARENTHESIS" << endl;
                        finished = true;
                        break;
                    case 23:
                        tokenizedfile << c << " $RIGHT_PARENTHESIS" << endl;
                        finished = true;
                        break;
                    case 24:
                        tokenizedfile << c << " $LEFT_CURLY_BRACE" << endl;
                        finished = true;
                        break;  
                    case 25:
                        tokenizedfile << c << " $RIGHT_CURLY_BRACE" << endl;
                        finished = true;
                        break;
                    case 26:
                        word += c;
                        if (file.peek() == '='){
                            file.get(c);
                            word += c;
                            currentState = table.nexxtState(currentState, inputSymbol);
                        }
                        else {
                            file.get(c);
                            inputSymbol = table.getInputSymbol(c);
                            currentState = table.nexxtState(currentState, inputSymbol);
                            file.unget();
                        }
                        break;
                    case 27:
                        tokenizedfile << word << " $EXCLAMATION" << endl;
                        word.clear();
                        finished = true;
                        break;
                    case 28:
                        tokenizedfile << word << " $NOT_EQUAL" << endl;
                        word.clear();
                        finished = true;
                        break;
                    case 29:
                        tokenizedfile << c << " $COMMA" << endl;
                        finished = true;
                        break;
                    case 30:
                        tokenizedfile << c << " $SEMICOLON" << endl;
                        finished = true;
                        break;
                    }
        } 
    }
    file.close();
    tokenizedfile.close();
}
void addSymbolTable(string symbolarray[100][5], string word, string type, string value, int &address, string segment, int &counter){
    // Generate address based on the codeaddress
    int currentAddress = 0;
    if (counter < 1) { currentAddress = 0; address -= 2; } 
    else { currentAddress = address; }
    symbolarray[counter][0] = word;
    symbolarray[counter][1] = type;
    symbolarray[counter][2] = value;
    symbolarray[counter][3] = to_string(currentAddress);
    symbolarray[counter][4] = segment;
    counter++;
}
void SymbolTable(SymbolTableDFSA &STable, const string& filename){
    ifstream file(filename);
    ofstream symboltable("symboltable.txt");
    string word, type;
    int currentState= 0;    int address = 0;    int counter = 0;
    int codeaddress = 0;bool finished = false;  int inputSymbol;
    // array to store the symbol table
    string symbolarray[100][5];
    while (!file.eof()){
        file >> word >> type;
        finished = false;
        string word1, type1; string value = "0"; string segment = "$DATASEGMENT";
        inputSymbol = STable.InputSymbolTable(type);
        currentState = STable.nextState(currentState, inputSymbol);
        while (!finished){
            switch (currentState){
                case 0:
                    file >> word >> type;
                    inputSymbol = STable.InputSymbolTable(type);
                    currentState = STable.nextState(currentState, inputSymbol);
                    finished = true;
                    break;
                case 1:
                    type1 = word;
                    file >> word >> type;
                    inputSymbol = STable.InputSymbolTable(type);
                    currentState = STable.nextState(currentState, inputSymbol);
                    segment = "$CODESEGMENT";
                    break;
                case 2:
                    word1 = word;
                    file >> word >> type;
                    inputSymbol = STable.InputSymbolTable(type);
                    currentState = STable.nextState(currentState, inputSymbol);
                    break;
                case 3:
                    if (type == "$NUMBER" || type == "$IDENTIFIER"){
                        if (type == "$NUMBER"){value = word.substr(3);} else {value = "0";}
                        addSymbolTable(symbolarray, word, type, value, address, segment, counter);
                        address += 2;
                        file >> word >> type;
                        inputSymbol = STable.InputSymbolTable(type);
                        currentState = STable.nextState(currentState, inputSymbol);
                    }
                    if (type == "$SEMICOLON" || type == "$LEFT_CURLY_BRACE"){
                        if (word1 == ""){finished = true;}
                        else {
                        addSymbolTable(symbolarray, word1, type1, value, address, segment, counter);
                        address += 2;
                        finished = true;
                        break;}
                    } else if (type == "$RIGHT_CURLY_BRACE"){
                        currentState = 12;
                    } 
                    else {
                        // get the next word and type
                        file >> word >> type;
                        inputSymbol = STable.InputSymbolTable(type);
                        currentState = STable.nextState(currentState, inputSymbol);
                    }
                    break;
                case 4: // constant
                    if (type == "$CONSTANT"){type1 = word;}
                    file >> word >> type;
                    inputSymbol = STable.InputSymbolTable(type);
                    currentState = STable.nextState(currentState, inputSymbol);
                    break;
                case 5: // identifier
                    word1 = word;
                    file >> word >> type;
                    inputSymbol = STable.InputSymbolTable(type);
                    currentState = STable.nextState(currentState, inputSymbol);
                    break;
                case 6: // assignment
                    file >> word >> type;
                    inputSymbol = STable.InputSymbolTable(type);
                    currentState = STable.nextState(currentState, inputSymbol);
                    break;  
                case 7: // number
                    value = word.substr(3);
                    file >> word >> type;
                    if (type == "$COMMA"){
                        addSymbolTable(symbolarray, word1, type1, value, address, segment, counter);
                        address += 2;
                        currentState = 4;
                    } else {
                        inputSymbol = STable.InputSymbolTable(type);
                        currentState = STable.nextState(currentState, inputSymbol);
                    }
                    break;
                case 8: //VAR STATE
                    if (type == "$VARIABLE"){type1 = word;}
                    file >> word >> type;
                    inputSymbol = STable.InputSymbolTable(type);
                    currentState = STable.nextState(currentState, inputSymbol);
                    break;
                case 9: // identifier
                    word1 = word;
                    file >> word >> type;
                    if (type == "$COMMA"){
                        addSymbolTable(symbolarray, word1, type1, value, address, segment, counter);
                        address += 2;
                        currentState = 8;
                    } else {
                        inputSymbol = STable.InputSymbolTable(type);
                        currentState = STable.nextState(currentState, inputSymbol);
                    }
                    break;
                case 10:
                    if (type == "$BEGIN" || type == "$END" || type == "$IF" || type == "$THEN" || type == "$ELSE" || type == "$WHILE" || type == "$DO" || type == "$ODD" || type == "$CLASS"){
                        segment = "$CODESEGMENT"; value = "0";
                        //addSymbolTable(symbolarray, word, type, value, address, segment, counter);
                        address += 2;
                        finished = true;
                    } else if (type == "$PROCEDURE" || type == "$CALL"){
                        currentState = 1;
                        
                    } else {
                        file >> word >> type;
                        inputSymbol = STable.InputSymbolTable(type);
                        currentState = STable.nextState(currentState, inputSymbol);
                    }
                    if (file.eof()){
                        currentState = 12;
                    }
                break;
                case 11:
                    value = word.substr(3);
                    addSymbolTable(symbolarray, word, type, value, address, segment, counter);
                    address += 2;
                    file >> word >> type;
                    inputSymbol = STable.InputSymbolTable(type);
                    currentState = STable.nextState(currentState, inputSymbol);
                    if (file.eof()){
                        currentState = 12;
                    }
                    break;
                case 12: // end of pass 1
                    // cout << "End of pass 1" << endl;
                    finished = true;
                break;       
            }
        }
    }
    // ADDING 10 TEMPORARY VARIABLES TO THE SYMBOL TABLE
    for (int i = 1; i < 11; i++){
            symbolarray[counter][0] = "T" + to_string(i);
            symbolarray[counter][1] = "$TEMPORARY";
            symbolarray[counter][2] = "0";
            symbolarray[counter][3] = to_string(address);
            symbolarray[counter][4] = "$DATASEGMENT";
            counter++;
            address += 2;
        }
    // remove duplicates from the symbol table
    for (int i = 0; i < counter; i++){
        for (int j = i+1; j < counter; j++){
            if (symbolarray[i][0] == symbolarray[j][0]){
                symbolarray[j][0] = "";
                symbolarray[j][1] = "";
                symbolarray[j][2] = "";
                symbolarray[j][3] = "";
                symbolarray[j][4] = "";
            }
        }
    }
    // print the symbol table
    for (int i = 0; i < counter; i++){
        symboltable << symbolarray[i][0] << " " << symbolarray[i][1] << " " << symbolarray[i][2] << " " << symbolarray[i][3] << " " << symbolarray[i][4] << endl;
    } 
    file.close();
    symboltable.close();
}
void PDA(PushdownAutomata &PDA, string filename, string symboltable){
    // READ THE FILE and the symbol table
    ifstream file;              file.open(filename);
    ifstream symboltablefile;   symboltablefile.open(symboltable);
    ofstream quadfile ("quads.txt");
    string word, type;
    int currentState = 0;       stack<string> myStack; stack<string> label; stack<string> whilestack;
    // all variable needed to perform the PDA
    string operatorstate = ""; int operatorinput = 0; int lastoperator = 0; string lastoperatorstring;
    bool finished = false; int inputSymbol = 0;
    myStack.push("$");  lastoperatorstring = "$";
    int i = 1; int l = 1; int j = 1;
    while (file >> word >> type){
        if (type == "$CLASS" || type == "$CLASS_NAME" || type == "$LEFT_CURLY_BRACE"){ continue;}
        if (type == "$CONSTANT"){while (type != "$SEMICOLON"){file >> word >> type;}file >> word >> type;}
        if (type == "$VARIABLE"){while (type != "$SEMICOLON"){file >> word >> type;}file >> word >> type;}
        // getting the input symbol
        finished = false;                               currentState = 0;
        string op1;                                     int opp;
        inputSymbol = PDA.InputsforPDA(type);
        currentState = PDA.QTransitionFunction(currentState, inputSymbol);
        // IF THE WORD IS A NUMBER OR A IDENTIFIFIER PUSH INTO THE STACK
        if (type == "$NUMBER" || type == "$IDENTIFIER" || type == "$CLASS_NAME" || type == "$PROCEDURE_NAME" || type == "$CALL_NAME"){
            myStack.push(word);
            //cout << "pushed " << word << " into the stack" << endl;
        } else {
            // IF IT IS AN OPERATOR THEN GET THE OPERATOR INPUT
            opp = PDA.operatorinputs(type);
            op1 = PDA.Operatorstate(lastoperator, opp, lastoperatorstring, type);
            //cout << type << " " << opp << " " << op1 << endl;
        }
        cout << word << " " << type << " " << currentState << " " << inputSymbol << endl;
        while (!finished){
            string operatorstate; string op;
            switch (currentState){
                case 0: // Start state
                    cout << "stmt" << word << " "<< type << endl;
                    if (type == "$IDENTIFIER" || type == "$NUMBER" || type == "$CLASS_NAME" || type == "$PROCEDURE_NAME" || type == "$CALL_NAME"){;}
                    else {
                        operatorinput = PDA.operatorinputs(type);
                        operatorstate = PDA.Operatorstate(lastoperator, operatorinput, lastoperatorstring, type);
                        op = word;
                    }
                    file >> word >> type;
                    //cout << word<< " " << type << endl;
                    inputSymbol = PDA.InputsforPDA(type);
                    currentState = PDA.QTransitionFunction(currentState, inputSymbol);
                    cout << word << " " << type << " " << currentState << " " << inputSymbol << endl;
                break;
                case 1: // empty
                break;
                case 2: // simple statement
                    //cout << "simple statement" << endl;
                    if (type == "$IDENTIFIER" || type == "$NUMBER" || type == "$CLASS_NAME" || type == "$PROCEDURE_NAME" || type == "$CALL_NAME"){;} 
                    else {
                        operatorinput = PDA.operatorinputs(type);
                        operatorstate = PDA.Operatorstate(lastoperator, operatorinput, lastoperatorstring, type);
                        op = word;
                    }
                    file >> word >> type;
                    inputSymbol = PDA.InputsforPDA(type);
                    currentState = PDA.QTransitionFunction(currentState, inputSymbol);
                break;
                case 3:
                    if (lastoperatorstring == "$PROCEDURE"){
                        operatorstate = op1;
                        op = word;
                        //cout << operatorstate << " " << op << endl;
                        file >> word >> type;
                        inputSymbol = PDA.InputsforPDA(type);
                        currentState = PDA.QTransitionFunction(currentState, inputSymbol);
                        quadfile << "PROCEDURE " << word << " ?" << " ?" << endl;
                    } else {
                        operatorinput = PDA.operatorinputs(type);
                        operatorstate = PDA.Operatorstate(lastoperator, operatorinput, lastoperatorstring, type);
                        op = word;
                        //cout << operatorstate << " " << op << endl;
                        file >> word >> type;
                        inputSymbol = PDA.InputsforPDA(type);
                        currentState = PDA.QTransitionFunction(currentState, inputSymbol);
                    }
                    cout << word << " " << type << " " << currentState << " " << inputSymbol << endl;
                break;
                case 4:
                if (type == "$IDENTIFIER" || type == "$NUMBER" || type == "$CLASS_NAME" || type == "$PROCEDURE_NAME" || type == "$CALL_NAME"){;}
                    else {
                        operatorinput = PDA.operatorinputs(type);
                        operatorstate = PDA.Operatorstate(lastoperator, operatorinput, lastoperatorstring, type);
                        op = word;
                    }
                    file >> word >> type;
                    //cout << word<< " " << type << endl;
                    inputSymbol = PDA.InputsforPDA(type);
                    currentState = PDA.QTransitionFunction(currentState, inputSymbol);
                    cout << word << " " << type << " " << currentState << " " << inputSymbol << endl;
                break;
                case 5:
                break;
                case 6:
                    cout << word<< " ---------------------- "<<type << endl;
                    if (lastoperatorstring == "$LEFT_CURLY_BRACE"){
                        if (lastoperatorstring == "$LEFT_CURLY_BRACE"){
                            operatorstate = op1;
                            op = word;
                            //cout << operatorstate << " " << op << endl;
                            file >> word >> type;
                            inputSymbol = PDA.InputsforPDA(type);
                            currentState = PDA.QTransitionFunction(currentState, inputSymbol);
                        } else {
                            operatorinput = PDA.operatorinputs(type);
                            operatorstate = PDA.Operatorstate(lastoperator, operatorinput, lastoperatorstring, type);
                            op = word;
                            //cout << operatorstate << " " << op << endl;
                            file >> word >> type;
                            inputSymbol = PDA.InputsforPDA(type);
                            currentState = PDA.QTransitionFunction(currentState, inputSymbol);
                        }
                    } else {
                        if (type == "$IDENTIFIER" || type == "$NUMBER" || type == "$CLASS_NAME" || type == "$PROCEDURE_NAME" || type == "$CALL_NAME"){;}
                            else {
                                operatorinput = PDA.operatorinputs(type);
                                operatorstate = PDA.Operatorstate(lastoperator, operatorinput, lastoperatorstring, type);
                                op = word;
                            }
                            file >> word >> type;
                            //cout << word<< " "<<type << endl;
                            inputSymbol = PDA.InputsforPDA(type);
                            currentState = PDA.QTransitionFunction(currentState, inputSymbol);
                            }
                    cout << word << " " << type << " " << currentState << " " << inputSymbol << endl;
                break;
                case 7:
                    //cout << "stmt list" << endl;
                    //cout << word<< " "<<type << endl;
                    if (type == "$IDENTIFIER" || type == "$NUMBER" || type == "$CLASS_NAME" || type == "$PROCEDURE_NAME" || type == "$CALL_NAME"){;}
                    else {
                        operatorinput = PDA.operatorinputs(type);
                        operatorstate = PDA.Operatorstate(lastoperator, operatorinput, lastoperatorstring, type);
                        op = word;
                    }
                    file >> word >> type;
                    //cout << word<< " "<<type << endl;
                    inputSymbol = PDA.InputsforPDA(type);
                    currentState = PDA.QTransitionFunction(currentState, inputSymbol);
                    cout << word << " " << type << " " << currentState << " " << inputSymbol << endl;
                break;
                case 8: // if statement
                    //cout << "if statement" << endl;
                    if (lastoperatorstring == "$IF"){
                        operatorstate = op1;
                        op = word;
                        //cout << operatorstate << " " << op << endl;
                        file >> word >> type;
                        inputSymbol = PDA.InputsforPDA(type);
                        currentState = PDA.QTransitionFunction(currentState, inputSymbol);
                    } else {
                        operatorinput = PDA.operatorinputs(type);
                        operatorstate = PDA.Operatorstate(lastoperator, operatorinput, lastoperatorstring, type);
                        op = word;
                        //cout << operatorstate << " " << op << endl;
                        file >> word >> type;
                        inputSymbol = PDA.InputsforPDA(type);
                        currentState = PDA.QTransitionFunction(currentState, inputSymbol);
                    }
                break;
                case 9: // while statement
                    cout << "while statement" << endl;
                    operatorstate = op1;
                    op = word;
                    file >> word >> type;
                    inputSymbol = PDA.InputsforPDA(type);
                    currentState = PDA.QTransitionFunction(currentState, inputSymbol);
                    cout << word << " " << type << " " << currentState << " " << inputSymbol << endl;
                break;
                case 10: // Boolean expression state
                    //cout << "Boolean expression state" << endl;
                    if (type == "$IDENTIFIER" || type == "$NUMBER" || type == "$CLASS_NAME" || type == "$PROCEDURE_NAME" || type == "$CALL_NAME"){;} 
                    else {
                        if (type == "$LESS_THAN" || type == "$LESS_THAN_OR_EQUAL" || type == "$GREATER_THAN" || type == "$GREATER_THAN_OR_EQUAL" || type == "$EQUAL" || type == "$NOT_EQUAL"){;}
                        else {
                            operatorinput = PDA.operatorinputs(type);
                            operatorstate = PDA.Operatorstate(lastoperator, operatorinput, lastoperatorstring, type);
                            op = word;
                        }
                    }
                    file >> word >> type;
                    inputSymbol = PDA.InputsforPDA(type);
                    currentState = PDA.QTransitionFunction(currentState, inputSymbol);
                    cout << word << " " << type << " " << currentState << " " << inputSymbol << endl;
                break;
                case 11: // relational operator state
                    //cout << "relational operator state" << endl;
                    inputSymbol = PDA.InputsforPDA(type);
                    currentState = PDA.QTransitionFunction(currentState, inputSymbol);
                    operatorinput = PDA.operatorinputs(type);
                    operatorstate = PDA.Operatorstate(lastoperator, operatorinput, lastoperatorstring, type);
                    op = word;
                break;
                case 12: // Expression state
                //cout << "Expression state------------------------------------------------------------------" << endl;
                    if (type == "$NUMBER" || type == "$IDENTIFIER"|| type == "$CLASS_NAME" || type == "$PROCEDURE_NAME" || type == "$CALL_NAME") {;} 
                    else {
                        if (type == "$RIGHT_PARENTHESIS"){ currentState = 16; break; }
                        operatorinput = PDA.operatorinputs(type);
                        operatorstate = PDA.Operatorstate(lastoperator, operatorinput, lastoperatorstring, type);
                        op = word;
                    }
                    file >> word >> type;
                    inputSymbol = PDA.InputsforPDA(type);
                    currentState = PDA.QTransitionFunction(currentState, inputSymbol);
                    //cout << word << " " << type << " ----------------------------------------" << currentState << " " << inputSymbol << endl;
                break;
                case 13: // addop state
                    //cout << "addop state" << endl;
                    inputSymbol = PDA.InputsforPDA(type);
                    currentState = PDA.QTransitionFunction(currentState, inputSymbol);
                    operatorinput = PDA.operatorinputs(type);
                    operatorstate = PDA.Operatorstate(lastoperator, operatorinput, lastoperatorstring, type);
                    op = word;
                    file >> word >> type;
                    //cout << word << " " << type << " " << currentState << " " << inputSymbol << endl;
                break;
                case 14: // term state
                    //cout << "term state" << endl;
                    file >> word >> type;
                    inputSymbol = PDA.InputsforPDA(type);
                    currentState = PDA.QTransitionFunction(currentState, inputSymbol);
                break;
                case 15: // mop state
                    //cout << "mop state" << endl;
                    operatorinput = PDA.operatorinputs(type);
                    operatorstate = PDA.Operatorstate(lastoperator, operatorinput, lastoperatorstring, type);
                    op = word;
                    file >> word >> type;
                    inputSymbol = PDA.InputsforPDA(type);
                    currentState = PDA.QTransitionFunction(currentState, inputSymbol);                   
                break;
                case 16: // factor state
                //cout << "factor state" << endl;
                    if (type == "$IDENTIFIER" || type == "$NUMBER"|| type == "$CLASS_NAME" || type == "$PROCEDURE_NAME" || type == "$CALL_NAME"){;} 
                    else {
                        operatorinput = PDA.operatorinputs(type);
                        operatorstate = PDA.Operatorstate(lastoperator, operatorinput, lastoperatorstring, type);
                        op = word;
                    }
                    file >> word >> type;
                    inputSymbol = PDA.InputsforPDA(type);
                    currentState = PDA.QTransitionFunction(currentState, inputSymbol);
                    cout << word << " " << type << " " << currentState << " " << inputSymbol << endl;
                break;
                case 17: // ERROR CHECKING CASE
                    cout << "PDA has entered an error state " << word << " " << type << " " << currentState << " " << inputSymbol << endl;
                    finished = true;
                break;
                case 18: // halt state
                    operatorinput = PDA.operatorinputs(type);
                    operatorstate = PDA.Operatorstate(lastoperator, operatorinput, lastoperatorstring, type);
                    op = word;
                break;
            }
            //cout << "here " << word << " " << type << " " << currentState << " " << inputSymbol << " " << operatorstate << " " << op << endl;
            switch (operatorstate[0]){
                case '<':
                    //cout << "pushing " << op << " into the stack" << endl;
                    myStack.push(op);
                    if (op == "WHILE"){
                        //cout << "W" << l << " ?" << " ?" << " ?" << endl;
                        whilestack.push("W" + to_string(l));
                        quadfile << "WHILE " << whilestack.top() << " ?" << " ?" << " ?" << endl;
                    }
                    if (op == "IF"){
                        //cout << op << " ?" << " ?" << " ?" << endl;
                        quadfile << op << " ?" << " ?" << " ?" << endl;
                    }
                break;
                case '>':
                    if (op == ";" || op == ")" || op == "}"){
                        //cout << "popping " << op << " from the stack" << endl;
                        // current stack
                        stack<string> tempstack = myStack;
                        while (!tempstack.empty()){
                            //cout << tempstack.top() << " ";
                            tempstack.pop();
                        }
                        //cout << endl;
                        PDA.popQuads(myStack, op, quadfile, label, i, j, l, whilestack);    
                        if (op == ";" || op == "}"){
                            currentState = 0;
                            i = 1;
                            finished = true;
                            //cout << "PDA has accepted the input " << word << " " << type << endl;
                        }
                    } else if (op == "THEN" || op == "DO") { 
                       // cout << "popping " << op << " quad the stack" << endl;
                        PDA.popQuads(myStack, op, quadfile, label, i, j, l, whilestack);
                        //cout << "pushing " << op << " into the stack" << endl;
                        myStack.push(op);
                        j++; l++;
                    } else {
                        PDA.popQuads(myStack, op, quadfile, label, i, j, l, whilestack);
                        myStack.push(op);
                        //cout << "pushing " << op << " into the stack" << endl;
                    }
                break;
                case '=':
                    myStack.push(word);
                break;
            }
            //cout << "reached the bottom of switch ! finished switch" << endl;
            if (type == "$IDENTIFIER" || type == "$NUMBER" || type == "$CLASS_NAME" || type == "$PROCEDURE_NAME" || type == "$CALL_NAME"){ // nonterminals just get pushed into the stack
                //cout << "pushing " << word << " into the stack" << endl;
                myStack.push(word);
                lastoperator = operatorinput;
            }
            //cout << "reached the bottom of while ! finished loop" << endl;
        }
        // IF THE STACK IS EMPTY PUSH $ INTO THE STACK
        if (myStack.empty()){
            cout << "pushing $ into the stack" << endl;
            myStack.push("$");
        }
    }
    // print the stack
    stack<string> tempstack = myStack;
    while (!tempstack.empty()){
        //cout << tempstack.top() << " ";
        tempstack.pop();
    }
    cout << endl;
    // print the label stack
    stack<string> templabel = label;
    while (!templabel.empty()){
        //cout << templabel.top() << " ";
        templabel.pop();
    }

    file.close();
}
int main() {
    class TableDrivenDFSA t;
    class SymbolTableDFSA st;
    class PushdownAutomata pda;
    //lexicalAnalyzer(t, "sample.txt");
    cout << "Lexical analysis done" << endl;
    //SymbolTable(st, "tokenizedfile.txt");
    cout << "Symbol table generated" << endl;
    //PDA(pda, "tokenizedfile.txt", "symboltable.txt");    
    pda.generateAssemblyCode();
    cout << "Assembly code generated" << endl;
    return 0;
}
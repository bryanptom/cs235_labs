#ifndef EXPRESSIONMANAGER_H
#define EXPRESSIONMANAGER_H

#include "ExpressionManagerInterface.h"
#include <string>
#include <stack>
#include <sstream>
using namespace std;

class ExpressionManager : public ExpressionManagerInterface
{

private:
	string rawExpression;
	stack <string> infixStack;
	stack <string> braceStack;
	stack <string> operatorStack;
	stack <string> postfixStack;
	char operators[5] = { '+', '-', '*', '/', '%' };
	char braces[6] = { '[', ']', '{', '}', '(', ')' };
	char bracesOpen[3] = { '[',  '{',  '('};
	char bracesClose[3] = { ']', '}', ')' };
	char operatorsOne[2] = { '+', '-' };
	char operatorsTwo[3] = { '*', '/', '%' };

public:
	ExpressionManager() {}
	~ExpressionManager() {};

	void setExpression(string expres) {
		rawExpression = expres;
	}

	bool isIn(char a, char b[], int length) {
		for (int i = 0; i < length; i++) {
			if (b[i] == a) {
				return true;
			}
		}
		return false;
	}

	void clearStack(stack <string> theStack) {
		while (!theStack.empty()) {
			theStack.pop();
		}
	}

	int value() {
		return 0;
	}

	string infix() {
		istringstream expres(rawExpression);
		string item;
		while (expres >> item) {
			if (item == "{" || item == "[" || item == "(") {
				braceStack.push(item);
			}
			else if (item == "}") {
				if (braceStack.top() == "{") {
					braceStack.pop();
				}
			}
			else if (item == "]") {
				if (braceStack.top() == "[") {
					braceStack.pop();
				}
			}
			else if (item == ")") {
				if (braceStack.top() == "(") {
					braceStack.pop();
				}
			}
		}
		if (!braceStack.empty()) {
			while (!braceStack.empty()) {
				braceStack.pop();
			}
			clearStack(braceStack);
			return "Unbalanced";
		}

		istringstream raw(rawExpression);
		int operatorCount = 0;
		int operandCount = 0;
		string last;
		while (raw >> item) {
			if (isIn(item[0], operators, 5)) {
				operatorCount++;
				if (last == "operator") {
					return "Missing Operand";
				}
				else {
					last = "operator";
				}
				infixStack.push(item);
			}
			else if (isIn(item[0], braces, 6)) {
				infixStack.push(item);
			}

			else {
				try {
					int a = stoi(item);
					infixStack.push(item);
					operandCount++;

					if (last == "operand") {
						clearStack(infixStack);
						return "Mising Operator";
					}
					else {
						clearStack(infixStack);
						last = "operand";
					}
				}
				catch (...) {
					clearStack(infixStack);
					return "Illegal Operator";
				}

			}
		}

		if (isIn(infixStack.top()[0], operators, 5)) {
			clearStack(infixStack);
			return "Missing Operand";
		}
		clearStack(infixStack);
		return rawExpression;

	}

	string postfix() {
		istringstream expres(rawExpression);
		string item;
		stack <string> tempStack;
		int intCount = 0;
		bool brace = false;
		int depth = 0;
		int braceOpps = 0;

		while (expres >> item) {
			if (isIn(item[0], operators, 5)) {
				if (intCount < 2) {
					operatorStack.push(item);
				}
				else if (intCount > 1) {
					if (operatorStack.empty()) {
						tempStack.push(item);
						intCount--;
					}
					else if (isIn(item[0], operatorsTwo, 3)) {
						if (isIn(operatorStack.top()[0], operatorsTwo, 3)) {
							tempStack.push(operatorStack.top());
							operatorStack.pop();
							operatorStack.push(item);
							if (brace) {
								braceOpps++;
							}
							intCount--;
						}
						else {
							operatorStack.push(item);
							if (brace) {
								braceOpps++;
							}
						}
					}
					else if (isIn(item[0], operatorsOne, 2)) {
						if (!operatorStack.empty()) {
							while (!operatorStack.empty() && intCount > 1) {
								tempStack.push(operatorStack.top());
								operatorStack.pop();
								intCount--;
							}
							if (intCount > 1) {
								tempStack.push(item);
							}
							else {
								operatorStack.push(item);
								if (brace) { braceOpps++; }
							}
						}
					}
				}
			}
			else if (isIn(item[0], bracesOpen, 3)) {
				if (intCount != 0) {
					intCount--;
				}
				/*if (brace) { 
					depth++; 
				}
				if (tempStack.empty() && !brace) {
					brace = true;
					depth = 1;
				}*/
				depth++;
			}
			else if (isIn(item[0], bracesClose, 3)) {
				depth--;
				while (intCount > 1){
					if (!operatorStack.empty()) {
						tempStack.push(operatorStack.top());
						operatorStack.pop();
					}
					intCount--;
					/*if (depth == 0) {
						while (!operatorStack.empty()) {
							tempStack.push(operatorStack.top());
							operatorStack.pop();
						}
					}
					else if (depth > 0) {
						if (!operatorStack.empty()) {
							tempStack.push(operatorStack.top());
							operatorStack.pop();
						}
					}*/
				}
				
					
				intCount++;
			}
			else {
				tempStack.push(item);
				intCount++;
			}
		}

		while (!operatorStack.empty()) {
			tempStack.push(operatorStack.top());
			operatorStack.pop();
		}

		while (!tempStack.empty()) {
			postfixStack.push(tempStack.top());
			tempStack.pop();
		}

		string finish = "";
		while (!postfixStack.empty()) {
			finish.append(postfixStack.top());
			postfixStack.pop();
			finish.append(" ");
		}
		clearStack(operatorStack);
		clearStack(tempStack);
		clearStack(postfixStack);

		return finish;
	}

	string prefix() {
		return "";
	}

	string toString() const {
		return "";
	}
};

#endif
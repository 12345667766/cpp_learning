#include <vector>
#include <iostream>
#include <stack>

using namespace std;

class Solution {
public:
    bool isOperator(string s) {
        if (s == "+" || s == "-" || s == "*" || s == "/") {
            return true;
        }
        return false;
    }

    int myItoa(string& s) {
        int ans = 0;
        int count = 0;
        int origin = 1;
        if (s[0] == '+') {
            for (int i = s.size() - 1; i >= 1; i--) {
                ans += (s[i] - '0') * (origin);
                origin *= 10;
            }
            return ans;
        } else if (s[0] == '-') {
            for (int i = s.size() - 1; i >= 1; i--) {
                ans += (s[i] - '0') * (origin);
                origin *= 10;
            }
            return -ans;
        } else {
            for (int i = s.size() - 1; i >= 0; i--) {
                ans += (s[i] - '0') * origin;
                origin *= 10;
            }
        }
        return ans;
    }

    int evalRPN(vector<string>& tokens) {
        stack<int> stk;
        for (int i = 0; i < tokens.size(); i++) {
            if (isOperator(tokens[i])) {
                int first = stk.top();
                stk.pop();
                int second = stk.top();
                stk.pop();
                int res = 0;
                if (tokens[i] == "+") {
                    res = first + second;
                } else if (tokens[i] == "-") {
                    res = second - first;
                } else if (tokens[i] == "*") {
                    res = first * second;
                } else {
                    res = second / first;
                }
                stk.push(res);
            } else {
                int tmp = myItoa(tokens[i]);
                stk.push(tmp);
            }
        }
        return stk.top();
    }
};
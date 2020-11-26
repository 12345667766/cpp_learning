#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int x[4] = {-1, 0, 1, 0};
    int y[4] = {0, 1, 0, -1};
    bool dfs(vector<vector<char>>& board, vector<vector<int>>& visited, string& word, int row, int column, int index) {
        if (board[row][column] != word[index]) {
            return false;
        }
        if (index == word.size() - 1) {
            return true;
        }
        bool flag = false;
        visited[row][column] = 1;  
        for (int i = 0; i < 4; i++) {
            int newX = x[i] + row;
            int newY = y[i] + column;
            if (newX >= 0 && newX < board.size() && newY >= 0 && newY < board[0].size()) {
                if (!visited[newX][newY]) {
                    if (dfs(board, visited, word, newX, newY, index + 1)) {
                        flag = true;
                        break;
                    }
                }
            }                                        
        }
        visited[row][column] = 0;
        return flag;
    }

    bool exist(vector<vector<char>>& board, string word) {
        int row = board.size();
        int column = board[0].size();
        vector<vector<int>> visited(row, vector<int>(column, 0));
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                if (board[i][j] == word[0]) {
                    if(dfs(board, visited, word, i, j, 0)) {
                        return true;
                    }                    
                }
            }
        }
        return false;
    }
};
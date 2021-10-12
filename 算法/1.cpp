#include <vector>
#include <iostream>
#include <map>
#include <string.h>

using namespace std;

typedef struct{
    // 操作类别 空白移动 0 推动障碍物 1
    int operate;
    // 移动方向
    pair<int, int> direction;
    // 移动目标点
    pair<int, int> target;
} eachStep;

typedef struct{
    int len;
    vector<eachStep> path;
} shortestPath;

vector<shortestPath> result;

bool canGo(vector<vector<int>>& matrix, pair<int, int> origin, pair<int, int> target, pair<int, int> direction);
bool canPush(vector<vector<int>>& matrix, pair<int, int> origin, pair<int, int> direction);

// 8个方向
constexpr int dirs[8][2] = { { -1, -1 },
                  { -1, 0 },
                  { -1, 1 },
                  { 0, -1 },
                  { 0, 1 },
                  { 1, -1 },
                  { 1, 0 },
                  { 1, 1 } };

bool canGo(vector<vector<int>>& matrix, pair<int, int> origin, pair<int, int> target, pair<int, int> direction) {
    int nx = target.first, ny = target.second;
    // 如果目标位置是边界
    if (nx < 0 || nx >= matrix.size() || ny < 0 || ny >= matrix[0].size()) {
        return false;
    }
    // 目标位置是空位
    if (matrix[nx][ny] == 0) {
        return true;
    }
    // 目标位置是障碍物， 且障碍物可以推动
    if (matrix[nx][ny] == 1 && canPush(matrix, target, direction)) {
        return true;
    }
    return false;
}

bool canPush(vector<vector<int>>& matrix, pair<int, int> origin, pair<int, int> direction) {
    int nx = origin.first + direction.first, ny = origin.second + direction.second;
    // 如果目标位置的推动方向是边界
    if (nx < 0 || nx >= matrix.size() || ny < 0 || ny >= matrix[0].size()) {
        return false;
    }
    // 如果目标位置的推动方向是空位置
    if (matrix[nx][ny] == 0) {
        return true;
    }
    return false;
}

void findNearestPath(shortestPath spath, vector<vector<int>> visited, vector<vector<int>> matrix, pair<int, int> origin, pair<int, int> target, int step) {
    int currX = origin.first, currY = origin.second;
    if (currX < 0 || currX >= matrix.size() || currY < 0 || currY >= matrix[0].size() || visited[currX][currY]) {
        return;
    }
    if (currX == target.first && currY == target.second) {
        spath.len = step;
        result.push_back(spath);
        return;
    }
    cout << "hello, world" << endl;
    visited[origin.first][origin.second] = true;
    for (int _ = 0; _ < 8; ++_) {
        int nx = currX + dirs[_][0];
        int ny = currY + dirs[_][1];
        // 当前位置
        pair<int, int> currPos{currX, currY};
        // 当前位置的目标位置
        pair<int, int> currTargetPos{nx, ny};
        // 目标位置已经越界， 也就是当前位置就是边界了
        if (nx < 0 || nx >= matrix.size() || ny < 0 || ny >= matrix[0].size()) {
            return;
        }
        // 目标位置已经访问过
        if (visited[nx][ny] == true) {
            continue;
        }
        pair<int, int> direction{dirs[_][0], dirs[_][1]};
        // 如果不能走
        if (!canGo(matrix, currPos, currTargetPos, direction)) {
            cout << "world" << endl;
            return;
        }
        // 能走
        cout << "hello";
        cout << nx << " " << ny << endl;
        visited[nx][ny] = true;
        // 如果当前的下一个搜索位置是空位，直接走过去
        if (matrix[nx][ny] == 0) {
            // 更新地图
            matrix[currPos.first][currPos.second] = 0;
            matrix[currTargetPos.first][currTargetPos.second] = 2;
            spath.len = step + 1;
            spath.path.push_back({0, direction, currTargetPos});
            findNearestPath(spath ,visited, matrix, currPos, target, step + 1);
        }
        // 如果当前的下一个位置是可以推动的障碍物
        // 则更新地图， 往目标方向推动
        // 当前位置置为空位
        matrix[currPos.first][currPos.second] = 0;
        // 原本障碍物位置置为机器人位置
        matrix[currTargetPos.first][currTargetPos.second] = 2;
        // 障碍物后方位置置为障碍物
        matrix[currTargetPos.first + direction.first][currTargetPos.second + direction.second] = 1;
        findNearestPath(spath, visited, matrix, currPos, target, step + 1);
    }
}


int main(void) {
    vector<vector<int>> matrix = {
        {2,0,1,0,0},
        {1,0,1,1,1},
        {1,1,0,0,1},
        {1,0,1,1,0},
        {1,1,1,1,1}}; 
    shortestPath spath;
    vector<vector<int>> visited(5, vector<int>(5, false));
    pair<int, int> origin{0, 0};
    pair<int, int> target{3, 4};
    findNearestPath(spath, visited, matrix, origin, target, 0);
    cout << result.size() << endl;
    for (int i = 0; i < result.size(); i++) {
        cout << result[i].len << endl;
    }
    return 0;
}
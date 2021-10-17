#include <iostream>
#include <ctime>
#include <math.h>
#include <iostream>

using namespace std;

#include <vector>
#include <list>

const int kCost1 = 1; //直移一格消耗
const int kCost2 = 1; //斜移一格消耗

struct Point
{
    int x, y;                                                            //点坐标，这里为了方便按照C++的数组来计算，x代表横排，y代表竖列
    int F, G, H;                                                         //F=G+H
    Point *parent;                                                       //parent的坐标，这里没有用指针，从而简化代码
    std::vector<std::vector<int>> maze;
    Point(int _x, int _y, std::vector<std::vector<int>> _maze) : x(_x), y(_y), F(0), G(0), H(0), maze(_maze), parent(NULL) //变量初始化
    {
    }
};

class Astar
{
public:
    void InitAstar(std::vector<std::vector<int>> &_maze);
    std::list<Point *> GetPath(Point &startPoint, Point &endPoint);

    Point *findPath(Point &startPoint, Point &endPoint);
    std::vector<Point *> getSurroundPoints(Point *point);
    bool isCanreach(Point *point, Point *target); //判断某点是否可以用于下一步判断
    Point *isInList(const std::list<Point *> &list, const Point *point) const;           //判断开启/关闭列表中是否包含某点
    Point *getLeastFpoint();                                                             //从开启列表中返回F值最小的节点
    //计算FGH值
    int calcG(Point *temp_start, Point *point);
    int calcH(Point *point, Point *end);
    int calcF(Point *point);

    // 初始地图
    std::vector<std::vector<int>> maze;
    std::list<Point *> openList;  //开启列表
    std::list<Point *> closeList; //关闭列表
};

void Astar::InitAstar(std::vector<std::vector<int>> &_maze)
{
    maze = _maze;
}

int Astar::calcG(Point *temp_start, Point *point)
{
    int extraG = abs(point->x - temp_start->x) + abs(point->y - temp_start->y);
    int parentG = point->parent == NULL ? 0 : point->parent->G; //如果是初始节点，则其父节点是空
    return parentG + extraG;
}

int Astar::calcH(Point *point, Point *end)
{
    //用简单的欧几里得距离计算H，这个H的计算是关键，还有很多算法，没深入研究^_^
    return abs(end->x - point->x) + abs(end->y - point->y);
}

int Astar::calcF(Point *point)
{
    return point->G + point->H;
}

Point *Astar::getLeastFpoint()
{
    if (!openList.empty())
    {
        auto resPoint = openList.front();
        for (auto &point : openList)
            if (point->F < resPoint->F)
                resPoint = point;
        return resPoint;
    }
    return NULL;
}

Point *Astar::findPath(Point &startPoint, Point &endPoint)
{
    openList.push_back(new Point(startPoint.x, startPoint.y, startPoint.maze)); //置入起点,拷贝开辟一个节点，内外隔离
    while (!openList.empty())
    {
       // for (auto& v : closeList) {
      //      vector<vector<int>> ().swap(v->maze);
      //  }
        auto curPoint = getLeastFpoint(); //找到F值最小的点
        openList.remove(curPoint);        //从开启列表中删除
        closeList.push_back(curPoint);    //放到关闭列表
        //1,找到当前周围八个格中可以通过的格子
        auto surroundPoints = getSurroundPoints(curPoint);

        for (auto &target : surroundPoints)
        {
            //2,对某一个格子，如果它不在开启列表中，加入到开启列表，设置当前格为其父节点，计算F G H
            if (!isInList(openList, target))
            {
                target->parent = curPoint;

                target->G = calcG(curPoint, target);
                target->H = calcH(target, &endPoint);
                target->F = calcF(target);
                openList.push_back(target);
            }
            //3，对某一个格子，它在开启列表中，计算G值, 如果比原来的大, 就什么都不做, 否则设置它的父节点为当前点,并更新G和F
            else
            {
                int tempG = calcG(curPoint, target);
                if (tempG < target->G)
                {
                    target->parent = curPoint;

                    target->G = tempG;
                    target->F = calcF(target);
                }
            }
            Point *resPoint = isInList(openList, &endPoint);
            if (resPoint)
                return resPoint; //返回列表里的节点指针，不要用原来传入的endpoint指针，因为发生了深拷贝
        }
    }

    return NULL;
}

std::list<Point *> Astar::GetPath(Point &startPoint, Point &endPoint)
{
    Point *result = findPath(startPoint, endPoint);
    if (result == NULL) {
        return std::list<Point*>();
    }
    std::cout << "end point matrix: " << std::endl;
    auto vec = result->maze;
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[0].size(); j++) {
            std::cout << vec[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::list<Point *> path;
    //返回路径，如果没找到路径，返回空链表
    while (result)
    {
        path.push_front(result);
        result = result->parent;
    }

	//打印
	cout << "show path: " << endl;
	for (auto& v : path) {
		cout << v->x << " " << v->y << endl;
        vec[v->x][v->y] = 9;
        
	}
	cout << endl;

    // 清空临时开闭列表，防止重复执行GetPath导致结果异常
    openList.clear();
    closeList.clear();


    std::cout << "end point matrix: " << std::endl;
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[0].size(); j++) {
            std::cout << vec[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return path;
}

Point *Astar::isInList(const std::list<Point *> &list, const Point *point) const
{
    //判断某个节点是否在列表中，这里不能比较指针，因为每次加入列表是新开辟的节点，只能比较坐标
    for (auto p : list)
        if (p->x == point->x && p->y == point->y)
            return p;
    return NULL;
}


bool Astar::isCanreach(Point* s, Point* e) {
    if (isInList(closeList, e)) {
        return false;
    }
    if (e->x == s->x && e->y == s->y) {
        return false;
    }
    if (e->maze[e->x][e->y] == 0) {
        e->parent = s;
        return true;
    }

    // 是障碍物，需要判断是否可以被推动
    if (e->maze[e->x][e->y] == 1) {
        Point direction {e->x - s->x, e->y - s->y, maze};
        // 如果推动方向是东南西北
        if ((direction.x == 0 && direction.y == 1) || (direction.x == 0 && direction.y == -1) || (direction.x == -1 && direction.y == 0) ||(direction.x == 1 && direction.y == 0)) {
            if (e->x + direction.x >= 0 && e->x + direction.x < maze.size() && e->y + direction.y >= 0 && e->y + direction.y < maze[0].size()) {
                if (e->maze[e->x + direction.x][e->y + direction.y] == 0) {
                    e->maze[e->x][e->y] = 0;
                    e->maze[e->x + direction.x][e->y + direction.y] = 1;
                    e->parent = s;
                    return true;
                }
            }
        }
    }
    return false;
}

std::vector<Point *> Astar::getSurroundPoints(Point *point)
{
    std::vector<Point *> surroundPoints;

    for (int x = point->x - 1; x <= point->x + 1; x++) {
        for (int y = point->y - 1; y <= point->y + 1; y++) {
			if (x < 0 || x >= maze.size() || y <0 || y >= maze[0].size()) 
				continue;
            auto targetPoint = new Point(x, y, point->maze);
            if (isCanreach(point, targetPoint)) {
                surroundPoints.push_back(targetPoint);
            }
        }
    }

    return surroundPoints;
}

int main()
{
    clock_t startTime, endTime;
    startTime = clock();//计时开始
	//初始化地图，用二维矩阵代表地图，1表示障碍物，0表示可通
	vector<vector<int>> maze={
        {0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0,0,0,0},
        {0,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,0},
        {0,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,0},
        {0,1,0,0,1,0,0,0,1,0,0,0,0,1,0,1,1,0,1,0,0,0,0,0,0,0,0},
        {0,1,1,1,1,0,0,0,1,0,0,0,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};
	Astar astar;
	astar.InitAstar(maze);
 
	//设置起始和结束点
	Point start(0, 0, maze);
	Point end(13, 26, maze);
	//A*算法找寻路径
	list<Point *> path=astar.GetPath(start,end);

    endTime = clock();//计时结束
    cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	system("pause");
	return 0;
}
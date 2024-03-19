// #include <iostream>
// #include <vector>
// #include <cmath>
// #include <algorithm>
// #include <cstring>
// #include <climits>
// #define MAXN 100
// using namespace std;
//
// bool vis[MAXN][MAXN];
// int dp[MAXN][MAXN];
//
//
// /*
//  * 类定义
//  */
// class Point
// {
// public:
//     double x,y;
//     Point(){};  // 默认构造函数
//     Point(double x, double y): x(x), y(y) {};
//     Point operator-(const Point &p) const
//     {
//         Point result(x - p.x, y - p.y);
//         return result;
//     }
//     double operator*(const Point &p) const
//     {
//         return x * p.x + y * p.y;
//     }
//     Point operator+(const Point &p) const
//     {
//         Point result(x + p.x, y + p.y);
//         return result;
//     }
// };
//
// Point points[MAXN];
// Point centers[MAXN];
//
// class Line
// {
// public:
//     Point p1, p2;
//     Line(){};   // 默认构造函数
//     Line(Point p1, Point p2): p1(p1), p2(p2) {};
// };
//
// bool OrdinateCmp(const Point &p1, const Point &p2)
// {
//     if (p1.x == p2.x)
//     {
//         return p1.y < p2.y;
//     }
//     else
//     {
//         return p1.x < p2.x;
//     }
// }
//
// bool PolarCmp(const Point &p1, const Point &p2)
// {
//     Point tmpa = p1 - points[0];
//     Point tmpb = p2 - points[0];
//     double tmp = tmpa.x * tmpb.y - tmpa.y * tmpb.x;
//     return tmp > 0;
// }
//
// double Distance(Point p1, Point p2)
// {
//     return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
// }
//
// bool CheckLine(const Line l, const Point c, const int R)
// {
//     Point v = l.p2 - l.p1;
//     Point w = c - l.p1;
//     double t = (v * w) / (v * v);
//     if (t < 0 || t > 1)
//     {
//         return false;
//     }
//     Point p = l.p1 + Point(v.x * t, v.y * t);
//     return Distance(p, c) > R;
// }
//
//
// bool isOKLine(const Line l, Point c[], const int G, const int R)
// {
//     for (int i = 0; i < G; i++)
//     {
//         if (CheckLine(l, c[i], R))
//         {
//             return false;
//         }
//     }
//     return true;
// }
//
// vector<Point> GrahamScan(vector<Point> &points) {
//     sort(points.begin(), points.end(), OrdinateCmp);
//     for (int i = 1; i < points.size(); i++) {
//         points[i] = points[i] - points[0];
//     }
//     sort(points.begin() + 1, points.end(), PolarCmp);
//     vector<Point> result;
//     result.push_back(points[0]);
//     result.push_back(points[1]);
//     for (int i = 2; i < points.size(); i++) {
//         while (result.size() > 1 && PolarCmp(result.back() - result[result.size() - 2], points[i] - result.back())) {
//             result.pop_back();
//         }
//         result.push_back(points[i]);
//     }
//     if (result.size() == points.size()) {
//         return result;
//     } else {
//         return GrahamScan(result);
//     }
// }
//
//
// int DP(int left, int right,  bool OKline[MAXN][MAXN])
// {
//     if(left == right || vis[left][right])
//     {
//         return dp[left][right];
//     }
//     vis[left][right] = true;
//     for (int mid = left+1;mid < right;mid++)
//     {
//         dp[left][right] = max(dp[left][right], DP(left, mid, OKline)+ DP(mid, right, OKline));
//     }
//     dp[left][right] += OKline[left][right];
//     return dp[left][right];
// }
// /*
//  * 主函数
//  */
//
// int main()
// {
//     // 输入处理
//     int N, G, R;    // N: 栅栏点数, G: 圆心数, R: 半径
//     cin >> N >> G >> R;
//     // Point points[N], centers[G];
//     for (int i = 0; i < N; i++)
//     {
//         cin >> points[i].x >> points[i].y;
//     }
//     for (int i = 0; i < G; i++)
//     {
//         cin >> centers[i].x >> centers[i].y;
//     }
//
//     //points = GrahamScan(points);
//     sort(points, points + N, OrdinateCmp);
//     sort(points + 1, points + N, PolarCmp);
//     sort(centers, centers + G, OrdinateCmp);
//
//     bool OKline[MAXN][MAXN]={false};
//     for (int i = 0; i < N; i++) {
//         for (int j = i + 1; j < N; j++)
//         {
//             if(i == 0 && j==N-1)
//             {
//                 continue;
//             }
//             else
//             {
//                 OKline[i][j] = isOKLine(Line(points[i], points[j]), centers, G, R);
//             }
//         }
//     }
//
//     int result = DP(0, N-1, OKline);
//     cout << result << endl;
//     return 0;
// }

#include <iostream>
#include <algorithm>
#include <cmath>
#define EPS 1e-20
#define MAXN 152
using namespace std;
int N, G;
double R;

class Point
{
public:
    double x, y;

    Point()
    {
        x = 0;
        y = 0;
    }

    Point(double x_, double y_)
    {
        x = x_;
        y = y_;
    }

    Point operator-(Point b)
    {
        return Point(x - b.x, y - b.y);
    }

    double operator*(Point b)
    {
        return x * b.x + y * b.y;
    }
    Point operator+(Point b)
    {
        return Point(x + b.x, y + b.y);
    }
} points[MAXN], circles[MAXN];

bool CMPOrder(Point a, Point b)
{//先按照顺序排好
    if (a.x == b.x)
    {
        return a.y < b.y;
    }
    else
    {
        return a.x < b.x;
    }
}

bool CMPAngle(Point a, Point b)
{//这里是来计算和第一个点的角度，这样的话就可以按照内角的大小排好序来找出非相邻边
    Point tmpa = a - points[1];
    Point tmpb = b - points[1];
    return tmpa.x * tmpb.y > tmpb.x * tmpa.y;
}

bool OKLines[MAXN][MAXN];

class Line
{
public:
    Point a, b;

    Line()
    {
        a = Point(0, 0);
        b = Point(0, 0);
    }

    Line(Point a_, Point b_)
    {
        a = a_;
        b = b_;
    }
};

double Dis(Point a, Point b)
{//计算两点之间的距离
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool CheckLine( Line l, Point c, const double R)
{
    Point v = l.b - l.a;
    Point w = c - l.a;
    double t = (v * w) / (v * v);
    if (t <= 0 || t >= 1)
    {
        return min(Dis(l.a, c),Dis(l.b, c))<=R+EPS;
    }
    Point p = l.a + Point(v.x * t, v.y * t);
    return Dis(p, c) <= R + EPS;
}

bool isOKLine(Line l)
{//判断是否是不过圆的
    for (int i = 1; i <= G; i++)
    {
        if (CheckLine(l, circles[i], R))
        {
            return false;
        }
    }
    return true;
}

bool vis[MAXN][MAXN];
int F[MAXN][MAXN];

int DP(int Left, int Right)
{//一开始的范围就是全部，然后不断DP找寻小的范围
    if (Left == Right || vis[Left][Right])
    {
        return F[Left][Right];
    }
    vis[Left][Right] = true; //标记已经访问过了
    for (int Mid = Left + 1; Mid < Right; Mid++)
    {//将其拆开为两部分的连线和中间仅链接他一个的谁的大
        F[Left][Right] = max(F[Left][Right], DP(Left, Mid) + DP(Mid, Right));
    }
    F[Left][Right] += OKLines[Left][Right];
    return F[Left][Right];
}

int main()
{
    cin >> N >> G >> R;
    for (int i = 1; i <= N; i++)
    {
        cin >> points[i].x >> points[i].y;
    }
    sort(points + 1, points + N + 1, CMPOrder);
    sort(points + 2, points + N + 1, CMPAngle);
    for (int i = 1; i <= G; i++)
    {
        cin >> circles[i].x >> circles[i].y;
    }
    sort(circles, circles + G, CMPOrder);

    for (int i = 1; i <= N; i++)
    {
        for (int j = i + 2; j <= N; j++)
        {//+2的原因是不能是相邻的两个点
            if (i == 1 && j == N)
            {//同时第一个和最后一个也不行
                continue;
            }
            OKLines[i][j] = isOKLine(Line(points[i], points[j]));
        }
    }
    cout << DP(1, N) << endl;
    return 0;
}

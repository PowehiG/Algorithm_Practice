#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int minRoomNeeded(vector<pair<int,int>> &activities)
{
    // 其排序方式为：按照开始时间排序，如果开始时间相同，则按照结束时间排序
    sort(activities.begin(), activities.end());
    priority_queue<int, vector<int>, greater<int>> rooms;
    rooms.push(activities[0].second);   // 将第一个活动的结束时间放入房间
    for (size_t i=1;i<activities.size();i++)
    {
        if (activities[i].first >= rooms.top())  // 如果当前活动的开始时间大于等于房间中最早结束的活动时间
        {
            rooms.pop();    // 将房间中最早结束的活动时间弹出
        }
        rooms.push(activities[i].second);   // 将当前活动的结束时间放入房间
    }
    return rooms.size();
}

int main() {
    // 接收输入
    int n;
    cin >> n;
    vector<pair<int,int>> activities(n);
    for (int i=0;i<n;i++)
    {
        cin >> activities[i].first >> activities[i].second;
    }
    // 计算最少需要的房间数
    cout << minRoomNeeded(activities) << endl;
    return 0;
}

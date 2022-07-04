#include "head.h"

void fib() { //斐波拉契数列
    vector<int> res;
    res.push_back(1); //1
    res.push_back(1); //2
    int n;
    cin >> n;
    if (n <= 2) cout << 1 << endl;
    else {
        for (int i = 2; i < n; i++) //>2的情况
            res.push_back(res[i - 1] + res[i - 2]);
        cout << res[n - 1] << endl;
    }
}


int dp_jumpFloor(int n) {  //经典的线性bp
    //一只青蛙一次可以跳上1级台阶，也可以跳上2级。
    //    求该青蛙跳上一个 n 级的台阶总共有多少种跳法（先后次序不同算不同的结果）。
    //1,2
    if (n == 0) return 1;
    if (n == 1) return 1;
    if (n == 2) return 2;
    int res = dp_jumpFloor(n - 2) + dp_jumpFloor(n - 1);
    return res;
}

void jumpFloor() {
    vector<int> res;
    int n;
    cin >> n;
    res.push_back(1); //0
    res.push_back(1); //1
    res.push_back(2); //2
    for (int i = 3; i < n + 1; i++) {
        res.push_back(dp_jumpFloor(i));
    }
    cout << res[n] << endl;
}

void jumpFloorExtra() {
    int n;
    cin >> n;
    vector<int> res;
    res.push_back(1); //0
    res.push_back(1); //1
    res.push_back(2); //2 
    //res.push_back(4); //3  
    //0 + 1 + 2  实际上就是以前所有计算出来的结果，都可以一步到n
    //也就说前面所有的值的累加，就等于下一个值
    //但是实际上操作的时候就会发现，因为上一个值就是上一个值之前的累加
    //因此现在这个值只需要上个值之前的累加，加，上个值，也就是上一个值的两倍。。。
    //比如说 4 -> 1 + 2 + 4 + 1  = 8 就是 4 + 4
    //总之也是动态规划
    for (int i = 3; i < n + 1; i++)
        res.push_back(res[i - 1] * 2);
    cout << res[n] << endl;
}

void jumpFloorCost() { //跳台阶的消耗问题，相比之前的跳台阶，额外加了每个台阶的键值，整个数组记录下就完了
    int n, temp;
    vector<int> floor;
    vector<int> cost;
    cin >> n;
    while (cin >> temp)
        floor.push_back(temp);
    cost.push_back(floor[0]);
    cost.push_back(floor[1]);
    for (int i = 2; i < n; i++) {
        cost.push_back(floor[i] + min(cost[i - 2], cost[i - 1]));
    }
    cout << min(cost[n - 1], cost[n - 2]) << endl;
}

void binarySearchTreeCount() {
    //简单来说，利用之前的结果，设置成左右树，然后统计总和。
    // j -1 + i - j = i -1.少一个结点是因为有个结点在根节点。
    int n;
    cin >> n;
    vector<int> count;
    count.push_back(1); //0
    count.push_back(1); //1;
    count.push_back(2); // 1 2 ,2 1
    for (int i = 3; i < n + 1; i++) {
        count.push_back(0);
        for (int j = 1; j <= i; j++)
            count[i] += count[j - 1] * count[i - j];
    }
    cout << count[n] << endl;
}


void maxSubArray() {
    int n;
    cin >> n;
    int temp;
    vector<int> arr;
    while (cin >> temp) arr.push_back(temp);
    int max = arr[0];
    int res = 0;
    //int l,r;
    for (int right = 0, left = 0; left < n; right++) {
        if (right == n) {
            right = ++left;
            res = arr[right];
            continue;
        }
        res += arr[right];
        if (arr[right] >= res) {
            left = right;
            res = arr[right];
        }
        if (res >= max) {
            max = res;
            //r = right;
            //l = left;
        }
    }
    cout << max << endl;
}


void maxSubArray_dp() { //动态规划版本，计算数组中子数组最大连续和
    int n;
    cin >> n;
    int temp;
    vector<int> arr;
    while (cin >> temp) arr.push_back(temp);
    int max = arr[0];
    vector<int> dp;
    dp.push_back(arr[0]);
    for (int i = 1; i < n; i++) {
        int temp = dp[i - 1] + arr[i] > arr[i] ? dp[i - 1] + arr[i] : arr[i];
        dp.push_back(temp);
        max = max > dp[i] ? max : dp[i];
    }
    cout << max << endl;
}

void maxSubArrayMutil() {//动态规划版本，计算数组中子数组最大连续乘积
    //这个题注意，因为有负数的存在，所以只记录最大值没有用
    //需要付出巨大的代价用双指针判断下一个负数在哪儿，还很麻烦
    //所以这里直接再放一个最小值进来。
    //最小值集会自动的维持最小值，遇到一对负数就会自动取负数，遇到单个负数就会把上一个最大值和这个负数相乘
    //最大值集合会自动维持最大做，遇到一对负数就会把第二个负数和前一个最小值相乘，遇到单个负数就会自动取负数  
    //遇到负数的情况，就整个最小值集合出来，因为负数最小值乘以负数就是整数最大值。
    int n;
    cin >> n;
    int temp;
    vector<int> arr;
    while (cin >> temp) arr.push_back(temp); //n个
    int res = arr[0];
    int max_dp = arr[0];
    int min_dp = arr[0];
    for (int i = 1; i < n; i++) {
        int max_temp = max_dp;
        int min_temp = min_dp;
        max_dp = max(max_temp * arr[i], max(arr[i], min_temp * arr[i]));
        min_dp = min(min_temp * arr[i], min(arr[i], max_temp * arr[i]));
        res = max(max_dp, res);
    }
    cout << res << endl;
}
/*
Problem: Maximum profit in job scheduling

Approach:
We can solve this problem considering the start time and end time of the jobs. 
In case of considering start time:
We sort the jobs according to their start time. For every job, if we select it then the total profit will be the profit from that job + the profit from the
job after it. If we don't select it, then the total profit will be the next job after start time +1, and we will consider the best of 2 for maximum profit.

In case of considering end time:
We sort the jobs according to their end time. For every job, if we select it, then the total profit will be the profit from that job + the profit from the job
before start time. If we don't select it, then the total profit will be the the next job before end -1, and we will consider the best of 2 for maximum profit.

Space Complexity: O(N)
Time Complexity: O(N(2^N))
*/

#include <bits/stdc++.h>
using namespace std;
struct Data{
   int s,e,c;
   Data(int x, int y, int z){
      s= x;
      e= y;
      c = z;
   }
};
bool cmp(Data a, Data b){
   return a.e<b.e;
}
class Solution {
   public:
   int jobScheduling(vector<int>& s, vector<int>& e, vector<int>& p){
      vector<Data> j;
      int n = s.size();
      for (int i = 0; i < n; i++) {
         Data temp(s[i], e[i], p[i]);
         j.push_back(temp);
      }
      sort(j.begin(), j.end(), cmp);
      vector<int> dp(n);
      dp[0] = j[0].c;
      for (int i = 1; i < n; i++) {
         int temp = 0;
         int low = 0;
         int high = i - 1;
         while (low < high) {
            int mid = low + (high - low + 1) / 2;
            if (j[mid].e <= j[i].s)
               low = mid;
            else
               high = mid - 1;
         }
         dp[i] = j[i].c;
         if (j[low].e <= j[i].s)
            dp[i] += dp[low];
         dp[i] = max(dp[i], dp[i - 1]);
      }
      return dp[n - 1];
   }
};
int main(){
   Solution ob;
   vector<int> startTime = {1,2,3,3}, endTime = {3,4,5,6}, profit =
   {500,100,400,700};
   cout << (ob.jobScheduling(startTime, endTime, profit));
}
#include <bits/stdc++.h>

using namespace std;

vector<int> nums; // the array
int k;            // sliding window size

deque<int> mono;  // decreasing deque of maxes
vector<int> ret;  // stores sliding window maxes

int main() {
  for (int i = 0; i < nums.size(); i++) {
    if (i >= k && mono.front() == nums[i-k]) mono.pop_front();
    while (!mono.empty() && mono.back() < nums[i]) {
      mono.pop_back();
    }
    mono.push_back(nums[i]);
    if (i >= k-1) ret.push_back(mono.front());
  }
}

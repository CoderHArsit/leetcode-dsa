class Solution {
public:
    int maxSum(vector<int>& nums) {
        set<int> st;
        for (auto i : nums) {
            st.insert(i);
        }
        int sum = -1;
        int sum2 = 0;
        for (auto i : st) {
            if (i >= 0)
                sum = max(i, sum + i);
            else {
                sum2 = max(i, sum2 + i);
            }
        }
        if (sum == -1)
            return sum2;
        return sum;
    }
};
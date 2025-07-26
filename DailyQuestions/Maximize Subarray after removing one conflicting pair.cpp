
lc 3480

HARD (Really Hard to understand optimize solution)
class Solution {
public:
    long long maxSubarrays(int n, std::vector<std::vector<int>>& conflictingPairs) {
        for (auto& pair : conflictingPairs) {
            if (pair[1] < pair[0]) {
                std::swap(pair[0], pair[1]);
            }
        }

        std::sort(conflictingPairs.begin(), conflictingPairs.end(),
                  [](const std::vector<int>& a, const std::vector<int>& b) {
                      return a[1] < b[1];
                  });

        int m = conflictingPairs.size();
        int max1 = 0;
        int max2 = 0;
        long long gain = 0;
        long long maxGain = 0;
        long long totalOccupied = 0;

        for (int i = 0; i < m; ++i) {
            int start = conflictingPairs[i][0];
            int base = n + 1 - conflictingPairs[i][1];
            if (i < m - 1) {
                base = conflictingPairs[i + 1][1] - conflictingPairs[i][1];
            }

            if (start > max1) {
                max2 = max1;
                max1 = start;
                gain = 0;
            } else if (start > max2) {
                max2 = start;
            }

            gain += static_cast<long long>(max1 - max2) * base;
            totalOccupied += static_cast<long long>(max1) * base;

            if (gain > maxGain) {
                maxGain = gain;
            }
        }

        long long total = static_cast<long long>(n) * (n + 1) / 2;
        return total - totalOccupied + maxGain;
    }
};


Visual Solution || NOT COMPLICATED || GREEDY || Beginner-Friendly

Array
Greedy
Sorting
Simulation

3+
For every conflict pair, let:

totalOccupied denote the number of subarrays it restricts,
gain represent the number of subarrays that could be recovered by removing that specific conflict pair.
maxGain be the highest gain among all conflict pairs.
The final result is obtained by computing the total number of subarrays, subtracting the cumulative totalOccupied from all conflict pairs, and then adding maxGain:

finalResult=totalSubarrays−totalOccupied+maxGain
​
 
While implementation details may vary to optimize for time or space complexity, the core logic is consistent and can be represented graphically as shown here:

cvv.png
//https://assets.leetcode.com/users/images/0dc14397-f356-4a76-969a-3b2352811a0e_1753488404.4796212.png

n=10, conflict pairs=[ [2, 4], [3, 9] ]

Each entry (x,y) in the table represents a possible subarray starting at x and ending at y.

Only cases where y>x are valid, so one half of the table is grayed out.

For any conflict pair (a,b), all subarrays with x≤a and y≥b will include it, and are thus considered occupied.

When removing a single conflict pair, only the entries that are occupied exclusively by that one pair will be released, and those contribute to the gain.

The gain region is shown in yellow for removing [2,4], and in green for removing [3,9].

The red region cannot be utilized by removing just one conflict pair.

The gain region is always bounded by the top two largest starting points among all conflict pairs, indicated by the green and blue arrows in the following graph.

//https://assets.leetcode.com/users/images/9fc5495d-883f-4e2f-bae9-6031fe5fa183_1753488814.619788.png

Only the conflict pair with the highest starting point (green arrow) contributes to the gain; removing others like (a 
2
​
 ,b 
2
​
 ) does not increase subarrays.

Essentially, find the white region, add the largest orange region, and that is the answer.
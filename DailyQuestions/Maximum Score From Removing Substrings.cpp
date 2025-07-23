
// topuic := greedy



//in this we are basically checking for match with pattern and keepon updating the inputstring to unremoved char when match found
//we decrease write by 2 in order to remove the two char and then on updating further index with unremoved string
// do a dry run you will get it

class Solution {
public:
    // Main function to maximize total gain by removing ab/ba
    int maximumGain(string s, int x, int y) {
        int totalPoints = 0;

        // Decide priority based on higher points
        if (x < y) {
            // Remove "ba" first, then "ab"
            totalPoints += removeAll(s, "ba", y);
            totalPoints += removeAll(s, "ab", x);
        } else {
            // Remove "ab" first, then "ba"
            totalPoints += removeAll(s, "ab", x);
            totalPoints += removeAll(s, "ba", y);
        }

        return totalPoints;
    }

    // Removes all occurrences of targetSubstring (like "ab" or "ba")
    // from inputString in one pass using stack-like in-place overwrite
    int removeAll(string& inputString, string targetSubstring, int pointsPerRemoval) {
        int totalPoints = 0;
        int writeIndex = 0;

        for (int readIndex = 0; readIndex < inputString.size(); readIndex++) {
            // Write current character to the writeIndex
            inputString[writeIndex++] = inputString[readIndex];

            // Check if last two characters match the target substring
            if (writeIndex > 1 &&
                inputString[writeIndex - 2] == targetSubstring[0] &&
                inputString[writeIndex - 1] == targetSubstring[1]) {
                    // Remove matched substring by "popping" both
                    writeIndex -= 2;
                    totalPoints += pointsPerRemoval;
            }
        }

        // Trim extra characters beyond writeIndex (they were "popped")
        inputString.erase(inputString.begin() + writeIndex, inputString.end());

        return totalPoints;
    }
};



| readIndex | char | inputString (after write) | writeIndex | Match with "ba"? | Action    | Points |
| --------- | ---- | ------------------------- | ---------- | ---------------- | --------- | ------ |
| 0         | c    | `c`                       | 1          | No               | keep      | 0      |
| 1         | d    | `c d`                     | 2          | No               | keep      | 0      |
| 2         | b    | `c d b`                   | 3          | No               | keep      | 0      |
| 3         | c    | `c d b c`                 | 4          | No               | keep      | 0      |
| 4         | b    | `c d b c b`               | 5          | No               | keep      | 0      |
| 5         | b    | `c d b c b b`             | 6          | No               | keep      | 0      |
| 6         | a    | `c d b c b b a`           | 7          | Yes ("b a")      | pop (→ 5) | +5     |
| 7         | a    | `c d b c b a`             | 6          | No               | keep      | 0      |
| 8         | b    | `c d b c b a b`           | 7          | Yes ("a b") ❌    | keep      | 0      |
| 9         | a    | `c d b c b a b a`         | 8          | Yes ("b a") ✅    | pop (→ 6) | +5     |
| 10        | b    | `c d b c b a b`           | 7          | No               | keep      | 0      |


| readIndex | char | inputString (after write) | writeIndex | Match with "ba"? | Action    | Points |
| --------- | ---- | ------------------------- | ---------- | ---------------- | --------- | ------ |
| 0         | c    | `c`                       | 1          | No               | keep      | 0      |
| 1         | d    | `c d`                     | 2          | No               | keep      | 0      |
| 2         | b    | `c d b`                   | 3          | No               | keep      | 0      |
| 3         | c    | `c d b c`                 | 4          | No               | keep      | 0      |
| 4         | b    | `c d b c b`               | 5          | No               | keep      | 0      |
| 5         | b    | `c d b c b b`             | 6          | No               | keep      | 0      |
| 6         | a    | `c d b c b b a`           | 7          | Yes ("b a")      | pop (→ 5) | +5     |
| 7         | a    | `c d b c b a`             | 6          | No               | keep      | 0      |
| 8         | b    | `c d b c b a b`           | 7          | Yes ("a b") ❌    | keep      | 0      |
| 9         | a    | `c d b c b a b a`         | 8          | Yes ("b a") ✅    | pop (→ 6) | +5     |
| 10        | b    | `c d b c b a b`           | 7          | No               | keep      | 0      |



//Similar to above question is this simple question based on same process and intuition


27. Remove Element
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int write=0,read=0,count =0;
  
        while(read<nums.size()){
            if(nums[read] != val){
                nums[write] = nums[read];
                read++;count++;write++;
            }else{
                read++;
            }
        }
        return count;
    }
};
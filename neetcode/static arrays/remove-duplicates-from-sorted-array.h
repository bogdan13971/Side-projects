// https://leetcode.com/problems/remove-duplicates-from-sorted-array/

#include <algorithm>
#include <vector>
#include <set>

int removeDuplicatesSTL(std::vector<int> &nums)
{
    // moves duplicates at the end of the vector
    const auto it = std::unique(nums.begin(), nums.end());
    // computes the index difference between 2 iterators
    return std::distance(nums.begin(), it);
}

// compares right pointer to left pointer
int removeDuplicatesManual(std::vector<int> &nums)
{
    int k = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] != nums[k])
        {
            k++;
            nums[k] = nums[i];
        }
    }

    return k + 1;
}

// compates two consecutive values
int removeDuplicatesNeet(std::vector<int> &nums)
{
    int k = 1;
    for (int i = 1; i < nums.size(); i++)
    {
        if (nums[i] != nums[i - 1])
        {
            k++;
            nums[k] = nums[i];
        }
    }

    return k;
}

int removeDuplicatesSet(std::vector<int> &nums)
{
    // filter uniques by adding them to a sorted set
    // ctor of set accepts iterators as many other STL containers
    std::set<int> unique(nums.begin(), nums.end());
    // copy elements from set back to vector
    int i = 0;
    for (int num : unique)
    {
        nums[i++] = num;
    }
    return unique.size();
}
// https://leetcode.com/problems/remove-element/

#include <algorithm>
#include <vector>

int removeElementSTL(std::vector<int> &nums, int val)
{
    // moves all the elements equal to val at the end of the array
    const auto it = std::remove(nums.begin(), nums.end(), val);
    // can delete the rest by using std::erase and given this iterator
    return std::distance(nums.begin(), it);
}

// algorithm similar to remove duplicates from sorted array
// two pointer approach
int removeElementStable(std::vector<int> &nums, int val)
{
    // handle case where nums is empty
    int k = -1;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] != val)
        {
            k++;
            nums[k] = nums[i];
        }
    }

    return k + 1;
}

// less comparisons but the order of the elements will change
int removeElementUnstable(std::vector<int> &nums, int val)
{
    // i from left to right
    // j from right to left
    int i = 0;
    int j = nums.size() - 1;

    // go from both ways and move elements equal to val at the end
    // by swapping elements
    while (i <= j)
    {
        if (nums[i] == val && nums[j] != val)
        {
            std::swap(nums[i], nums[j]);
            i++;
            j--;
        }
        else
        {
            if (nums[i] != val)
            {
                i++;
            }
            if (nums[j] == val)
            {
                j--;
            }
        }
    }

    return j + 1;
}

// both pointer going right to left
// because on the right all values should be value
int removeElementUnstable_v2(std::vector<int> &nums, int val)
{
    int k = nums.size() - 1;
    for (int i = nums.size() - 1; i >= 0; i--)
    {
        if (nums[i] == val)
        {
            std::swap(nums[i], nums[k]);
            k--;
        }
    }

    return k + 1;
}
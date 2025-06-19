// https://leetcode.com/problems/concatenation-of-array/description/

#include <vector>
#include <algorithm>
#include <iterator>

std::vector<int> getConcatenationSTL(std::vector<int> &nums)
{
    // copies the elements into new vector
    std::vector ans(nums);
    // copies them again at the end
    // no need for back inserter because std::vector::insert will handle the resizing
    ans.insert(ans.end(), nums.begin(), nums.end());
    return ans;
}

std::vector<int> getConcatenationSTL_move(std::vector<int> &nums)
{
    std::vector ans(nums);
    // this moves directly moves the contents of the vector into the new one
    ans.insert(ans.end(), std::make_move_iterator(nums.begin()), std::make_move_iterator(nums.end()));
    return ans;
}

std::vector<int> getConcatenation(std::vector<int> &nums)
{
    // resizing is faster then pushing back multiple times
    std::vector<int> ans(nums.size() * 2);

    for (int i = 0; i < nums.size(); i++)
    {
        ans[i] = nums[i];
        ans[i + nums.size()] = nums[i];
    }

    return ans;
}
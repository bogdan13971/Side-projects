// https://leetcode.com/problems/design-browser-history/

#include <string>

class BrowserHistory
{
public:
    // use C array as a stack of fixed size
    std::string history[101];
    int index;
    int size;

    BrowserHistory(std::string homepage)
    {
        index = 0;
        size = 1;
        history[0] = homepage;
    }

    void visit(std::string url)
    {
        index += 1;
        history[index] = url;
        size = index + 1;
    }

    std::string back(int steps)
    {
        index = std::max(index - steps, 0);
        return history[index];
    }

    std::string forward(int steps)
    {
        index = std::min(index + steps, size - 1);
        return history[index];
    }
};
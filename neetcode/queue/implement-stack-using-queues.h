// https://leetcode.com/problems/implement-stack-using-queues

#include <queue>

// a queue is always empty
class MyStack
{
private:
    std::queue<int> q1;
    std::queue<int> q2;

public:
    MyStack()
    {
    }

    // add element to the empty queue and then move all elements from the other queue
    void push(int x)
    {
        std::queue<int> &emptyQueue = q1.empty() ? q1 : q2;
        std::queue<int> &otherQueue = q1.empty() ? q2 : q1;

        emptyQueue.push(x);
        while (!otherQueue.empty())
        {
            emptyQueue.push(otherQueue.front());
            otherQueue.pop();
        }
    }

    int pop()
    {
        std::queue<int> &otherQueue = q1.empty() ? q2 : q1;
        int val = otherQueue.front();
        otherQueue.pop();

        return val;
    }

    int top()
    {
        std::queue<int> &otherQueue = q1.empty() ? q2 : q1;

        return otherQueue.front();
        ;
    }

    bool empty()
    {
        std::queue<int> &otherQueue = q1.empty() ? q2 : q1;

        return otherQueue.empty();
    }
};

// Second method uses a single queue
class MyStack
{
private:
    std::queue<int> q;
public:
    MyStack()
    {
    }

    //push 0 as separator because x > 0 by problem description
    //copy from front to back until reaching separator
    void push(int x)
    {
        q.push(0);
        q.push(x);
        while (q.front() != 0)
        {
            q.push(q.front());
            q.pop();
        }

        q.pop();
    }

    //neetcode method
    //no need for separator because you know how many elements to use
    void push(int x) {
        q.push(x);
        for (int i = q.size() - 1; i > 0; i--) {
            q.push(q.front());
            q.pop();
        }
    }

    int pop()
    {
        int x = q.front();
        q.pop();

        return x;
    }

    int top()
    {
        return q.front();
    }

    bool empty()
    {
        return q.empty();
    }
};

//neetcode version for queues of queues (queue implemented on linked list)
//you only have to access the head for stack operations

#include <memory>

class MyStack {
private:
    struct Node {
        int val;
        std::shared_ptr<Node> next;
        Node(int v, std::shared_ptr<Node> n) : val(v), next(n) {}
    };
    std::shared_ptr<Node> q;

public:
    MyStack() : q(nullptr) {}

    void push(int x) {
        q = std::make_shared<Node>(x, q);
    }

    int pop() {
        if (!q) return -1;
        int top = q->val;
        q = q->next;
        return top;
    }

    int top() {
        if (!q) return -1;
        return q->val;
    }

    bool empty() {
        return q == nullptr;
    }
};
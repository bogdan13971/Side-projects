// https://leetcode.com/problems/reverse-linked-list/description/

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Simple recursive solution
// Set the next of the next as the current
ListNode *reverseRec(ListNode *node)
{
    if (node == nullptr || node->next == nullptr)
    {
        return node;
    }

    ListNode *head = reverseRec(node->next);
    node->next->next = node;
    node->next = nullptr;

    return head;
}

ListNode *reverseList(ListNode *head)
{
    if (head == nullptr)
    {
        return head;
    }

    return reverseRec(head);
}

// Tail recursive solution
// Uses an accumulator to build the response on the go
ListNode *reverseRec(ListNode *node, ListNode *acc)
{
    if (node == nullptr)
    {
        return acc;
    }

    ListNode *next = node->next;

    node->next = acc;

    return reverseRec(next, node);
}

ListNode *reverseList(ListNode *head)
{
    if (head == nullptr)
    {
        return head;
    }

    return reverseRec(head, nullptr);
}

// iterative solution
// keep prev and use it as next for the next node
ListNode *reverseList(ListNode *head)
{
    ListNode *prev = nullptr;
    ListNode *curr = head;

    while (curr != nullptr)
    {
        ListNode *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}

// https://leetcode.com/problems/merge-two-sorted-lists/submissions/1511502197/

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Recursive method
// Set the next of the current node to the recursion result
ListNode *mergeRec(ListNode *list1, ListNode *list2)
{
    if (list1 == nullptr)
    {
        return list2;
    }
    if (list2 == nullptr)
    {
        return list1;
    }

    ListNode *node = nullptr;
    if (list1->val < list2->val)
    {
        node = list1;
        node->next = mergeRec(list1->next, list2);
    }
    else
    {
        node = list2;
        node->next = mergeRec(list1, list2->next);
    }

    return node;
}

ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
{
    return mergeRec(list1, list2);
}

// Build new list on the fly
// Merged is the prev node of the final list
ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
{
    ListNode *node1 = list1;
    ListNode *node2 = list2;
    ListNode *merged = nullptr;

    if (list1 == nullptr)
    {
        return list2;
    }

    if (list2 == nullptr)
    {
        return list1;
    }

    while (node1 != nullptr && node2 != nullptr)
    {
        if (node1->val < node2->val)
        {
            if (merged != nullptr)
            {
                merged->next = node1;
            }

            merged = node1;
            node1 = node1->next;
        }
        else
        {
            if (merged != nullptr)
            {
                merged->next = node2;
            }

            merged = node2;
            node2 = node2->next;
        }
    }

    if (node1 == nullptr)
    {
        merged->next = node2;
    }
    else
    {
        merged->next = node1;
    }

    if (list1->val < list2->val)
    {
        return list1;
    }
    else
    {
        return list2;
    }
}
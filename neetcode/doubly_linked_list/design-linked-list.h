// https://leetcode.com/problems/design-linked-list/

struct Node
{
    int val;
    Node *next;
    Node(int val, Node *next)
        : val{val}, next{next}
    {
    }
};

class MyLinkedList
{
public:
    Node *head;
    Node *tail;
    int size;

    MyLinkedList()
    {
        // use dummy node for head for easy inserition
        head = new Node{-1, nullptr};
        tail = nullptr;
        size = 0;
    }

    int get(int index)
    {
        if (index < 0 || index >= size)
        {
            return -1;
        }

        Node *node = head->next;
        // if index is valid preffer for instead of two condition while
        for (int i = 0; i < index; i++)
        {
            node = node->next;
        }

        return node->val;
    }

    void addAtHead(int val)
    {
        head->next = new Node{val, head->next};

        if (tail == nullptr)
        {
            tail = head->next;
        }

        size++;
    }

    void addAtTail(int val)
    {
        // if first inserted element use add at head
        if (head->next == nullptr)
        {
            addAtHead(val);
            return;
        }

        tail->next = new Node(val, nullptr);
        tail = tail->next;

        size++;
    }

    void addAtIndex(int index, int val)
    {
        if (index == 0)
        {
            addAtHead(val);
            return;
        }
        if (index == size)
        {
            addAtTail(val);
            return;
        }
        if (index > size || index < 0)
        {
            return;
        }

        Node *curr = head->next;
        Node *prev = head;

        for (int i = 0; i < index; i++)
        {
            prev = curr;
            curr = curr->next;
        }

        prev->next = new Node(val, curr);

        size++;
    }

    void deleteAtIndex(int index)
    {
        if (index < 0 || index >= size)
        {
            return;
        }

        Node *prev = head;
        Node *node = head->next;

        for (int i = 0; i < index; i++)
        {
            prev = node;
            node = node->next;
        }

        if (index == size - 1)
        {
            tail = prev;
        }

        prev->next = node->next;
        delete node;

        size--;
    }
};

#include <iostream>

template <typename T>
struct Node {
    T data;
    Node* next;
    unsigned priority;

    Node() : data(0), next(NULL), priority(0)
    {}

    Node(const Node<T>& o) : data(o.data), next(o.next), priority(o.priority)
    {}

    Node(T data, unsigned priority) : data(data), next(NULL), priority(priority)
    {}

    Node(T data, Node<T>* next, unsigned priority) : data(data), next(next), priority(priority)
    {}

    ~Node ()
    {
            next = NULL;
            data = 0;
            priority = 0;
    }
    Node<T>& operator = (Node<T>& o)
    {
        data = o.data;
        next = o.next;
        priority = o.priority;

        return *this;
    }

    T get_data() const { return data; }

    unsigned get_priority() const { return priority; }
};

template <typename T>
std::ostream& operator << (std::ostream& os, Node<T>& node)
{
    os << '(' << node.get_priority() << ", " << node.get_data() << ')';
    return os;
}

template <typename T>
class MyPriorityQueue
{
    Node<T>* front;
    Node<T>* rear;

public:
    MyPriorityQueue() : front(NULL), rear(NULL)
    {}

    MyPriorityQueue(const MyPriorityQueue& o) : front(o.front), rear(o.rear)
    {}

    MyPriorityQueue(Node<T>* front, Node<T>* rear) : front(front), rear(rear)
    {
        rear->next = NULL;
    }

    MyPriorityQueue(Node<T>* node) : front(node), rear(node)
    {
        front->next = NULL;
        rear->next = NULL;
    }

    ~MyPriorityQueue()
    {
        Node<T>* curr = front;
        while (curr)
        {
            Node<T>* temp = curr->next;
            curr->~Node();
            curr = temp;
        }
        front = NULL;
        rear = NULL;
    }

    void push(Node<T>* item)
    {
        if (!front)
        {
            front = item;
            rear = item;
            front->next = NULL;
            rear->next = NULL;
        }
        else
        {
            if (front->priority > item->priority)
            {
                Node<T>* temp = front;
                front = item;
                front->next = temp;
            }

            else
            {
                bool flag = false;
                Node<T>* curr = front;
                while (curr->next)
                    if (curr->next->priority > item->priority)
                    {
                        item->next = curr->next;
                        curr->next = item;
                        flag = true;
                        break;
                    }
                    else
                    {
                        curr = curr->next;
                    }
                if (!flag)
                {
                    curr->next = item;
                    rear = item;
                    rear->next = NULL;
                }
            }
        }
    }


    Node<T>* pop()
    {
        Node<T>* temp = front;
        front = front->next;
        return temp;
    }

    Node<T>* peek() const { return front; }

    size_t size() const
    {
        size_t size = 0;
        Node<T>* curr = front;

        while (curr)
        {
            size += 1;
            curr = curr->next;
        }
        return size;
    }

};

template <typename T>
std::ostream& operator << (std::ostream& os, MyPriorityQueue<T>& qu)
{
    Node<T>* curr = qu.peek();
    while (curr)
    {
        os << *curr << ' ';
        curr = curr->next;
    }
    os << std::endl;
    return os;
}

int main()
{
    Node <int> node1(36, 1);

    Node <int> node2(37, 2);

    Node <int> node3(38, 2);

    Node <int> node4(39, 5);

    MyPriorityQueue<int> queue(&node3);

    std::cout << queue.size() << std::endl;

    queue.push(&node4);

    std::cout << queue.size() << std::endl;

    queue.push(&node2);

    std::cout << queue;
    std::cout << queue.size() << std::endl;

    queue.push(&node1);

    std::cout << queue;
    std::cout << queue.size() << std::endl;


    int temp;
    temp = queue.pop()->data;

    std::cout << queue;

    temp = queue.peek()->data;

    std::cout << temp << std::endl;
    std::cout << queue;

    return 0;
}
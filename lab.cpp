#include <iostream>

using std::endl;
using std::cout;

template <typename T>
struct Node {
    T data;
    Node* next;

    Node (): data (0), next (NULL)
    {}

    Node (const Node& o): data (o.data), next (o.next)
    {}

    Node (T data): data (data), next (NULL)
    {}

    Node (T data, Node<T> *next): data (data), next (next)
    {}

    ~Node()
    {
        data = 0;
        next = NULL;
    }

    Node<T>& operator = (Node<T>& o)
    {
        data = o.data;
        next = o.next;

        return *this;
    }
};

template <typename T>
class MyPriorityQueue
{
        Node<T>* front;
        Node<T>* rear;

    public: 
    MyPriorityQueue(Node<T>* front, Node<T>* rear): front (front), rear (rear)
    {}
 
    void push (Node<T>* item)
    {
        rear->next = item;
        rear = item;
        rear->next = NULL;
    }

    Node<T>* pop()
    {
        Node<T>* temp = front;
        front = front->next;
        return temp;
    }

    Node<T>* peek() const {return front;}

    size_t size() const
    {
        size_t size = 0;
        Node<T>*curr = front;
        
        while (curr)
        {
            size += 1;
            curr = curr->next;
        }
        return size;
    }

};

template <typename T>
std::ostream& operator << (std::ostream& os, MyPriorityQueue<T> qu)
{
    os << qu.peek()->data;
    Node<T>* curr = qu.peek()->next;
    while (curr)
    {
        os << " " << curr->data;
        curr = curr->next;
    }
    os << std::endl;
    return os;
}

int main ()
{
    Node <int> node1 (36);

    Node <int> node2 (37, &node1);

    Node <int> node3 (38, &node2);

    Node <int> node4 (39, &node3);

    MyPriorityQueue<int> queue (&node4, &node1);

    Node <int> node5 (40);

    std::cout << queue;
    std::cout << queue.size() << std::endl;

    queue.push(&node5);

    std::cout << node5.data << std::endl;

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
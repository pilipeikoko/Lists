#include <string>
#include <iostream>
#include "Lists.hpp"
using namespace std;


int main()
{
    UnidirectionalList<int> unidirectional_list;
    unidirectional_list.PushBack(2);
    unidirectional_list.PushBack(3);
    unidirectional_list.PushBack(4);
    unidirectional_list.PushBack(5);
    cout << unidirectional_list.Find(3)<<endl;
    cout << unidirectional_list.Find(2)<<endl;
    cout << unidirectional_list.Find(5) << endl;
    cout << unidirectional_list.Find(0) << endl;
    unidirectional_list.PrintList();
    unidirectional_list.DeleteElement(3);
    unidirectional_list.PrintList();
    unidirectional_list.DeleteElement(2);
    unidirectional_list.PrintList();
    unidirectional_list.DeleteElement(4);
    unidirectional_list.PrintList();
    


    BidirectionalList<int> bidirectional_list;
    bidirectional_list.PushBack(1);
    bidirectional_list.PushBack(2);
    bidirectional_list.PushBack(3);
    bidirectional_list.PushFront(0);
    cout << bidirectional_list.Find(1) << endl;
    cout << bidirectional_list.Find(2) << endl;
    cout << bidirectional_list.Find(0) << endl;
    cout << bidirectional_list.Find(5) << endl;
    bidirectional_list.PrintList();
    bidirectional_list.DeleteElement(3);
    bidirectional_list.PrintList();
    bidirectional_list.PushBack(3);
    bidirectional_list.PrintList();
    bidirectional_list.DeleteElement(0);
    bidirectional_list.PrintList();
    bidirectional_list.PushFront(0);
    bidirectional_list.PrintList();

    Queue<int, BidirectionalList> bidirectional_queue;
    bidirectional_queue.PushBack(2);
    bidirectional_queue.PushBack(3);
    cout << bidirectional_queue.GetSize()<<endl;
    cout << bidirectional_queue.Pop()<<endl;
    cout << bidirectional_queue.Pop()<<endl;
    cout<< bidirectional_queue.GetSize()<<endl;

    Queue<int, UnidirectionalList> unidirectional_queue;
    unidirectional_queue.PushBack(2);
    unidirectional_queue.PushBack(3);
    cout << unidirectional_queue.GetSize() << endl;
    cout << unidirectional_queue.Pop()<<endl;
    cout << unidirectional_queue.Pop()<<endl;
    cout << unidirectional_queue.GetSize();
    

}

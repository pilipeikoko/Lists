#include <string>
#include <iostream>
#include "Lists.hpp"
using namespace std;


int main()
{
    try {
        UnidirectionalList<int> unidirectional_list;
        unidirectional_list.PushBack(2);
        unidirectional_list.PushBack(3);
        unidirectional_list.PushBack(4);
        unidirectional_list.PushBack(5);
        cout << unidirectional_list.Find(3) << endl;
        cout << unidirectional_list.Find(2) << endl;
        cout << unidirectional_list.Find(5) << endl;
        cout << unidirectional_list.Find(0) << endl;
        unidirectional_list.PrintList();
        unidirectional_list.PopElement(3);
        unidirectional_list.PrintList();
        unidirectional_list.PopElement(2);
        unidirectional_list.PrintList();
        unidirectional_list.PopElement(4);
        unidirectional_list.PrintList();

      //  Mistake will be thrown becouse list is empty

      //  unidirectional_list.PopElement(5);
      //  unidirectional_list.PrintList();



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
        bidirectional_list.PopElement(3);
        bidirectional_list.PrintList();
        bidirectional_list.PushBack(3);
        bidirectional_list.PrintList();
        bidirectional_list.PopElement(0);
        bidirectional_list.PrintList();
        bidirectional_list.PushFront(0);
        bidirectional_list.PrintList();  

        BidirectionalList<int> bidirectional_list_1;
        bidirectional_list_1.PushBack(1);
        bidirectional_list_1.PushBack(2);
        Queue<int, BidirectionalList> bidirectional_list_decorator(bidirectional_list_1);
        cout << bidirectional_list_decorator.Pop() << endl;
        cout << bidirectional_list_decorator.Pop() << endl;

        UnidirectionalList<int> unidirectional_list_1;
        unidirectional_list_1.PushBack(1);
        unidirectional_list_1.PushBack(2);
        Queue<int, UnidirectionalList> unidirectional_list_decorator(unidirectional_list_1);
        cout << unidirectional_list_decorator.Pop() << endl;
        cout << unidirectional_list_decorator.Pop() << endl;

    }
    catch (string message) {
        cout << message;
    }

}

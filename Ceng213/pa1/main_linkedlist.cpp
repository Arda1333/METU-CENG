#include <iostream>

#include "LinkedList.h"

int main() {
    LinkedList<int> llist;


    llist.print();

    llist.insertAtTheEnd(3);
    llist.insertAtTheFront(1);
    llist.insertAfterNode(2, llist.getNode(1));
    llist.insertAtTheEnd(4);
    llist.insertAtTheEnd(5);


    llist.print();

    llist.removeAllNodes();

    llist.print();

    //llist.shuffle(4);


    //std::cout << llist.getNodeAtIndex(10) << std::endl;

    return 0;
}

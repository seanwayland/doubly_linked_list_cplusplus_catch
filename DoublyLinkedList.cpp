#define CATCH_CONFIG_MAIN

#include <string>
#include "catch.hpp"

using namespace std;

class Node {
public:
    int data;
    Node *next;
    Node *prev;

    Node(int data) {
        this->data = data;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

//linked list that is  a doubly linked list, allowing movement forward and backward
// use at your own risk !
class DoublyLinkedList {
public:
    Node *head;
    Node *tail;

    DoublyLinkedList() {
        this->head = nullptr;
        this->tail = nullptr;
    }

    void add(int data) {
        Node *newNode = new Node(data);

        if (this->head == nullptr) {
            this->head = newNode;
            this->tail = newNode;
        } else {
            this->tail->next = newNode;
            newNode->prev = this->tail;
            this->tail = newNode;
        }
    }

    void remove(int data) {
        Node *current = this->head;

        while (current != nullptr) {
            if (current->data == data) {
                if (current == this->head) {
                    this->head = current->next;
                    if (this->head != nullptr) {
                        this->head->prev = nullptr;
                    }
                } else if (current == this->tail) {
                    this->tail = current->prev;
                    if (this->tail != nullptr) {
                        this->tail->next = nullptr;
                    }
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }

                delete current;
                return;
            }

            current = current->next;
        }
    }

    string returnListString() {
        string str;
        Node *currentNode = this->head;

        while (currentNode != nullptr) {
            str += to_string(currentNode->data);
            currentNode = currentNode->next;
        }
        return str;
    }

    int checkList() {
        int checkSum = 0;
        Node *current = this->head;

        while (current->next != nullptr) {
            checkSum += current->data;
            current = current->next;
        }

        checkSum += current->data;

        while (current->prev != nullptr) {
            checkSum -= current->data;
            current = current->prev;

        }

        checkSum -= current->data;


        return checkSum;
    }


};

// Unit tests for DoublyLinkedList class
TEST_CASE("DoublyLinkedList tests", "[DoublyLinkedList]") {
    DoublyLinkedList list;

    SECTION("Test add function") {
        list.add(5);
        list.add(10);
        list.add(15);
        REQUIRE(list.returnListString() == "51015");
    }

    SECTION("Test remove function") {
        list.add(5);
        list.add(10);
        list.add(15);
        list.remove(10);
        REQUIRE(list.returnListString() == "515");

        list.remove(5);
        REQUIRE(list.returnListString() == "15");

        list.remove(15);
        REQUIRE(list.returnListString() == "");
    }


    SECTION("Test check function") {
        DoublyLinkedList list2;
        list2.add(1);
        list2.add(2);
        list2.add(3);
        list2.add(4);
        REQUIRE(list2.checkList() == 0);
    }

    SECTION("Test check function") {
        DoublyLinkedList list3;
        list3.add(1);
        list3.add(15);
        list3.add(17);
        list3.add(4);
        REQUIRE(list3.checkList() == 0);
    }
}

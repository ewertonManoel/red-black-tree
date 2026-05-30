#include <iostream>
#include <string>
#include <vector>
#include "redBlackTree.hpp"

int main() {
    // Creating two instances of the RedBlackTree class.
    // The goal is to test if the class works with different data types.
    RedBlackTree<int> myIntTree;
    RedBlackTree<std::string> myStringTree;

    // Storing data to test the tree.
    std::vector<int> numbers = {45, 20, 50, 10, 30, 25, 15};
    std::vector<std::string> languages = {"C++", "C", "Python", "Java", "HTML", "SQL"};

    // Inserting data into each tree.
    for(int number : numbers) myIntTree.insert(number);
    for(std::string language : languages) myStringTree.insert(language);

    // Checking if the duplicate key exception is handled.
    std::cout << "Trying to insert a key that already exists:" << std::endl;
    try {
        myStringTree.insert("C++");
    }
    catch(const std::exception& e) {
        std::cerr << "Expected exception: " << e.what() << std::endl;
    }

    // Testing the deleteNode method.
    std::cout << "\nSearching for 30 before deletion: " << (myIntTree.search(30) ? "found" : "not found") << std::endl;
    myIntTree.deleteNode(myIntTree.search(30));
    std::cout << "Searching for 30 after deletion: " << (myIntTree.search(30) ? "found" : "not found") << std::endl;
    
    myIntTree.deleteNode(myIntTree.search(45));
    myStringTree.deleteNode(myStringTree.search("HTML"));

    // Attempting to delete an invalid node.
    std::cout << "\nTrying to delete a node that doesn't exist:" << std::endl;
    try {
        myStringTree.deleteNode(myStringTree.search("PHP"));
    }
    catch(const std::exception& e) {
        std::cerr << "Expected exception: " << e.what() << std::endl;
    }

    return 0;
}

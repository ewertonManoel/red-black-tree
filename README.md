# 🌳 Red-Black Tree Implementation in C++

![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Data Structures](https://img.shields.io/badge/Data_Structures-Library-orange?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)

This project contains a red-black tree implementation that can perform insertion, deletion and search operations in a logarithmic time O(logn). 

The red-black tree differs from the common binary search tree because it can balance itself, ensuring this time complexity in every scenario. 

This is done using rotations and recolorations. In synthesis, every Red-Black Tree operation needs to follow five principles:

* Every node is red or black.
* Root is always black.
* Every leaf (NIL) is black.
* If a node is red, its children must be black.
* For each node, all the paths to the leaves have the same number of black nodes.

By following these rules, it is guaranteed that the tree will be balanced and its height will be at maximum 2log2​(n+1).

---

## Time Complexity

| Operation | Time Complexity |
| :--- | :--- |
| **Insertion** | $O(\log n)$ |
| **Deletion** | $O(\log n)$ |
| **Search** | $O(\log n)$ |

---

## Functionalities of the project:

* **General-purpose:** It uses templates to allow multiple types of trees. This means that you can use the tree to store integers, floats, strings (which will be ordered lexicographically) and many other types of data.
* **Security:** It uses a recursive destructor to prevent memory leaks and prohibits the creation of shallow copies, making the tree secure to use.
* **Exception handling:** It handles exceptions that can stop the correct working of the tree, preventing the user from inserting duplicate keys and deleting invalid nodes (NIL and nullptr).
* **Sentinel node:** It replaces the nullptr with the sentinel node (NIL), making the pointers logic clean and simple and preventing invalid access in the memory.

---

## Author: 
**Ewerton M. F. L. de Carvalho**

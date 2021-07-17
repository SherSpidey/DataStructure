cmake_minimum_required(VERSION 3.19)
project(DataStructure)

set(CMAKE_CXX_STANDARD 14)

add_executable(C1 C1/C1.cpp C1/C1.h C1/bubbleSort.cpp C1/extra.cpp)
add_executable(C2 C2/C2.cpp C2/C2.h C2/myVector.cpp C2/myVector.h)
add_executable(C3 C3/C3.cpp C3/C3.h C3/MyList.h C3/ListNode.h)
add_executable(C4 C4/C4.cpp C4/C4.h C4/MyStack.h C4/extra.cpp C4/MyQueue.h)
add_executable(C5 C5/C5.cpp C5/C5.h C5/BinNode.h C5/MyBinTree.h)
add_executable(C6 C6/C6.cpp C6/C6.h C6/Graph.h)
add_executable(C7 C7/C7.cpp C7/C7.h C7/Entry.h C7/BST.h)
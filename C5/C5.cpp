//
// Created by 62736 on 2021/7/5.
//

#include "C5.h"

int main( ){
    List_visit visit;
    MyBinTree<int> myBinTree;

    myBinTree.insertAsRoot(1);
    myBinTree.insertAsLC(myBinTree.root(),2);
    myBinTree.insertAsRC(myBinTree.root(),3);
    myBinTree.insertAsRC(myBinTree.root()->lc,4);
    myBinTree.insertAsLC(myBinTree.root()->rc,5);

    myBinTree.travPost(visit);

}
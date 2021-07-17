//
// Created by 62736 on 2021/7/6.
//

#ifndef DATASTRUCTURE_MYBINTREE_H
#define DATASTRUCTURE_MYBINTREE_H

#endif //DATASTRUCTURE_MYBINTREE_H

#include "BinNode.h"
#include "iostream"

using namespace std;

template<typename T>
class MyBinTree {
protected:
    //
    int _size;
    BinNodePosi<T> _root;

    virtual int updateHeight(BinNodePosi<T> x);     //更新高度
    void updateHeightAbove(BinNodePosi<T> x);       //更新节点与其父辈节点的高度

public:
    //构造函数
    MyBinTree() : _size(0), _root(NULL) {}

    //析构函数
    ~MyBinTree() { if (0 < _size) remove(_root); }

    int size() const { return _size; }        //返回规模
    bool empty() const { return !_root; }     //是否为空
    BinNodePosi<T> root() const { return _root; }     //返回根节点
    BinNodePosi<T> insertAsRoot(T const &e);        //插入根节点
    BinNodePosi<T> insertAsLC(BinNodePosi<T> x, T const &e);        //作为左子节点插入
    BinNodePosi<T> insertAsRC(BinNodePosi<T> x, T const &e);        //作为右子节点插入
    BinNodePosi<T> attachAsLC(BinNodePosi<T> x, MyBinTree<T> *&S);     //作为左子树插入
    BinNodePosi<T> attachAsRC(BinNodePosi<T> x, MyBinTree<T> *&S);     //作为右子树插入
    int remove(BinNodePosi<T> x);       //移除当前子树，返回原来规模
    MyBinTree<T> *secede(BinNodePosi<T> x);        //摘除当前子树并作为新的二叉树
    template<typename VST>
    void travLevel(VST &visit) { if (_root) _root->travLevel(visit); }      //层次遍历
    template<typename VST>
    void travPre(VST &visit) { if (_root) _root->travPre(visit); }       //前序遍历
    template<typename VST>
    void travIn(VST &visit) { if (_root) _root->travIn(visit); }      //中序遍历
    template<typename VST>
    void travPost(VST &visit) { if (_root) _root->template travPost(visit); }       //后序遍历
    bool operator<(MyBinTree<T> const &t) {
        return _root && t._root && lt(_root, t._root);
    }

    bool operator==(MyBinTree<T> const &t) {
        return _root && t._root && (_root == t._root);
    }
};

template<typename T>
void release(T e) {
    delete e;
}


template<typename T>
int MyBinTree<T>::updateHeight(BinNodePosi<T> x) {
    return x->height = 1 + max(stature(x->lc), stature(x->rc));
}

template<typename T>
void MyBinTree<T>::updateHeightAbove(BinNodePosi<T> x) {
    //自下而上，依次更新所有父辈节点
    while (x) {      //可以优化，高度停止变化可以提前停止
        updateHeight(x);
        x = x->parent;
    }
}

template<typename T>
BinNodePosi<T> MyBinTree<T>::insertAsRoot(const T &e) {
    _size = 1;
    return _root = new BinNode<T>(e);
}

template<typename T>
BinNodePosi<T> MyBinTree<T>::insertAsRC(BinNodePosi<T> x, const T &e) {
    _size++;
    x->insertAsRC(e);
    updateHeightAbove(x);   //向上更新高度
    return x->rc;
}

template<typename T>
BinNodePosi<T> MyBinTree<T>::insertAsLC(BinNodePosi<T> x, const T &e) {
    _size++;
    x->insertAsLC(e);
    updateHeightAbove(x);       //向上更新高度
    return x->lc;
}

template<typename T>
BinNodePosi<T> MyBinTree<T>::attachAsRC(BinNodePosi<T> x, MyBinTree<T> *&S) {
    x->rc = S->_root;       //确认子节点
    if (x->rc)
        x->rc->parent = x;      //确认父节点
    _size += S->_size;
    updateHeight(x);
    S->_root = NULL;
    S->_size = 0;
    release(S);
    S = NULL;
    return x;
}

template<typename T>
BinNodePosi<T> MyBinTree<T>::attachAsLC(BinNodePosi<T> x, MyBinTree<T> *&S) {
    x->lc = S->_root;       //确认子节点
    if (x->lc)
        x->lc->parent = x;      //确认父节点
    _size += S->_size;
    updateHeight(x);
    S->_root = NULL;
    S->_size = 0;
    release(S);
    S = NULL;
    return x;
}

template<typename T>
static int removeAt(BinNodePosi<T> x) {
    if (!x) return 0;
    int n = 1 + removeAt(x->lc) + removeAt(x->rc);
    release(x->data);
    release(x);
    return n;
}

template<typename T>
int MyBinTree<T>::remove(BinNodePosi<T> x) {
    FromParentTo(*x) = NULL;
    updateHeightAbove(x->parent);
    int n = removeAt(x);
    _size -= n;
    return n;
}

template<typename T>
MyBinTree<T> *MyBinTree<T>::secede(BinNodePosi<T> x) {
    FromParentTo(*x) = NULL;
    updateHeightAbove(x->parent);
    MyBinTree<T> *S = new MyBinTree<T>;
    S->_root = x;
    x->parent = NULL;
    S->_size = x->size();
    _size -= S->_size;
    return S;
}
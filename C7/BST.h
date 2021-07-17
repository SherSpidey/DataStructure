//
// Created by 62736 on 2021/7/15.
//

#ifndef DATASTRUCTURE_BST_H
#define DATASTRUCTURE_BST_H

#endif //DATASTRUCTURE_BST_H

#include "../C5/MyBinTree.h"

//理想左右平衡
#define Balanced(x) (stature((x).lc)==stature((x).rc))

//AVL平衡因子
#define BalFac(x) (stature((x).lc)-stature((x).rc))

//AVL平衡条件
#define AvlBalanced(x) ((-2<BalFac(x))&&(BalFac(x)<2))

#define tallerChild(x) ((stature((x).lc)>stature((x).rc))?((x).lc):((x).rc))


//由二叉树派生
template<typename T>
class BST : public MyBinTree<T> {
public:
    virtual BinNodePosi<T> &search(const T &);//查找
    virtual BinNodePosi<T> insert(const T &);//插入
    virtual bool remove(const T &);//删除

protected:
    BinNodePosi<T> _hot;    //命中节点的父亲
    BinNodePosi<T> connect34(       //3+4重构
            BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T>,
            BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T>
    );

    BinNodePosi<T> rotateAt(BinNodePosi<T>);//旋转调整
};

template<typename T>
class AVL : public BST<T> {
public:
    BinNodePosi<T> insert(const T &);

    bool remove(const T &);
};

//典型的尾递归
template<typename T>
static BinNodePosi<T> &searchIn(BinNodePosi<T> &v,     //当前（子）树根
                                const T &e,        //目标关键码
                                BinNodePosi<T> &hot)       //记忆热点
{
    if (!v || (e == v->data)) return v;   //足以确定失败、成功
    hot = v;
    return searchIn(((e < v->data) ? v->lc : v->rc), e, hot);
}//运行时间正比于返回节点v的深度，不会超过树高o(h)

//_hot指向最后返回的父节点，即如果失败，则返回真实存在的最后一个查找节点
template<typename T>
BinNodePosi<T> &BST<T>::search(const T &e) {
    return searchIn(BST<T>::_root, e, _hot = NULL);
}

template<typename T>
BinNodePosi<T> BST<T>::insert(const T &e) {
    BinNodePosi<T> &x = search(e);     //查找目标（留意_hot的设置，&？）
    if (!x) {
        x = new BinNode<T>(e, _hot);
        BST<T>::_size++;
        BST<T>::updateHeightAbove(x);
    }
    return x;
}

template<typename T>
static BinNodePosi<T> removeAt(BinNodePosi<T> &x, BinNodePosi<T> &hot) {
    BinNodePosi<T> w = x;     //实际被摘除的节点
    BinNodePosi<T> succ = NULL; //删除后的接替者
    if (!HasLChild(*x)) succ = x = x->rc;       //左子树为空
    else if (!HasRChild(*x)) succ = x = x->lc;  //右子树为空
    else {
        w = w->succ();
        swap(x->data, w->data);
        BinNodePosi<T> u = w->parent;
        (u == x ? u->rc : u->lc) = succ = w->rc;//后继就是x的右节点的情况
    }
    hot = w->parent;
    if (succ)
        succ->parent = hot;
    release(w->data);
    release(w);
    return succ;
}

template<typename T>
bool BST<T>::remove(const T &e) {
    BinNodePosi<T> &x = search(e);     //定位目标节点
    if (!x) return false;
    removeAt(x, _hot);
    BST<T>::_size--;    //更新全树规模
    BST<T>::updateHeightAbove(_hot);    //更新_hot及其历代祖先的高度
    return true;
}

template<typename T>
BinNodePosi<T> BST<T>::connect34(BinNodePosi<T> a, BinNodePosi<T> b, BinNodePosi<T> c,
                                 BinNodePosi<T> T0, BinNodePosi<T> T1,
                                 BinNodePosi<T> T2, BinNodePosi<T> T3) {
    a->lc = T0;
    if (T0) T0->parent = a;
    a->rc = T1;
    if (T1) T1->parent = a;
    BST<T>::updateHeight(a);
    c->lc = T2;
    if (T2) T2->parent = c;
    a->rc = T3;
    if (T3) T3->parent = c;
    BST<T>::updateHeight(c);
    b->lc = a;
    a->parent = b;
    b->rc = c;
    c->parent = b;
    BST<T>::updateHeight(b);
    return b;       //该子树新的根节点
}

template<typename T>
BinNodePosi<T> BST<T>::rotateAt(BinNodePosi<T> v) {
    BinNodePosi<T> p = v->parent, g = p->parent;
    if (IsLChild(*p))   //zip
        if (IsLChild(*v)) { //zip-zip
            p->parent = g->parent;  //向上级联
            return connect34(v, p, g,
                             v->lc, v->rc, p->rc, g->rc);
        } else {     //zig-zag
            v->parent = g->parent;
            return connect34(p, v, g,
                             p->lc, v->lc, v->rc, g->rc);
        }
    else {
        if (IsLChild(*v)) {
            v->parent = g->parent;
            return connect34(g, v, p,
                             g->lc, v->lc, v->rc, p->rc);
        } else {
            p->parent = g->parent;
            return connect34(g, p, v,
                             g->lc, p->lc, v->lc, v->rc);
        }

    }
}

template<typename T>
BinNodePosi<T> AVL<T>::insert(const T &e) {
    BinNodePosi<T> &x = AVL<T>::search(e);
    if (x)
        return x;//节点不存在
    x = new BinNode<T>(e, AVL<T>::_hot);
    AVL<T>::_size++;
    BinNodePosi<T> xx = x;
    for (BinNodePosi<T> g = x->parent; g; g = g->parent)
        if (!AvlBalanced(*g)) {
            FromParentTo(*g) = AVL<T>::rotateAt(tallerChild(*tallerChild(*g)));
            break;
        } else
            AVL<T>::updateHeight(g);
    return xx;
}

template<typename T>
bool AVL<T>::remove(const T &e) {
    BinNodePosi<T> &x = AVL<T>::search(e);
    if (!x)
        return false;
    removeAt(x, AVL<T>::_hot);
    AVL<T>::_size--;
    for (BinNodePosi<T> g = AVL<T>::_hot; g; g = g->parent) {
        if (!AvlBalanced(*g))
            g = FromParentTo(*g) = AVL<T>::rotateAt(tallerChild(*tallerChild(*g)));
        AVL<T>::updateHeight(g);
    }
    return true;
}
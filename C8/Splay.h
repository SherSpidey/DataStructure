//
// Created by 62736 on 2021/7/17.
//

#ifndef DATASTRUCTURE_SPLAY_H
#define DATASTRUCTURE_SPLAY_H

#endif //DATASTRUCTURE_SPLAY_H

#include "../C7/BST.h"

template<typename T>
class Splay : public BST<T> {
protected:
    BinNodePosi<T> splay(BinNodePosi<T> v); //将v伸展至根

public: //伸展树的查找也会引起整树的结构调整，所以需要重写search()
    BinNodePosi<T> &search(const T &e);

    BinNodePosi<T> insert(const T &e);

    bool remove(const T &e);
};

template<typename T>
BinNodePosi<T> Splay<T>::splay(BinNodePosi<T> v) {
    if (!v) return NULL;
    BinNodePosi<T> p;   //父节点以及以下的祖父节点
    BinNodePosi<T> g;
    while ((p = v->parent) && (g = p->parent)) {
        BinNodePosi<T> gg = g->parent;  //记录下一轮的父亲
        if (IsLChild(*v))
            if (IsLChild(*p)) {//zip-zip

            } else {//zig-zap

            }
        else if (IsRChild(*p)) {  //zag-zag

        } else { //zag-zip

        }
        if (!gg)    //此时已经为根节点
            v->parent = NULL;
        else        //否则添加
            (g == gg->lc) ? Splay<T>::attachAsLC(gg, v) : Splay<T>::attachAsRC(gg, v);
        Splay<T>::updateHeight(g);
        Splay<T>::updateHeight(p);
        Splay<T>::updateHeight(v);
    }
    if (p = v->parent) {

    }
    v->parent = NULL;
    return v;
}
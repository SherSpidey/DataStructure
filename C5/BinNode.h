//
// Created by 62736 on 2021/7/5.
//

#ifndef DATASTRUCTURE_BINNODE_H
#define DATASTRUCTURE_BINNODE_H

#endif //DATASTRUCTURE_BINNODE_H

#include <cstdlib>
#include "cstddef"
#include "../C4/MyStack.h"
#include "../C4/MyQueue.h"

#define stature(p) ((p)?(p)->height:-1)     //节点高度

#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x)&&(&(x)==(x).parent->lc))
#define IsRChild(x) (!IsRoot(x)&&(&(x)==(x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x)||HasRChild(x))
#define HasBothChild(x) (HasLChild(x)&&HasRChild(x))
#define IsLeaf(x) (!HasChild(x))

//兄弟节点
#define sibling(p) (IsLChild(*(p))?(P)->parent:(P)->parent->lr)
//叔叔辈节点
#define uncle(p) (IsLChild(*((x)->parent))?(x)->parent->rc:(x)->parent->parent->lc)
//父节点的引用
#define FromParentTo(x) (IsRoot(x)?_root:(IsLChild(x)?(x).parent->lc:(x).parent->rc))


template<typename T>
struct BinNode;

template<typename T>
using BinNodePosi = BinNode<T> *;      //节点位置替换

typedef enum {
    RB_RED, RB_BLACK
} RBColor;     //节点颜色

//二叉树节点模板类
template<typename T>
struct BinNode {
    //成员
    T data;     //数据
    BinNodePosi<T> parent;      //父节点
    BinNodePosi<T> lc;      //左子节点
    BinNodePosi<T> rc;      //右子节点
    int height;     //高度
    int npl;        //Null Path Length
    RBColor color;      //颜色（红黑树）

    //构造函数
    BinNode() :
            parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) {}

    explicit BinNode(T e, BinNodePosi<T> p = NULL, BinNodePosi<T> lc = NULL,
                     BinNodePosi<T> rc = NULL, int h = 0, int l = 1, RBColor c = RB_RED) :
            data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}

    //操作接口
    int size();     //统计当前节点的后代总数，亦即以其为根的子树的规模
    BinNodePosi<T> insertAsLC(T const &);       //作为当前节点的左子节点插入
    BinNodePosi<T> insertAsRC(T const &);       //作为当前节点的右子节点插入
    BinNodePosi<T> succ();      //取当前节点的直接后继
    template<typename VST>
    void travLevel(VST &);        //子树层次遍历
    template<typename VST>
    void travPre(VST &);      //子树先（前）序遍历
    template<typename VST>
    void travIn(VST &);       //子树中序遍历
    template<typename VST>
    void travPost(VST &);     //子树后序遍历

    //比较器、判断器
    bool operator<(BinNode const &bn) {
        return data < bn.data;
    }//小于
    bool operator==(BinNode const &bn) {
        return data == bn.data;
    }//等于
};

//向下递归，求其规模
template<typename T>
int BinNode<T>::size() {
    int s = 1;
    if (lc)
        s += lc->size();
    if (rc)
        s += rc->size();
    return s;
}

template<typename T, typename VST>
void travPre_R(BinNodePosi<T> x, VST &visit) {
    //为空退出
    if (!x) return;
    visit(x->data);
    //遍历左子树
    travPre_R(x->lc, visit);
    //遍历右子树
    travPre_R(x->rc, visit);
}

//后序遍历思想一样，递归较为简单
template<typename T, typename VST>
void travPost_R(BinNodePosi<T> x, VST &visit) {
    if (!x) return;
    travPost_R(x->lc, visit);
    travPost_R(x->rc, visit);
    visit(x->data);
}

//中序遍历
template<typename T, typename VST>
void travIn_R(BinNodePosi<T> x, VST &visit) {
    if (!x) return;
    travIn_R(x->lc, visit);
    visit(x->data);
    travIn_R(x->rc, visit);
}

//每一次遍历后更新的节点都会变成新的根节点，输出根节点，右节点入栈，左节点继续更新。
template<typename T, typename VST>
static void visitAlongLeftBranch(BinNodePosi<T> x, VST &visit, MyStack<BinNodePosi<T>> &S) {
    while (x) {
        visit(x->data);
        S.push(x->rc);
        x = x->lc;
    }
}

template<typename T, typename VST>
void travPre_I(BinNodePosi<T> x, VST &visit) {
    MyStack<BinNodePosi<T>> S;      //辅助栈
    while (true) {
        visitAlongLeftBranch(x, visit, S);
        if (S.empty())
            break;
        //之前保存的右节点出栈，更新为根节点遍历
        x = S.pop();
    }
}

//向下无需输出，依此把左节点更新为根节点压入
template<typename T>
static void goAlongLeftBranch(BinNodePosi<T> x, MyStack<BinNodePosi<T>> &S) {
    while (x) {
        S.push(x);
        x = x->lc;
    }
}

template<typename T, typename VST>
void travIn_I(BinNodePosi<T> x, VST &visit) {
    MyStack<BinNodePosi<T>> S;
    while (true) {
        goAlongLeftBranch(x, S);
        //if判断位置很重要，更新节点后如果栈剩余+新增为空，遍历完毕
        if (S.empty()) break;
        //出站后就变成一个个平凡的二叉节点，输出根节点，（左节点为空或者已输出），遍历右节点
        x = S.pop();
        visit(x->data);
        x = x->rc;
    }
}

template<typename T>
static void goHLVFL(MyStack<BinNodePosi<T>> &S) {
    while (BinNodePosi<T> x = S.top()) {
        if (HasLChild(*x)) {
            if (HasRChild(*x))
                S.push(x->rc);  //保存前进过程中的右节点
            S.push(x->lc);
        } else
            S.push(x->rc);      //没有左节点，转为右节点继续前进
    }
    S.pop();//弹出跳出循环时的空节点
}

//后序遍历的迭代
template<typename T, typename VST>
void travPost_I(BinNodePosi<T> x, VST &visit) {
    MyStack<BinNodePosi<T>> S;
    if (x) S.push(x);
    while (!S.empty()) {
        if (S.top() != x->parent)    //只有右节点向下遍历（左节点已经遍历完毕了）
            goHLVFL(S);
        x = S.pop();        //弹出栈顶进行输出
        visit(x->data);
    }
}

//新节点作为左子节点插入
template<typename T>
BinNodePosi<T> BinNode<T>::insertAsLC(const T &e) {
    return lc = new BinNode(e, this);
}

//新节点作为右子节点插入
template<typename T>
BinNodePosi<T> BinNode<T>::insertAsRC(const T &e) {
    return rc = new BinNode(e, this);
}


//找出当前节点的中序直接后继
template<typename T>
BinNodePosi<T> BinNode<T>::succ() {
    BinNodePosi<T> s = this;
    if (rc) {//存在右子树，那么直接后继肯定是该子树的最左节点
        s = rc;
        while (HasLChild(*s))
            s = s->lc;
    } else { //不存在右子树，那么后继则需要往上返回
        while (IsRChild(*s))    //当前已为右节点，说明该层已经输出
            s = s->parent;      //已经输出，需要返回两层
        s = s->parent;      //向上返回
    }
    return s;
}

//只是第一种迭代方法的变体
template<typename T, typename VST>
void travIn_I2(BinNodePosi<T> x, VST &visit) {
    MyStack<BinNodePosi<T>> S;
    while (true) {
        if (x) {
            S.push(x);
            x = x->lc;
        } else if (!S.empty()) {
            x = S.pop();
            visit(x->data);
            x = x->rc;
        } else
            break;
    }
}

//利用succ找出直接后继然后输出
template<typename T, typename VST>
void travIn_I3(BinNodePosi<T> x, VST &visit) {
    bool backtrack = false;     //阻止反复向下遍历
    while (true) {
        if (!backtrack && HasLChild(*x))
            x = x->lc;      //左树最深处，为最前驱
        else {
            visit(x->data);     //开始输出
            if (HasRChild(*x)) {
                x = x->rc;
                backtrack = false;  //右节点允许向下遍历
            } else {
                if (!(x = x->succ()))//无直接后继即可返回
                    break;
                backtrack = true;    //返回节点不允许遍历
            }
        }
    }
}

//前序遍历入口
template<typename T>
template<typename VST>
void BinNode<T>::travPre(VST &visit) {
    switch (0) {
        case 0:
            travPre_I(this, visit);
            break;
        case 1:
            travPre_R(this, visit);
            break;
        default:
            break;
    }
}

//中序遍历统一入口
template<typename T>
template<typename VST>
void BinNode<T>::travIn(VST &visit) {
    switch (0) {
        case 0:
            travIn_I3(this, visit);
            break;
        case 1:
            travIn_R(this, visit);
            break;
        default:
            break;
    }
}

//后序遍历统一入口
template<typename T>
template<typename VST>
void BinNode<T>::travPost(VST &visit) {
    switch (0) {
        case 0:
            travPost_I(this, visit);
            break;
        case 1:
            travPost_R(this, visit);
            break;
        default:
            break;
    }
}

//层次遍历
template<typename T>
template<typename VST>
void BinNode<T>::travLevel(VST &visit) {
    MyQueue<BinNodePosi<T>> Q;
    Q.enqueue(this);    //根节点如队列
    while (!Q.empty()) {
        BinNodePosi<T> x = Q.dequeue();
        visit(x->data);
        if (HasLChild(*x))
            Q.enqueue(x->lc);
        if (HasRChild(*x))
            Q.enqueue(x->rc);
    }
}
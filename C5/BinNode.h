//
// Created by 62736 on 2021/7/5.
//

#ifndef DATASTRUCTURE_BINNODE_H
#define DATASTRUCTURE_BINNODE_H

#endif //DATASTRUCTURE_BINNODE_H

#define stature(p) ((p)?(p)->height:-1)     //节点高度

template<typename T>
struct BinNode;

template<typename T>
using BinNodePosi = BinNode<T> *;      //节点位置替换

typedef enum {RB_RED,RB_BLACK} RBColor;     //节点颜色

//
template<typename T>
struct BinNode{
    //成员
    T data;     //数据
    BinNodePosi<T> parent;      //父节点
    BinNodePosi<T> lc;      //左子节点
    BinNodePosi<T> rc;      //右子节点
    int height;     //高度
    int npl;        //Null Path Length
    RBColor color;      //颜色（红黑树）

    //构造函数
    BinNode():
    parent(NULL),lr(NULL),rc(NULL),height(0),npl(1),color(RB_RED){}
    explicit BinNode(T e, BinNodePosi<T> p = NULL, BinNodePosi<T> lc = NULL,
                     BinNodePosi<T> rc = NULL,int h = 0, int l =1,RBColor c = RB_RED):
            data(e),parent(p),lc(lc),rc(rc),height(h),npl(l),color(c){}

    //操作接口
    int size();     //统计当前节点的后代总数，亦即以其为根的子树的规模
    BinNodePosi<T> insertAsLC(T const&);       //作为当前节点的左子节点插入
    BinNodePosi<T> insertAsRC(T const&);       //作为当前节点的右子节点插入
    BinNodePosi<T> succ();      //取当前节点的直接后继
    template<typename VST> void travLevel(VST&);        //子树层次遍历
    template<typename VST> void travPre(VST&);      //子树先（前）序遍历
    template<typename VST> void travIn(VST&);       //子树中序遍历
    template<typename VST> void travPost(VST&);     //子树后序遍历

    //比较器、判断器
    bool operator< (BinNode const & bn){
        return data<bn.data;
    }//小于
    bool operator== (BinNode const & bn){
        return data==bn.data;
    }//等于
};
//
// Created by 62736 on 2021/6/18.
//

#ifndef DATASTRUCTURE_MYLIST_H
#define DATASTRUCTURE_MYLIST_H

#endif //DATASTRUCTURE_MYLIST_H

#include "ListNode.h"   //引入列表节点类

template <typename T>
class MyList { //列表模板类
private:
    int _size;
    ListNodePosi<T> header;
    ListNodePosi<T> trailer; //规模、头哨兵、尾哨兵

protected:
    void init(); //列表创建时的初始化
    int clear(); //清除所有节点
    void copyNodes ( ListNodePosi<T>, int ); //复制列表中自位置p起的n项
    ListNodePosi<T> merge (ListNodePosi<T> &, int, MyList<T> &, ListNodePosi<T>, int ); //归并
    void mergeSort ( ListNodePosi<T> &, int ); //对从p开始连续的n个节点归并排序
    void selectionSort ( ListNodePosi<T>, int ); //对从p开始连续的n个节点选择排序
    void insertionSort ( ListNodePosi<T>, int ); //对从p开始连续的n个节点插入排序
    void radixSort(ListNodePosi<T>, int); //对从p开始连续的n个节点基数排序

public:
    // 构造函数
    MyList() { init(); } //默认
    MyList (MyList<T> const& L ); //整体复制列表L
    MyList (MyList<T> const& L, Rank r, int n ); //复制列表L中自第r项起的n项
    MyList (ListNodePosi<T> p, int n ); //复制列表中自位置p起的n项
    // 析构函数
    ~MyList(); //释放（包含头、尾哨兵在内的）所有节点
    // 只读访问接口
    Rank size() const { return _size; } //规模
    bool empty() const { return _size <= 0; } //判空
    T& operator[] ( Rank r ) const; //重载，支持循秩访问（效率低）
    ListNodePosi<T> operator() (Rank r);
    ListNodePosi<T> first() const { return header->succ; } //首节点位置
    ListNodePosi<T> last() const { return trailer->pred; } //末节点位置
    bool valid ( ListNodePosi<T> p ) //判断位置p是否对外合法
    { return p && ( trailer != p ) && ( header != p ); } //将头、尾节点等同于NULL
    ListNodePosi<T> find ( T const& e ) const //无序列表查找
    { return find ( e, _size, header ); }
    ListNodePosi<T> find ( T const& e, int n, ListNodePosi<T> p ) const; //无序区间查找
    ListNodePosi<T> search ( T const& e ) const //有序列表查找
    { return search ( e, _size, trailer ); }
    ListNodePosi<T> search ( T const& e, int n, ListNodePosi<T> p ) const; //有序区间查找
    ListNodePosi<T> selectMax ( ListNodePosi<T> p, int n ); //在p及其n-1个后继中选出最大者
    ListNodePosi<T> selectMax() { return selectMax ( header->succ, _size ); } //整体最大者
    // 可写访问接口
    ListNodePosi<T> insertAsFirst ( T const& e ); //将e当作首节点插入
    ListNodePosi<T> insertAsLast ( T const& e ); //将e当作末节点插入
    ListNodePosi<T> insert ( ListNodePosi<T> p, T const& e ); //将e当作p的后继插入
    ListNodePosi<T> insert ( T const& e, ListNodePosi<T> p ); //将e当作p的前驱插入
    T remove ( ListNodePosi<T> p ); //删除合法位置p处的节点,返回被删除节点
    void merge (MyList<T> & L ) { merge (header->succ, _size, L, L.header->succ, L._size ); } //全列表归并
    void sort ( ListNodePosi<T> p, int n ); //列表区间排序
    void sort() { sort ( first(), _size ); } //列表整体排序
    int deduplicate(); //无序去重
    int uniquify(); //有序去重
    void reverse(); //前后倒置（习题）
    // 遍历
    void traverse ( void (* ) ( T& ) ); //遍历，依次实施visit操作（函数指针，只读或局部性修改）
    template <typename VST> //操作器
    void traverse ( VST& ); //遍历，依次实施visit操作（函数对象，可全局性修改）
}; //MyList

template <typename T>
void MyList<T>::init() {
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ = trailer;
    header->pred = NULL;
    trailer->pred = header;
    trailer->succ = NULL;
    _size = 0;
}

template <typename T>
T& MyList<T>::operator[](Rank r) const {
    ListNodePosi<T> p = first();
    while(0 < r--)
        p = p->succ;
    return p->data;
}

template <typename T>
ListNodePosi<T> MyList<T>::operator()(Rank r) {
    ListNodePosi<T> p = first();
    while(0 < r--)
        p = p->succ;
    return p;
}

template <typename T>
ListNodePosi<T> MyList<T>::find(const T &e, int n, ListNodePosi<T> p) const {
    while (0 < n--)
        if (e == (p = p->succ)->data)
            return p;
    return NULL;
}

template <typename T>
ListNodePosi<T> MyList<T>::insertAsFirst(const T &e) {
    _size++;
    return header->insertAsSucc(e);
}

template <typename T>
ListNodePosi<T> MyList<T>::insertAsLast(const T &e) {
    _size++;
    return trailer->insertAsPred(e);
}

template <typename T>
ListNodePosi<T> MyList<T>::insert(ListNodePosi<T> p, const T &e) {
    _size++;
    return p->insertAsSucc(e);
}

template <typename T>
ListNodePosi<T> MyList<T>::insert(const T &e, ListNodePosi<T> p) {
    _size++;
    return p->insertAsPred(e);
}

template <typename T>
void MyList<T>::copyNodes(ListNodePosi<T> p, int n) {
    init();
    while (n--) { insertAsLast(p->data); p = p->succ;}
}

template <typename T>
MyList<T>::MyList(ListNodePosi<T> p, int n) {
    copyNodes(p,n);
}

template <typename T>
MyList<T>::MyList(const MyList<T> &L) {
    copyNodes(L.first(), L._size);
}

template <typename T>
MyList<T>::MyList(const MyList<T> &L, Rank r, int n) {
    ListNodePosi<T> t = L.first();
    for(int i =0 ;i<r;i++)
        t = t->succ;
    copyNodes(t, n);
}

template <typename T>
T MyList<T>::remove(ListNodePosi<T> p) {
    T e = p->data;
    p->succ->pred = p->pred;
    p->pred->succ = p->succ;
    delete p;
    _size--;
    return e;
}

template <typename T>
MyList<T>::~MyList() {
    clear();
    delete header;
    delete trailer;
}

template <typename T>
int MyList<T>::clear() {
    int oldSize = _size;
    while (0<_size)
        remove(header->succ);
    return oldSize;
}

template <typename T>
int MyList<T>::deduplicate() {
    if (_size < 2)
        return 0;
    int oldSize = _size;
    ListNodePosi<T> p = header;
    Rank r = 0;
    while (trailer != (p = p->succ)){
        ListNodePosi<T> q = find(p->data, r, header);
        q ? remove(q) : r++;
    }
    return oldSize;
}

template <typename T>
void MyList<T>::traverse(void (*visit)(T &)) {
    for(ListNodePosi<T> p = header->succ; p != trailer ; p = p->succ)
        visit(p->data);
}

template <typename T> template <typename VST>
void MyList<T>::traverse(VST &visit) {
    for(ListNodePosi<T> p = header->succ; p != trailer ; p = p->succ)
        visit(p->data);
    visit();
}

template <typename T>
int MyList<T>::uniquify() {
    if(_size < 2)
        return 0;
    int oldSize = _size;
    ListNodePosi<T> p = first();
    ListNodePosi<T> q;
    while (trailer != (q = p->succ)){
        if(p->data != q->data)
            p = q;
        else
            remove(q);
    }
    return oldSize;
}

template <typename T>
ListNodePosi<T> MyList<T>::search(const T &e, int n, ListNodePosi<T> p) const {
    while (0 <= n--)
        if((( p=p->pred)->data) <=e ) break;
    return p;
}

template <typename T>
void MyList<T>::sort(ListNodePosi<T> p, int n) {
    switch (rand()%3) {
        case 1:
            insertionSort(p, n);
            break;
        case 2:
            selectionSort(p, n);
            break;
        default:
            mergeSort(p, n);
            break;
    }
}

template <typename T>
void MyList<T>::insertionSort(ListNodePosi<T> p , int n) {
    for(Rank r = 0; r < n;r++){
        insert(search(p->data, r, p),p->data);
        p = p->succ;
        remove(p->pred);
    }
}

template <typename T>
void MyList<T>::selectionSort(ListNodePosi<T> p, int n) {
    ListNodePosi<T> head = p->pred;
    ListNodePosi<T> tail = p;
    for(int i =0;i<n;i++)
        tail = tail->succ;
    while (1 < n){
        ListNodePosi<T> max = selectMax(head->succ, n--);
        insert(remove(max),tail);
        tail = tail->pred;
    }
}

template <typename T>
ListNodePosi<T> MyList<T>::selectMax(ListNodePosi<T> p, int n) {
    ListNodePosi<T> max = p;
    for(ListNodePosi<T> cur = p; 1 < n; n--)
        if((cur=cur->succ)->data > max->data)
            max = cur;
    return max;
}

template <typename T>
void MyList<T>::mergeSort(ListNodePosi<T> &p, int n) {
    if(n<2)
        return;
    int m = n >> 1;
    ListNodePosi<T> q = p;
    for(int i = 0; i < m; i++)
        q = q->succ;
    mergeSort(p,m);
    mergeSort(q,n-m);
    p = merge(p,m,*this,q,n-m);
}

template <typename T>
ListNodePosi<T> MyList<T>::merge(ListNodePosi<T> &p, int n, MyList<T> & L, ListNodePosi<T> q, int m) {
    ListNodePosi<T> pp = p->pred;
    while( 0 < m)
        if((0 < n)&&(p->data<=q->data)){
            if(q == (p = p->succ))      //如果p区的数据都已经转移完毕
                break;
            n--;
        }
        else{
            insert(L.remove((q = q->succ)->pred),p);
            m--;
        }
    return pp->succ;
}

template<typename T>
void MyList<T>::reverse() {
    ListNodePosi<T> T1 = first();
    ListNodePosi<T> T2 = T1->succ;
    for(int i =1 ;i<_size;i++){         //中间部分的连接交换
        ListNodePosi<T> temp = T2->succ;
        T1->pred = T2;
        T2->succ = T1;
        T1 = T2;
        T2 = temp;
    }
    T2=first();                         //首位部分的连接交换，交换前要先保存
    T1=last();
    T1->pred = header;
    header -> succ =T1;         //交换后first就不同了
    T2 ->succ = trailer;
    trailer ->pred = T2;        //交换后last就不同了
}


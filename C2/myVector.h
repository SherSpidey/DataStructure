//
// Created by 62736 on 2021/6/15.
//

#include <random>
#include "iostream"

#ifndef DATASTRUCTURE_MYVECTOR_H
#define DATASTRUCTURE_MYVECTOR_H

#endif //DATASTRUCTURE_MYVECTOR_H

typedef int Rank; //定义秩
#define DEFAULT_CAPACITY  10 //默认存储空间个数

template<typename T>
void swap(T &T1, T &T2);

template<typename T>
//没有斐波那契头文件，用2:1切割替代
static Rank fibSearch(T *A, T const &e, Rank lo, Rank hi);

template<typename T>
static Rank binSearch(T *A, T const &e, Rank lo, Rank hi);

template<typename T>
class MyVector {
protected:
    Rank _size;
    int _capacity;
    T *_elem;   //规模，容量以及数据区地址
    void copyFrom(T const *A, Rank lo, Rank hi); //复制数组区间A[lo,hi)
    void expand(); //空间不足时扩容
    void shrink(); //装填过少时压缩
    Rank bubble(Rank lo, Rank hi); //扫描交换
    void bubbleSort(Rank lo, Rank hi); //气泡排序法
    Rank max(Rank lo, Rank hi); //找出最大值元素
    void selectionSort(Rank lo, Rank hi); //选择排序法
    void merge(Rank lo, Rank mi, Rank hi); //归并算法
    void mergeSort(Rank lo, Rank hi); //归并排序法
    Rank partition(Rank lo, Rank hi); //轴点构造算法
    void quickSort(Rank lo, Rank hi); //快速排序算法
    void heapSort(Rank lo, Rank hi); //堆排序
public:
    //构造函数
    MyVector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)  //容量为c，规模为s，元素初始值为v
    {
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v);
    }

    MyVector(T const *A, Rank n) { copyFrom(A, 0, n); }  //从数组复制指定长度元素
    MyVector(T const *A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } //从数组复制区间元素
    MyVector(MyVector<T> const &V) { copyFrom(V._elem, 0, V._size); } //向量全部复制
    MyVector(MyVector<T> const &V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); }

    //析构函数
    ~MyVector() { delete[] _elem; }    //释放空间

    //只读访问接口
    Rank size() const { return _size; }

    bool empty() const { return !_size; }

    int disOrdered() const;

    Rank find(T const &e) const { return find(e, 0, _size); }

    Rank find(T const &e, Rank lo, Rank hi) const;

    Rank search(T const &e) const {
        return (0 >= _size) ? -1 : search(e, 0, _size);
    }

    Rank search(T const &e, Rank lo, Rank hi) const;

    //可写访问接口
    T &operator[](Rank r) const; //重载下标操作符，可以类似于数组形式引用各元素
    MyVector<T> &operator=(MyVector<T> const &); //重载赋值操作符，以便直接克隆向量
    T remove(Rank r); //初除秩为r的元素
    int remove(Rank lo, Rank hi); //删除秩在区间[lo, hi)内的元素
    Rank insert(Rank r, T const &e); //插入元素
    Rank insert(T const &e) { return insert(_size, e); } //默认在末尾插入
    void sort(Rank lo, Rank hi); //对[lo, hi)排序
    void sort() { sort(0, _size); } //整体排序
    void unsort(Rank lo, Rank hi); //对[lo, hi)置乱
    void unsort() { unsort(0, _size); } //整体置乱
    int deduplicate(); //无序去重
    int unify(); //有序去重

    //遍历
    void traverse(void (*)(T &)); //遍历，使用函数指针，只读或者局部性更改

    template<typename VST>
    void traverse(VST &); //遍历，使用函数对象，可全局性修改

    //输出打印元素
    void print();
};

template<typename T>
void swap(T &T1, T &T2) {
    T temp;
    temp = T1;
    T1 = T2;
    T2 = temp;
}

template<typename T>
void MyVector<T>::print() {
    for (int i = 0; i < _size; i++)
        std::cout << _elem[i] << ' ';
    std::cout << std::endl;
}

template<typename T>
Rank MyVector<T>::max(Rank lo, Rank hi) {
    MyVector<T> temp = MyVector<T>(*this);
    temp.sort();
    T value = temp[_size - 1];
    return find(value);
}

template<typename T>
void MyVector<T>::copyFrom(const T *A, Rank lo, Rank hi) {
    _elem = new T[_capacity = 2 * (hi - lo)];             //分配空间
    _size = 0;
    while (lo < hi)
        _elem[_size++] = A[lo++];
}

template<typename T>
MyVector<T> &MyVector<T>::operator=(const MyVector<T> &V) {
    if (_elem) delete[] _elem;         //如果原有存在，就释放原有内存
    copyFrom(V._elem, 0, V.size());
    return *this;   //返回当前对象的引用，以便链式赋值
}

template<typename T>
void MyVector<T>::expand() {
    if (_size < _capacity) return;       //向量未满，无需扩容
    if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
    T *oldElem = _elem;
    _elem = new T[_capacity <<= 1];     //左移容量加倍
    for (int i = 0; i < _size; i++)
        _elem[i] = oldElem[i];
    delete[] oldElem;
}

template<typename T>
void MyVector<T>::shrink() {
    if (_capacity < DEFAULT_CAPACITY << 1) return;      //最小不能小于DEFAULT
    if (_size << 2 > _capacity) return;        //以25%为界
    T *oldElem = _elem;
    _elem = new T[_capacity >>= 1];     //容量减半
    for (int i = 0; i < _size; i++)
        _elem[i] = oldElem[i];
    delete[] oldElem;
}

template<typename T>
T &MyVector<T>::operator[](Rank r) const {
    return _elem[r];        //assert: 0<=r<_size
}

template<typename T>
void permute(MyVector<T> &V) {
    for (int i = V.size(); i > 0; i--)     //自后向前
        swap(V[i - 1], V[rand() % i]);      //当前元素与随机元素交换
}

template<typename T>
static bool lt(T &a, T &b) { return a < b; } //less than
template<typename T>
static bool lt(T *a, T *b) { return lt(*a, *b); } //less than
template<typename T>
static bool eq(T &a, T &b) { return a == b; } //equal
template<typename T>
static bool eq(T *a, T *b) { return eq(*a, *b); } //equal

template<typename T>
Rank MyVector<T>::find(const T &e, Rank lo, Rank hi) const {
    while ((lo < hi--) && (e != _elem[hi]));        //从后向前查找，找中即返回
    return hi;
}

template<typename T>
Rank MyVector<T>::insert(Rank r, const T &e) {
    expand();
    for (int i = _size; i > r; i--)
        _elem[i] = _elem[i - 1];
    _elem[r] = e;
    _size++;
    return r;
}

template<typename T>
int MyVector<T>::remove(Rank lo, Rank hi) {
    if (lo == hi) return 0;
    while (hi < _size)
        _elem[lo++] = _elem[hi++];
    _size = lo;      //直接舍弃后面重复的部分
    shrink();
    return hi - lo;
}

template<typename T>
T MyVector<T>::remove(Rank r) {
    T e = _elem[r];
    remove(r, r + 1);
    return e;
}

template<typename T>
int MyVector<T>::deduplicate() {
    int oldSize = _size;
    Rank i = 1;
    while (i < _size)
        (find(_elem[i], 0, i) < 0) ? i++ : remove(i);
    return oldSize - _size;
}

template<typename T>
//借助函数指针遍历
void MyVector<T>::traverse(void (*visit)(T &)) {
    for (int i = 0; i < _size; i++)
        visit(_elem[i]);
}

template<typename T>
template<typename VST>
//借助函数对象遍历
void MyVector<T>::traverse(VST &visit) {
    for (int i = 0; i < _size; i++)
        visit(_elem[i]);
    visit();
}

template<typename T>
struct Incease {
    virtual void operator()(T &e) { e++; }
};

template<typename T>
void increase(MyVector<T> &V) {
    V.traverse(Incease<T>());
}

template<typename T>
int MyVector<T>::disOrdered() const {
    int n = 0;
    for (int i = 1; i < _size; i++)
        if (_elem[i] < _elem[i - 1])
            n++;
    return n;
}

template<typename T>
//主需要将不重复的元素赋值到一起，更改长度即可
int MyVector<T>::unify() {
    int i = 0, j = 0;
    while (++j < _size)
        if (_elem[i] != _elem[j])
            _elem[++i] = _elem[j];
    _size = ++i;
    shrink();
    return j - i;
}

template<typename T>
Rank MyVector<T>::search(const T &e, Rank lo, Rank hi) const {
    return binSearch(_elem, e, lo, hi);//(rand() % 2)? binSearch(_elem, e, lo ,hi) : fibSearch(_elem, e, lo ,hi);
}

template<typename T>
//二分查找法，追求稳定的查找长度，满足特定的查找需求
static Rank binSearch(T *A, T const &e, Rank lo, Rank hi) {
    while (lo < hi) {
        Rank mi = (lo + hi) >> 1;
        (e < A[mi]) ? hi = mi : lo = mi + 1;
    }
    return --lo;
}

template<typename T>
//没有斐波那契头文件，用2:1切割替代
static Rank fibSearch(T *A, T const &e, Rank lo, Rank hi) {
    Rank mi;
    while (lo < hi) {
        mi = lo + (hi - lo) * 2 / 3;
        if (A[mi] < e)
            lo = mi + 1;
        else if (e < A[mi])
            hi = mi;
        else
            return mi;
    }
    return -1;
}

template<typename T>
void MyVector<T>::sort(Rank lo, Rank hi) {
    switch (3) {       //随机选取排序方法
        case 1:
            bubbleSort(lo, hi);
            break;
        case 2:
            selectionSort(lo, hi);
            break;
        case 3:
            mergeSort(lo, hi);
            break;
        case 4:
            heapSort(lo, hi);
            break;
        default:
            quickSort(lo, hi);
            break;
    }
}

template<typename T>
void MyVector<T>::bubbleSort(Rank lo, Rank hi) {
    while (lo < bubble(lo, hi));
}

template<typename T>
Rank MyVector<T>::bubble(Rank lo, Rank hi) {
    Rank last = lo;
    while (++lo < hi) {
        if (_elem[lo] < _elem[lo - 1]) {
            last = lo;
            swap(_elem[lo - 1], _elem[lo]);
        }
    }
    return last;
}

template<typename T>
void MyVector<T>::mergeSort(Rank lo, Rank hi) {
    if (hi - lo < 2)
        return;
    int mi = (lo + hi) >> 1;
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    merge(lo, mi, hi);
}

template<typename T>
void MyVector<T>::merge(Rank lo, Rank mi, Rank hi) {
    T *A = _elem + lo;
    int lb = mi - lo;
    T *B = new T[lb];
    for (Rank i = 0; i < lb; B[i++] = A[i]);
    int lc = hi - mi;
    T *C = _elem + mi;
    for (Rank i = 0, j = 0, k = 0; j < lb;) {
        if ((k >= lc || (B[j] <= C[k]))) A[i++] = B[j++];
        if ((k < lc) && (C[k] < B[j])) A[i++] = C[k++];
    }
    delete[] B;
}
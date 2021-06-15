//
// Created by 62736 on 2021/6/15.
//

#include <random>

#ifndef DATASTRUCTURE_MYVECTOR_H
#define DATASTRUCTURE_MYVECTOR_H

#endif //DATASTRUCTURE_MYVECTOR_H

typedef int Rank; //定义秩
#define DEFAULT_CAPACITY  10 //默认存储空间个数

template<typename T> void swap(T& T1, T& T2);

template<typename T> class MyVector {
protected:
    Rank _size;
    int _capacity;
    T *_elem;   //规模，容量以及数据区地址
    void copyFrom(T const *A, Rank lo, Rank hi); //复制数组区间A[lo,hi)
    void expand(); //空间不足时扩容
    void shrink(); //装填过少时压缩
    bool bubble(Rank lo, Rank hi); //扫描交换
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
};

template<typename T> void swap(T& T1, T& T2){
    T temp;
    temp = T1;
    T2 = T1;
    T1 = temp;
}

template <typename  T> void MyVector<T>::copyFrom(const T *A, Rank lo, Rank hi) {
    _elem = new T[_capacity = 2*(hi - lo)];             //分配空间
    _size = 0;
    while(lo<hi)
        _elem[_size++] = A[lo++];
}

template<typename T> MyVector<T>& MyVector<T>::operator= (const MyVector<T> & V) {
    if( _elem) delete [] _elem;         //如果原有存在，就释放原有内存
    copyFrom(V._elem, 0, V.size());
    return *this;   //返回当前对象的引用，以便链式赋值
}

template <typename  T> void MyVector<T>::expand() {
    if(_size < _capacity) return;       //向量未满，无需扩容
    if(_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
    T * oldElem = _elem;
    _elem = new T[_capacity <<= 1];     //左移容量加倍
    for (int i = 0;i<_size;i++)
        _elem[i]=oldElem[i];
    delete [] oldElem;
}

template<typename T> void MyVector<T>::shrink() {
    if(_capacity <DEFAULT_CAPACITY<<1) return;      //最小不能小于DEFAULT
    if(_size<<2 > _capacity) return;        //以25%为界
    T * oldElem = _elem;
    _elem = new T[_capacity >>= 1];     //容量减半
    for(int i=0;i<_size;i++)
        _elem[i] = oldElem[i];
    delete [] oldElem;
}

template<typename T> T &MyVector<T>::operator[](Rank r) const {
    return _elem[r];        //assert: 0<=r<_size
}

template<typename T> void permute(MyVector<T>& V){
    for(int i=V.size();i>0;i--)     //自后向前
        swap(V[i-1], V[rand()%i]);      //当前元素与随机元素交换
}

template <typename T> static bool lt ( T& a, T& b ) { return a < b; } //less than
template <typename T> static bool lt ( T* a, T* b ) { return lt ( *a, *b ); } //less than
template <typename T> static bool eq ( T& a, T& b ) { return a == b; } //equal
template <typename T> static bool eq ( T* a, T* b ) { return eq ( *a, *b ); } //equal
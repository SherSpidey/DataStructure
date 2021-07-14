//
// Created by 62736 on 2021/7/13.
//

#ifndef DATASTRUCTURE_GRAPH_H
#define DATASTRUCTURE_GRAPH_H

#endif //DATASTRUCTURE_GRAPH_H

#include "iostream"
#include "../C4/MyStack.h"
#include "../C4/MyQueue.h"

typedef enum {
    UNDISCOVERED, DISCOVERED, VISITED
} VStatus;
typedef enum {
    UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD
} EStatus;

template<typename Tv>
struct Vertex {        //顶点对象（并未严格封装）
    Tv data;
    int inDegree, outDegree;    //数据、出入度数
    VStatus status;     //对应上述三种状态
    int dTime, fTime;   //时间标签
    int parent;     //在遍历树中的父节点
    int priority;   //在遍历树中的优先级(最短通路、极短跨边等)
    Vertex(Tv const &d) :
            data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
            dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}

};

template<typename Te>
struct Edge {     //边对象(未严格封装)
    Te data;
    int weight;
    EStatus status;

    Edge(Te const &d, int w) :
            data(d), weight(w), status(UNDETERMINED) {}

};

template<typename Tv, typename Te>
class Graph {    //顶点类型，边类型
private:
    void reset() { //
        for (int i = 0; i < n; i++) { //
            status(i) = UNDISCOVERED;
            dTime(i) = fTime(i) = -1; //状态，时间标签
            parent(i) = -1;
            priority(i) = INT_MAX; //
            for (int j = 0; j < n; j++) //
                if (exists(i, j)) status(i, j) = UNDETERMINED; //类型
        }
    }

    void BFS(int, int &); //（连通域）广度优先搜索算法
    void DFS(int, int &); //（连通域）深度优先搜索算法
    void BCC(int, int &, MyStack<int> &); //
    bool TSort(int, int &, MyStack<Tv> *); //
    template<typename PU>
    void PFS(int, PU); //

public:
    // 顶点
    int n{}; //顶点总数
    virtual int insert(Tv const &) = 0; //揑
    virtual Tv remove(int) = 0; //
    virtual Tv &vertex(int) = 0; //
    virtual int inDegree(int) = 0; //
    virtual int outDegree(int) = 0; //
    virtual int firstNbr(int) = 0; //
    virtual int nextNbr(int, int) = 0; //
    virtual VStatus &status(int) = 0; //
    virtual int &dTime(int) = 0; //
    virtual int &fTime(int) = 0; //
    virtual int &parent(int) = 0; //
    virtual int &priority(int) = 0; //

    int e{}; //边总数
    virtual bool exists(int, int) = 0; //边(v, u)是否存在
    virtual void insert(Te const &, int, int, int) = 0; //
    virtual Te remove(int, int) = 0; //
    virtual EStatus &status(int, int) = 0; //
    virtual Te &edge(int, int) = 0; //
    virtual int &weight(int, int) = 0; //
    // 算法
    void bfs(int); //广度优先搜索算法
    void dfs(int); //深度优先搜索算法
    void bcc(int); //
    MyStack<Tv> *tSort(int); //
    void prim(int); //
    template<typename PU>
    void pfs(int, PU); //优先级搜索框架

};

template<typename Tv, typename Te>
class GraphMatrix : public Graph<Tv, Te> {
private:
    MyVector<Vertex<Tv>> V; //顶点集
    MyVector<MyVector<Edge<Te> *>> E;    //边集
public:
    GraphMatrix() { GraphMatrix::n = GraphMatrix::e = 0; }  //构造
    ~GraphMatrix() {     //析构
        for (int j = 0; j < GraphMatrix::n; j++)
            for (int k = 0; k < GraphMatrix::n; k++)
                delete E[j][k];     //清除所有动态申请的边记录
    }

    Tv &vertex(int i) { return V[i].data; }

    int inDegree(int i) { return V[i].inDegree; }

    int outDegree(int i) { return V[i].outDegree; }

    VStatus &status(int i) { return V[i].status; }

    int &dTime(int i) { return V[i].dTime; }

    int &fTime(int i) { return V[i].fTime; }

    int &parent(int i) { return V[i].parent; }

    int &priority(int i) { return V[i].priority; }

    int nextNbr(int i, int j) {       //若已枚举至邻居j，则转向下一邻居
        while ((-1 < j) && !exists(i, --j));   //逆向顺序查找，o(n)
        return j;
    }

    int firstNbr(int i) {
        return nextNbr(i, GraphMatrix::n);
    }

    bool exists(int i, int j) {
        return (0 <= j) && (i < GraphMatrix::n) && (0 <= j) && (j < GraphMatrix::n) && E[i][j] != NULL;
    }

    Te &edge(int i, int j) { return E[i][j]->data; }

    EStatus &status(int i, int j) { return E[i][j]->status; }

    int &weight(int i, int j) { return E[i][j]->weight; }

    void insert(Te const &edge, int w, int i, int j) {       //插入(i,j,w)
        if (exists(i, j)) return;     //忽略已有的边
        E[i][j] = new Edge<Te>(edge, w); //创建新边
        GraphMatrix::e++;   //更新边计数
        V[i].outDegree++;   //更新关联节点的出度
        V[j].inDegree++;    //更新关联节点的入度
    }

    Te remove(int i, int j) {        //删除顶点i与j之间的联边
        Te eBak = edge(i, j);        //备份边(i,j)的信息
        delete E[i][j];
        E[i][j] = NULL;             //删除边
        GraphMatrix::e--;
        V[i].outDegree--;
        V[j].inDegree--;            //更新各项计数
        return eBak;
    }

    int insert(Tv const &vertex) {
        for (int j = 0; j < GraphMatrix::n; j++)
            E[j].insert(NULL);      //列拓展
        GraphMatrix::n++;           //索引扩增
        E.insert(MyVector<Edge<Te> *>(GraphMatrix::n, GraphMatrix::n, NULL)); //行拓展
        return V.insert(Vertex<Tv>(vertex));        //节点扩增
    }
};

//广度优先搜索(连通)
template<typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int &clock) {
    MyQueue<int> Q;
    status(v) = DISCOVERED;
    Q.enqueue(v);   //初始化
    while (!Q.empty()) {
        int v = Q.dequeue();
        dTime(v) = ++clock;
        for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {  //依次向前枚举节点
            if (UNDISCOVERED == status(u)) {      //相邻节点未被发现
                status(u) = DISCOVERED;
                Q.enqueue(u);       //现已发现，入队
                status(v, u) = TREE; //引入树边
                parent(u) = v;
            } else
                status(v, u) = CROSS;    //已被发现，或者已经访问结束，归类于跨边
        }
        status(v) = VISITED;//至此，当前顶点访问完毕
    }
}

//广度优先搜索
template<typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s) {
    reset();
    int clock = 0;
    int v = s;  //初始化
    do {
        if (UNDISCOVERED == status(v))
            BFS(v, clock);
    } while (s != (v = (++v % n)));
    //所有的节点按序号启动搜索，回到s时退出
}

//广度优先搜索(可达区)
template<typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int &clock) {
    dTime(v) = ++clock;
    status(v) = DISCOVERED;     //当前顶点可访问
    for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
        switch (status(u)) {
            case UNDISCOVERED:  //可访问节点
                status(v, u) = TREE;     //标记树边
                parent(u) = v;
                DFS(u, clock);       //递归
                break;
            case DISCOVERED:
                status(v, u) = BACKWARD; //已被访问但没有访问完毕，此时v到u是回传
                break;
            default:
                //如果已经被访问完毕，则根据时间节点确定先后顺序。
                status(v, u) = dTime(v) < dTime(u) ? FORWARD : CROSS;
                //FORWARD表示u是后代，但被其他路径访问完毕,CROSS则表示非亲的跨越
                break;
        }
    }
    status(v) = VISITED;
    fTime(v) = ++clock;
}

#define hca(x) (fTime(x))
using namespace std;

template<typename Tv, typename Te>
void Graph<Tv, Te>::BCC(int v, int &clock, MyStack<int> &S) {
    hca(v) = dTime(v) = ++clock;
    status(v) = DISCOVERED;
    S.push(v);
    for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
        switch (status(u)) {
            case DISCOVERED:
                status(v, u) = BACKWARD;
                if (u != parent(v))
                    hca(v) = min(hca(v), dTime(u));   //更新高度，越小越高
                break;
            case UNDISCOVERED:
                parent(u) = v;
                status(v, u) = TREE;
                BCC(u, clock, S);
                if (hca(u) < dTime(v))      //若u都能经过其他边指向v的真祖先
                    hca(v) = min(hca(v), hca(u));   //则v也可以
                else
                    while (u != S.pop());//弹出当前BCC中除v外所有的节点并进行进一步处理
                break;
            default:
                status(v, u) = dTime(v) < dTime(u) ? FORWARD : CROSS;
                break;
        }
    }
    status(v) = VISITED;
}

#undef hca
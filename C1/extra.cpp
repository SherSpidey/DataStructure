//
// Created by 62736 on 2021/5/13.
//

int countOnes(unsigned int n){                   //对数复杂度
    if(n)         //如若不为0，继续计数，递归
        return countOnes(n>>1)+(1&n);//反复检查最低位，为1则计数
    return 0;     //否则则返回
}

int sumI(int A[], int n){                        //线性复杂度，多项式复杂度的特殊情况
    if(n)
        return A[n-1]+ sumI(A,n-1);
    return 0;
}

long long power2BF_I(int n){                     //依旧是线性复杂度，但是？
    if(n)
        return power2BF_I(n-1)<<1;
    return 1;
}

//暴力算法每一次都重新计算fib(n-1)与fib(n-2)，直接将其上升到指数复杂度
long long fib(int n,long long &pre){              //优化后的Fibonacci级数，利用其规律，线性递归
    if(!n){                                       //但需要额外的O(n)的空间
        pre = 1;    //这里到达递归基，pre即代表索引为-1的假象的值
        return 0;   //返回当前层（n=0）的值
    }
    else{
        long long prePre;
        pre = fib(n-1,prePre);
        return prePre+pre;
    }
}

//递归过程中产生的额外空间无法消除。我们其实只是暂时需要这个额外空间，采用迭代可以解决这个问题
long long fibI(int n){
    long long f=1,g=0;
    while (n--){
        g+=f;        //计算前两项的和
        f=g-f;       //前一项的更新，注意此时g已经改变，需要更新的是g之前的值，所以需要减去f
    }
    return g;
}




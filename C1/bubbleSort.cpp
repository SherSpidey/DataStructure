//
// Created by 62736 on 2021/5/13.
//
void swap(int &a,int &b){
    int temp;
    temp=a;
    a=b;
    b=temp;
}

void bubbleSort1A(int A[],int n){   //重用性堪忧
    bool sorted = false;
    while(!sorted){
        sorted = true;  //假定已经全部排序完毕
        for(int i=0; i<n-1; i++){
            if(A[i]>A[i+1]){
                swap(A[i],A[i+1]);
                sorted = false;
            }
        }
        n--;  //每次循环范围缩减
    }
}



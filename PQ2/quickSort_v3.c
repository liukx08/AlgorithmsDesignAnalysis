#include<stdio.h>

void quick_sort(int n,int * array, int * count){
    if(n==1);
    else if(n==2){
        if(array[0]>array[1]){int temp=array[0];array[0]=array[1];array[1]=temp;*count+=1;}
        else *count+=1;
    }
    else {
        int i=1,j=0,k=0,temp;
        if((array[(n-1)/2]-array[0])*(array[(n-1)/2]-array[n-1])<0){
            temp=array[(n-1)/2];
            array[(n-1)/2]=array[0];
            array[0]=temp;
        }
        if((array[n-1]-array[(n-1)/2])*(array[n-1]-array[0])<0){
            temp=array[(n-1)];
            array[n-1]=array[0];
            array[0]=temp;
        }
        int pivot=array[0];
        for(j=1;j<n;j++){
            if(array[j]<pivot){temp=array[i];array[i]=array[j];array[j]=temp;i++;}
        }
        array[0]=array[i-1];
        array[i-1]=pivot;
        *count+=n-1;
//     int low_array[i-1],high_array[n-i];
 //       for(k=0;k<i-1;k++)low_array[k]=array[k];
//        for(k=0;k<n-i;k++)high_array[k]=array[i+k];
        if(i==1)quick_sort(n-1,array+1,count);
        else if(i==n)quick_sort(n-1,array,count);
        else {
            quick_sort(i-1,array,count);
            quick_sort(n-i,array+i,count);
        }
//        for(k=0;k<i-1;k++)array[k]=low_array[k];
//        for(k=0;k<n-i;k++)array[i+k]=high_array[k];
     }
}

int main() {
    int N;
    scanf("%d",&N);
    int array[N],i;
    int count=0;
    for(i=0;i<N;i++)scanf("%d",&array[i]);
    quick_sort(N,array,&count);
//    for(i=0;i<N;i++)printf("%d",array[i]);
    printf("%d\n",count);
}

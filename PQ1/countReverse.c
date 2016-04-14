#include<stdio.h>

void merge_sort(int n,int * array,int * sort_array,long int * count_rev){
    if(n==1)sort_array[0]=array[0];
    else {
        int upper[n/2],lower[n-n/2],i,j,k;
        int sort_upper[n/2],sort_lower[n-n/2];
        for(i=0;i<n/2;i++)upper[i]=array[i];
        for(i=0;i<n-n/2;i++)lower[i]=array[i+n/2];
        merge_sort(n/2,upper,sort_upper,count_rev);
        merge_sort(n-n/2,lower,sort_lower,count_rev);
        i=0;j=0;
        for(k=0;k<n;k++){
            if(i==n/2){sort_array[k]=sort_lower[j];j++;}
            else if(j==n-n/2){sort_array[k]=sort_upper[i];i++;}
            else {
                if(sort_upper[i]<=sort_lower[j]){sort_array[k]=sort_upper[i];i++;}
                else {sort_array[k]=sort_lower[j];j++;*count_rev+=n/2-i;}
            }
        }
    }
}

int main() {
    int N;
    scanf("%d",&N);
    int array[N],sort_array[N],i;
    long int count=0;
    for(i=0;i<N;i++)scanf("%d",&array[i]);
    merge_sort(N,array,sort_array,&count);
    printf("%ld\n",count);
}

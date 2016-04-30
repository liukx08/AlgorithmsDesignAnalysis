#include<iostream>
#include<cstdlib>
#include<stdio.h>
#include<string>
#include<sstream>
#include<ctime>
#define SIZE 875714
#define FILENAME "SCC.txt" 

using namespace std;

class Edge {
  public:
    long head;
    Edge *next;
};

Edge *graph[SIZE+1];
bool visited[SIZE+1];
long finishing[SIZE+1];
long t=0;
long scc[5]={0,0,0,0,0};

void insert(long size){
  int i=0;
  if(size>scc[4]){
    scc[4]=size;
    for(i=4;i>0;i--){
      if(scc[i]>scc[i-1]){
        long temp=scc[i];
        scc[i]=scc[i-1];
        scc[i-1]=temp;
      }
      else break;
    }
  }
}

long DFSR(long node, long size){
  visited[node]=true;
  size++;
  Edge *temp=NULL;
  temp=graph[node];
  while(temp!=NULL){
    if(!visited[temp->head]) size=DFSR(temp->head,size);
    temp=temp->next;
  }
  t++;
  finishing[t]=node;
  return size;
}

void DFSRLoop(){
  long size;
  long i=0;
  for(i=SIZE;i>0;i--){
    size=0;
    if(!visited[i]){
      size=DFSR(i,size);
      insert(size);
    }
  }
}

long DFS(long node, long size){
  visited[node]=true;
  size++;
  Edge *temp=NULL;
  temp=graph[node];
  while(temp!=NULL){
    if(!visited[temp->head]) size=DFS(temp->head,size);
    temp=temp->next;
  }
  t++;
  return size;
}

void DFSLoop(){
  long size;
  long i=0;
  for(i=SIZE;i>0;i--){
    size=0;
    if(!visited[finishing[i]]){
      size=DFS(finishing[i],size);
      insert(size);
    }
  }
}

int main(int argc,char** argv){
  FILE *fp=fopen(FILENAME,"r");
  long i=0;
  long head=0,tail=0;
  for(i=1;i<=SIZE;i++){
    graph[i]=NULL;
    finishing[i]=0;
    visited[i]=false;
  }
  char *a=new char[20];
  while(fgets(a,20,fp)){
    head=atol(a);
    while(a[0]!=' ')a++;
    tail=atol(++a);
    Edge *temp=new Edge;
    temp->head=head;
    temp->next=graph[tail];
    graph[tail]=temp;
    a=new char[20];
  }
  fclose(fp);
  DFSRLoop();
  t=0;
  for(i=0;i<5;i++)scc[i]=0;
  fp=fopen(FILENAME,"r");
  for(i=1;i<=SIZE;i++){
    graph[i]=NULL;
    visited[i]=false;
  }
  a=new char[20];
  while(fgets(a,20,fp)){
    tail=atol(a);
    while(a[0]!=' ')a++;
    head=atol(++a);
    Edge *temp=new Edge;
    temp->head=head;
    temp->next=graph[tail];
    graph[tail]=temp;
    a=new char[20];
  }
  fclose(fp);
  DFSLoop();
  for(i=0;i<5;i++)cout<<scc[i]<<endl;
  return 0;
}

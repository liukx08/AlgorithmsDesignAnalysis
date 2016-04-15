#include<iostream>
#include<cstdlib>
#include<stdio.h>
#include<string>
#include<sstream>
#include<ctime>
#define SIZE 200
#define ITERATIONS 1000

using namespace std;

class Edge {
  public:
    string Ename;
    Edge *Enext;
};

class Vertex {
  public:
    string Vname;
    Vertex *Vnext;
    Edge *first;
} *head; 

void output(){
    Vertex *vp=head;
    Edge *ep=head->first;
    cout<<"---------------------------------------------------------------------"<<endl;
    while(vp!=NULL){
      cout << vp->Vname << '\t';
      while(ep!=NULL){
        cout << ep->Ename << '\t';
        ep=ep->Enext;
      }
      cout << endl;
      vp=vp->Vnext;
      if(vp!=NULL)ep=vp->first;
    }
    cout<<"---------------------------------------------------------------------"<<endl;
}

void readGroup(int *nedge,char *fileName) {
  FILE *data=fopen(fileName,"r");
  int i,m=0;
  head=NULL;
  for(i=1;i<=SIZE;i++){
    char *entry=new char[200];
    fgets(entry,200,data);
    Vertex *newVertex=new Vertex;
    stringstream sout;
    sout << i;
    newVertex->Vname=sout.str();
    newVertex->Vnext=NULL;
    newVertex->first=NULL;
    while(1){
      while(*entry!='\t')entry=entry+1;
      entry=entry+1;
      if(*entry=='\n')break;
      else {
        Edge *newEdge=new Edge;
        m++;
        stringstream sout;
        sout << atoi(entry);
        newEdge->Ename=sout.str();
        newEdge->Enext=newVertex->first;
        newVertex->first=newEdge;
      }
    }
    if(head==NULL)head=newVertex;
    else {
      Vertex *temp=head;
      while(temp->Vnext!=NULL)temp=temp->Vnext;
      temp->Vnext=newVertex;
    }
  }
  *nedge=m;
  fclose(data);
}

void getEdge(int m,Vertex* &node1,Vertex* &node2) {
  int r=rand()%m+1;
  Edge *theEdge=NULL;
  node1=head;
  theEdge=node1->first;
  while(r>1){
    if(theEdge==NULL){
      node1=node1->Vnext;
      theEdge=node1->first;
    }
    else {
      theEdge=theEdge->Enext;
      r--;
    }
  }
  if(theEdge==NULL){
      node1=node1->Vnext;
      theEdge=node1->first;
  }
  node2=head;
  while(node2->Vname!=theEdge->Ename)node2=node2->Vnext;
}

void mergeVertex(int *m, Vertex* &v1, Vertex* &v2) {
  Vertex *merged=new Vertex;
  merged->Vname=v1->Vname+','+v2->Vname;
  merged->Vnext=head;
  merged->first=NULL;
  head=merged;
  Edge *tail=v1->first;
  Edge *sweep=v1->first->Enext;
  Edge *temp=NULL;
/*delete v2 edges in v1*/
  while(sweep!=NULL){
    if(sweep->Ename==v2->Vname){
      temp=sweep;
      sweep=sweep->Enext;
      (*m)--;
      delete temp;
      temp=NULL;
    }
    else {
      tail->Enext=sweep;
      tail=tail->Enext;
      sweep=sweep->Enext;
    }
  }
  tail->Enext=NULL;
  if(v1->first->Ename==v2->Vname){
    temp=v1->first;
    v1->first=v1->first->Enext;
    (*m)--;
    delete temp;
    temp=NULL;
  }
/*delete v1 edges in v2*/
  tail=v2->first;
  sweep=v2->first->Enext;
  while(sweep!=NULL){
    if(sweep->Ename==v1->Vname){
      temp=sweep;
      sweep=sweep->Enext;
      (*m)--;
      delete temp;
      temp=NULL;
    }
    else {
      tail->Enext=sweep;
      tail=tail->Enext;
      sweep=sweep->Enext;
    }
  }
  tail->Enext=NULL;
  if(v2->first->Ename==v1->Vname){
    temp=v2->first;
    v2->first=v2->first->Enext;
    (*m)--;
    delete temp;
    temp=NULL;
  }
  merged->first=v1->first;
  tail=v1->first;
  if(tail==NULL)merged->first=v2->first;
  else{
    while(tail->Enext!=NULL)tail=tail->Enext;
    tail->Enext=v2->first;
  }
  Vertex *NodeSweep=head;
  while(NodeSweep->Vnext->Vname!=v1->Vname)NodeSweep=NodeSweep->Vnext;
  NodeSweep->Vnext=NodeSweep->Vnext->Vnext;
  NodeSweep=head;
  while(NodeSweep->Vnext->Vname!=v2->Vname)NodeSweep=NodeSweep->Vnext;
  NodeSweep->Vnext=NodeSweep->Vnext->Vnext;
  sweep=merged->first;
  while(sweep!=NULL){
    NodeSweep=head;
    while(NodeSweep->Vname!=sweep->Ename)NodeSweep=NodeSweep->Vnext;
    temp=NodeSweep->first;
    while(temp!=NULL){if((temp->Ename==v1->Vname)||(temp->Ename==v2->Vname))temp->Ename=merged->Vname;temp=temp->Enext;}
    sweep=sweep->Enext;
  }
  delete v1;v1=NULL;
  delete v2;v2=NULL;
}


int main(int argc, char **argv) {
  int min_cut=SIZE;
  int l,k;
  for(l=1;l<=ITERATIONS;l++){
    int m=0;
    srand(l);
    readGroup(&m,"./karger.txt");
//    output();
    for(k=0;k<SIZE-2;k++){
      Vertex *N1=NULL;
      Vertex *N2=NULL;
      getEdge(m,N1,N2);
      mergeVertex(&m,N1,N2);
    }
    if(min_cut>(m/2))min_cut=m/2;
  }
  cout<<min_cut<<endl;
  return 0;
}

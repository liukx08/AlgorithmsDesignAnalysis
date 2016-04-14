#include<iostream>
#include<cstdlib>
#include<stdio.h>
#include<string>
#include<sstream>
#include<ctime>
#define SIZE 8
#define ITERATIONS 50

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
  node2=head;
  while(node2->Vname!=theEdge->Ename)node2=node2->Vnext;
}

void mergeVertex(Vertex *v1, Vertex *v2) {
  Vertex *merged=new Vertex;
  merged->Vname=v1->Vname+','+v2->Vname;
  merged->Vnext=head;
  merged->first=NULL;
  head=merged;
  Edge *temp=v1->first;
  while(temp!=NULL){
    if(temp->Ename==v2->Vname)
}

int main(int argc, char **argv) {
  int m=0;
  readGroup(&m,"./data");
  Vertex *vp=head;
  Edge *ep=head->first;
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
  cout << m << endl;
  Vertex *N1=head;
  Vertex *N2=head;
  getEdge(m,N1,N2);
  cout << N1->Vname << "  " << N2->Vname << endl;
  return 0;
}

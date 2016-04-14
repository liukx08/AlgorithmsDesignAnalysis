#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <string>
#include <iostream>
#include <time.h>       /* time */

using namespace std;

class Edge {
  public:
    string Ename;
    Edge *Enext;
};


int main ()
{
  printf ("First number: %d\n", rand()%100);
  srand (time(NULL));
  printf ("Random number: %d\n", rand()%100);
  srand (1);
  printf ("Again the first number: %d\n", rand()%100);
  std::string a="success";
  std::string b="success";
  if(a==b)std::cout << "success" << std::endl;
  Edge *po=new Edge;
  po->Ename="the Edge";
  po->Enext=NULL;
  delete po;
  if(po==NULL) cout << "I am right" << endl;
  return 0;
}

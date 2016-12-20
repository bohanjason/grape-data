#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector> 
#include <list>
#include <ctime>
#include <time.h>
#include <set>

struct idt
{
   int id;
   int edge;
   bool operator < (const idt& x) const
   {
      return id < x.id;
   } 
};

using namespace std;
 int id_label[30000000];//1000w
 set<idt> info[30000000]; //10,000 个点
int max= -1;
int get_rand_edge()
{
    int num;
   // srand((unsigned)time(NULL));
   
    // 1-20  kws
   num = rand() % 20 + 1;
    
   // 0-9  iso sim
   // num = rand()%10;
    
    //1-5  sssp
//   num = rand()%5 + 1;
    
    return num;
}

int main(int   argc,   char*   argv[])  
{ 
  ifstream infile(argv[1]);
  ifstream infilev(argv[2]);
  ofstream outfile(argv[3]);   
  
  //ifstream infile("./dbpedia.e");
  //   ifstream infilev("./dbpedia-l40-law28.v");
  //   ofstream outfile("./dbpedia-graphlab-kws.txt");
    int e_label, v_label,from, to;
    char a;
    int e;
    int cnt = 0;
    while(infile >> from >> to >> e)
     {  
      idt tmp;
       tmp.id = to + 1;
        tmp.edge = e;
        if(from != to)
           info[from + 1].insert(tmp);
    }
  int id, label;
  while(infilev >> id >> label)
  {
      cnt++;
      id_label[id+1] = label+1;
  }
for(int i  =1 ; i <= cnt; i++)
{
        set<idt>::iterator iter;

   outfile << i  << "\t" << id_label[i] << "\t" << "5 1 3 4 10 15 ";// << " " << info[i].size() ;
  for(iter = info[i].begin(); iter != info[i].end(); iter++)
  {
   outfile  <<  (*iter).id << "\t";// << (*iter).edge << "\t"  ;//<< " " << id_label[*iter];
  }
  
  outfile << endl;
}
    return 0;

}


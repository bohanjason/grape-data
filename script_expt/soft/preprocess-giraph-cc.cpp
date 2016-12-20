#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector> 
#include <list>
#include <ctime>
#include <time.h>
#include <set>

using namespace std;
 int id_label[30000000];//1000w
 set<int> info[30000000]; //10,000 个点
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
  //     ifstream infile("./livejournal.e");
  // ifstream infilev("./livejournal.v");
  // ofstream outfile("./livejournal-giraph-cc.txt");
    int e_label, v_label,from, to;
    char a;
    int e;
    int cnt = 0;
    while(infile >> from >> to >> e)
     {
       
		if(from != to)
                   info[from].insert(to);
      
     }
  int id, label;
  while(infilev >> id >> label)
  {
      cnt++;
      id_label[id] = label;
  }
for(int i  =1 ; i <= cnt; i++)
{
        set<int>::iterator iter;

   outfile << i ;// << " " << info[i].size() ;
  for(iter = info[i].begin(); iter != info[i].end(); iter++)
  {
   outfile  <<" " <<  *iter   ;//<< " " << id_label[*iter];
  }
  
  outfile << endl;
}
    return 0;

}


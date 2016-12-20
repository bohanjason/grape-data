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
     ifstream infile("./livejournal.e");
     ifstream infilev("./livejournal.v");
     ofstream outfile("./livejournal-giraph-sim-9.txt");
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
    
    //   outfile <<i <<"!5!"<<id_label[i]<<"!"<< "0,1,2,3,4;1,0,2,3;2,1;3,0,1,4;4,0,1,2,3!";

	//outfile <<i <<"!5!"<<id_label[i]<<"!"<< "1,2,3,4,5;2,1,3,4;3,2;4,1,2,5;5,1,2,3,4!";
	
	//outfile<< i << "!9!" <<id_label[i]<<"!"<<"1;2,4;3;4,7;5;6,2,4;7;8;9,4!"; //pattern: ~/query/sim-1.ptn
	//outfile<< i <<"!9!"<<id_label[i]<<"!"<<"1,2;2,3;3,4;4,5;5,6;6,7;7,8;8,9;9!"; //pattern: ~/query/sim-6.ptn
	outfile<< i <<"!9!"<<id_label[i]<<"!"<<"1,2,3,4,5,6,7,8,9;2,3,4,5,6,7,8,9;3,4,5,6,7,8,9;4,5,6,7,8,9;5,6,7,8,9;6,7,8,9;7,8,9;8,9;9!";//pattern:~/query/sim-7.ptn
//	outfile<<i<<"!9!"<<id_label[i]<<"!"<<"1,2,3;2,4,5;3,6,7;4,8,9;5,8,9;6,8,9;7,8,9;8;9!"; //pattern:~/query/sim-8.ptn
//outfile<<i<<"!9!"<<id_label[i]<<"!"<<"1,2,3;2,3,4;3,4,5;4,5,6;5,6,7;6,7,8;7,8,9;8,9;9!"; //pattern:~/query/sim-9.ptn
	//outfile << i  << "!3!" << id_label[i] << "!" << "0,1,2;1,2;2!" ; //info[i].size() ;
  for(iter = info[i].begin(); iter != info[i].end(); iter++)
  {
   outfile   <<  *iter  << ","   ;//<< " " << id_label[*iter];
  }
  
  outfile << endl;
}
    return 0;

}


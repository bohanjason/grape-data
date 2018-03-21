#include <iostream>
#include <fstream> 
#include <vector> 
#include <set>
#include <map>
#include <string> 
#include <cassert> 
using namespace std;

struct edge
{
    int w_id; 
    int cnt; 
    edge(int x,int y):w_id(x),cnt(y){}; 
    bool operator < (const edge & y) const 
    {
    	return w_id < y.w_id;
    }
};


int main()
{
    string FILE_IN = "./doc_word_count.tsv";
    string FILE_DIC = "../dictionary.txt";
    string FILE_OUT_V = "./daily_kos.v";
    string FILE_OUT_E = "./daily_kos.e";
    string FILE_OUT_R = "./daily_kos.r";
    
    ifstream infile_(FILE_IN.c_str());
    ifstream infile_dic(FILE_DIC.c_str());
    ofstream outfile_v(FILE_OUT_V.c_str());
    ofstream outfile_e(FILE_OUT_E.c_str());
    ofstream outfile_r(FILE_OUT_R.c_str());
    
    int w_id, doc_id, cnt;
    map<int, set<edge> > doc_w; 
    set<int> w_set;  
    int W_NUM = 0; 
    int DOC_NUM = 0;  
    int TOK_NUM = 0; 
    while(infile_ >> doc_id  >> w_id >> cnt ) 
    { 
        TOK_NUM += cnt; 
        w_set.insert(w_id);
        if(doc_w.find(doc_id) == doc_w.end()) // not found
        {
            set<edge> tmp;
            doc_w[doc_id] = tmp; 
        }

        edge x(w_id, cnt);
        doc_w[doc_id].insert(x);
    }
    DOC_NUM = doc_w.size();
    W_NUM = w_set.size();
  
    string word; 
    int id = 0; 
    map<int, string> wid_word;
    //parse dictionary
    while(infile_dic >> word)
    {
        wid_word[id] = word;
        id++;
    }
//    cout << id << " " << W_NUM << endl;     
    assert(id == W_NUM);
 
    // doc id: 0, 1, 2 ..., DOC_NUM - 1    -- type: 0
    // word id: DOC_NUM, DOC_NUM + 1, DOC_NUM + 2..., W_NUM + DOC_NUM - 1  -- type: 1

    // output file.e  
    for (auto &pair : doc_w) 
    {
       doc_id = pair.first; 
       auto &words = pair.second; 
       for(auto &w_cnt: words)
       { 
          outfile_e << doc_id << " " << w_cnt.w_id + DOC_NUM << " " << w_cnt.cnt << endl; 
       } 
    }

    // output file.v
    for(int i = 0; i < DOC_NUM; i++) // output doc 
    {
        outfile_v << i << " " << 0 << endl;
    }        
    
    for(int i = 0; i < W_NUM; i++) // output word 
    {
	outfile_v << i + DOC_NUM << " " << 1 << endl; // wid_word[i] << endl ;
    }        
 
    // output file.r  Round Robin
    for(int i = 0; i < DOC_NUM + W_NUM; i++)
    {
        outfile_r << i << " " << i%4 << endl;    
    }
 
    cout << "doc num: " << DOC_NUM << endl; 
    cout << "word num: " << W_NUM << endl; 
    cout << "tok num: " << TOK_NUM << endl; 

}

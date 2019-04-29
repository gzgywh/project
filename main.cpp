#include<bits/stdc++.h>
#include<fstream>
#include "cut.h"
using namespace std;
typedef long long LL;
const int filenum = 125;//子文件的数量
const int topK = 100;//前100个URL
const LL file_size = 500*1024*1024;//子文件的大小
struct P{
    string url;
    int cnt;
    friend bool operator<(P a,P b){
        return a.cnt>b.cnt;  //以cnt为关键字的小顶堆
    }
};
bool cmp(P x,P y){
    return x.cnt>y.cnt;
}

//字符串转化成整数
int Rev(string str){
    int sum=0;
    for(int i=0;i<str.length();i++){
        sum*=10;
        sum+=str[i]-'0';
    }
    return sum;
}

//使用EFLhash算法对字符串进行hash
unsigned int ELFhash(const char *url){
    unsigned int hash=0;
    unsigned int ans=0;
    char* str = const_cast<char *>(url);
    for(int i=0;str[i]!='\0';i++){
        hash=(hash<<4)+str[i];
        if((ans=hash & 0xf0000000)!=0){
                hash^=(ans>>24);
                hash&=~ans;
        }
    }
    return (hash & 0x7fffffff);
}

//将字符串hash到对应的文件
void Hash(string file_name,int num){
    string url;
    ifstream fin;
    fin.open(file_name);
    if(!fin) return ;
    while(fin>>url){
        unsigned int file_hash = ELFhash(url.c_str())%filenum;
        string resolved = "Hash_" + to_string((LL)file_hash) + ".txt";
        ofstream fout(resolved,ios::app);
        fout << url << endl;
        fout.close();
    }
    fin.close();
}

int main()
{
    string file = "testdata.txt";
    Hash(file,filenum);
    solve(filenum,file_size,topK);
    /*
        建立一个以cnt为关键字的优先队列，然后在优先队列中只维护100个元素，
        如果元素再有新的元素加入，则和优先队列中cnt最小的元素进行比较，如果
        比堆顶元素的cnt大，则把堆顶出堆，把新元素插入堆中，否则，不做任何改变
    */
    priority_queue<P>que;
    ifstream fin;
    string file_name="";
    for(int i=0;i<filenum;++i){
        file_name = "Hash_" + to_string((LL)i) + ".txt";
        file_name = "sorted_" + file_name;
        fin.open(file_name);
        assert(fin.is_open());
       // cout<<i<<endl;
        string url;
        while(fin>>url){
            string c="";
            fin>>c;
            P tmp;tmp.cnt = Rev(c);tmp.url=url;
           // cout<<tmp.url<<" "<<tmp.cnt<<endl;
            if(que.size()<topK) que.push(tmp);
            else{
                P x=que.top();
                if(x.cnt>=tmp.cnt) continue;
                else{
                    que.pop();
                    que.push(tmp);
                }
            }
        }
        fin.close();
    }
    vector<P>v;
    while(!que.empty()){
        P t=que.top(); que.pop();
        v.push_back(t);
    }

    //对出现次数top100的元素进行排序
    sort(v.begin(),v.end(),cmp);
    for(auto t:v) cout<<t.url<<" "<<t.cnt<<endl;
    return 0;
}
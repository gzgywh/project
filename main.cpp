#include<bits/stdc++.h>
#include<fstream>
#include "cut.h"
using namespace std;
typedef long long LL;
const int filenum = 125;//max sub file number
const int topK = 20;//select topK URLs
const LL file_size = 800*1024*1024;//sub file max size
struct P{
    string url;
    int cnt;
    friend bool operator<(P a,P b){
        return a.cnt>b.cnt;  //小顶堆
    }
};
bool cmp(P x,P y){
    return x.cnt>y.cnt;
}
int Rev(string str){
    int sum=0;
    for(int i=0;i<str.length();i++){
        sum*=10;
        sum+=str[i]-'0';
    }
    return sum;
}
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

void Hash(string file_name,int num){
    string url;
    ifstream fin;
    fin.open(file_name);
    if(!fin)
        return ;
    while(getline(fin,url)){
        unsigned int file_hash = ELFhash(url.c_str())%filenum;
        string resolved = "resolved_" + to_string((long long)file_hash) + ".txt";
        ofstream fout(resolved,ios::app);
        fout << url << endl;
        fout.close();
    }
    fin.close();
}

int main()
{
    string file_name = "testdata.txt";
    Hash(file_name,filenum);
    solve(filenum,file_size,topK);

    priority_queue<P>que;
    ifstream fin;
    string file_name="";
    for(int i=0;i<filenum;++i){
        file_name = "resolved_" + to_string((long long)i) + ".txt";
        file_name = "sorted_" + file_name;
        fin.open(file_name);
        assert(fin.is_open());
       // cout<<i<<endl;
        string url;
        while(fin>>url){
            string c="";
            fin>>c;
            P tmp;
            tmp.cnt = Rev(c);
            tmp.url=url;
           // cout<<tmp.url<<" "<<tmp.cnt<<endl;
            if(que.size()<20){
                que.push(tmp);
            }else{
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
    sort(v.begin(),v.end(),cmp);
    for(auto t:v){
        cout<<t.url<<" "<<t.cnt<<endl;
    }
    return 0;
}
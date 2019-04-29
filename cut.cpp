#include<bits/stdc++.h>
#include<assert.h>
#include<sys/stat.h>
#include "cut.h"
using namespace std;
typedef long long LL;

//获取文件大小
LL Filesize(string file_name){
    struct stat statbuff;
    stat(file_name.c_str(),&statbuff);
    LL size = statbuff.st_size;
    return size;
}

//将大小超过size的文件切分成子文件
void Split(string filename, int &subfile, int size){
    if(Filesize(filename)>size){
        ifstream fin;
        fin.open(filename);
        if(!fin) return ;
        string url;
        LL size = 0;
        string pre=filename.substr(0, filename.length()-4) + "_";
        ofstream fout;
        int cnt = 0;
        string str = pre + to_string((LL)cnt) + ".txt";
        fout.open(str,ios::ate);
        assert(fout.is_open());
        while(fin>>url){
            int length = url.length();
            if(size + length > size){
                fout.close();
                cnt++;
                str = pre + to_string((long long)(cnt)) + ".txt";
                fout.open(str,ios::ate);
                assert(fout.is_open());
                size = 0;
            }
            fout << url << endl;
            size += length;
        }
        fout.close();
        fin.close();
        subfile = cnt+1;
    }
}

//统计小文件中每个URL出现的次数，同时叠加不同小文件中相同的URL
void merge(string pre,int n,int topK){
    unordered_map<string,int> mp;
    for(int i = 0;i < n;i++){
        string filename = pre + to_string((LL)i) + ".txt";
        ifstream fin;
        fin.open(filename);
        assert(fin.is_open());
        string url;
        while(fin>>url){
            string c;
            fin>>c;
            int count = atoi(c.c_str());
            //cout<<count<<endl;
            if(mp.find(url) != mp.end()) mp[url]+=count;
            else mp[url]=count;
        }
        fin.close();
    }
    string output = pre.substr(0, pre.length()-1) + ".txt";
    ofstream fout(output,ios::ate);
    multimap<int,string> f;
    for(auto v:mp) f.insert(pair<int,string>(v.second,v.first));
    multimap<int,string>::reverse_iterator  rit ;
    int size = 0;
    for(rit = f.rbegin();rit != f.rend() && size < topK;rit++){
            size++;
            fout << rit->second << endl;
            fout << rit->first << endl;
    }
    fout.close();
}

//对小文件中的URL按照出现次数进行排序
void sortFiles(string source,int topK){
    ifstream fin;
    fin.open(source);
    if(!fin) return ;
    string url;
    unordered_map<string,int> mp;
    while(fin>>url){
        if(mp.find(url) != mp.end()) mp[url]+=1;
        else mp[url]=1;
    }
    fin.close();
    string sorted = "sorted_" + source;
    ofstream fout(sorted,ios::app);
    multimap<int,string> f;
    for(auto v:mp) f.insert(pair<int,string>(v.second,v.first));
    multimap<int,string>::reverse_iterator  rit ;
    int size = 0;
    for(rit = f.rbegin();rit != f.rend() && size < topK;rit++){
            size++;
            fout << rit->second << endl;
            fout << rit->first << endl;
    }
    fout.close();
}

void solve(int filenum,int size,int topK){
    for(int i = 0;i < filenum;i++){
        string filename = "Hash" + to_string((LL)i) + ".txt";
        int subfile = 0;
        Split(filename,subfile,size);
        if(subfile == 0) sortFiles(filename,topK);
        else{
            string prename = filename.substr(0, filename.length()-4);
            prename += "_";
            for(int j = 0;j < subfile;j++){
                string sub_file_name = prename + to_string((LL)j) + ".txt";
                sortFiles(sub_file_name,topK);
            }
            prename = "sorted_" + prename;
            merge(prename,subfile,topK);
        }
    }
}
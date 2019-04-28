#include<bits/stdc++.h>
#include<assert.h>
#include<sys/stat.h>
#include "cut.h"
using namespace std;
typedef long long LL;

LL Filesize(string file_name){
    struct stat statbuff;
    stat(file_name.c_str(),&statbuff);
    LL size = statbuff.st_size;
    return size;
}

void Split(string filename, int &subfile, int file_size){
    if(Filesize(filename) > file_size){
        ifstream fin;
        fin.open(filename);
        if(!fin) return ;
        LL size = 0;
        int len=filename.length()-4;
        string pre=filename.substr(0, len-4) + "_";
        ofstream fout;
        int cnt = 0;
        string subname = pre + to_string((LL)cnt) + ".txt";
        fout.open(subname,ios::ate);
        assert(fout.is_open());
        string url;
        while(getline(fin,url)){
            int len= url.length();
            //cout<<url<<endl;
            if(size + len > file_size){
                fout.close();
                cnt++;
                subname = pre + to_string((LL)(cnt)) + ".txt";
                fout.open(subname,ios::ate);
                assert(fout.is_open());
                size = 0;
            }
            fout << url << endl;
            size += len;
        }
        fout.close();
        fin.close();
        subfile = cnt+1;
    }
}


void merge(string pre,int n,int topK){
    unordered_map<string,int> mp;
    for(int i = 0;i < n;i++){
        string file_name = pre + to_string((LL)i) + ".txt";
        ifstream fin;
        fin.open(file_name);
        assert(fin.is_open());
        string url;
        while(getline(fin,url)){
            string c;
            getline(fin,c);
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

void sortFiles(string source_file_name,int topK){
    ifstream fin;
    fin.open(source_file_name);
    if(!fin) return;
    string url;
    unordered_map<string,int> mp;
    while(getline(fin,url)){
        if(mp.find(url) != mp.end()) mp[url]+=1;
        else mp[url]=1;
    }
    fin.close();

    string sorted = "sorted_" + source_file_name;
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

void solve(int file_num,int file_size,int topK){
    for(int i = 0;i < file_num;i++){
        string file_name = "Hash_" + to_string((LL)i) + ".txt";
        int subfile = 0;
        Split(file_name,subfile,file_size);
        if(subfile == 0)
            sortFiles(file_name,topK);
        else{
            string prefile = file_name.substr(0, file_name.length()-4);
            prefile +=  "_";
            for(int j = 0;j < subfile;j++){
                string sub_file_name = prefile + to_string((LL)j) + ".txt";
                sortFiles(sub_file_name,topK);
            }
            prefile = "sorted_" + prefile;
            merge(prefile,subfile,topK);
        }
    }
}
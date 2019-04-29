#ifndef CUT
#define CUT

#include<bits/stdc++.h>
#include<fstream>
#include<limits.h>

using namespace std;
typedef long long LL;

LL Filesize(string file_name); 

void Split(string filename, int &subfile, int size);

void merge(string pre,int n,int topK);

void sortFiles(string source,int topK=INT_MAX);

void solve(int filenum,int size,int topK);

#endif 

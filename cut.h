#ifndef CUT
#define CUT

#include<bits/stdc++.h>
#include<fstream>
#include<limits.h>

using namespace std;
typedef long long LL;

LL filesize(string filename);

void splitfile(string filename, int &num, int size);

void merge(string pre,int n,int topK);

void sortFiles(string source_file_name,int topK=INT_MAX);

void solve(int file_num,int file_size,int topK);

#endif 

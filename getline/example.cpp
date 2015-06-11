#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdio>
using namespace std;
int main()
{
	FILE* ifs = fopen("a.txt","r");
	int a,b;
	char strs[40][40];
	time_t start = time(NULL);
	while(fscanf(ifs,"%s%d%s%s%s%s%s%d",strs[0],&a,strs[1],strs[2],strs[3],strs[4],strs[5],&b) > 0){
	}
	time_t stop = time(NULL);
	cout<<stop-start<<"s\n";
	fclose(ifs);
	return 0;
}

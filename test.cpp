#include"textquery.h"
#include"Query_base.h"
#include<iostream>
using namespace std;
ostream &print(ostream &os,const Queryresult &q)
{
	os<<q.qs<<"查找到"<<q.lines->size()<<endl;
	for(auto num:*q.lines)
	{
		os<<num+1<<" "<<*(q.data->begin()+num)<<endl;
	}
	return os;
}

int main()
{
	ifstream file("test.text");
	Textquery text(file);
	Query Q=~Query("aa");
	Queryresult result=Q.eval(text);
	print(cout,result);
}

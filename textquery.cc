#include<iostream>
#include<sstream>
#include "textquery.h"
using namespace std;
Textquery::Textquery(ifstream &is):data(new vector<string>)
{
	string text;
	string word;
	while(getline(is,text))
	{
		data->push_back(text);
		int n=data->size()-1;
		istringstream line(text);
		while(line>>word)
		{
			auto &lines=wm[word];
			if(!lines)
			{
				lines.reset(new set<int>);
			}
			lines->insert(n);
		}
	}

}
Queryresult Textquery::query(const string &s) const
{
	static shared_ptr<set<int>> nodata(new set<int>);
	auto loc=wm.find(s);
	if(loc==wm.end())
		return Queryresult(s,nodata,data);
	else 
		return Queryresult(s,loc->second,data);
}


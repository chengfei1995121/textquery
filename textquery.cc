#include<iostream>
#include<sstream>
#include "textquery.h"

Textquery::Textquery(ifstream &is):data(new vector<string>)
{
	string text;
	string word;
	while(getline(is,text))
	{
		data->push_back(text);
		int n=data->size();
		istringstream line(text);
		while(line>>word)
		{
			auto &lines=wm[word];
			if(!lines)
			{
				lines.reset(new set<line_no>);
			}
			lines->insert(n);
		}
	}

}
Queryresult Textquery::query(const string &s)
{
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	auto loc=wm.find(s);
	if(loc==wm.end())
		return Queryresult(s,nodata,data);
	else 
		return Queryresult(s,loc->second,data);
}

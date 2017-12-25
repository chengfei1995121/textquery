#ifndef __textquery_h__
#define __textquery_h__ 
#include<string>
#include<vector>
#include<set>
#include<map>
#include<fstream>
#include<memory>
using namespace std;
class Queryresult;
class Textquery{
	public:
		using line_no=vector<string>::size_type;
		Textquery(ifstream &is);
		Queryresult query(const string &);
	private:
		shared_ptr<vector<string>> data;
		map<string,shared_ptr<set<line_no>>> wm;
};
class Queryresult{
	public:
	using line_no=vector<string>::size_type;
	Queryresult(const string &s,shared_ptr<set<line_no>> l,shared_ptr<vector<string>> d):qs(s),lines(l),data(d){}
	private:
		string qs;
		shared_ptr<set<line_no>> lines;
		shared_ptr<vector<string>> data;
};
#endif

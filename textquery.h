#ifndef __textquery_h__
#define __textquery_h__ 
#include<string>
#include<vector>
#include<set>
#include<map>
#include<fstream>
#include<memory>
class Queryresult;
class Textquery{
	public:
		Textquery(std::ifstream &is);
		Queryresult query(const std::string &) const;
	private:
		std::shared_ptr<std::vector<std::string>> data;
		std::map<std::string,std::shared_ptr<std::set<int>>> wm;
};
class Queryresult{
	public:
	friend std::ostream &print(std::ostream &os,const Queryresult &q);
	using line_no=std::vector<std::string>::size_type;
	Queryresult(const std::string &s,std::shared_ptr<std::set<int>> l,std::shared_ptr<std::vector<std::string>> d):qs(s),lines(l),data(d){}
	std::set<int>::iterator begin(){
		return lines->begin();
	}
	std::set<int>::iterator end()
	{
		return lines->end();
	}
	std::shared_ptr<std::vector<std::string>> get_file()
	{
		return data;
	}
	private:
	std::string qs;
	std::shared_ptr<std::set<int>> lines;
	std::shared_ptr<std::vector<std::string>> data;
};

#endif

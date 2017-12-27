#ifndef __QUERY_BASE_H__
#define __QUERY_BASE_H__
#include"textquery.h"
#include<algorithm>
using namespace std;
class Query_base{
	friend class Query;
	protected:
	virtual ~Query_base()=default;
	private:
		virtual Queryresult eval(const Textquery&)const=0;
		virtual string rep()const=0;
};

class WordQuery:public Query_base{

	friend class Query;
	WordQuery(const string &s):query_word(s){};
	Queryresult eval(const Textquery &t) const 
	{
		return t.query(query_word);
	}
	string rep() const
	{
		return query_word;
	}
	string query_word;
};
class Query{
	public:
	friend Query operator~(const Query&);
	friend Query operator|(const Query&,const Query&);
	friend Query operator&(const Query&,const Query&);
		Query(const string &s):q(new WordQuery(s)){};
		Queryresult eval(const Textquery &t) const 
		{
			return q->eval(t);
		}
		string rep() const {return q->rep();}
		void storage(const Queryresult &qr);
	private:
		Query(shared_ptr<Query_base> query):q(query){};
		shared_ptr<Query_base> q;
		map<int,shared_ptr<map<string,int>>> history;
};
inline void Query::storage(const Queryresult &qr)
{
	shared_ptr<map<string,int>> a(new map<string,int>({{qr.qs,qr.lines->size()}}));
	
}
class NotQuery:public Query_base{
	friend Query operator ~(const Query &);
	NotQuery(const Query &q):query(q){};
	Queryresult eval(const Textquery &t) const;
	string rep() const{
	return "~("+query.rep()+")";
	}
	Query query;
};
inline Query operator~(const Query &operand)
{
	return shared_ptr<Query_base> (new NotQuery(operand));
}
class BinaryQuery:public Query_base{
	protected:
	BinaryQuery(const Query &l,const Query &r,const string &s):lhs(l),rhs(r),ops(s){}
	string rep() const {
	return "("+lhs.rep()+" "+ops+" "+rhs.rep()+")";
	}
	Query lhs,rhs;
	string ops;
};
class AndQuery:public BinaryQuery{
	friend Query operator&(const Query &l,const Query &r);
	AndQuery(const Query &l,const Query &r):BinaryQuery(l,r,"&"){}
	Queryresult eval(const Textquery &t) const;
};
inline Query operator& (const Query &l,const Query &r)
{
	return shared_ptr<Query_base> (new AndQuery(l,r));
}
class OrQuery:public BinaryQuery{
	
	friend Query operator|(const Query &l,const Query &r);
	OrQuery(const Query &l,const Query &r):BinaryQuery(l,r,"|"){}
	Queryresult eval(const Textquery &t) const;
};
inline Query operator|(const Query &l,const Query &r)
{
	return shared_ptr<Query_base> (new OrQuery(l,r));
}
Queryresult OrQuery::eval(const Textquery &t) const 
{
	auto left=lhs.eval(t),right=rhs.eval(t);
	auto re_lines=make_shared<set<int>>(left.begin(),left.end());
	re_lines->insert(right.begin(),right.end());
	return Queryresult(rep(),re_lines,left.get_file());
}
Queryresult AndQuery::eval(const Textquery &t) const 
{
	auto left=lhs.eval(t),right=rhs.eval(t);
	auto re_lines=make_shared<set<int>>();
	set_intersection(left.begin(),left.end(),right.begin(),right.end(),inserter(*re_lines,re_lines->begin()));
	return Queryresult(rep(),re_lines,left.get_file());
}
Queryresult NotQuery::eval(const Textquery &t) const 
{
	auto result=query.eval(t);
	auto re_lines=make_shared<set<int>>();
	auto beg=result.begin(),en=result.end();
	auto si=result.get_file()->size();
	for(size_t n=0;n!=si;n++)
	{
		if(beg==en ||*beg!=n)
			re_lines->insert(n);
		else 
			beg++;
	}
	return Queryresult(rep(),re_lines,result.get_file());
}
#endif

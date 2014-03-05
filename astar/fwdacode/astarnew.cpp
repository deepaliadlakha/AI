#include <climits>
#include <vector>
#include <cstdlib>
#include <bitset>

#define prime_const 1000000000+7 
typedef unsigned long long int ull;
using namespace std;
int inf = 1000000;

template<typename T>
int binrep(const T& a)
{
	const char* beg = reinterpret_cast<const char*>(&a);
	const char* end = beg + sizeof(a);
	ull temp=0, prime=1;
	while(beg != end){
		temp=(temp+prime*(ull)(bitset<CHAR_BIT>(*beg++)).to_ulong())%prime_const;
		prime=(prime*256)%prime_const;
	}
	return temp;
}

class node{

public:
	int m;
	int c;
	int side;
	node(int m1=0, int c1=0, int side1=-1){
		m=m1;
		c=c1;
		side=side1;
	}


	int hashint() const{

		ull hint=binrep<node>(*this);
		return hint;

	}

	bool isvalid(int m,int c) const
	{
		if(m==c || m==0 || m==3)
			return true;
		else 
			return false;
	}

	vector <pair<node, int> > edges() const{
		vector <pair <node,int> > v;
		if(side==0){
			if(m-1>=0 && c-1>=0 && isvalid(m-1,c-1)){
				v.push_back(pair<node,int> (node(m-1,c-1,1),1));
			}
			if(m-2>=0 && isvalid(m-2,c)){
				v.push_back(pair<node,int> (node(m-2,c,1),1));
			}
			if(c-2>=0 && isvalid(m,c-2)){
				v.push_back(pair<node,int> (node(m,c-2,1),1));
			}
			if(m-1>=0 && isvalid(m-1,c)){
				v.push_back(pair<node,int> (node(m-1,c,1),1));
			}
			if(c-1>=0 && isvalid(m,c-1)){
				v.push_back(pair<node,int> (node(m,c-1,1),1));
			}

		}
		else {
			int mn=3-m;
			int cn=3-c;
			if(mn-1>=0 && cn-1>=0 && isvalid(m+1,c+1)){
				v.push_back(pair<node,int> (node(m+1,c+1,0),1));
			}
			if(mn-2>=0 && isvalid(m+2,c)){
				v.push_back(pair<node,int> (node(m+2,c,0),1));
			}
			if(cn-2>=0 && isvalid(m,c+2)){
				v.push_back(pair<node,int> (node(m,c+2,0),1));
			}
			if(mn-1>=0 && isvalid(m+1,c)){
				v.push_back(pair<node,int> (node(m+1,c,0),1));
			}
			if(cn-1>=0 && isvalid(m,c+1)){
				v.push_back(pair<node,int> (node(m,c+1,0),1));
			}

		}

		return v;

	}

	int h(node &dest) const{
		if (m%2==0)
			return 2*m+2*c-3+3*side;
		else
			return m+c+side;
	}

	int h1(node &dest) const{
		if(m+c==0)
			return 0;
		return m+c+side;
	}

	bool operator< (const node& nd) const {
		return m==nd.m ? c==nd.c ? side<nd.side : c<nd.c : m<nd.m;
	}
	
	bool operator== (const node& nd) const {
		return m==nd.m && c==nd.c && side==nd.side;
	}
};

ostream &operator<<(ostream &out, node& n){
	out<<n.m<<" "<<n.c<<" "<<n.side<<endl;
		
}

istream &operator>>(istream &in, node& n){
	in>>n.m>>n.c>>n.side;
		
}

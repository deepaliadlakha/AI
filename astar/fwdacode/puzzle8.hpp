typedef unsigned int uint;	
int inf = 10000000;

struct node {
	uint data;
	node(uint x=0): data(x) {}
	int h(node &dest) const {
		uint ret = 0;
		for (uint i=0; i<32; i+=4)
			if (((data >> i)&15) != ((dest.data >> i)&15))
				ret++;
		return ret;
	}
	
	int h1(node &dest) const {
		uint ret = 0;
		for (uint i=0; i<32; i+=2)
			ret += abs((int)((data >> i)&3) - (int)((dest.data >> i)&3));
		return ret;
	}
	
	int h2(node &dest) const {
		return 0;
	}
	
	vector<pair<node, int>> edges() const {
		vector<pair<node, int>> ret;
		uint loc = 90;
		for (int i=0; i<32; i+=4)
			loc -= (data>>i)&15;
		
		uint posses[4]{loc-1, loc+1, loc-4, loc+4};
		for (int i=0; i<32; i+=4)
			for (int j=0; j<4; j++)
				if (((data>>i)&15) == posses[j])
					ret.push_back(pair<node,int> (node(data-(posses[j]<<i)+(loc<<i)), 1));
		
		return ret;
	}
	
	inline size_t hashint() const {
		return data;
	}
	
	bool operator< (const node& nd) const {
		return data<nd.data;
	}
	
	bool operator== (const node& nd) const {
		return data==nd.data;
	}
};

ostream& operator<< (ostream &out, node &nd) {
	uint pos[4][4]{0};
	for (int i=1; i<=8; i++)
		pos[(nd.data>>34-4*i)&3][(nd.data>>32-4*i)&3] = i;
	
	for (int i=1; i<=3; i++) {
		for (int j=1; j<=3; j++)
			out << pos[i][j] << " ";
		out << endl;
	}
}

istream& operator>> (istream &in, node &nd) {
	nd.data = 0;
	int p;
	for (int i=0; i<9; i++) {
		in >> p;
		if (p)
			nd.data += (4*(i/3+1) + (i%3)+1)<<(4*(8-p));
	}
}

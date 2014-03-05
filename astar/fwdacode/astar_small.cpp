#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;
/* Required functions in class node:
 *   size_t hashint()
 *   vector<pair<node, int>> edges()
 *   int h()
 */
#include "puzzle8.hpp"
node start, dest;

namespace std {
	template<>
	struct hash<node> {
		size_t operator() (const node& nd) const {
			return nd.hashint();
		}
	};
}

struct nodeinfo {
	node parent;
	bool closed;
	int g;
	nodeinfo(node p=node(), bool c=false, int gg=inf) {parent=p; closed=c; g=gg;}
};

struct distinfo {
	node nd;
	int g;
	distinfo (node n=node(), int gg=inf): nd(n), g(gg) {}
	inline int f() const {return g+nd.h(dest);}
	bool operator< (const distinfo& d) const {
		return f()==d.f() ? nd<d.nd : f()<d.f();
	}
};

typedef pair<node,nodeinfo> nodestruct;

int main() {
	int expanded = 0, inclosed=0;
	cout << "Enter start node:\n"; cin >> start;
	cout << "Enter destination node:\n"; cin >> dest;
	
	set<distinfo> distopen{distinfo(start,0)};
	unordered_map<node, nodeinfo> listed{nodestruct(start, nodeinfo(node(),false,0))};
	
	while (!distopen.empty() && !(distopen.begin()->nd == dest)) {
		inclosed++;
		node curr = distopen.begin()->nd;
		distopen.erase(distopen.begin());
		listed[curr].closed = true;
		for (auto& edge: curr.edges()) {
			if (!listed.count(edge.first)) {
				distopen.insert(distinfo(edge.first,inf));
				expanded++;
			}
			
			nodeinfo &nif = listed[edge.first];
			if (!nif.closed && nif.g > listed[curr].g + edge.second) {
				distopen.erase(distinfo(edge.first,nif.g));
				nif.g = listed[curr].g + edge.second;
				distopen.insert(distinfo(edge.first,nif.g));
				nif.parent = curr;
			}
		}
	}
	
	cout << "Expanded nodes: " << expanded << " " << inclosed << endl;
	if (distopen.empty())
		cout << "No path found.\n";
	else {
		cout << "Cost of path is " << listed[dest].g << endl;
		cout << "\nPath is:\n";
		for (node curr = dest; !(curr == node()); curr=listed[curr].parent)
			cout << "Previous node:\n" << curr << endl;
	}
	
	return 0;
}

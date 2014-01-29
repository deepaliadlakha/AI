#include <iostream>
#include <vector>
#include <bitset>
#include <cstdio>
using namespace std;
#define BREAKPT 1000000

struct perceptron {
	vector<int> weight;
	perceptron(int num) : weight(num) {}
	
	int dotp(vector<int> &input) {
		int sum=0;
		for (int i=0; i<weight.size(); i++)
			sum += input[i]*weight[i];
		return sum;
	}
	
	void train (vector< vector<int> > &positives) {
		bool changed = true;
		int steps = 0;
		vector<int> referWeight;
		while (changed) {
			changed = false;
			if (steps==BREAKPT)
				referWeight = weight;
			else if (steps==2*BREAKPT) {
				cout << "Too many iterations. Aborting.\n";
				return;
			}
			else if (steps>BREAKPT) {
				if (weight==referWeight) {
					cout << "Found cycle of size " << (steps-BREAKPT) << ".\n";
					for (int i_=0; i_<steps-BREAKPT; i_++) {
						cout << "The weights are ";
						for (int i=0; i<weight.size() - 1; i++)
							cout << weight[i] << ", ";
		
						cout << "and the threshhold is " << weight[weight.size()-1] << endl;
						
						for (vector<int> inp: positives) {
							if (dotp(inp) <= 0) {
								for (int i=0; i<weight.size(); i++)
									cout << inp[i] << " ";
								cout << "\n\n";
								for (int i=0; i<weight.size(); i++)
									weight[i] += inp[i];
								changed = true;
								break;
							}
						}
					}
						
					return;
				}
			}
			
			for (vector<int> inp: positives) {
				if (dotp(inp) <= 0) {
					for (int i=0; i<weight.size(); i++)
						weight[i] += inp[i];
					changed = true;
					break;
				}
			}
			
			steps++;
		}
		
		cout << "The weights are ";
		for (int i=0; i<weight.size() - 1; i++)
			cout << weight[i] << ", ";
		
		cout << "and the threshhold is " << weight[weight.size()-1] << endl;
	}
};

struct cond {
	char op;
	cond *left, *right;
	int eval(vector<int> &inp) {
		switch (op) {
			case '+':
				return left->eval(inp) + right->eval(inp);
				break;
			case '&':
				return left->eval(inp) & right->eval(inp);
				break;
			case '|':
				return left->eval(inp) | right->eval(inp);
				break;
			case '^':
				return left->eval(inp) ^ right->eval(inp);
				break;
			case '!':
				return 1-left->eval(inp);
				break;
			case '>':
				return left->eval(inp) > right->eval(inp) ? 1 : 0;
				break;
			default:
				return inp[op-'a'];
		};
	}
};

istream & operator>> (istream &in, cond& con) {
	in >> con.op;
	if (con.op<'a' || con.op>'z') {
		con.left = new cond;
		in >> *con.left;
		if (con.op != '!') {
			con.right = new cond;
			in >> *con.right;
		}
	}
	return in;
}

int main () {
	cond root;
	int args;
	cout << "Input the number of args: ";
	cin >> args;
	cout << "Input the function: ";
	cin >> root;
	
	vector<vector<int> > posit;
	for (int i=0; i<(1<<args); i++) {
		vector<int> val(args+1);
		for (int j=0; j<args; j++)
			val[j] = (i>>j)&1;
		
		val[args] = -1;
		cout << (bitset<8>)i << " " << root.eval(val) << endl;
		if (!root.eval(val))
			for (int& k: val)
				k = -k;
		
		posit.push_back(val);
	}
	
	perceptron perp(args+1);
	perp.train(posit);
	
	return 0;
}

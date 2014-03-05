#include <iostream>
#include <vector>
#include <cstdlib>
#include <map>
#include <cmath>
#include <ctime>
#include <cstring>
#include <fstream>

using namespace std;
class neuron *constn;
typedef pair<double,double> weightpair;
typedef pair<neuron*,weightpair> neurpair;
typedef vector< vector<double> > vec2d;

inline double sqr (const double &i) {return i*i;}

class neuron {
public:
	map<neuron*,weightpair> weights;
	double delta, output;
	neuron() : output(-1) {}
	
	neuron(vector<neuron>& inps) {
		weights.insert(neurpair(constn, weightpair(0.5,0)));
		for(neuron& n: inps)
			weights.insert(neurpair(&n, weightpair(0.5,0)));
	}
	
	inline void compute() {
		double sum = 0;
		for (auto np: weights)
			sum += np.first->output * np.second.first;
		output = 1/(1+ exp(-sum));
	}
};

class network {
public:
	vector<vector<neuron>> mat;
	double eta;
	
	network (const vector<int>& sizes) : mat(sizes.size()), eta(0.0625L) {
		mat[0].resize(sizes[0]);
		for (int i=1; i<sizes.size(); i++)
			for (int j=0; j<sizes[i]; j++)
				mat[i].push_back(neuron(mat[i-1]));
	}
	
	void reset() {
		cout << "Resetting the network.\n";
		for (auto &lyr: mat)
			for (auto &nr: lyr)
				for (auto &np: nr.weights)
					np.second = weightpair(2*(double)rand()/RAND_MAX - 1, 0);
	}
	
	inline void compute (const vector<double> &input) {
		for (int i=0; i<input.size(); i++)
			mat[0][i].output = input[i];
		
		for(int i=1;i<mat.size();i++)
			for(neuron& nr: mat[i])
				nr.compute();
	}
	
	inline bool train(const vec2d &inputs,const vec2d &targets, double max_error, bool print) {
		double init_error = error(inputs, targets), curr_error;
		for (int u=0; u<inputs.size(); u++) {
			compute(inputs[u]);
			
			for (int i=0; i<targets[u].size(); i++) {
				double oj = mat[mat.size()-1][i].output;
				mat[mat.size()-1][i].delta= (targets[u][i] - oj)*oj*(1-oj);
			}
			
			for(int i=mat.size()-2;i>=0;i--) {
				for(neuron& bottom: mat[i]) {
					bottom.delta = 0;
					for(neuron& top: mat[i+1])
						bottom.delta += top.weights[&bottom].first * top.delta * bottom.output * (1-bottom.output);
				}
			}
			
			for(int i=1;i<mat.size();i++)
				for(neuron& top: mat[i])
					for(auto &np: top.weights)
						np.second.second += top.delta * np.first->output;
		}
		
		double mulfac = 0;
		for(int i=1;i<mat.size();i++)
			for(neuron& top: mat[i])
				for(auto &np: top.weights)
					mulfac += np.second.second * np.second.second;
		mulfac = eta / sqrt (mulfac);
		if (print)
			cout << eta/mulfac << " ";
		
		for(int i=1;i<mat.size();i++)
			for(neuron& top: mat[i])
				for(auto &np: top.weights) {
					np.second.second *= mulfac;
					np.second.first += np.second.second;
				}
		
		for (; (curr_error = error(inputs, targets)) >= init_error && eta > 0x1.0p-25; eta /= 2)
			for(int i=1;i<mat.size();i++)
				for(neuron& top: mat[i])
					for(auto &np: top.weights) {
						np.second.second /= 2;
						np.second.first -= np.second.second;
					}
		
		for(int i=1;i<mat.size();i++)
			for(neuron& top: mat[i])
				for(auto &np: top.weights) {
					np.second.first -= np.second.second / 3;
					np.second.second = 0;
				}
		
		curr_error = error(inputs, targets);
		if (print)
			cout << eta << " " << init_error << " " << curr_error << endl;
		eta *= 2;
		
		return (init_error>curr_error) && (curr_error>max_error);
	}
	
	inline double error (const vec2d &inputs, const vec2d &targets) {
		double ret = 0;
		for (int i=0; i<inputs.size(); i++) {
			compute(inputs[i]);
			for (int j=0; j<targets[i].size(); j++)
				ret += sqr(mat[mat.size()-1][j].output - targets[i][j]);
		}
		
		return ret;
	}
	
	inline int errorint (const vec2d &inputs, const vec2d &targets) {
		int ret = 0;
		for (int i=0; i<inputs.size(); i++) {
			compute(inputs[i]);
			int wrong = false;
			for (int j=0; j<targets[i].size(); j++)
				if ((mat[mat.size()-1][j].output>0.5) != (targets[i][j]==1))
					wrong = true;
			if (wrong)
				ret++;
		}
		
		return ret;
	}
	
	inline void print() {
		for(int i=1;i<mat.size();i++) {
			for(int j=0; j<mat[i].size(); j++) {
				cout << j << ": ";
				for(auto &np: mat[i][j].weights)
					cout << (np.first==constn ? -1 : np.first - &mat[i-1][0]) << " " << np.second.first << "\t";
				cout << endl;
			}
			cout << endl;
		}
	}
};

void fill_file (char *filename, vec2d& table, vec2d& out_final,int inpnum,int outpnum) {
	ifstream in(filename);
	while (in) {
		vector<double> inp(inpnum), outp (outpnum);
		for (int j=0; j<inpnum; j++)
			in >> inp[j];
		
		for (int j=0; j<outpnum; j++)
			in >> outp[j];
		
		table.push_back(inp);
		out_final.push_back(outp);
	}
}

int main(int argc, char **argv) {
	srand (time(NULL));
	constn = new neuron;
	int n = atoi(argv[1]);
	vector<int> sizes(n+1);
	for(int i=0; i<=n; i++)
		sizes[i] = atoi(argv[i+2]);
	
	network net(sizes);
	
	double max_err = atof(argv[n+3]);
	int test_index = argv[n+4][0] - 48;
	
	int inpnum = sizes[0], outpnum = sizes[n];
	vec2d table, out_final;
	char filename[10] = "data_1";
	for (int i=1; i<=5; i++)
		if (i!=test_index) {
			filename[5] = i+48;
			fill_file(filename, table, out_final,inpnum,outpnum);
		}
	
	int k;
	while (net.error(table, out_final) > max_err) {
		net.reset();
		for(k=0;net.train(table,out_final,max_err,k%1000 == 0);k++)
			if (k%100000 == 0)
				net.print();
		cout << "Current error is " << net.error(table, out_final) << " in " << k << " steps.\n";
	}
	
	cout << "Trained the neural network.\n";
	net.print();
	vec2d table_test, out_test;
	filename[5] = test_index+48;
	fill_file(filename, table_test, out_test,inpnum,outpnum);
	cout << "Error on test " << net.errorint(table_test, out_test)<< "\n";
	return 0;
}

#include<iostream>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<ctime>
using namespace std;
int debug =0;
class neuron
{
	public:
	int weightSize;
	vector<float> weights;
	vector<float> prev_updates;
	float delta;	
	float output;
	neuron(){}
	neuron(int a)
	{
		weightSize =a+1;
		weights.resize(weightSize);
		prev_updates.resize(weightSize);
		for(int i=0;i<weightSize;i++)
		{
			weights[i] = 2*((double) rand() / (double) (RAND_MAX) -0.5);
		}
	}
	float sigmoid (float x)
	{
		return 1/(1+ exp(-x));
	}
	float dotp(vector<float> &input) {
		float sum=0;
		for (int i=0; i<weights.size(); i++)
			sum += input[i]*weights[i];
		return sigmoid(sum);
	}
	
};

class layer
{
	public:
	int noNeuron;
	vector< neuron > v;
	vector<float> output;

	layer(){}
	layer(int a,int x)
	{
		v.resize(a);
		output.resize(a);
		output.push_back(1);
		noNeuron=a;
		for(int i=0;i<a;i++)
		{
			v[i].weightSize =x+1;
			v[i].weights.resize(v[i].weightSize);
			v[i].prev_updates.resize(v[i].weightSize);			
			for(int j=0;j<v[i].weightSize;j++)
			{
				v[i].weights[j] = 2*((double) rand() / (double) (RAND_MAX) - 0.5);
			}
		}
	}
}
;

class network
{
	public:
	int noLayers;
	vector<layer> mat;
	float eta;
	float error;
	float momentum;
	void propogate(int i,vector<float>& input)
	{
			int layersize = mat[i].noNeuron;
			//cout<<"layer "<<i<<" size "<<layersize<<endl;
			for(int j=0;j<layersize;j++)
			{
				mat[i].v[j].output = mat[i].v[j].dotp(input);
				mat[i].output[j] = mat[i].v[j].output;
				if(debug)
					cout<<"layer "<<i<<" neuron "<<j<<" "<<mat[i].v[j].output<<endl;
				//cout<<"output of layer "<<i<<"  neuron "<<j<<"  is  "<<mat[i].output[j]<<endl;
			}	
	}
	
	void train(vector<float> &input,vector<int>&target)
	{
		if(debug)
		for(int j=0;j<input.size();j++)
					cout<<input[j]<<" ";
		propogate(0,input);
		for(int i=1;i<noLayers;i++)
		{
			propogate(i,mat[i-1].output);
			
		}
		error = 0;
		int output  = 0;
		int p = 1;
		for(int i=0;i<mat[noLayers-1].noNeuron;i++)
		{
			float oj = mat[noLayers-1].v[i].output;
			//cout<<" target for "<<i<<"th neuron is ";
//			cout<<target[i]<<" output is ";
			
			mat[noLayers-1].v[i].delta= ((float)target[i] - oj)*oj*(1-oj);
			error+=((float)target[i]-oj)*((float)target[i]-oj);
			output += p*(int)(oj+0.5);
			p*=2;
		}
		if(debug)cout<<output<<endl;
		//cout<<"current error "<<error/2<<endl;
		for(int i=noLayers-2;i>=0;i--)
		{
			for(int j=0;j<mat[i].noNeuron;j++)
			{
				float sum = 0;
				for(int k = 0;k<mat[i+1].noNeuron;k++)
				{
					float oj = mat[i].output[j];
					sum+=mat[i+1].v[k].weights[j]*mat[i+1].v[k].delta*oj*(1-oj);
				}
				mat[i].v[j].delta = sum;
			}
		}
		//cout<<"deltas calculated"<<endl;
		for(int i=1;i<noLayers;i++)
		{
	
			for(int k=0;k<mat[i].noNeuron;k++)
			{
					
					for(int j=0;j<mat[i-1].noNeuron+1;j++)
					{
						//cout<<"layer "<<i<<"neuron "<<j<<"input "<<k<<" weight "<<mat[0].v[j].weights[k]<<endl;						
						float update = eta*mat[i].v[k].delta*mat[i-1].output[j];						
						mat[i].v[k].prev_updates[j] = (update + mat[i].v[k].prev_updates[j]*momentum);
						mat[i].v[k].weights[j]  += mat[i].v[k].prev_updates[j];
					}	
			}
		}
		for(int k=0;k<mat[0].noNeuron;k++)
		{
		
			for(int j=0;j<input.size();j++)
			{
				//cout<<"layer 0 "<<"neuron "<<j<<"input "<<k<<" weight "<<mat[0].v[j].weights[k]<<endl;
				float update = eta*mat[0].v[k].delta*input[j];						
				mat[0].v[k].prev_updates[j] = (update + mat[0].v[k].prev_updates[j]*momentum);
				mat[0].v[k].weights[j]  += mat[0].v[k].prev_updates[j];
				
			}	
		}
	//	cout<<"weights updated"<<endl;
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
int evaluate_input(vector<int>& input,vector<cond>& roots)
{
	for(int i=0;i<roots.size();i++)
		if(roots[i].eval(input) == 1)
			return i;
	return roots.size();
}
int main(int argc, char* argv[])
{
	srand (time(NULL));
	network net;
	int n;
	//cout<<"enter num layers"<<endl;
	cin>>n;

	int inputs;
	//cout<<"number of inputs"<<endl;
	cin>>inputs;
	net.noLayers = n;	
	net.eta = atoi(argv[1])/100.0;
	net.momentum = atoi(argv[2])/100.0;
	int temp;

	for(int i=0;i<n;i++)
	{
		//cout<<"enter number of neurons \n";
		cin>>temp;
		net.mat.push_back(layer(temp,inputs));
		inputs = temp;
	}
	
	vector<cond> root;
	int args;
	//cout << "Input the number of args: \n";
	cin >> args;
	int no_functions;
	//cout<<"enter number of functions \n";
	cin>>no_functions;
	
	root.resize(no_functions);
	for(int i=0;i<no_functions;i++)
	{
		//cout << "Input the function: ";
		cin >> root[i];
	}
	float threshold;
	cin>>threshold;
	vector< vector <float> > table;	
	vector<vector<int> > out_final;
	vector<int> answers;
	for (int i=0; i<(1<<args); i++) {
		vector<int> val(args);
		vector<float> values(args);
		for (int j=0; j<args; j++)
		{
			val[j] = (i>>j)&1;
			values[j] = val[j];
		}
		
		values.push_back(1);
		table.push_back(values);
		vector<int> temp(4);
		int ans = evaluate_input(val,root);	
		answers.push_back(ans);
		//cout<<ans<<endl;			
		for (int j=0; j<4; j++)
		{
			temp[j] = (ans>>j)&1;
			
		}
		out_final.push_back(temp);
	//	temp.clear();
		//val.clear();
//		values.clear();
	}
	//cout<<"made truth table"<<endl;
	for(int itrcount=0;;itrcount++)
	{
		float total_error = 0;
		for(int i=0;i<table.size();i++)
		{
			if(debug)
			cout<<answers[i]<<" ";
			net.train(table[i],out_final[i]);
			total_error +=net.error;
		}
		cout<<itrcount<<" "<<total_error<<endl;
		//cout<<total_error<<endl;
		if(total_error < threshold)
		{
			//cout<<	"stopped after "<<k << " iterations with total error "<<total_error<<endl;
			
			debug = 1;
			break;
		}
		if(itrcount>100000)
		{
			for(int i =0;i<net.noLayers;i++)
				for(int j=0;j<net.mat[i].noNeuron;j++)
					for(int k=0;k<net.mat[i].v[j].weightSize;k++)
						net.mat[i].v[j].weights[k] = 2*((double) rand() / (double) (RAND_MAX) -0.5);
			itrcount = 0;
		}
	}
	for(int i=0;i<table.size();i++)
	{
		//if(debug)
		//cout<<answers[i]<<" ";
		net.train(table[i],out_final[i]);
	}
	/*for(int i =0;i<net.noLayers;i++)
			for(int j=0;j<net.mat[i].noNeuron;j++)
				for(int k=0;k<net.mat[i].v[j].weightSize;k++)
					cout<<" layer "<<i<<" neuron "<<j<<" weight "<<k<<" is "<<net.mat[i].v[j].weights[k]<<endl;;*/
	return 0;	
}

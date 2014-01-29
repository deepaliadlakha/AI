#include<iostream>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<ctime>
using namespace std;

class neuron
{
	public:
	int n;
	vector<float> weights;
	float delta;	
	float output;
	neuron(){}
	neuron(int a)
	{
		n =a+1;
		weights.resize(n);
		for(int i=0;i<n;i++)
		{
			weights[i] = ((double) rand() / (double) (RAND_MAX))-0.5;
		}
	}
	float sigmoid (float x)
	{
		return 1/(1+ exp(-x));
	}
	float dotp(vector<float> &input) {
		float sum=0;
		for (int i=0; i<weights.size(); i++) {
			sum += input[i]*weights[i];
			//cout << input[i] << " " << weights[i] << "Yo MoFo" << endl;
		}
	//	cout<<"sum is "<<sum<<endl;
		//cout<<sigmoid(sum);
		return sigmoid(sum);
	}
	
};

class layer
{
	public:
	int n;
	vector< neuron > v;
	vector<float> output;

	layer(){}
	layer(int a,int x)
	{
		v.resize(a);
		output.resize(a);
		output.push_back(1);
		n=a;
		for(int i=0;i<a;i++)
		{
			v[i].n =x+1;
			v[i].weights.resize(x+1);
			for(int j=0;j<=x;j++)
			{
				v[i].weights[j] = ((double) rand() / (double) (RAND_MAX))-0.5;
			//	cout << v[i].weights[j]<<",";
			}
		}
	}
}
;

class network
{
	public:
	int n;
	int incount;
	vector<layer> mat;
	float eta;
	float error;
	void propogate(int i,vector<float>& input)
	{
			int layersize = mat[i].n;
			//cout<<"layer "<<i<<" size "<<layersize<<endl;
			for(int j=0;j<layersize;j++)
			{
				mat[i].v[j].output = mat[i].v[j].dotp(input);
				mat[i].output[j] = mat[i].v[j].output;
			//	cout<<i<<" "<<j<<" "<<mat[i].output[j]<<endl;
			}	
	}
	
	void train(vector<float> &input,vector<int>&target)
	{
		/*for(int i=0;i<input.size();i++)
			cout<<input[i]<<" ";
		cout<<target[0]<<endl;*/
		propogate(0,input);
		for(int i=1;i<n;i++)
		{
			propogate(i,mat[i-1].output);
			
		}
		error = 0;
		for(int i=0;i<mat[n-1].n;i++)
		{
			float oj = mat[n-1].v[i].output;
			mat[n-1].v[i].delta= ((float)target[i] - oj)*oj*(1-oj);
//			cout<<target[i]<<" "<<oj<<endl;
		//	cout<<"delta for last layer "<< i<<" th neuron = "<<mat[n-1].v[i].delta<<endl;
			error+=((float)target[i]-oj)*((float)target[i]-oj);
			//cout<<error<<endl;
		}
		//cout<<"current error "<<error<<endl;
		for(int i=n-2;i>=0;i--)
		{
			for(int j=0;j<mat[i].n;j++)
			{
				float sum = 0;
				for(int k = 0;k<mat[i+1].n;k++)
				{
					float oj = mat[i].output[j];
					sum+=mat[i+1].v[k].weights[j]*mat[i+1].v.at(k).delta*oj*(1-oj);
				}
				mat[i].v[j].delta = sum;
			//	cout<<"delta for layer "<< i<<" and "<<j<<" th neuron = "<<mat[i].v[j].delta<<endl;
			}
		}
		//cout<<"deltas calculated"<<endl;
		for(int i=1;i<n;i++)
		{
	
			int layersize = mat[i].n;
			for(int j=0;j<layersize;j++)
			{
					int layersize2 = mat[i-1].n;
					for(int k=0;k<layersize2+1;k++)
					{
					//	cout<<"layer "<<i<<"neuron "<<j<<"input "<<k<<" weight "<<mat[i].v[j].weights[k]<<endl;						
						mat[i].v[j].weights[k]+=eta*mat[i].v[j].delta*mat[i-1].output[k];
					
					}	
			}
		}
		for(int j=0;j<mat[0].n;j++)
		{
		
			int layersize2 = input.size();
			for(int k=0;k<layersize2;k++)
			{
				//cout<<"layer 0 "<<"neuron "<<j<<"input "<<k<<" weight "<<mat[0].v[j].weights[k]<<endl;
				mat[0].v[j].weights[k]+=eta*mat[0].v[j].delta*(float)input[k];
				
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
int main()
{
	srand (time(NULL));
	network net;
	int n;
	cout<<"enter num layers"<<endl;
	cin>>n;

	int inputs;
	cout<<"number of inputs"<<endl;
	cin>>inputs;
	inputs++;
	net.n = n;
	net.incount = inputs;	
	net.eta = 0.3;
	int temp;
	inputs--;
	for(int i=0;i<n;i++)
	{
		cout<<"enter number of neurons \n";
		cin>>temp;
		net.mat.push_back(layer(temp,inputs));
		inputs = temp;
	}
	
	cond root;
	int args;
	cout << "Input the number of args: ";
	
	cin >> args;
	cout << "Input the function: ";
	cin >> root;
	vector< vector <float> > table;	
	vector<vector<int> > out_final;
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
		vector<int> temp;
		temp.push_back(root.eval(val));				
		out_final.push_back(temp);
	}
	cout<<"made truth table"<<endl;
	
	for(int k=0;;k++)
	{
		float total_error = 0;
		for(int i=0;i<table.size();i++)
		{
			net.train(table[i],out_final[i]);
			total_error +=net.error;
		}
		cout<<total_error<<endl;
		if(total_error < 0.001)
		{
			cout<<	"stopped after "<<k << " iterations with total error "<<total_error;
			break;
		}
	}
	return 0;	
}

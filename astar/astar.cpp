#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <cstdio>
using namespace std;

void swap(int& a, int& b){
	int temp=a;
	a=b;
	b=temp;
}

int goal_state[9]= {1,2,3,8,-1,4,7,6,5};
int start_state[9]= {-1,1,3,4,2,5,8,7,6};
int mode;

void print(int* arr){
	for(int i=0;i<9;i++){
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}





int displaced_tiles(int* curr){
	int count=0;
	for(int i=0;i<9;i++){
		if(curr[i]!=-1 && curr[i]!=goal_state[i])
			count++;
	}
	return count;
}

int manhattan_dist(int* curr){
	int count=0;
	for(int i=0;i<9;i++){
		int curr_pos=curr[i];
		if(curr_pos!=-1){
			int j;
			for(j=0;j<9;j++){
				if(goal_state[j]==curr_pos)
					break;
			}
			count=count+abs(j/3-i/3)+ abs(j%3-i%3);
		}
	}
	return count;

}

class node{
public:
	int f,g,h;
	int node_state[9];
	node(int gn, int hn, int* ns){
		g=gn;
		h=hn;
		f=g+h;
		for(int i=0;i<9;i++){
			node_state[i]=ns[i];
		}
	}

	bool operator==( const node& rhs) const{
		//cout<<"here"<<endl;
		for(int i=0;i<9;i++){
			if(node_state[i]!=rhs.node_state[i])
				return false;
		}
		return true;
	}

	bool is_goal_node(){
		for(int i=0;i<9;i++){
			if(node_state[i]!=goal_state[i]){
				return false;
			}
		}
		return true;
	}

	vector <node> my_find_succ(){
		int ipos;
		for(int i=0;i<9;i++){
			if(node_state[i]==-1){
				ipos=i;
				break;
			}
		}
		vector <node> result;
		if(ipos%3<2){
			swap(node_state[ipos],node_state[ipos+1]);
			int new_h = mode==0?displaced_tiles(this->node_state):manhattan_dist(this->node_state);
			result.push_back(node(g+1,new_h,node_state));
			swap(node_state[ipos],node_state[ipos+1]);
		}

		if(ipos%3>0){
			swap(node_state[ipos],node_state[ipos-1]);
			int new_h = mode==0?displaced_tiles(this->node_state):manhattan_dist(this->node_state);
			
			result.push_back(node(g+1,new_h,node_state));
			swap(node_state[ipos],node_state[ipos-1]);
			
		}

		if(ipos/3<2){
			swap(node_state[ipos],node_state[ipos+3]);
			int new_h = mode==0?displaced_tiles(this->node_state):manhattan_dist(this->node_state);
			
			result.push_back(node(g+1,new_h,node_state));
			swap(node_state[ipos],node_state[ipos+3]);
			
		}

		if(ipos/3>0){
			swap(node_state[ipos],node_state[ipos-3]);
			int new_h = mode==0?displaced_tiles(this->node_state):manhattan_dist(this->node_state);
			
			result.push_back(node(g+1,new_h,node_state));
			swap(node_state[ipos],node_state[ipos-3]);
			
		}

		return result;



	}
};


struct ol_compare{
	bool operator() (const node& lhs, const node& rhs) const
	{return lhs.f < rhs.f;}
};



int simulate(multiset<node,ol_compare> ol, multiset<node,ol_compare> cl){

	if(ol.size()==0) return -1;
	//cout<<"ol size is "<<ol.size()<<endl;
	node* curr_min= new node(ol.begin()->g,ol.begin()->h,(int *)(ol.begin()->node_state));
	cl.insert(*curr_min);
	ol.erase(ol.begin());
	if(curr_min->is_goal_node()){
		//cout<<"fffds "<<curr_min->h<<endl;
		//print(curr_min->node_state);
		//print(goal_state);
		return curr_min->g;
	}
	cout<<"curr min: "<<curr_min->g<<" "<<curr_min->h<<" ";print(curr_min->node_state);
	
	vector<node> succ=curr_min->my_find_succ();
	for(int i=0; i<succ.size();i++){
	//	print(succ[i].node_state);

		multiset<node,ol_compare>::iterator it;
		for (it=ol.begin(); it!=ol.end(); ++it){
				
			if((*it)==succ[i])
				break;
		}
				
	


		if(it!=ol.end()){
	//		cout<<"already in ol\n";
			if((*it).g > (curr_min->g)+1){
	//			cout<<"Updating, already in ol\n";
				ol.erase(it);
				ol.insert(succ[i]);
			}
			
		}
		else{

			multiset<node,ol_compare>::iterator itn;
			for (itn=cl.begin(); itn!=cl.end(); ++itn){
				if(*itn==succ[i])
					break;
			
			}
	//		cout<<endl;
			if(itn==cl.end()){
				ol.insert(succ[i]);
	//			cout<<"Inserting in ol\n";
			}
		}

	}
	
	//cout<<"cl size "<<cl.size()<<endl;
	

	//print(curr_min.node_state);
	return simulate(ol,cl);

}


int main(int argc, char* argv[]){
	mode=atoi(argv[1]);

	multiset<node,ol_compare> ol;
	int new_h = mode==0?displaced_tiles(start_state):manhattan_dist(start_state);
	//cout<<"dasfdsfd "<<new_h<<endl;
	ol.insert(node(0,new_h,start_state));
	multiset <node,ol_compare> cl;
	//print(start_state);
	cout<<"Answer is "<<simulate(ol,cl)<<endl;
	

	return 0;

}
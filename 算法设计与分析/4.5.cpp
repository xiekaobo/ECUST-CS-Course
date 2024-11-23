#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <queue>
using namespace std;
class Node{
public:
	static int k;
	static int n;
	Node();
	Node(const Node &other);
	void compute(int i);//当前节点的所需time
	int time;
	int t;
	int *select;
	int *mac;
};
int Node::k = 0;
int Node::n = 0;
Node::Node(){
	time = 0;
	t = 0;
	select = new int[n + 1];
	mac = new int[k + 1];
	int i;
	for (i = 0; i <= n; ++i)
	{
		select[i] = 0;
	}
	for (i = 0; i<= k; ++i)
	{
		mac[i] = 0;
	}
}
Node::Node(const Node &other){
	t = other.t;
	time = other.time;
	mac = new int[k + 1];
	select = new int[n + 1];
	int i;
	for (i = 1; i <= k; ++i)
	{
		mac[i] = other.mac[i];
	}
	for (i = 1; i <= n; ++i)
	{
		select[i] = other.select[i];
	}
}
void Node::compute(int i){
	if (time < mac[i])
	{
		time = mac[i];
	}
}
class Schedule{
public:
	Schedule(int n, int k, int *data){
		this->data = data;
		this->n = n;
		this->k = k;
		MinMac = new int[n + 1];
		MinTime = INT_MAX;
	};
	int getMT(){return MinTime;}
	int *getMM(){return MinMac;}
	void ExScedule();
protected:
	int n;
	int k;
	int *data;
	int MinTime;
	int *MinMac;
};
void Schedule::ExScedule(){
	queue<Node> Q;
	Node::k = k;
	Node::n = n;
	Node initial;
	Q.push(initial);
	while(!Q.empty()){
		Node father = Q.front();
		Q.pop();
		if (father.t == n)
		{
			if (father.time < MinTime)
			{
				MinTime = father.time;
				for (int i = 1; i <= n; ++i)
				{
					this->MinMac[i] = father.select[i];
				}
			}
		}
		else
		{
			for (int i = 1; i <= k; ++i)
			{
				Node Child(father);
				Child.t++;
				Child.select[Child.t] = i;
				Child.mac[i] += data[Child.t];
				Child.compute(i);
				if (Child.time <= MinTime)
				{
					Q.push(Child);
				}
			}
		}
	}
}
int main(){

		int n,k,i,j;
		cin>>n>>k;
		int *data = new int[n + 1];
		for (i = 1; i <= n; ++i){cin>>data[i];}
		Schedule test(n,k,data);
		test.ExScedule();
		cout<<test.getMT()<<endl;
	return 0;
}

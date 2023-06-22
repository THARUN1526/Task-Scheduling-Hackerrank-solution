#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

const int BufferSize = 120000;

struct Node
{
	int from;
	int to;
	long long maximum;
	long long offset;
	Node *left;
	Node *right;
};

int len = 0;
Node nodes[BufferSize*2];
int d[BufferSize];
int m[BufferSize];
int t;

Node *MakeTree(int from, int to)
{
	Node *p = &nodes[len++];
	p->from = from;
	p->to = to;
	p->maximum = -(1LL << 60);
	p->offset = 0;

	if (from+1 < to)
	{
		int mid = (from + to)/2;
		p->left = MakeTree(from, mid);
		p->right = MakeTree(mid, to);
	}

	return p;
}

void Insert(Node *p, int from, int to, long long x)
{
	if (from <= p->from && p->to <= to)
	{
		//x += p->offset;
		if (x > p->maximum)
			p->maximum = x;
	}
	else
	{
		int mid = (p->from + p->to)/2;
		if (from < mid && to > p->from)
		{
			Insert(p->left, from, to, x);
			long long tmp = p->left->maximum + p->left->offset;
			if (tmp > p->maximum)
				p->maximum = tmp;
		}
		if (from < p->to && to > mid)
		{
			Insert(p->right, from, to, x);
			long long tmp = p->right->maximum + p->right->offset;
			if (tmp > p->maximum)
				p->maximum = tmp;
		}
	}
}

void Add(Node *p, int from, int to, long long x)
{
	if (from <= p->from && p->to <= to)
	{
		p->offset += x;
	}
	else
	{
		int mid = (p->from + p->to)/2;
		if (from < mid && to > p->from)
		{
			Add(p->left, from, to, x);
			long long tmp = p->left->maximum + p->left->offset;
			if (tmp > p->maximum)
				p->maximum = tmp;
		}
		if (from < p->to && to > mid)
		{
			Add(p->right, from, to, x);
			long long tmp = p->right->maximum + p->right->offset;
			if (tmp > p->maximum)
				p->maximum = tmp;
		}
	}
}

int main(int argc, char *argv[])
{

	scanf("%d", &t);
	for (int i = 0; i < t; ++i)
		scanf("%d %d", &d[i], &m[i]);

	int max_d = *max_element(d, d + t) + 1;
	MakeTree(0, max_d);

	for (int i = 0; i < t; ++i)
	{
		Add(nodes, d[i], max_d, m[i]);
		Insert(nodes, d[i], d[i]+1, -d[i]);
		cout << max(0LL, nodes->maximum) << endl;
	}

	return 0;
}
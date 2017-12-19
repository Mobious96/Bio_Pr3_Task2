#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <time.h>
//motif and median string search
using namespace std;

const string filename4 = "Input.txt";
const char alphabet[4] = { 'A', 'C', 'G', 'T' };

int strNum(string _filename)
{
	int res = 0;
	string s;
	ifstream fin(_filename, ios_base::in);
	if (fin.is_open()) while (getline(fin, s)) res++;
	else return 0;
	fin.close();
	return res;
}

//DNA  - array of strings, t - num of str, l - pattern length, n - num of letters in row
void motifSearch(list<string> &_list, string *DNA, int t, int l, int n)
{

	int bestScore = 0;
	vector<int> alignment(t);
	for (int i = 0; i < t; i++) alignment[i] = 0;
	int k = 0;
	int *ind = new int[t];
	for (int i = 0; i < t; i++) ind[i] = 0;

	int c = pow(n - l + 1, t); // number of different positions
	for (int i = 0; i < c; i++)
	{
		//refresh indexes
		for (int j = 0; j < t; j++)
		{
			ind[j]++;
			if (ind[j] < n - l + 1)
				break;
			ind[j] = 0;
		}
	}
}

//get number of rows and length of pattern
void getNums(int *num, string tmp)
{
	string tmp1 = "";
	int g = 0;
	for (int i = 0; i < tmp.length(); i++)
	{
		if (47 < tmp[i] < 58)
		{
			tmp1 += tmp[i];
		}
		if (tmp[i] == ' ' || i == tmp.length() - 1)
		{
			num[g] = stoi(tmp1);
			tmp1 = "";
			g++;
		}
	}
}

char getSymb(int ind)
{
	return alphabet[ind];
}

int distance(string s1, string s2)
{
	int result = 0;
	for (int i = 0; i < s1.length(); i++)
		if (s1[i] != s2[i]) result++;
	return result;
}
int totalDisatance(string *DNA, string v, int t)
{

	int result = 0;
	int min = v.length() + 1;

	for (int i = 0; i < t; i++)
	{
		for (int j = 0; j < DNA[0].length() - v.length() + 1; j++)
		{
			if (distance(v, DNA[i].substr(j, v.length())) < min)
			{
				min = distance(v, DNA[i].substr(j, v.length()));
			}
		}
		result += min;
		min = v.length() + 1;

	}
	return result;
}

//getting median string
void getMedianStr(string &median, string *DNA, int t, int l, int n)
{
	int bestDistance = INT_MAX;
	string  bestWord = "";
	int i = 0;
	int prefix_count = l / 3;
	while (i < l)
	{
		bestWord +=
			'A';
		i++;
	}
	int *ind = new int[l];
	for (int i = 0; i < t; i++) 
		ind[i] = 0;

	string wordL = "";
	string prefixL = "";
	int k = 0;
	int c = pow(4, l);
	for (int i = 0; i < c; i++)
	{
		for (int j = 0; j < l; j++)
		{
			wordL += getSymb(ind[j]);
		}
		for (int j = 0; j < prefix_count; j++)
		{
			prefixL[j] = wordL[j];
		}
		if (totalDisatance(DNA, prefixL, t) > bestDistance)
		{
			for (int j = 0; j < prefix_count; j++)
			{
				ind[j]++;
				if (ind[j] < 4)
					break;
				ind[j] = 0;
			}
			continue;
		}

		if (totalDisatance(DNA, wordL, t) < bestDistance)
		{
			bestDistance = totalDisatance(DNA, wordL, t);
			bestWord = wordL;
		}
		wordL = "";
		//refresh indexes
		for (int j = 0; j < l; j++)
		{
			ind[j]++;
			if (ind[j] < 4)
				break;
			ind[j] = 0;
		}
	}
	median = bestWord;
}

int main() {
	list<string> motifs;
	string *DNA;
	string median, tmp;
	clock_t t1, t2;
	ifstream fin(filename4, ios_base::in);

	getline(fin, tmp);
	int l = stoi(tmp);
	DNA = new string[strNum(filename4)];
	int j = 0;
	while (getline(fin, DNA[j])) j++;
	for (int i = 0; i < j; i++)
	{ 
		cout << DNA[i] << endl; 
	}
	t1 = clock();
	getMedianStr(median, DNA, j, l, DNA[0].length());
	t2 = clock();
	cout << t2 - t1 << "ms" << endl;
	delete[]DNA;
	cout << "median " << median << endl;
	system("pause");
	return 0;
}
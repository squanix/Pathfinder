
#include <bits/stdc++.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int* generateBin(int num)
{
	int n = 4*CHAR_BIT*sizeof(num);
	int* s = new int[n];
	for (int i=(n-1); i>=0; i--)
	{
		s[i] = (num%2);
		num = num/2;
	}
	return s;
}

void printBin(int* gen_t, int length)
{
	int lengthloop = 4*CHAR_BIT*sizeof(length);
	for (int i=0; i<lengthloop; i++)
	{
		cout << gen_t[i];
	}
}

template<typename T>
T random(T range_from, T range_to) {
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<T>    distr(range_from, range_to);
    return distr(generator);
}

int* generatePathVar(int length)
{
	int* path = new int[length];
	for (int i=0; i<length; i++)
	{
		int rand_var = random(0, 10000);
		path[i] = rand_var;
	}
	return path;
}

void printPath(int* path_t, int length)
{
	int lengthloop = 4*CHAR_BIT*sizeof(length);
	for (int i=0; i<lengthloop; i++)
	{
		cout << path_t[i];
		cout << " ";
	}
}

int PathCostIdeal(int* challenge, int* PathA, int* PathB, int lengthchallenge)
{
	int totalcost = 0;
	for (int i = (lengthchallenge-2); i>=0; i--)
	{
		if((challenge[i] == 0) and (challenge[i+1] == 1))
			totalcost += PathA[i-1];
		if((challenge[i] == 0) and (challenge[i+1] == 0))
			totalcost++;
		if((challenge[i] == 1) and (challenge[i+1] == 0))
			totalcost += PathB[i-1];
		if((challenge[i] == 1) and (challenge[i+1] == 1))
			totalcost++;
	}
	return totalcost;
}

int PathCostNotIdeal(int* challenge, int* PathA, int* PathB, int* PathA1, int* PathB1, int lengthchallenge)
{
	int totalcost = 0;
	for (int i = (lengthchallenge-2); i>=0; i--)
	{
		if((challenge[i] == 0) and (challenge[i+1] == 1))
			{
				if(PathA[i-1] > PathA1[i-1])
					totalcost += PathA1[i-1];
				else
					totalcost += PathA[i-1];
			}
		if((challenge[i] == 0) and (challenge[i+1] == 0))
			totalcost += PathA1[i-1];
		if((challenge[i] == 1) and (challenge[i+1] == 0))
			{
				if(PathB[i-1] > PathB1[i-1])
					totalcost += PathB1[i-1];
				else
					totalcost += PathB[i-1];
			}
		if((challenge[i] == 1) and (challenge[i+1] == 1))
			totalcost+= PathB1[i-1];
	}
	return totalcost;
}

int PathCostNotIdeal_4path(int* challenge, int* PathA, int* PathB, int* PathA1, int* PathB1, int* PathC, int* PathD, int* PathC1, int* PathD1, int lengthchallenge)
{
	int totalcost = 0;
	for (int i = (lengthchallenge-2); i>=0; i--)
	{
		if(challenge[i] == 0)
		{
			totalcost += std::min(PathA[i], std::min(PathB1[i], std::min(PathC1[i], PathD1[i])));
		}
		if(challenge[i] == 1)
		{
			totalcost += std::min(PathB[i], std::min(PathC[i], std::min(PathD[i], PathA1[i])));
		}
	}
	return totalcost;
}


int main()
{
	ofstream outfileA, outfileB, outfileCH;
    outfileA.open("/home/squanix/vscodeserver/Pathfinder/dataA.csv");
	outfileB.open("/home/squanix/vscodeserver/Pathfinder/dataB.csv");

	int lengthofchallenge = 128;
	int* pathA = (int*)malloc(sizeof(int));
	int* pathA1 = (int*)malloc(sizeof(int));
	int* pathB = (int*)malloc(sizeof(int));
	int* pathB1 = (int*)malloc(sizeof(int));
	int* pathC = (int*)malloc(sizeof(int));
	int* pathC1 = (int*)malloc(sizeof(int));
	int* pathD = (int*)malloc(sizeof(int));
	int* pathD1 = (int*)malloc(sizeof(int));

	pathA = generatePathVar(lengthofchallenge);
	pathB = generatePathVar(lengthofchallenge);
	pathC = generatePathVar(lengthofchallenge);
	pathD = generatePathVar(lengthofchallenge);

	int* genChellenge = (int*)malloc(sizeof(int));

	for (int64_t i = 0; i<= 4000000000000; i++)
	{
		genChellenge = generateBin(i);

		//int costA = PathCostIdeal(genChellenge, pathA, pathB, lengthofchallenge);
		
		//cout << "idelcost " << costA << endl;

		//cout << " " << endl;

		int real_costA = PathCostNotIdeal(genChellenge, pathA, pathB, pathA1, pathB1, lengthofchallenge);

		int real_cost4path = PathCostNotIdeal_4path(genChellenge, pathA, pathB, pathA1, pathB1, pathC, pathD, pathC1, pathD1, lengthofchallenge);
		
		//cout << "predicted " << real_costA << endl;

		//outfileA << costA << endl;
		outfileB << real_costA << endl;
		outfileA << real_cost4path << endl;
		}
	
	return 0;
}

// Here I Found the simulation end
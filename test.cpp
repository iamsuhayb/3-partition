#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//this declares the size of the initial array or the set
const int POPSIZE  = 60;

//this declares how many possible subsets is the array going to contain
const int ROW = POPSIZE/3;

void crossover(int parent[][3], int offspring[][3], int x, int y)
{
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<3; j++)
		{
			if(i==0)
			{
				switch(j)
				{
					case 0:
					offspring[i][j]=parent[y][2];
					break;
					case 1:
					offspring[i][j]=parent[x][1];
					break;
					case 2:
					offspring[i][j]=parent[y][0];
					break;
					default :
					cout<<"Something is wrong \n";
				}

			}
			else
			{
				switch(j)
				{
					case 0:
					offspring[i][j]=parent[x][2];
					break;
					case 1:
					offspring[i][j]=parent[y][1];
					break;
					case 2:
					offspring[i][j]=parent[x][0];
					break;
					default :
					cout<<"Something is wrong \n";
				}
			}
		}
	}
}

void mutate(int offspring[][3])
{
	for(int i=0; i<2; i++)
	{
		if(i==0)
		{
			int temp= offspring[0][2];
			offspring[0][2]= offspring[0][1];
			offspring[0][1]=temp;

		}
		else
		{
			int temp= offspring[1][0];
			offspring[1][0]= offspring[1][1];
			offspring[1][1]=temp;
		}
	}
}

void replace(int pop[][3], int offspring[][3],int x, int y)
{
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<3; j++)
		{
			if(i==0)
				pop[x][j]=offspring[i][j];
			else
				pop[y][j]=offspring[i][j];
		}

	}
}


int fitnesfunction(int A[][3], int row)
{
	int sum =0;
	for(int i=0; i<3; i++)
	{
		sum += A[row][i];
	}

	return sum;
}

void openFile(int initialPop[])
{
	int count =0, value;
	ifstream infile;
	string inputFileName;
	cout<<"Enter the name of the file \n";
	cin>>inputFileName;
	infile.open(inputFileName);
	while(infile>>value)
	{
		initialPop[count]=value;
		count++;
	}

}

void populate(int initial[], int after[][3])
{
	int n=0;
	for(int i=0; i<ROW; i++)
	{
		for(int j=0; j<3; j++)
		{
			after[i][j]= initial[n];
			n++;
		}
	}
}

void calculatefitness(int pop[][3], int fit[][2])
{
	int sum = 0;
	for(int i=0; i<ROW; i++)
	{
		for(int j=0; j<2; j++)
		{
			switch(j)
			{
				case 0 :
				fit[i][j]= i;
				break;
				case 1:
					sum = fitnesfunction(pop,i);
					fit[i][j]= sum;
					break;
			}
		}
	}
}

void sortFitness(int fit[][2])
{
	for(int i=0; i<ROW; i++)
	{
		for(int j=i+1; j<ROW; j++)
		{
			if(fit[i][1]<fit[j][1])
			{
				int temp1 = fit[i][0];
				int temp2 = fit[i][1];
				fit[i][0] = fit[j][0];
				fit[i][1] = fit[j][1];
				fit[j][0] = temp1;
				fit[j][1] = temp2;
			}
		}
	}
}

int sum(int pop[], int size)
{	
	if(size<0)
		return 0;
	else 
		return pop[size] + sum(pop, size-1);
}

bool test(int fit[][2], int value)
{
	for(int i=0; i<	ROW; i++)
	{
		if(fit[i][1] != value)
			return false;
	}

	return true;
}

int main()
{
	int sum1;
	int initialPop[POPSIZE];
	int population[ROW][3];
	int offspring[2][3];
	int fitness[ROW][2];

	//populate the initial array
	openFile(initialPop);
	//populate the first 2d array.
	populate(initialPop, population);
	//calculate initial fitness.
	calculatefitness(population, fitness);
	//sort initial fitness of chromosomes
	sortFitness(fitness);
	/*******************************************************this will be deleted *****/
	cout<<"********* this is before GA is applied *************** \n";
	for(int i=0; i<ROW; i++)
	{
		for(int j=0; j<3; j++)
			cout<<population[i][j]<<" ";
		cout<<endl;
	}
	cout<<"**************Here is the fitness ***** \n";
	for(int i=0; i<ROW; i++)
	{
		for(int j=0; j<2; j++)
			cout<<fitness[i][j]<<" ";

		cout<<endl;
	}
	
	//do the actual ga
	int limit = 30000;
	while(fitness[19][1] <100)
	{
		int j=ROW -1;
		int parent1;
		int parent2;

		for(int i=0; i<(ROW/2); i++)
		{
			parent1 = fitness[i][0];
			parent2 = fitness[j][0];

			crossover(population,offspring, parent1,parent2);
			mutate(offspring);
			replace(population, offspring, parent1, parent2);
			j--;

		}
		calculatefitness(population, fitness);
		sortFitness(fitness);

		limit--;
	}



	

cout<<"*************This is after the GA is applied ****************** \n";
	//calculatefitness(population, fitness);
	//sort initial fitness of chromosomes
	//sortFitness(fitness);
	//sort
	//sortFitness(fitness);

	for(int i=0; i<ROW; i++)
	{
		for(int j=0; j<3; j++)
			cout<<population[i][j]<<" ";
		cout<<endl;
	}

	cout<<"**********Here is the fitness***********\n";

		for(int i=0; i<ROW; i++)
	{
		for(int j=0; j<2; j++)
			cout<<fitness[i][j]<<" ";

		cout<<endl;
	}

	sum1 = sum(initialPop, (POPSIZE-1));

	cout<<"Total of array is "<<sum1<<endl;

	return 0;
}

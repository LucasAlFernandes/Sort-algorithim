#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>
#include <assert.h>
#include <semaphore.h>
#include<time.h>  


typedef struct
{
	int 		* vet;
	int			inicio,
				fim;
}ordenacao;

/*Otmizado*/

/*Quick Sort*/
void * ordenaVetorordenacaoQuick_t(void * args)
{
	int i 		= ((ordenacao*)args)->inicio;
	int j 		= ((ordenacao*)args)->fim;
	int pivo 	= ((ordenacao*)args)->vet[(int)(((ordenacao*)args)->inicio+((ordenacao*)args)->fim)/2];
	int tmp;
	pthread_t thread[2];// = calloc(2, sizeof(pthread_t));
	ordenacao  * agd = malloc(1 * sizeof(ordenacao)), *age = malloc(1 * sizeof(ordenacao));

	while (i < j)
	{
		for(i = i; i < j && ((ordenacao*)args)->vet[i] < pivo; i++){}
		for(j = j; i < j && ((ordenacao*)args)->vet[j] > pivo; j--){}

		if (i < j)
		{
			tmp							= ((ordenacao*)args)->vet[i];
			((ordenacao*)args)->vet[i] 	= ((ordenacao*)args)->vet[j];
			((ordenacao*)args)->vet[j] 	= tmp;
			i++;
			j--;
		}
	}	

	agd->inicio 	= ((ordenacao*)args)->inicio;
	agd->fim 		= j;
	agd->vet 		= ((ordenacao*)args)->vet;

	age->inicio 	= i;
	age->fim 		= ((ordenacao*)args)->fim;
	age->vet 		= ((ordenacao*)args)->vet;
	
	if(((ordenacao*)args)->inicio < j - 1)
		pthread_create(&thread[0], NULL, ordenaVetorordenacaoQuick_t, agd);
	if(((ordenacao*)args)->fim > i + 1)
		pthread_create(&thread[1], NULL, ordenaVetorordenacaoQuick_t, age);
	free(args);

	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
}
void executarordenacaoQuickSort_t(int * vet, int max)
{
	ordenacao * args = malloc(1 * sizeof(ordenacao));
	args->fim 		= max - 1;
	args->inicio 	= 0;
	args->vet 		= vet;

	ordenaVetorordenacaoQuick_t(args);
}
/*Bubble Sort*/
void * OrdenarLR(void * args)
{
	int i,j, tmp;
	for(i = ((ordenacao*)args)->inicio; i >= ((ordenacao*)args)->inicio / 2 ; i--)
	{
		for(j = 0; j < i; j++)
		{
			if(((ordenacao*)args)->vet[j + 1] < ((ordenacao*)args)->vet[j])
			{
				tmp 							= ((ordenacao*)args)->vet[j + 1];
				((ordenacao*)args)->vet[j + 1] 	= ((ordenacao*)args)->vet[j];
				((ordenacao*)args)->vet[j] 		= tmp;
			}
		}
	}
}
void * OrdenarRL(void * args)
{
	int i,j, tmp;
	for(i = 0; i < ((ordenacao*)args)->inicio / 2; i++)
	{
		for(j = ((ordenacao*)args)->inicio; j > i; j--)
		{
			if(((ordenacao*)args)->vet[j-1] > ((ordenacao*)args)->vet[j])
			{
				tmp 							= ((ordenacao*)args)->vet[j - 1];
				((ordenacao*)args)->vet[j - 1] 	= ((ordenacao*)args)->vet[j];
				((ordenacao*)args)->vet[j] 		= tmp;
			}
		}
	}
}
void executarBubbleSort_t(int * vet, int max)
{
	pthread_t thread[2];

	ordenacao  * agd = malloc(1 * sizeof(ordenacao));

	agd->inicio 	= max;
	agd->vet 		= vet;

	pthread_create(&thread[0], NULL, OrdenarRL, agd);
	pthread_create(&thread[0], NULL, OrdenarRL, agd);

	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
}
/*InsertionSort*/
void executarInsertionSort_t(int * vet, int max)
{

}
/*CombSort*/
void executarCombSort_t(int * vet, int max)
{

}
/*ShellSort*/
void executarShellSort_t(int * vet, int max)
{
	int i, j, increment, tmp;
	increment = max / 2;

	while(increment > 0)
	{
		for(i = increment; i < max; i++)
		{
			j = i;
			tmp = vet[i];
			while((j >= increment) && (vet[j - increment] > tmp))
			{
				vet[j] = vet[j - increment];
				j = j - increment;
			}
			vet[j] = tmp;
		}
		if(increment == 2)
					increment = 1;
				else
					increment = increment * 5 / 11;
	}
}


/*Comum*/

/*Quick Sort*/
void ordenaVetorordenacaoQuick(int inicio, int fim, int * vet)
{
	int i 		= inicio;
	int j 		= fim;
	int pivo 	= vet[(int)(inicio + fim)/2];
	int tmp;
	while (i < j)
	{
		for(i = i; i < j && vet[i] < pivo; i++){}
		for(j = j; i < j && vet[j] > pivo; j--){}

		if (i < j)
		{
			tmp			= vet[i];
			vet[i] 		= vet[j];
			vet[j] 		= tmp;
			i++;
			j--;
		}
	}
	if(inicio < j - 1)
		ordenaVetorordenacaoQuick(inicio, j, vet);
	if(fim > i + 1)
		ordenaVetorordenacaoQuick(i, fim, vet);
}
/*Bubble Sort*/
void executarBubbleSort(int * vet, int max)
{
	int i,j, tmp;
	for(i = 0; i < max; i++)
	{
		for(j = max; j > i; j--)
		{
			if(vet[j-1] > vet[j])
			{
				tmp 		= vet[j - 1];
				vet[j - 1] 	= vet[j];
				vet[j] 		= tmp;
			}
		}
	}
}
/*ShellSort*/
void executarShellSort(int * vet, int max)
{
	int i, j, increment, tmp;
	increment = max / 2;

	while(increment > 0)
	{
		for(i = 0; i < max; i++)
		{
			j = i;
			tmp = vet[i];
			while((j >= increment) && (vet[j - increment] > tmp))
			{
				vet[j] = vet[j - increment];
				j = j - increment;
			}
			vet[j] = tmp;
		}
		if(increment == 2)
			increment = 1;
		else
			increment = increment * 5 / 11;
	}

}
/*InsertionSort*/
void executarInsertionSort(int * vet, int max)
{
	int i;
	for(i = 1; i < max; i++)
	{
		int val 	= vet[i];
		int j 		= i - 1;
		int done	= 0;
		do
		{
			if(vet[j] > val)
			{
				vet[j + 1] =  vet[j];
				j--;
				if(j < 0)
				{
					done = 1;
				}
			}
			else
			{
				done = 1;
			}
		}while(!done);
		vet[j + 1] = val;
	}
}
/*CombSort*/
void executarCombSort(int * vet, int max)
{
	int gap 	= max,
		swaps 	= 0;

	do
	{
		gap =  (int)(gap / 1.247330950103979);
		if (gap < 1)
		{
			gap = 1;
		}
		int i = 0;
		swaps = 0;

		do
		{
			if (vet[i] > vet[i + gap])
			{
				int tmp = vet[i];
				vet[i] = vet[i + gap];
				vet[i + gap] = tmp;
				swaps = 1;
			}
			i++;
		} while (!(i + gap >= max));
	}while(!(gap == 1 && swaps == 0));
}


void main()
{
	int op;
	int inc = 10;
	int i, j;

	FILE *fp = fopen("/media/shared/Bubble.txt", "ab");

	for (i = 0; i < 60; i++)
	{
		inc = 8 * pow(2.71, (0.245 * i));
		int v = 0;
		float cont = 9999999;


		while (v < 5)
		{
			clock_t t1, t2;
			int * vet = calloc(inc, sizeof(int));
			for (j = 0; j < inc; j++)
				vet[j] = rand() % 100;

			t1 = clock();
			executarBubbleSort(vet, inc);
			t2 = clock();
			float diff = (((float)t2 - (float)t1) / 1000000.0F) * 1000;	
			cont = diff < cont ? diff : cont;
			v++;
			free(vet);
		}
		printf("Valores = %d | Tempo = %f\n",inc, cont);
		fprintf(fp, "%d;%f-", inc, diff);
	}
	fclose(fp);
}

#include <stdio.h>
#include <pthread.h>


#define LENGTH 10
int numbers[] =
{
	10, 9, 8, 7, 6, 5, 4, 3, 2, 1
};

struct Parameters
{
	int *numbers;
	int length;
};

void *selection_sort(void *parameters);
void merge_two(int *into, int *first, int length_first,
		int *second, int length_second);

int main()
{
	pthread_t tid[2]; // workers
	pthread_attr_t attr; /* set of thread attributes */

	/* set the default attributes of the thread */
	pthread_attr_init(&attr);

	/* divide array into two halves */
	/* main stack will be here for sure :) */
	struct Parameters apar[2];
	apar[0].numbers = numbers;
	apar[0].length = LENGTH/2;

	apar[1].numbers = numbers + apar[0].length;
	apar[1].length = LENGTH - apar[0].length;

	for (int i = 0; i < 2; i++)
	{
		pthread_create(&tid[i], &attr, selection_sort, &apar[i]);
	}

	for (int i = 0; i < 2; i++)
	{
		pthread_join(tid[i], NULL);
	}

	int numbers[LENGTH];
	merge_two(numbers, apar[0].numbers, apar[0].length,
		apar[1].numbers, apar[1].length);

	for(int i = 0; i < LENGTH; i++)
	{
		printf("%d ", numbers[i]);
	}
	puts("");
}

void merge_two(int *into, int *first, int length_first,
		int *second, int length_second)
{
	int length = length_first + length_second;
	int index1 = 0, index2 = 0;

	for (int i = 0; i < length; i++)
	{
		if (index1  == length_first)
		{
			into[i] = second[index2];
			index2++;
			continue;
		}
		else if (index2 == length_second)
		{
			into[i] = first[index1];
			index1++;
			continue;
		}

		if (first[index1] < second[index2])
		{
			into[i] = first[index1];
			index1++;
		}
		else
		{
			into[i] = second[index2];
			index2++;
		}
	}
}

void *selection_sort(void *parameters)
{
	struct Parameters *par = (struct Parameters *) parameters;
	int *numbers = par->numbers;
	int length = par->length;

	for(int base = 0; base < length - 1; base++)
	{
		for(int i = base + 1; i < length; i++)
		{
			if(numbers[base] > numbers[i])
			{
				int temp = numbers[i];
				numbers[i] = numbers[base];
				numbers[base] = temp;
			}
		}
	}
}

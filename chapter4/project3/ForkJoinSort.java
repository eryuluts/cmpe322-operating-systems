/*
	In this project we are going to implement a
	multithreaded sorting algorithm using java
	fork-join threading API.

	This project will be developed in two different
	versions:
	1 - Quicksort: Select pivot to create sub-arrays.
	2 - Mergesort: Divide at half to create sub-arrays.

	When sub-array length is lower than a threshold value,
	directly apply simple sorting algoritms like
	selection or insertion sort to that sub-array.
 */
import java.util.concurrent.*;

class MergeSort extends RecursiveAction
{
	static final int THRESHOLD = 5;

	private int begin;
	private int end;
	private int[] array;

	public MergeSort(int begin, int end, int[] array)
	{
		this.begin = begin;
		this.end = end;
		this.array = array;
	}

	private void SelectionSort()
	{
		for (int base = begin; base <= end - 1; base++)
		{
			for (int i = base + 1; i <= end; i++)
			{
				System.out.printf("base: %d, i: %d\n", base, i);
				if (array[base] > array[i])
				{
					int temp = array[i];
					array[i] = array[base];
					array[base] = temp;
				}
			}
		}
	}

	private void Merge(int begin, int mid, int end)
	{
		int index1 = begin;
		int index2 = mid + 1;
		int length = end - begin + 1;

		int[] numbers = new int[length];
		System.out.printf("length: %d\n", length);
		for(int i = 0; i < length; i++)
		{
			if (index1 > mid)
			{
				numbers[i] = array[index2];
				index2++;
				continue;
			}
			else if (index2 > end)
			{
				numbers[i] = array[index1];
				index1++;
				continue;
			}

			if (array[index1] < array[index2])
			{
				numbers[i] = array[index1];
				index1++;
			}
			else
			{
				numbers[i] = array[index2];
				index2++;
			}
		}

		System.arraycopy(numbers, 0, array, begin, length);
	}

	protected void compute()
	{
		if ((end - begin + 1) <= THRESHOLD)
		{
			System.out.println("Selection Sort");
			SelectionSort();
		}
		else
		{
			int mid = (end + begin) / 2;
			MergeSort left_task = new MergeSort(begin, mid, array);
			MergeSort right_task = new MergeSort(mid + 1, end, array);

			left_task.fork();
			right_task.fork();

			left_task.join();
			right_task.join();

			Merge(begin, mid, end);
		}
	}
}


public class ForkJoinSort
{
	public static void main(String[] args)
	{
		ForkJoinPool pool = new ForkJoinPool();
		int[] numbers = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1};

		MergeSort ms = new MergeSort(0, numbers.length - 1, numbers);
		pool.invoke(ms);

		for (int i : numbers)
		{
			System.out.printf("%d ", i);
		}
	}
}

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <time.h>
#include <limits>
#include <algorithm>

// utility functions //
template<typename T>
void swap(T *a, T *b)
{
	T temp = (*a);
	(*a) = (*b);
	(*b) = temp;	
}

template<typename T>
void printArray(std::vector<T> A)
{
	std::cout<<"\n";
	for(unsigned int i=0; i<A.size(); ++i)
		std::cout<<A[i]<<"\t";
	std::cout<<"\n";
}

// searching algorithms //

// Binary Search ///////////////////////////////////////////////
// time: O( log(n) ), assumes sorted arrays
// space: O(1)
// in place
int binarySearch(std::vector<int> A, int left, int right, int x)
{
	if(left<right)
	{
		int mid = (left+right)/2;
		if(A[mid]==x)
			return mid;
		else if(A[mid]>=x)
			return binarySearch(A,left,mid,x);
		else
			return binarySearch(A,mid+1,right,x);
	}
}


// sorting algorithms //

// Selection Sort /////////////////////////////////////////////
// time: O( n^2 )
// space: O(1)
// in place
void selectionSort(std::vector<int> A)
{
	std::cout<<"Before sorting:\n";
	printArray<int>(A);
	
	for(unsigned int i=0; i<A.size()-1; ++i)
	{
		int min = std::numeric_limits<int>::max();
		int idx = -1;
		for(unsigned int j=i+1; j<A.size(); ++j)
		{
			if(A[j]<min)
			{
				min = A[j];
				idx = j;
			}			
		}
		if(A[i]>A[idx])
			swap<int>(&A[i],&A[idx]);		
	}
	std::cout<<"After sorting:\n";
	printArray<int>(A);
}


// Insertion Sort /////////////////////////////////////////////
// time: O( n^2 )
// space: O(1)
// in place
// best when almost sorted array
// Algorithmic Paradigm: Incremental Approach

void insertionSort(std::vector<int> A)
{
	std::cout<<"Before sorting:\n";
	printArray<int>(A);
	
	for(unsigned int i = 1; i<A.size(); ++i)
		for(unsigned int j = i; j>0; --j)
			if(A[j]<=A[j-1])
				swap<int>(&A[j],&A[j-1]);
	
	std::cout<<"After sorting:\n";
	printArray<int>(A);	
}

// Merge Sort //////////////////////////////////////////////////
// time: theta( n log(n) )
// auxilary space: O(1)
// Algorithmic Paradigm: Divide and Conquer
void merge(std::vector<int>& A,int left, int right, int mid)
{
	std::vector<int> temp;
	temp.resize(right-left+1);
	
	unsigned int k = 0;
	unsigned int i = left;
	unsigned int j = mid+1;
	
	while(i<=mid && j<=right)
	{
		if(A[i]<A[j])
			temp[k++]=A[i++];
		else
			temp[k++]=A[j++];
	}
	
	while(i<=mid)			// make sure to copy the rest of the array
		temp[k++] = A[i++];
	
	while(j<=right)
		temp[k++] = A[j++];
	
	k=0;
	while(k<temp.size())
		A[left+k] = temp[k++];
}
void mergeSort(std::vector<int>& A, int left, int right)
{
	if(left<right)
	{
		int mid = (left+right)/2;
		mergeSort(A,left,mid);
		mergeSort(A,mid+1,right);
		merge(A,left,right,mid);
	}	
}

// Heap Sort //////////////////////////////////////////////////
// time:  O( n log(n) )

void maxHeapify(std::vector<int>& A,int i,int N)
{
	int largest = i;
	int left = (i<<1)+1; //2*i+1
	int right = (i+1)<<1; //2*i+2
	
// 	std::cout<<"Index"<<i<<std::endl;
	
	if(left<N && A[left]>A[largest])
		largest = left;
	
	if(right<N && A[right]>A[largest])
		largest = right;

	if(largest != i)
	{
		swap<int>(&A[i],&A[largest]);
		maxHeapify(A,largest,N);
	}
}
void buildMaxHeap(std::vector<int>& A)
{
	// this has to be bottom up
	for(int i= A.size()/2; i>=0; i--)
	{
		maxHeapify(A,i,A.size());	
	}
}
void heapSort(std::vector<int>& A)
{
	
	std::cout<<"Before sorting:\n";
	printArray<int>(A);
	
	buildMaxHeap(A);
	
	int N = A.size();
	for(unsigned int i=N-1; i>=1; --i)
	{
		swap<int>(&A[0],&A[i]);
		maxHeapify(A,0,--N);
	}
	
	std::cout<<"After sorting:\n";
	printArray<int>(A);	
}

// Quick Sort //////////////////////////////////////////////////
// time: average O( n log(n) ), worst theta( n^2 ), best theta( n log(n) )
int partition(std::vector<int>& A, int left, int right)
{
	int pivot = A[right]; // pick the pivot at the end of the array
	int mid = left-1;
	for(int i=left; i<right-1; ++i)
	{
		if( A[i] <= pivot )
		{
			++mid;
			swap<int>(&A[i],&A[mid]);			
		}
	}
	swap<int>(&A[mid+1],&A[right]);
	return mid+1;
}
void quickSort(std::vector<int>& A, int left, int right)
{
	if(left<right)
	{
		int mid = partition(A,left,right);
		quickSort(A,left,mid-1);
		quickSort(A,mid+1,right);
	}
	
}


int main()
{
    srand(time(NULL));
	std::vector<int> Array;
	Array.resize(10);
	for(unsigned int i=0; i<Array.size(); ++i)
	{
		Array[i]= rand()%100;
// 		Array[i] = i+3;
	}
//	std::cout<<binarySearch(Array,0,Array.size(),5)<<std::endl;
	
//	selectionSort(Array);
// 	insertionSort(Array);

// 	std::cout<<"Before sorting:\n";
// 	printArray<int>(Array);
// 	mergeSort(Array,0,Array.size()-1);
// 	std::cout<<"After sorting:\n";
// 	printArray<int>(Array);	

// 	heapSort(Array);
	
	std::cout<<"Before sorting:\n";
	printArray<int>(Array);
	quickSort(Array,0,Array.size()-1);
	std::cout<<"After sorting:\n";
	printArray<int>(Array);		
	
}




















#include<bits/stdc++.h>
#define MAXHEAP  1
#define MINHEAP  0
using namespace std;



void minHeapify(vector<int> &heap,int index){
	int smallest = index;
	int left = 2*index + 1;
	int right = 2*index + 2;

	if(left<heap.size()&&heap[left]<heap[index]){
		smallest = left;

	}else if(right<heap.size()&&heap[right]<heap[smallest]){
		smallest = right;
	}

	if(smallest!=index){
		int temp = heap[smallest];
		heap[smallest] = heap[index];
		heap[index] = temp;
		minHeapify(heap,smallest);
	}
}

void maxHeapify(vector<int> &heap,int index){

	int largest = index;
	int left =  2*index + 1;
	int right = 2*index + 2;

	if(left<heap.size()&&heap[left]>heap[index]){
		largest = left;
	}
	else if(right<heap.size()&&heap[right]>heap[largest]){
		largest = right;
	}

	if(largest!=index){
		int temp = heap[largest];
		heap[largest] = heap[index];
		heap[index] = temp;
		maxHeapify(heap,largest);
	}

}

void pushElement(vector<int> &minHeap,vector<int> &maxHeap,int element){
	if(maxHeap.size()==0||element<maxHeap[0]){
		maxHeap.push_back(element);
		maxHeapify(maxHeap,0);
	}else{
		minHeap.push_back(element);
		minHeapify(minHeap,0);
	}
}

int popElement(vector<int> &heap,int type){
	int top = heap[0];
	heap[0] = heap[heap.size()-1];
	heap.erase (heap.begin()+heap.size()-1);
	if(type == MAXHEAP){
		maxHeapify(heap,0);
	}else{
		minHeapify(heap,0);
	}
	return top;
}

void printHeaps(vector<int> &minHeap,vector<int> &maxHeap){
	
	for(int i=0;i<minHeap.size();i++){
		cout<<minHeap[i]<<" ";
	}

	for(int i=0;i<maxHeap.size();i++){
		cout<<maxHeap[i]<<" ";
	}
	cout<<"\n";
}

void balanceHeaps(vector<int> &minHeap,vector<int> &maxHeap){
	
	int maxHeapSize = maxHeap.size();
	int minHeapSize = minHeap.size();
	
	int difference = abs(maxHeapSize-minHeapSize);

	if(difference>1){
		if(minHeap.size()>maxHeap.size()){
			maxHeap.push_back(popElement(minHeap,MINHEAP));
			maxHeapify(maxHeap,0);
		}else if(maxHeap.size()>minHeap.size()){
			minHeap.push_back(popElement(maxHeap,MAXHEAP));
			minHeapify(minHeap,0);
		}
	}
}

double getMedian(vector<int> &minHeap,vector<int> &maxHeap){
	if(minHeap.size()==maxHeap.size()){
		return (double)(minHeap[0]+maxHeap[0])/2;
	}else if(minHeap.size()>maxHeap.size()){
		return (double)minHeap[0];
	}else{
		return (double)maxHeap[0];
	}
	return -1;
}

int main(){

	vector<int> minHeap ,maxHeap;

	int n;
	cout<<"Enter element: ";
	while(cin>>n){

		cout<<"\n";
		pushElement(minHeap,maxHeap,n);
		//balanceHeaps(minHeap,maxHeap);
		cout<<"Elements in minHeap: ";
		for(int i=0;i<minHeap.size();i++)
			cout<<minHeap[i]<<" ";
		cout<<"\n";
		cout<<"Elements in maxHeap: ";
		for(int i=0;i<maxHeap.size();i++)
			cout<<maxHeap[i]<<" ";
		cout<<"\n";
		//printHeaps(minHeap,maxHeap);
		balanceHeaps(minHeap,maxHeap);
		cout<<"Median: "<<getMedian(minHeap,maxHeap)<<"\n";
		cout<<"Enter next element: ";
	}
	return 0;	
}	
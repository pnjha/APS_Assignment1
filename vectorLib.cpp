#include <bits/stdc++.h>

using namespace std;

class Vector{

private:

	int Size;
	int index = -1;
	int MIN_INDEX = -1;
	int *vectorPtr = (int*)malloc(sizeof(int));
	int emptyFlag = 1;
	int defaultSize = 10;
	double resizeRatio = 1.5;
	double shrinkRatio = 0.6;
	double maxLoadFactor = 0.8;
	double minLoadFactor = 0.5;

	void checkExpand(){
		int maxThresholdSize = (int)(this->Size*this->maxLoadFactor);
		if(this->index+1>=maxThresholdSize){
			int temp = this->Size;
			int resize = this->Size*this->resizeRatio;
 			this->vectorPtr = (int*)realloc(this->vectorPtr,sizeof(int)*resize);
 			this->Size = resize;
 			for(int i=temp;i<this->Size;i++)
 				this->vectorPtr[i] = 0;
		}
	}

	void checkShrink(){
		int minThresholdSize = (int)this->Size*this->minLoadFactor;
		if(this->index<=defaultSize){
 			this->vectorPtr = (int*)realloc(this->vectorPtr,sizeof(int)*defaultSize);
 			this->Size = defaultSize;
		}
 		else if(this->index<minThresholdSize){
 			int resize = this->Size*this->shrinkRatio;
 			this->vectorPtr = (int*)realloc(this->vectorPtr,sizeof(int)*resize);
 			this->Size = resize;
 		}
	}

	int isEmpty(){
		if(this->index==MIN_INDEX)
			return 1;
		return 0;
	}

public:
	
	Vector(){
		this->vectorPtr = (int *)calloc(defaultSize,sizeof(int));
		this->Size = defaultSize;
		for(int i=0;i<defaultSize;i++)
			this->vectorPtr[i] = 0;
		this->index++;
	} 
	
	Vector(int explicitSize ,int value){
		//cout<<"sdfsd\n";
		int temp = explicitSize;
		explicitSize = (int)(explicitSize*this->resizeRatio);
		//cout<<"sdfsd\n";
		this->vectorPtr = (int*)realloc(this->vectorPtr,sizeof(int)*explicitSize);
		//cout<<"sdfsd\n";
		this->Size = explicitSize;
		for(int i=0;i<this->Size;i++){
			if(i<temp)
				this->vectorPtr[i] = value;
			else
				this->vectorPtr[i] = 0;
		}

		this->index = temp-1;
	} 
 
	int size(){
		return this->index+1;
	}
 
 	void push_back(int value){
 	
		checkExpand();
		
		this->index += 1;
		
		this->vectorPtr[this->index] = value;
		
 	}
 
 	int operator[](int index){
 		return this->vectorPtr[index];
 	}


 	int pop_back(){

 		if(isEmpty()==0){
			int temp = this->vectorPtr[this->index];
			this->index--;
			checkShrink();
			return temp;
 		}

 		return -1;
 	}
 
 	void insert(int index,int value){
 		if(this->index<this->Size-1){
 			this->index++;	
 		}else{
 			checkExpand();
 			this->index++;
 		}
 		int temp2,temp1 = this->vectorPtr[index];
 		this->vectorPtr[index] = value;
 		for(int i = index+1;i<=this->index;i++){
 			temp2 = this->vectorPtr[i];
 			this->vectorPtr[i] = temp1;
 			temp1 = temp2;
 		}

 		checkExpand();
 	} 
 
 	void erase(int index){
 		if(isEmpty()==0&&index<=this->index){

			if(index==this->index)
				this->index--;
			else{
				for(int i = index+1;i<=this->index;i++){
					this->vectorPtr[i-1] = this->vectorPtr[i];
				}
					this->index--;	
			}
			checkShrink();
 		}
 	}
 
 	int front(){
 		if(isEmpty()){
 			return -1;
 		}else{
 			return this->vectorPtr[0];
 		}
 	}
 
 	int back(){
 		if(isEmpty()){
 			return -1;
 		}else{
 			return this->vectorPtr[this->index];
 		}
 	}

};


int main(){

	Vector v(10,4);
	
	v.push_back(157);
	cout<<v.size()<<"\n";
	v.push_back(159);
	cout<<v.size()<<"\n";
	
	v.insert(1,1522);
	for(int i=0;i<v.size();i++)
		cout<<v[i]<<" ";
	cout<<"\n";
	
	v.erase(1);

	cout<<"pop_back: "<<v.pop_back()<<"\n";
	
	cout<<"vector front: "<<v.front()<<"\n";
	cout<<"vector back: "<<v.back()<<"\n";
	return 0;
}
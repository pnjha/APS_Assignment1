#include<bits/stdc++.h>
#define MAXHEAP  1
#define MINHEAP  0
#define ll long long int 
#define SIZE 100007
using namespace std;

ll minHeap[SIZE] ,maxHeap[SIZE];
ll minIndex = -1;
ll maxIndex = -1;


void minHeapify(ll index){
    //cout<<"minHeapify\n";
    ll smallest = index;
    ll left = 2*index + 1;
    ll right = 2*index + 2;

    if(left<=minIndex&&minHeap[left]<minHeap[index]){
        smallest = left;

    }
    if(right<=minIndex&&minHeap[right]<minHeap[smallest]){
        smallest = right;
    }

    if(smallest!=index){
        ll temp = minHeap[smallest];
        minHeap[smallest] = minHeap[index];
        minHeap[index] = temp;
        minHeapify(smallest);
    }
}

void maxHeapify(ll index){
    //cout<<"maxHeapify\n";
    ll largest = index;
    ll left =  2*index + 1;
    ll right = 2*index + 2;

    if(left<=maxIndex&&maxHeap[left]>maxHeap[index]){
        largest = left;
    }
    if(right<=maxIndex&&maxHeap[right]>maxHeap[largest]){
        largest = right;
    }

    if(largest!=index){
        ll temp = maxHeap[largest];
        maxHeap[largest] = maxHeap[index];
        maxHeap[index] = temp;
        maxHeapify(largest);
    }

}


void insertMinHeap(){
    //cout<<"insertMinHeap\n";
    ll temp,t,i;
    if(minIndex==1){
        if(minHeap[0]>minHeap[1]){
            temp = minHeap[0];
            minHeap[0] = minHeap[1];
            minHeap[1] = temp;
        }
    }
    else if(minIndex>=2){
        temp = minIndex;
        double numerator = (double)temp,denominator = 2.0;
        i = (temp-1)/2;
      //  cout<<"parent: "<<i<<" child: "<<temp<<"\n";
        while(i>=0){
            //cout<<" minHeap "<<minHeap[i]<<" temp "<<temp<<"\n";
            if(minHeap[i]>minHeap[temp]){
                t = minHeap[temp];
                minHeap[temp] = minHeap[i];
                minHeap[i] = t;
                //minHeap[temp] = minHeap[i/2];
                temp = i;
                numerator = (double)i;
                i = (i-1)/2;
               // cout<<"parent: "<<i<<" child: "<<temp<<"\n";
            }else{
                break;
            }
            //cout<<"i "<<i<<"\n";
        }
    }
}


void insertMaxHeap(){
    ll temp,t,i;
    if(maxIndex==1){
        if(maxHeap[0]<maxHeap[1]){
            temp = maxHeap[0];
            maxHeap[0] = maxHeap[1];
            maxHeap[1] = temp;
        }
    }
    else if(maxIndex>=2){
        temp = maxIndex;
        double numerator = (double)temp,denominator = 2.0;
        i = (temp-1)/2;
       // cout<<"parent: "<<i<<" child: "<<temp<<"\n";
        while(i>=0){
            //cout<<" minHeap "<<minHeap[i]<<" temp "<<temp<<"\n";
            if(maxHeap[i]<maxHeap[temp]){
                t = maxHeap[temp];
                maxHeap[temp] = maxHeap[i];
                maxHeap[i] = t;
                //minHeap[temp] = minHeap[i/2];
                temp = i;
                numerator = (double)i;
                i = (i-1)/2;
               // cout<<"parent: "<<i<<" child: "<<temp<<"\n";
            }else{
                break;
            }
            //cout<<"i "<<i<<"\n";
        }
    }
}

void pushElement(ll element){
    //cout<<"pushElement\n";
    if(maxIndex==-1||element<maxHeap[0]){
        maxIndex++;    
        maxHeap[maxIndex] = element;
        insertMaxHeap();
    }else{
        minIndex++;
        minHeap[minIndex] = element;
        insertMinHeap();
    }
}

ll popElement(ll type){
    ll top;
    if(type == MAXHEAP){
        top = maxHeap[0];
        maxHeap[0] = maxHeap[maxIndex];
        maxIndex--;
        maxHeapify(0);
    }else{
        top = minHeap[0];
        minHeap[0] = minHeap[minIndex];
        minIndex--;
        minHeapify(0);
    }
    return top;
}

void printHeaps(){
    
    cout<<"minHeap: ";
    for(ll i=0;i<=minIndex;i++){
        cout<<minHeap[i]<<" ";
    }
    cout<<"\nMaxheap: ";
    for(ll i=0;i<=maxIndex;i++){
        cout<<maxHeap[i]<<" ";
    }
    cout<<"\n";
}

void balanceHeaps(){

    ll difference = abs((maxIndex+1) - (minIndex+1));

    if(difference>1){
        if((maxIndex+1)<(minIndex+1)){
            maxIndex++;
            maxHeap[maxIndex] = popElement(MINHEAP);
            insertMaxHeap();
        }else if((maxIndex+1)>(minIndex+1)){
            minIndex++;
            minHeap[minIndex] = popElement(MAXHEAP);
            insertMinHeap();
        }
    }
}

long double getMedian(){
    //cout<<"getMedian\n";
    if(minIndex==maxIndex){
        return (long double)(minHeap[0]+maxHeap[0])/2;
    }else if(minIndex>maxIndex){
        return (long double)minHeap[0];
    }else{
        return (long double)maxHeap[0];
    }
    return -1;
}



void buildMaxHeap(){
    for(int i=maxIndex;i>=0;i--)
        maxHeapify(i);
}

void buildMinHeap(){
    for(int i=minIndex;i>=0;i--)
        minHeapify(i);
}


int main(){

    ll t, n;
    cin>>t;
    while(t--){
        cin>>n;
        pushElement(n);
       // printHeaps();
        balanceHeaps();
       // buildMinHeap();
       // buildMaxHeap();
        //printHeaps();
        printf("%0.1Lf\n",getMedian());
    }
    return 0;    
}
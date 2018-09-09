#include <bits/stdc++.h>
#define ll long long int 
using namespace std;

string addBigInteger(string,string);
string subtractBigInteger(string,string);
string multiplyBigInteger(string,string);
string divideBigInteger(string,string);
string gcdBigInteger(string,string);


string gcdBigInteger(string big_int1,string big_int2){
	
	string temp,ans,remainder,quotient;

	if(big_int1.size()<big_int2.size()){
		temp = big_int1;
		big_int1 = big_int2;
		big_int2 = temp;
	}

	remainder = big_int2;
	if(big_int2.compare(big_int1)==0){
		return big_int1;
	}else{
		while(remainder.compare("0")!=0){
			big_int2 = remainder;
			quotient = divideBigInteger(big_int1,big_int2);
			temp = multiplyBigInteger(quotient,big_int2);
			remainder = subtractBigInteger(big_int1,temp);

			cout<<quotient<<" "<<remainder<<" "<<temp<<"\n";

			big_int1 = big_int2;
			
		}
		ans = big_int2;
	}

	return ans;
}

string divideBigInteger(string big_int1,string big_int2){
	string ans;

	int flag = 0,flag1 = 0,flag2 = 0;

	if(big_int1[0]=='-'){
		big_int1.erase(0,1);
		flag1 = 1;
	}
	
	if(big_int2[0]=='-'){
		big_int2.erase(0,1);
		flag2 = 1;
	}
	
	string i = "1",eol = "0",temp = "0";

	if((flag1 == 0&&flag2==0)||(flag1 == 1&&flag2==1))
		flag = 0;
	else
		flag = 1;

	if(big_int2.compare(eol)==0){
		return "0";
	}	
	else if(big_int1.size()<big_int2.size()){
		return "0";
	}
	else if(big_int1.compare(big_int2)==0){
		if(flag)
			ans = "-1";
		else
			ans = "1";
		return ans;
	}
	else{
		while(big_int1.compare(eol)!=0&&big_int1[0]!='-'){
			ans = addBigInteger(ans,i);
			big_int1 = subtractBigInteger(big_int1,big_int2);
			//cout<<"\nans: "<<ans<<" big_int1: "<<big_int1<<" big_int2 "<<big_int2<<"\n";
		}
	}
	//cout<<"\nans: "<<ans<<" big_int1: "<<big_int1<<" big_int2 "<<big_int2<<"\n";
	if(big_int1[0]=='-')
		ans = subtractBigInteger(ans,i);

	if(flag){
		ans = '-'+ans;
	}

	return ans;
}

string multiplyBigInteger(string big_int1,string big_int2){

	string ans;
	//cout<<"pos1\n";
	int flag = 0,flag1 = 0,flag2 = 0;

	if(big_int1[0]=='-'){
		big_int1.erase(0,1);
		flag1 = 1;
	}
	
	if(big_int2[0]=='-'){
		big_int2.erase(0,1);
		flag2 = 1;
	}
	
	string i = "1",eol = "-1",temp = "";

	if((flag1 == 0&&flag2==0)||(flag1 == 1&&flag2==1))
		flag = 0;
	else
		flag = 1;

	if(big_int1.size()<big_int2.size()){
		//cout<<"pos2\n";
		string lookUpTable[11];
		lookUpTable[0] = "0";
		lookUpTable[1] = big_int2;

		for(int i=2;i<11;i++){
			lookUpTable[i] = addBigInteger(lookUpTable[i-1],big_int2);
		}

		for(ll i=big_int1.size()-1;i>=0;i--){
			string t = lookUpTable[(int)(big_int1[i]-'0')]+temp;
			ans = addBigInteger(ans,t);
			temp += "0";
		}

		temp = "";

		
	}else{
		//cout<<"pos3\n";
		string lookUpTable[11];
		lookUpTable[0] = "0";
		lookUpTable[1] = big_int1;

		for(int i=2;i<11;i++){
			lookUpTable[i] = addBigInteger(lookUpTable[i-1],big_int1);
			//cout<<"pos4\n";
		}

		for(ll i=big_int2.size()-1;i>=0;i--){
			string t = lookUpTable[(int)(big_int2[i]-'0')]+temp;
			ans = addBigInteger(ans,t);
			temp += "0";
			//cout<<"pos5\n";
		}

		temp = "";
		
	}

	if(flag)
		ans = "-"+ans;

	return ans;
}

int checkMinusCompatibility(string big_int1,string big_int2){
	if(big_int2.size()>big_int1.size()){
		return 1;
	}else if(big_int2.size() < big_int1.size()){
		return 0;
	}else{
		for(ll i= 0;i< big_int1.size();i++){
			if((int)(big_int1[i]-'0')<(int)(big_int2[i]-'0'))
				return 1;
			else if((int)(big_int1[i]-'0')>(int)(big_int2[i]-'0')){
				return 0;
			}
		}
	}
	return 0;
}

string subtractBigInteger(string big_int1,string big_int2){
	
	int flag1 = 0,flag2 = 0 , flag = 0;

	string temp;

	if(big_int1[0]=='-')
		flag1 = 1; 

	if(big_int2[0]=='-')
		flag2 = 1;
	//cout<<flag1<<" "<<flag2<<"\n";
	if(flag2==1&&flag1==1){
		big_int2.erase(0,1);
		big_int1.erase(0,1);
		flag = checkMinusCompatibility(big_int1,big_int2);
		//cout<<"flag "<<flag<<"\n";
		if(flag == 1){
			temp = big_int1;
			big_int1 = big_int2;
			big_int2 = temp;
			flag = 0;
		}
	}else if(flag2==1&&flag1==0){
		big_int2.erase(0,1);
		return addBigInteger(big_int1,big_int2);
	}else if(flag2==0&&flag1==1){
		flag = 1;
		big_int1.erase(0,1);
		//cout<<"sdfs "<<big_int1.erase(0,1)<<"\n";
		string t = '-'+addBigInteger(big_int2,big_int1);
		return t;
	}else if(flag2==0&&flag1==0){
		//cout<<"\n"<<big_int1<<" "<<big_int2<<"\n";
		flag = checkMinusCompatibility(big_int1,big_int2);
		//cout<<"flag "<<flag<<"\n";
		if(flag == 1){
			temp = big_int1;
			big_int1 = big_int2;
			big_int2 = temp;
		}
	}


	int borrow = 0,diff = 0;
	int i = big_int1.size()-1;
	int j = big_int2.size()-1;
	string ans;
	
	//cout<<big_int1<<" "<<big_int2<<"\n";

	while(i>=0&&j>=0){
		if(((int)(big_int1[i]-'0')-borrow)>=(int)(big_int2[j]-'0')){
			diff = (int)(big_int1[i]-'0') - (int)(big_int2[j]-'0') - borrow;
			borrow = 0;
			ans = to_string(diff) + ans;	
		}else if((((int)big_int1[i]-'0')-borrow)<(int)(big_int2[j]-'0')){
			diff = (int)(big_int1[i]-'0') + 10 - (int)(big_int2[j]-'0') - borrow;
			borrow = 1;
			ans = to_string(diff) + ans;
		}
		i--;
		j--;
		//cout<<"ans "<<ans<<"\n";
	}

	//cout<<i<<" "<<j<<" "<<borrow<<" \n";

	if(i>=0&&j<=0){
		//cout<<"here\n";
		while(i>=0){
			//cout<<"here again\n";
			if((int)(big_int1[i]-'0') - borrow<0){
				diff = (int)(big_int1[i]-'0') + 10 - borrow;
				borrow = 1;
				ans = to_string(diff) + ans;
			}else{
				diff = (int)(big_int1[i]-'0') - borrow;
				borrow = 0;
				ans = to_string(diff) + ans;	
			}
			i--;
			//cout<<"ans1 "<<ans<<"\n";
		}
	}

	ll count = 0;

	for(ll i = 0;i<ans.size();i++){
		if(ans[i]!='0')
			break;

		if(ans[i]=='0'){
			ans.erase(i,1);
			i--;
		}
		//cout<<ans<<"\n";
	}

	if(ans.size()==0){
		ans = '0'; 
	}

	//reverse(ans.begin(),ans.end());

	if(flag==1){
		ans = '-'+ans;
	}

	return ans;
}

string addBigInteger(string big_int1,string big_int2){

	int flag1 = 0,flag2 = 0, flag = 0;

	if(big_int1[0]=='-')
		flag1 = 1; 

	if(big_int2[0]=='-')
		flag2 = 1;

	if(flag2==1&&flag1==1){
		flag = 1;
		big_int2.erase(0,1);
		big_int1.erase(0,1);
	}else if(flag2==1&&flag1==0){
		big_int2.erase(0,1);
		return subtractBigInteger(big_int1,big_int2);
	}else if(flag2==0&&flag1==1){
		big_int1.erase(0,1);
		return subtractBigInteger(big_int2,big_int1);
	}else if(flag2==0&&flag1==0){
		flag = 0;
	}

	int carry = 0,sum = 0;
	int i = big_int1.size()-1;
	int j = big_int2.size()-1;
	string ans;
	
	//cout<<big_int1<<" "<<big_int2<<"\n";

	while(i>=0&&j>=0){
		
		sum = (int)((int)(big_int1[i] - '0') + (int)((big_int2[j]) - '0')) + carry;
		if(sum >= 10){
			carry = 1;
			ans = to_string(sum%10)+ans;
		}else{
			carry = 0;
			ans = to_string(sum)+ans;
		}
		
		sum = 0;
		i--;
		j--;
		//cout<<"i "<<i<<" j "<<j<<"\n";
	}

	if(i>=0&&j<=0){
		while(i>=0){
			sum = (int)((int)(big_int1[i]-'0') + carry);
			if(sum >= 10){
			carry = 1;
			ans = to_string(sum%10)+ans;
			}else{
				carry = 0;
				ans = to_string(sum)+ans;
			}	
			i--;
			//cout<<"i "<<i<<" j "<<j<<"\n";	
		}
	}else if(i<=0&&j>=0){
		while(j>=0){
			sum = (int)((int)(big_int2[j]-'0') + carry);
			if(sum >= 10){
			carry = 1;
			ans = to_string(sum%10)+ans;
			}else{
				carry = 0;
				ans = to_string(sum)+ans;
			}
			j--;
			//cout<<"i "<<i<<" j "<<j<<"\n";	
		}
		
	}

	if(carry>0){
		ans = to_string(carry)+ans;
	}

	//reverse(ans.begin(),ans.end());
	if(flag)
		ans = '-'+ans;
	return ans;
}

int main(){

	string big_int1 , big_int2;
	ll t=0,b=1,query;
	cin>>t;
	while(t--){

		if(b)
			cin.ignore();
		getline(cin,big_int1);
		getline(cin,big_int2);
		cin>>query;

		//cout<<big_int1<<" "<<big_int2<<" "<<query<<"\n";

		if(query==1){
			cout<<addBigInteger(big_int1 , big_int2)<<"\n";
		}else if(query==2){
			cout<<subtractBigInteger(big_int1 , big_int2)<<"\n";
		}else if(query==3){
			cout<<multiplyBigInteger(big_int1 , big_int2)<<"\n";
		}else if(query==4){
			cout<<divideBigInteger(big_int1 , big_int2)<<"\n";
		}else if(query==5){
			cout<<gcdBigInteger(big_int1 , big_int2)<<"\n";
		}
	}
	
	/*
	cout<<"Result Addition: "<<addBigInteger(big_int1 , big_int2)<<"\n";
	cout<<"Result Subtract: "<<subtractBigInteger(big_int1 , big_int2)<<"\n";
	cout<<"Result Multiply: "<<multiplyBigInteger(big_int1 , big_int2)<<"\n";
	cout<<"Result Divide: "<<divideBigInteger(big_int1 , big_int2)<<"\n";
	cout<<"Result GCD: "<<gcdBigInteger(big_int1 , big_int2)<<"\n";
	*/
	return 0;
}
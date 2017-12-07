//Author - Siddharth Jain
//Playfair Encryption Cipher


#include <iostream>

using namespace std;




int main()
{
	int *x = new int[26];   //for storing row no. of each character of the key in the 5x5 matrix.
	int *y = new int[26];	//for storing column no. of each character of the key in the 5x5 matrix.
	int *enc;
	char *enccip;
	int (*a)[5] = new int[5][5];	//5x5 matrix.
	string key;
	string pt;
	char alp[26]= {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};	//utility array to convert the chars into decimal number.
	int *intpt, *encpt;	//intpt is the array that will contain the plaintext converted to decimal.
	int *intkey;	//intkey is the array that will contain the key in decimal format.
	int i,j,k,m,n;
	int *arr = new int[26];
	for(i=0;i<26;i++){
		arr[i]=0;
		x[i]=0;
		y[i]=0;
	}
	cin>>key;	//input key.
	intkey = new int[key.length()];		
	for(i=0;i<key.length();i++){	//convert key in decimal format.
		intkey[i] = key[i]-97;
	}
	j=0;
	for(k=0;k<key.length();k++){	//storing the key characters in the matrix.
		if(arr[intkey[k]] == 0){
			if((intkey[k] == 8)&&(arr[9]==0)){ 
				m = j/5;
				n = (j)%5;
				arr[8]++;
				j++;
			}
			else if(intkey[k] == 8){	//handling the cases of i and j individually.
				a[m][n] = 809;
				arr[8]++;
			}
			else if((intkey[k] == 9)&&(arr[8]==0)){
				m = j/5;
				n = (j)%5;
				arr[9]++;
				j++;
			}
			else if(intkey[k] == 9){
				a[m][n] = 809;
				arr[9]++;
			}
			else{
				a[j/5][(j)%5] = intkey[k];
				j++;
				arr[intkey[k]]++;
			}
			x[intkey[k]] = (j-1)/5;
			y[intkey[k]] = (j-1)%5;
		}
	}
	for(i=0;i<26;i++){	//adding all the characters in the matrix that were not present in the key.
		if(arr[i] == 0){
			if((i==8)&&(arr[9]==0)){
				a[j/5][(j)%5] = i;
				arr[8]++;
				m=j/5;
				n=j%5;
				j++;

			}
			else if(i==8){
				a[m][n] = 809;
				arr[8]++;
			}
			else if(i==9){
				a[m][n] = 809;
				arr[9]++;
			}
			else{
				a[j/5][(j)%5] = i;
				j++;
				arr[i]++;
				if(i == 8){
					m = j/5;
					n = (j)%5;
					arr[8]++;
					j++;
				}
			}
			x[i] = (j-1)/5;
			y[i] = (j-1)%5;
		}
	}
	cin>>pt;
	intpt = new int[pt.length()];
	for(i=0;i<pt.length();i++){
		intpt[i]=pt[i]-'a';
	}
	encpt = new int[pt.length()*2];
	for(i=0;i<pt.length()*2;i++){
		encpt[i] = 0;
	}
	k=1;
	i=1;
	while(i<pt.length()){	//converting the plaintext into 2 character format.
		if(intpt[i]!=intpt[i-1]){
			encpt[k-1] = intpt[i-1];
			encpt[k] = intpt[i];
			i++;
		}
		else{
			encpt[k-1] = intpt[i-1];
			encpt[k] = 23;
		}
		k+=2;
		i++;
	}
	enc = new int[k-1];
	i=1;
	while(i<k-1){	//encrypting the modified plaintext according to the matrix.
		if(x[encpt[i]]==x[encpt[i-1]]){
			enc[i-1]=a[x[encpt[i]]][y[encpt[i-1]]+1];
			enc[i]=a[x[encpt[i]]][y[encpt[i]]+1];
		}
		else if(y[encpt[i]]==y[encpt[i-1]]){
			enc[i-1]=a[x[encpt[i-1]]+1][y[encpt[i]]];
			enc[i]=a[x[encpt[i]]+1][y[encpt[i]]];
		}
		else{
			enc[i-1]=a[x[encpt[i-1]]][y[encpt[i]]];
			enc[i]=a[x[encpt[i]]][y[encpt[i-1]]];
		}
		i+=2;
	}

	enccip = new char[k-1];
	for(i=0;i<k-1;i++){	//printing the encrypted text.
		if(enc[i]!=809){
			enccip[i]=alp[enc[i]];
			cout<<enccip[i]<<" ";
		}
		else{
			enccip[i]='i';
			cout<<enccip[i]<<" ";
		}
	}
	cout<<endl;
}
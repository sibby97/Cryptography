//Author - Siddharth Jain
//Substitution and Permutation Network Encryption



//Input of plaintext will be in binary format.
//Each block contains of 16 bits of plaintext.
//Key is also taken in as input.
//There are 5 rounds.
//Each round contains a 16 bit round key.





#include <iostream>
#include <cstdlib>

using namespace std;


void sbox(int *a,int l,int r){	//The code for S-Box.
//I have chosen the function such that the output of the box is inverted input(0s and 1s are inverted).
	int i;
	for(i=l;i<r;i++){
		a[i] = !a[i];
	}
}

void pbox(int *a){	//The code for Permutation Box.
//I have chosen the function to include rand function to show the permutations among the 4bit S-box outputs.
//The choice of rand function was solely to provide the implementation of permuting the 4bit S-box outputs.
//The rand function cannot be used in real life as the decryption algorithm will become impossible.
//Here one small block of 4 bits is permuted.

	int *temp = new int[4];	
	int i,j;
	int r;
	for(i=0;i<4;i++){
		r=(rand()%(4-i));
		for(j=0;j<4;j++){
			temp[j]=a[j+i*4];
		}
		for(j=0;j<4;j++){
			a[j+i*4]=a[j+i*r];
		}
		for(j=0;j<4;j++){
			a[j+i*r]=temp[j];
		}
	}
}

void roundkey(int *a,int *b, int l, int r){	//Function to calculate the roundkey from the key.
	int i;
	for(i=l;i<=r;i++){
		a[i-l]=b[l];
	}
}

int xorone(int a,int b){	//Function to calculate single bit xor.
	if((a&&b)||(!a&&!b))	return 0;
	else	return 1;
}

int main(){
	int i,j,l,r;
	int *pt = new int[16];		//binary input
	int *key = new int[32];		//binary key
	int *rkey = new int[16];   	//round key
	for(i=0;i<16;i++){
		cin>>pt[i];
	}
	for(i=0;i<32;i++){
		cin>>key[i];
	}
	l=0;
	r=15;
	for(i=0;i<4;i++){			
		roundkey(rkey,key,l,r);
		for(j=0;j<16;j++){
			pt[j]=xorone(pt[j],rkey[j]);
		}
		for(j=0;j<4;j++){
			sbox(pt,l+j*4,l+4+j*4);
		}
		pbox(pt);


		l+=4;
		r+=4;
	}
	//last round
	roundkey(rkey,key,l,r);
	for(j=0;j<16;j++){
		pt[j]=xorone(pt[j],rkey[j]);
	}
	for(j=0;j<4;j++){
		sbox(pt,l+j*4,l+4+j*4);
	}
	for(i=0;i<16;i++){
		cout<<pt[i]<<" ";
	}
	cout<<endl;
}

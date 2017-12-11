//Author - Siddharth Jain
//Triple DES


#include <iostream>
#include <math.h>



using namespace std;

/*
int xor(int a,int b){	//utility function to perform xor operation between two bits.
	if((a&&b)||((!a)&&(!b))){
		return 0;
	}
	else return 1;
}
*/


void p(int *a){	//for intial permutation, left shift is being used.
	int i,temp;
	int n=64;
	for(i=0;i<n-1;i++){
		temp=a[i];
		a[i]=a[(i+1)%n];
		a[(i+1)%n]=temp;
	}
}


void invp(int *a){	//for reverse permutation right shift is being used.
	int i,temp;
	int n = 64;
	for(i=n-1;i>0;i--){
		temp=a[i];
		a[i]=a[(i+n-1)%n];
		a[(i+n-1)%n]=temp;
	}
} 


void straightp(int *a){	//for straight permutation used in the function f, left shift is being used.
	int i,temp;
	int n=32;
	for(i=0;i<n-1;i++){
		temp=a[i];
		a[i]=a[(i+1)%n];
		a[(i+1)%n]=temp;
	}
}

int *compressbit(int *r){	//compresses 56 bit key to 48 bit key

	int *a = new int[48];
	int i,j;
	int n=48;
	for(i=0;i<8;i++){
		a[i*6]=r[i*7]^r[i*7+1];
		a[i*6+1]=r[i*7+2];
		a[i*6+2]=r[i*7+3];
		a[i*6+3]=r[i*7+4];
		a[i*6+4]=r[i*7+5];
		a[i*6+5]=r[i*7+6];
	}
	//cout<<"compressbit(): a"<<endl;
	//for(i=0;i<48;i++){
	//	cout<<a[i];
	//}
	//cout<<endl;
	return a;
}

void keyp(int *a){	//for the first key permutation, circular left shift is being used.  (Permuted Choice 1)[PC-1]
	int i,temp;
	int n=56;
	for(i=0;i<n-1;i++){
		temp=a[i];
		a[i]=a[(i+1)%n];
		a[(i+1)%n]=temp;
	}
}

int *pc2(int *a){		//Permuted Choice 2[PC-2] - circular left shift
	int i,temp;
	int n=56;
	int *b = new int[n];
	int *c = new int[48];
	for(i=0;i<n-1;i++){
		b[i] = a[i];
	}
	for(i=0;i<n-1;i++){
		temp=b[i];
		b[i]=b[(i+1)%n];
		b[(i+1)%n]=temp;
	}
	//cout<<"pc2(): b"<<endl;
	//for(i=0;i<56;i++){
	//	cout<<b[i];
	//}
	//cout<<endl;
	c = compressbit(b);
	//cout<<"pc2(): c"<<endl;
	//for(i=0;i<48;i++){
	//	cout<<c[i];
	//}
	//cout<<endl;
	return c;
}

int *roundkey(int *a){		//Round key generation
	int i,temp;
	int n = 28;
	int *c = new int[48];
	for(i=0;i<n-1;i++){		//circular left shift of the first 28 bits
		temp=a[i];
		a[i]=a[(i+1)%n];
		a[(i+1)%n]=temp;
	}
	for(i=n;i<2*n-1;i++){		//circular left shift of the last 28 bits
		temp=a[i];
		a[i]=a[(i+1)%n];
		a[(i+1)%n]=temp;
	} 
	//cout<<"roundkey(): a"<<endl;
	//for(i=0;i<56;i++){
	//	cout<<a[i];
	//}
	//cout<<endl;
	c = pc2(a);
	//cout<<"roundkey(): c"<<endl;
	//for(i=0;i<48;i++){
	//	cout<<c[i];
	//}
	//cout<<endl;
	return c;
} 


int *expandbit(int *r){	//r is 32 bits

	int *a = new int[48];
	int i,j;
	int n=48;
	for(i=0;i<8;i++){
		a[(((i-1)*6+n)%n)+5]=r[i*4];
		a[i*6+1]=r[i*4];
		a[i*6+2]=r[i*4+1];
		a[i*6+3]=r[i*4+2];
		a[i*6+4]=r[i*4+3];
		a[(((i+1)*6)%n)]=r[i*4+3];
	}
	return a;
}

int tobinary(int x){
	int i,bin;
	i=1;
	bin=0;
	while(x){
		bin+=(x%2)*i;
		i *=10;
		x /= 2;
	}
	return bin;
}


int todecimal(int x){
	int i,dec;
	i=0;
	dec=0;
	while(x){
		dec+=(x%10)*pow(2,i);
		x/=10;
		i++;
	}
	return dec;

}


int sbox(int *a,int l,int r){
	int (*arr)[16]=new int[4][16];
	int i,j;
	for(i=0;i<4;i++){
		for(j=0;j<16;j++){
			arr[i][j]=tobinary(i^j);	//xor of i row number and column number.
		}
	}
	i=todecimal(a[l]*10+a[r]);
	j=todecimal(a[l+1]*1000+a[l+2]*100+a[r-2]*10+a[r-1]);
	return arr[i][j];
}

int *f(int *r, int *rk){
	int *nr=new int[48];
	int i;
	//cout<<"f(): before expanding r"<<endl;
	//for(i=0;i<32;i++){
	//	cout<<r[i];
	//}
	//cout<<endl;
	nr=expandbit(r);
	//cout<<"f(): after expanding r:nr"<<endl;
	//for(i=0;i<48;i++){
	//	cout<<nr[i];
	//}
	//cout<<endl;
	int temp,j;
	int *ret = new int[32];
	for(i=0;i<48;i++){
		nr[i]=nr[i]^rk[i];
	}
	for(i=0;i<8;i++){
		temp=sbox(nr,i*6,i*6+5);
		j=0;
		while(temp){
			ret[i*4+(3-j)]=temp%10;
			temp/=10;
			j++;
		}
	}
	straightp(ret);		//useinv
	return ret;
}

void round(int *a,int *rk){

	int i,j;
	int temp;
	int *r=new int[32];
	for(i=0;i<32;i++){		//swap the left 32 bits with the right 32 bits
		temp=a[i];
		a[i]=a[i+32];
		a[i+32]=temp;
		r[i]=a[i];
	}
	r=f(r,rk);
	for(i=0;i<32;i++){
		a[i+32]=a[i+32]^r[i];
	}
}

void decryptround(int *a,int *rk){

	int i,j;
	int temp;
	int *l=new int[32];
	for(i=0;i<32;i++){
		temp=a[i];
		a[i]=a[i+32];
		a[i+32]=temp;
		l[i]=a[i+32];
	}
	l=f(l,rk);
	for(i=0;i<32;i++){
		a[i]=a[i]^l[i];
	}
}


void decryptdes(int *a,int *k){
	int i,j;
	int (*rk)[48] = new int[16][48];
	int *temp = new int[48];
	p(a);
	keyp(k);
	for(i=0;i<16;i++){
		temp=roundkey(k);
		for(j=0;j<48;j++){
			rk[i][j]=temp[j];
		}
	}
	for(i=15;i>=0;i--){
		//cout<<"decryptdes(): rk for "<<i<<endl;
		for(j=0;j<48;j++){
			temp[j] = rk[i][j];
		}
		decryptround(a,temp);
		/*cout<<"decryptdes(): cipher at round "<<i<<endl;
		cout<<"key "<<i<<endl;
		for(j=0;j<48;j++){
			cout<<temp[j];
		}
		cout<<endl;
		cout<<"ciphertext "<<i<<endl;
		for(j=0;j<64;j++){
			cout<<a[j];
		}
		cout<<endl;*/
	}
	//for(i=0;i<16;i++){
	//	decryptround(a,rk[i]);
	//}
	invp(a);
}

void des(int *a,int *k){	//k is 56 bits.

	int i,j;
	int *rk = new int[48];
	p(a);
	keyp(k);
	cout<<endl;
	for(i=0;i<16;i++){
		rk = roundkey(k);
		//cout<<"des(): rk "<<i<<endl;
		//for(j=0;j<48;j++){
		//	cout<<rk[j];
		//}
		//cout<<endl;
		round(a,rk);
		/*cout<<"des(): cipher ar round "<<i<<endl;
		cout<<"key"<<endl;
		for(j=0;j<48;j++){
			cout<<rk[j];
		}
		cout<<endl;
		cout<<"ciphertext"<<endl;
		for(j=0;j<64;j++){
			cout<<a[j];
		}
		cout<<endl;*/
	}
	invp(a);
}

void tripledes(int *a, int *k1, int *k2){
	int *k1_1 = new int[56];
	int i;
	for(i=0;i<56;i++){
		k1_1[i] = k1[i];
	}
	des(a, k1);
	decryptdes(a, k2);
	des(a, k1_1);
}

void decrypttripledes(int *a, int *k1, int *k2){
	int *k1_1 = new int[56];
	int i;
	for(i=0;i<56;i++){
		k1_1[i] = k1[i];
	}
	decryptdes(a, k1);
	des(a, k2);
	decryptdes(a, k1_1);
}

int main(){

	int *pt = new int[64];	//64 bit binary plaintext is being encrypted.
	int i,j;	
	int *k1= new int[56];
	int *k2= new int[56];
	int *k1_1 = new int[56];
	int *k2_1 = new int[56];
	char zero = '0';
	string a1, a2,a3;
	cin>>a1>>a2>>a3;
	for (i=0;i<64;i++){
		pt[i] = a1[i] - zero;
	}
	for(i=0;i<56;i++){
		k1[i] = a2[i] - zero;
		k2[i] = a3[i] - zero;
		k1_1[i] = k1[i];
		k2_1[i] = k2[i];
	}
	//for(i=0;i<56;i++){
	//	cin>>k2[i];
	//}
	tripledes(pt,k1,k2);
	decrypttripledes(pt,k1_1,k2_1);
	//des(pt,k1);
	cout<<"Cipher Text"<<endl;
	for(i=0;i<64;i++){
		cout<<pt[i];
	}
	cout<<endl;
}
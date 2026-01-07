// Lab 1.2: WAP to find Fibonacci sequence of given term.
#include <iostream>
#include <stdlib.h>
using namespace std;
int fibonacci(int n)
{
    if(n<=1)
        return n;
    else
        return fibonacci(n-2)+fibonacci(n-1);
}
int main()
{
    int n;
    cout<<"Enter nth term of Fibonacci sequence : ";
    cin>>n;
    if(n<=0)
		cout<<"Invalid input";
	else
	{
        cout<<"Fibonacci Sequence upto "<<n<<"th term :"<<endl;
		for(int i=0;i<n;i++)
			cout<<fibonacci(i)<<"\t";
	}
    return 0;
}
//Header Files
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>  

using namespace std;
#include "ipgen.h"


int main()
{
	
	IpCreate a;
	int* temp;
	
	int i;

	srand (time(NULL));
	for(int i=0; i<9000; i++)
	{
		temp=a.Generate();
		for(int i=0; i<4; i++)
		{
		cout<<temp[i]<<'.';
		}
		cout<<endl;
	}

	cin>>i;
} 
//Function implementation

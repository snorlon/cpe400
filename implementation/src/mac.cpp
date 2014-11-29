#include "mac.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>

mac::mac()
{
    //default all of the values to 0.0.0.0
    strcpy_s(address,"empty");

}

mac::~mac()
{
    //what do?

	//Maybe set these to impossible values?
    strcpy_s(address,"NULL");
}

bool mac::generate()
{
    //empty for now
	int checksum;
	char buffer [30];
	address[0]='\0';
	//Replace current mac with new mac;
	for(int i=0;i<6;i++)
	{
		
		checksum=rand() % 256;
		_itoa_s (checksum,buffer,16);
		if (checksum<16)
		{
			strcat_s(address,"0");
		}
		strcat_s(address,buffer);
		if (i<5)
		{
		strcat_s(address,"-");
		}

	}

	//Not sure what to use this for
    return false;
}

bool mac::equal(mac &address2)
{
    //compare to see if equal
  if(strcmp(address,address2.address)==0)
  {
	  return true;
  }
  else 
  {
	  return false;
  }

}

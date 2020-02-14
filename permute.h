/* 
Warren Ball
permute.h

These functions allow you have all the permutations of a given string

-Permute with just a string parameter will just call the other permute

-The other permute swaps the current lowest letter with every other leter in the string, prints it out, then switches it
back, this ensures every letter visits every placement in the string

date of creation - 2/3/20 - 2/13/20

*/
#include <string>
#include <iostream>
#include <queue>
using namespace std;


void permute( const string &str, int low, int high )
{
	//we create a temporary string because we don't wish to manipute the orignal string
	string temp = str;	

	if(low == high)//when a letter makes its way to the end, it'll print the entire word
	{
		cout<<temp<<endl;
	}
	else
	{
		for(int i = low; i <= high; i++)
		{
			swap(temp[low],temp[i]);

			permute(temp, low+1, high);

			swap(temp[low],temp[i]);
		}

	}

}


void permute(const string &str)
{


	permute(str, 0, str.length() - 1);
}





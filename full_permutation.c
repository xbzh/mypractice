/***********************************
 *generate string's full permutation
 **********************************/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void swap(char *a,char *b)
{
	char c = *a;
	*a = *b;
	*b = c;
}

bool can_swap(char *str,int beg,int end)
{
	bool bSwap = true;
	for(int i = beg; i < end; ++i)
	{
		if(str[i] == str[end])
		{
			bSwap = false;
			break;
		}	
	}
	return bSwap;
}

void full_permutation_core(char *str, int len, int idx)
{
	if(idx == len)
		printf("%s\n",str);

	for(int i = idx; i < len; ++i)
	{
		if(can_swap(str,idx,i))
		{
			swap(&str[i],&str[idx]);
			full_permutation_core(str,len,idx+1);
			swap(&str[i],&str[idx]);
		}
	}
}

void full_permutation(char *str)
{
	if(str == NULL)
		return;
	full_permutation_core(str,strlen(str),0);
}

int main()
{
	char str[5] ="abb";
	full_permutation(str);
	return 0;
}

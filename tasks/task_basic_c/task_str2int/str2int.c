#include "str2int.h"
#include <assert.h>
#include "stdio.h"

int str2int(const char* str)
{
	int len=0;
	int is_negative=0;
	int start=0;
	int res=0;

	while(str[len]!='\0'){
		len++;
	}

	if(str[0]=='-'){
		is_negative=1;
		start++;
	}else if(str[0]=='+'){
		start++;
	}

	while(str[start]!='\0'){
		res+=res*10 + str[len]+'0';
	}

	return res;

}

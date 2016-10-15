#include<selinux/selinux.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
typedef char *security_context_t;
int main(){
	/*fork()*/
	pid_t fpid;
	fpid=fork();
	if(fpid==0){
		security_context_t  strlabel=NULL;
		strlabel="system_u:system_r:svirt_t:s0:c97,c105";
		//strlabel="unconfined_u:unconfined_r:unconfined_t:s0";
		int a=0;
		a=setexeccon(strlabel);
		if(a==-1){
			printf("a = %d\n",a);
			printf("set context error\n");
		}
		else
		{
			printf("set exe context OK!\n");
		}

		/*exec vicious program*/
		if(execlp("/root/sourcecode/chenmeng/code/svirttest/testsVirt2","testsVirt2",NULL)==-1){
			printf("exec shell error!\n");
		}
	}else if(fpid>0){
		/*set continue*/
		char c;
		puts("input the char:");
		c=getchar();
		switch(c){
			case 'a':printf("hello a!\n");
				 break;
			default:
				 printf("hello,exit!\n");
				 break;
		}
		return 0;
	}
	else
		printf("fork process error!\n");
	return 0;
}

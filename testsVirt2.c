#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(){
	FILE *fp;
	pid_t fpid;
	char *currcon;
	getcon(&currcon);
	printf("I am secope process! my label is :%s\n",currcon);
	printf("---------------------------------------------------------------------\n");
	free(currcon);

	fpid=fork();

	if(fpid==0){
		//sleep(2);
		char *childcon;
		getcon(&childcon);
		printf("I am child of secope process! my label is :%s\n",childcon);
		free(childcon);
		printf("now I want to attack HOST file!\n");
		fp=fopen("/etc/selinux/targeted/policy/policy.29","r+");
		if(fp==NULL)
			printf("open policy file failed!\n");
		else{
			printf("open policy succeed!\n");
			fclose(fp);
		}
		printf("now I want to attack VM  file!\n");
		fp=fopen("/var/lib/libvirt/images/win7.qcow2","rb");
		if(fp==NULL)
			printf("open win7.qcow2  failed!\n");
		else{
			printf("open win7.qcow2  succeed!\n");
			fclose(fp);
		}
		printf("---------------------------------------------------------------------\n");
	}
	else if(fpid>0)
	{
		sleep(2);
		printf("I want to execute shell command！\n");
		if(execl("/usr/sbin/semodule","semodule","-l",NULL)==-1){
			printf("exec semodule failed!\n");
		}
	}
	else
		printf("fork process error!\n");

}

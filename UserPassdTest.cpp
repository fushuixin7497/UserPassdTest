#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <shadow.h>
#include <errno.h>
#include <crypt.h>

void get_salt(char *salt,char *passwd)
{
	int i,j;
	for(i=0,j=0;passwd[i] && j != 3;++i)
	{
		if(passwd[i] == '$')
		{
			++j;
		}
	}
	strncpy(salt,passwd,i-1);
}


int SignIn(std::string &strUser, std::string &strPasswd)
{
	struct spwd *sp = NULL;
	const char *passwd = strPasswd.c_str();
	char salt[512]={0};
	printf("username = [%s], password = [%s]\n",strUser.c_str(),strPasswd.c_str());
	if((sp=getspnam(strUser.c_str())) == NULL)
	{
		printf("getspnam failed\n");
		return -1;
	}   
	printf("1. sp->sp_pwdp=%s\n",sp->sp_pwdp);
	get_salt(salt,sp->sp_pwdp);
	const char* crypt_passwd = crypt(passwd,salt);
	if(crypt_passwd == NULL || sp->sp_pwdp == NULL)
	{
		printf("crypt_passwd or sp->sp_pwdp is NULL\n");
		return -1;
	}
	printf("crypt_passwd=%s\n",crypt_passwd);
	int nSize = strlen(sp->sp_pwdp);
	int nSize1 = strlen(crypt_passwd);
	printf("%d--%d\n",nSize,nSize1);
	if(strncmp(sp->sp_pwdp,crypt_passwd,nSize1) == 0)
	{
		printf("strcmp succeed\n");
		return 0;
	}    
	else
	{
		printf("sp->sp_pwdp=%s\n",sp->sp_pwdp);
		printf("strcmp failed\n");
		return -1;
	} 
}

int main(int argc,char **argv)
{
	if(argc !=3)
		return -1;
	printf("username=%s\n",argv[1]);
	printf("passwrd=%s\n",argv[2]);
	std::string strUsr(argv[1]);
	std::string strPsd(argv[2]);
	SignIn(strUsr,strPsd);
	
	return 0;
}
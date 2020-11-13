#include "func.h"
void trim_space(char *src)//排除每行前的空格，并将行中的其他空格类字符转换为空格
{
	int fast_index,last_index;
	for (fast_index = 0,last_index=-1; src[fast_index] !=0; fast_index++)
	{
		if (!isspace(src[fast_index]))//不是符号
		{
			src[++last_index]=src[fast_index];
		}else
		{
			if (last_index!=-1&&!isspace(src[last_index]))
			{
				src[++last_index]=' ';
			}
		}
	}
	src[++last_index]=0;
}

void system_init(char *config ,pACCOUNT *pphead_acc ,pSTU *pphead_stu)
{
	FILE *fp_config,*fp_account,*fp_stu;
	char line[LINE_LEN];//存储按行读取的路径名，用fgets
	pACCOUNT pnew,pcur,ppre;
	pSTU pnew_stu,pcur_stu,ppre_stu;

	fp_config=fopen(config,"r");
	if (NULL==fp_config)
	{
		printf("open config fail!\n");
		system("pause");
		exit(1);//0代表正常结束，非零代表异常
	}
	memset(line,0,sizeof(line));
	fflush(stdin);
	fgets(line,LINE_LEN,fp_config);
	line[strlen(line)-1]=0;
	//获取config中账户文件路径字符串

	fp_account=fopen(line,"r");
	if (NULL==fp_account)
	{
		printf("open account fail!\n");
		system("pause");
		exit(1);
	}
	while (memset(line,0,sizeof(line)),fgets(line,LINE_LEN,fp_account)!=NULL)//将账户信息有序导入*pphead_acc
	{
		pnew=(pACCOUNT)calloc(1,sizeof(ACCOUNT));//申请空pnew来承接line内容
		sscanf(line,"%s%s%d",pnew->m_name,pnew->m_passwd,&pnew->m_role);
		pcur=*pphead_acc;
		ppre=NULL;
		while(pcur && strcmp(pcur->m_name,pnew->m_name)<0)
		{
			ppre=pcur;
			pcur=pcur->m_next;
		}
		if(NULL==ppre)
		{
			pnew->m_next=*pphead_acc;
			*pphead_acc=pnew;
		}else
		{
			pnew->m_next=pcur;
			ppre->m_next=pnew;
		}
	}
	fclose(fp_account);
	//将账户信息读入

	memset(line,0,sizeof(line));
	fgets(line,LINE_LEN,fp_config);//fgets:按行读取
	line[strlen(line)-1]=0;
	fclose(fp_config);
	//获取用户文件路径字符串

	fp_stu=fopen(line,"r");
	if (NULL==fp_stu)
	{
		printf("open stu fail!\n");
		system("pause");
		exit(1);
	}
	while (memset(line,0,sizeof(line)),fgets(line,LINE_LEN,fp_stu)!=NULL)//将账户信息有序导入*pphead_stu
	{
		pnew_stu=(pSTU)calloc(1,sizeof(STU));
		trim_space(line);

		sscanf(line,"%d%s %c%lf%lf%lf%lf%lf",&pnew_stu->m_id,pnew_stu ->m_name,
			   &pnew_stu->m_gender, &pnew_stu->m_scores[0],
			   &pnew_stu->m_scores[1],&pnew_stu->m_scores[2],
			   &pnew_stu->m_scores[3],&pnew_stu->m_scores[4]);
		pcur_stu=*pphead_stu;
		ppre_stu=NULL;
		while (pcur_stu && pcur_stu->m_id <pnew_stu->m_id)
		{
			ppre_stu=pcur_stu;
			pcur_stu=pcur_stu->m_next;
		}
		if (NULL==ppre_stu)
		{
			pnew_stu->m_next=*pphead_stu;
			*pphead_stu=pnew_stu;
		}else
		{
			pnew_stu->m_next=pcur_stu;
			ppre_stu->m_next=pnew_stu;
		}
	}
	fclose(fp_stu);
	//将用户信息读入
}

int role_confirm(pACCOUNT phead_acc ,char *name)
{
	int cnt=0;//count
	char ch;
	int index=0;//密码数组下标
	pACCOUNT pcur;
	char usr_name[NAME_LEN];
	char usr_passwd[PWD_LEN];

	/*while (cnt<CONFIRM_CNT)
	{*/
		system("cls");
		printf("usr_name : ");
		fflush(stdin);
		fgets(usr_name,NAME_LEN,stdin);//从屏幕输入name
		usr_name[strlen(usr_name)-1]=0;
		strcpy(name,usr_name);

		printf("ust_pwd : ");
		fflush(stdin);
		for (index = 0; index < PWD_LEN; index++)
		{
			ch=getch();
			if('\r'==ch)
			{
				break;
			}
			if ('\b'==ch)
			{
				printf("\b \b");
				usr_passwd[--index]=0;
				--index;
				continue;
			}
			usr_passwd[index]=ch;
			printf("*");
		}
		usr_passwd[index]=0;
		//1,2进入循环.并输入用户名和密码

		pcur=phead_acc;
		while (pcur)//循环匹配账户信息
		{
			if (0==strcmp(usr_name,pcur->m_name) && 0==strcmp(usr_passwd,pcur->m_passwd))
			{
				break;
			}
			pcur=pcur->m_next;
		}
		if (pcur)
		{
			return pcur->m_role;
		}
	//	else
	//	{
	//		cnt++;
	//	}
	//}//while(cnt<CONFIRM_CNT)
	return -1;
}

int show_system_menu(int role)
{
	int select;
	int flag=0;//while判断标记
	while (!flag)//1
	{
		system("cls");//清屏
		if (1==role)//admin
		{
			printf("%s\n",M1);
			printf("%s\n",M2);
			printf("%s\n",M3);
			printf("%s\n",M4);
			printf("%s\n",M5);
			printf("%s\n",M6);
			printf("%s\n",M7);
			printf("%s\n",M8);
			printf("%s\n",M9);
		}else//usr
		{
			printf("%s\n",M1);
			printf("%s\n",M9);
		}
		printf("Please  select  num : ");
		fflush(stdin);
		select=getchar();
		if (1==role)//admin跳转界面条件
		{
			if ('1'<=select && '9'>=select)
			{
				flag=1;
			}
		}else//usr
		{
			if ('1'==select||'9'==select)
			{
				flag=1;
			}
		}
	}//while(!flag)
	return select-'0';//转数字
}

void link_save_to_file(pSTU phead ,char *dest)
{
	char buf[1024];
	pSTU ppre=NULL,pcur=phead;
	FILE *fp_out=fopen(dest,"w");
	if (NULL==fp_out)
	{
		printf("open fail!\n");
		return;
	}
	while (pcur)
	{
		memset(buf,0,sizeof(buf));
		sprintf(buf,"%03d  %-15s%-3c%-8.2f%-8.2f%-8.2f%-8.2f%-8.2f\n",
			   pcur->m_id, pcur->m_name, pcur->m_gender,
			   pcur->m_scores[0],pcur->m_scores[1],pcur->m_scores[2],
			   pcur->m_scores[3],pcur->m_scores[4]);
		puts(buf);
		fputs(buf,fp_out);
		ppre=pcur;
		pcur=pcur->m_next;
		//free(ppre);
	}
	fclose(fp_out);
}

void link_save_to_file_acc(pACCOUNT phead ,char *dest)
{
	char buf[1024];
	pACCOUNT ppre=NULL,pcur=phead;
	FILE *fp_out=fopen(dest,"w");
	if (NULL==fp_out)
	{
		printf("open fail!\n");
		return ;
	}
	while (pcur)
	{
		memset(buf,0,sizeof(buf));
		sprintf(buf,"%-25s%-15s%-3d\n",pcur->m_name,
			   pcur->m_passwd,pcur->m_role );//将内容写入buf
		puts(buf);
		fputs(buf,fp_out);
		ppre=pcur;
		pcur=pcur->m_next;
		//free(ppre);
	}
	fclose(fp_out);
}
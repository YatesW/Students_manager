#include "func.h"
int main(int argc ,char *argv[])
{
	pACCOUNT account_list=NULL;
	pACCOUNT pnew_acc=NULL;
	pACCOUNT pcur_acc=NULL,ppre_acc=NULL;
	pSTU stu_list=NULL;
	pSTU pcur=NULL,ppre=NULL;
	pSTU pnew_stu=NULL;
	int role;
	int select;//菜单界面选择的编号
	char input_name[NAME_LEN];
	char delete_name[20];
	char modify_name[20];
	char input_information[1024];
	char partion;
	char myName[NAME_LEN];
	int input_id;
	int modify_id;
	int delete_id;
	int input_role;
	system_init(argv[1],&account_list,&stu_list);//account_list,stu_list对应stu_account.txt stu_info.txt
	if ((role=role_confirm(account_list,myName))==-1)
	{
		printf("\n");
		printf("fail to login!\n");
		system("pause");
		return 0;
	}
Label1:while (system("cls"),(select=show_system_menu(role))!=9)//选择服务
	  {
		  if (1==role)
		  {
			  switch(select)
			  {
			  case 1://查找学生信息
			  {
				  system("cls");
				  printf("0.search all\n");
				  printf("1.search by name\n");
				  printf("2.search by id\n");
				  printf("3.return\n");//查找的子功能
				  while (fflush(stdin),(partion=getchar())!='3')
				  {
					  system("cls");
					  fflush(stdin);
					  switch(partion-'0')//char->int
					  {
					  case 0://search all
						  {
							  pcur=stu_list;
							  printf("ID                     NAME          SEX Chinese  Math   English   Art    P.E\n");
							  while (pcur)
							  {								  
								  printf("%03d%25s%10c%8.2f%8.2f%8.2f%8.2f%8.2f\n",
									     pcur->m_id,pcur->m_name,pcur->m_gender,
										 pcur->m_scores[0],pcur->m_scores[1],
										 pcur->m_scores[2],pcur->m_scores[3],
										 pcur->m_scores[4]);
								  pcur=pcur->m_next;
							  }
							  system("pause");
							  goto Label1;
							  break;
						  }
					  case 1://by name
						  {
							  printf("Please input a name :\n");
							  fflush(stdin);
							  fflush(stdout);
							  gets(input_name);
							  system("cls");
							  pcur=stu_list;
							  while (pcur)
							  {
								  if (strcpy(pcur->m_name,input_name))//strcpy成功返回*to
								  {
									  break;
								  }
								  pcur=pcur->m_next;
							  }
							  printf("ID                     NAME          SEX Chinese  Math   English   Art    P.E\n");
							  printf("%03d%25s%10c%8.2f%8.2f%8.2f%8.2f%8.2f\n",
									     pcur->m_id,pcur->m_name,pcur->m_gender,
										 pcur->m_scores[0],pcur->m_scores[1],
										 pcur->m_scores[2],pcur->m_scores[3],
										 pcur->m_scores[4]);
							  system("pause");
							  goto Label1;
							  break;
						  }//case 1
					  case 2://by id
						  {
							  printf("Please input a id :\n");
							  fflush(stdin);
							  scanf("%d",&input_id);
							  system("cls");
							  pcur=stu_list;
							  while (pcur)
							  {
								  if (pcur->m_id==input_id)
								  {
									  break;
								  }
								  pcur=pcur->m_next;
							  }
							  printf("ID                     NAME          SEX Chinese  Math   English   Art    P.E\n");
							  printf("%03d%25s%10c%8.2f%8.2f%8.2f%8.2f%8.2f\n",
									     pcur->m_id,pcur->m_name,pcur->m_gender,
										 pcur->m_scores[0],pcur->m_scores[1],
										 pcur->m_scores[2],pcur->m_scores[3],
										 pcur->m_scores[4]);
							  system("pause");
							  goto Label1;
							  break;
						  }//case 2
					  case 3://return
						  goto Label1;
						  }//switch(partion);
					  }//while(partion)
				  }//select=1
			  break;

Label2: case 2://增加学生信息
			  {
				  system("cls");
				  printf("返回上一层请按‘*’，确认添加请按回车 ：");
				  fflush(stdin);
				  fflush(stdout);
				  if (getchar()=='*')
				  {
					  goto Label1;
				  }else//添加
				  {
					  pcur=stu_list;
					  ppre=NULL;
					  pnew_stu=(pSTU)calloc(1,sizeof(STU));
					  printf("Please input the student's informatioin in correct order:\n");
					  fflush(stdin);
					  fflush(stdout);
					  scanf("%d %s %c %lf %lf %lf %lf %lf",
						     &pnew_stu->m_id,pnew_stu->m_name,
							 &pnew_stu->m_gender,&pnew_stu->m_scores[0],
							 &pnew_stu->m_scores[1],&pnew_stu->m_scores[2],
							 &pnew_stu->m_scores[3],&pnew_stu->m_scores[4]);
					  while (pcur)
					  {
						  if (pcur->m_id==pnew_stu->m_id)//重复
						  {
							  printf("Insert Error!\n");
							  goto Label2;
						  }
						  if (pnew_stu->m_id < pcur->m_id)//确定插入位置
						  {
							  break;
						  }
						  ppre=pcur;
						  pcur=pcur->m_next;
					  }
					  if (NULL==ppre)//组合
					  {
						  stu_list=pnew_stu;
						  pnew_stu->m_next=pcur;
					  }else
					  {
						  pnew_stu->m_next=pcur;
						  ppre->m_next=pnew_stu;
					  }
					  printf("Mission Success!\n");
					  system("pause");
				  }
			  }//select=2
			  link_save_to_file(stu_list,argv[3]);
			  break;

Label3: case 3://更新学生信息
			  {
				  system("cls");
				  printf("\n\n***************************Bug***************************\n\n");
				  printf("Please input a ID of the studnet who needs to be modifyed:\n");
				  printf("\n\n***************************Bug***************************\n\n");
				  fflush(stdin);
				  fflush(stdout);
				  scanf("%d",&modify_id);			
				  pcur=stu_list;
				  ppre=NULL;
				  while (pcur)
				  {
					  if (pcur->m_id==modify_id)
					  {
						  break;
					  }
					  pcur=pcur->m_next;
				  }
				  if(!pcur)
				  {					
					  goto Label3;
				  }else
				  {
					  printf("Search success! New information :\n");
					  fflush(stdin);
					  fflush(stdout);
					  scanf("%d %c %lf %lf %lf %lf %lf",
						     &pnew_stu->m_id,pnew_stu->m_name,
							 &pnew_stu->m_gender,&pnew_stu->m_scores[0],
							 &pnew_stu->m_scores[1],&pnew_stu->m_scores[2],
							 &pnew_stu->m_scores[3],&pnew_stu->m_scores[4]);
					  system("pause");
				  }
			  }
			  link_save_to_file(stu_list,argv[3]);	
			  system("pause");
			  break;

Label4: case 4://删除学生信息
			  {
				  system("cls");
				  printf("Please input a ID of the studnet who needs to be deleted:\n");
				  fflush(stdin);
				  fflush(stdout);
				  scanf("%d",&delete_id);			
				  pcur=stu_list;
				  ppre=NULL;
				  while (pcur)
				  {
					  if (pcur->m_id==delete_id)
					  {
						  break;
					  }
					  ppre=pcur;
					  pcur=pcur->m_next;
				  }
				  if (NULL==ppre)
				  {
					 printf("Not found!\n");
					 goto Label4;
				  }else			  
				  {
					  ppre->m_next=pcur->m_next;
				  }
				  free(pcur);
			  }
			  link_save_to_file(stu_list,argv[3]);
			  system("pause");
			  break;

Label5: case 5:
			  {
				  system("cls");
				  printf("0. search all\n");
				  printf("1. search by name\n");
				  printf("2. search by role\n");
				  printf("3. return\n");
				  while (fflush(stdin),(partion=getchar())!='3')
				  {
					  system("cls");
					  fflush(stdin);
					  switch(partion-'0')//char->int
					  {
					  case 0://search all
						  {
							  pcur_acc=account_list;
							  while (pcur_acc)
							  {								  
								  printf("%-25s%-15s%d\n",pcur_acc->m_name,
									      pcur_acc->m_passwd,pcur_acc->m_role);
								  pcur_acc=pcur_acc->m_next;
							  }
							  system("pause");
							  goto Label5;
							  break;
						  }
					  case 1://by name
						  {
							  printf("Please input a name :\n");
							  fflush(stdin);
							  fflush(stdout);
							  gets(input_name);
							  system("cls");
							  pcur_acc=account_list;
							  while (pcur_acc)
							  {
								  if (strcmp(pcur_acc->m_name,input_name)==0)								
								  {
									  break;
								  }
								  pcur_acc=pcur_acc->m_next;
							  }
							  printf("%-25s%-15s%d\n",pcur_acc->m_name,
									      pcur_acc->m_passwd,pcur_acc->m_role);
							  system("pause");
							  goto Label5;
							  break;
						  }//case 1
					  case 2://by role
						  {
							  printf("Please input the role number :\n");
							  fflush(stdin);
							  scanf("%d",&input_role);
							  system("cls");
							  pcur_acc=account_list;
							  while (pcur_acc)
							  {
								  if (pcur_acc->m_role==input_role)
								  {
									  printf("%-25s%-15s%d\n",pcur_acc->m_name,
									      pcur_acc->m_passwd,pcur_acc->m_role);									 
								  }
								  pcur_acc=pcur_acc->m_next;
							  } 							  
							  system("pause");
							  goto Label5;
							  break;
						  }//case 2
					  case 3://return
						  goto Label1;
						  }//switch(partion);
				  }//while
			  }
			  break;

Label6:case 6://添加用户
			  {
				  system("cls");
				  printf("返回上一层请按‘*’，确认添加请按回车 ：");
				  fflush(stdin);
				  fflush(stdout);
				  if (getchar()=='*')
				  {
					  goto Label1;
				  }else//添加
				  {
					  pcur_acc=account_list;
					  ppre_acc=NULL;
					  pnew_acc=(pACCOUNT)calloc(1,sizeof(ACCOUNT));
					  printf("Please input the student's informatioin in correct order:\n");
					  fflush(stdin);
					  fflush(stdout);
					  scanf("%s %s %d",pnew_acc->m_name,pnew_acc->m_passwd,&pnew_acc->m_role);
					  while (pcur_acc)
					  {
						  if (strcmp(pnew_acc->m_name,pcur_acc->m_name)==0)//重复
						  {
							  printf("Insert Error!\n");
							  goto Label6;
						  }			  
						  ppre_acc=pcur_acc;
						  pcur_acc=pcur_acc->m_next;
					  }
					  ppre_acc->m_next=pnew_acc;
					  pnew_acc->m_next=pcur_acc;
					  printf("Mission Success!\n");
					  system("pause");//
				  }
			  }
			  link_save_to_file_acc(account_list,argv[2]);
			  system("pause");
			  break;

Label7:case 7://更新用户
			  {
				  system("cls");
				  printf("Please input the name of the account that needs to be modifyed:\n");
				  fflush(stdin);
				  fflush(stdout);
				  scanf("%s",modify_name);			
				  pcur_acc=account_list;				  
				  while (pcur_acc)
				  {
					  if (strcmp(pcur_acc->m_name,modify_name)==0)
					  {
						  break;
					  }					  
					  pcur_acc=pcur_acc->m_next;
				  }
				  if(!pcur_acc)
				  {					
					  goto Label7;
				  }else
				  {
					  printf("Search success! New information :\n");
					  fflush(stdin);
					  fflush(stdout);
					  scanf("%s %s %d",pcur_acc->m_name,pcur_acc->m_passwd,&pcur_acc->m_role);
					  system("pause");
				  }
			  }
			  link_save_to_file_acc(account_list,argv[2]);
			  system("pause");
			  break;

Label8:case 8://删除用户
			  {
				  system("cls");
				  printf("Please input the name of the account that needs to be deleted :\n");
				  fflush(stdin);
				  fflush(stdout);
				  scanf("%s",delete_name);
				  ppre_acc=NULL;
				  pcur_acc=account_list;
				  while (pcur_acc)
				  {
					  if (strcmp(pcur_acc->m_name,delete_name)==0)
					  {
						  break;
					  }
					  ppre_acc=pcur_acc;
					  pcur_acc=pcur_acc->m_next;
				  }
				  if (NULL==pcur_acc)
				  {
					  printf("Not found!\n");
					  goto Label8;
				  }else
				  {
					  if (NULL==pcur_acc)
					  {
						  account_list=pcur_acc->m_next;
					  }
					  else
					  {
						  ppre_acc->m_next=pcur_acc->m_next;
					  }
					  free(pcur_acc);
				  }				  
			  }
			  link_save_to_file_acc(account_list,argv[2]);
			  system("pause");
			  break;

case 9: return;
			  }//switch(select)
		  }//if(1==role)



			else//2==role只有查询本人成绩的功能
			{		
				fflush(stdin);
				fflush(stdout);
				system("cls");
				pcur=stu_list;
				while (pcur)
				{
					if (strcpy(pcur->m_name,myName))//strcpy成功返回*to
					{
					break;
					}
					pcur=pcur->m_next;
				}
				printf("ID                     NAME          SEX Chinese  Math   English   Art    P.E\n");
				printf("%03d%25s%10c%8.2f%8.2f%8.2f%8.2f%8.2f\n",
							pcur->m_id,pcur->m_name,pcur->m_gender,
							pcur->m_scores[0],pcur->m_scores[1],
							pcur->m_scores[2],pcur->m_scores[3],
							pcur->m_scores[4]);
				system("pause");
			}//usr查询功能
		  }//while(select)
	system("pause");	  
}
	
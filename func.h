#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>//输入账户密码后去内存中匹配
#define PWD_LEN 10
#define NAME_LEN	20
#define LINE_LEN 512
#define M1 "1 . search  student  information"
#define M2 "2 . add  student  information"
#define M3 "3 . update  student  information"
#define M4 "4 . delete  student  information"
#define M5 "5 . search user account"
#define M6 "6 . add  user  account"
#define M7 "7 . update  user  account"
#define M8 "8 . delete  user  account"
#define M9 "9 . exit"

//链表实现
typedef struct stu_account_tag//学生账户信息。登录
{
	char m_passwd[PWD_LEN];
	char m_name[20];
	int m_role;
	struct stu_account_tag *m_next;
}ACCOUNT,*pACCOUNT;

typedef struct stu_info_tag//用户信息。显示
{
	int m_id;
	char m_name[NAME_LEN];
	char m_gender;
	double m_scores[5];
	struct stu_info_tag *m_next;
}STU,*pSTU;

/*系统数据主要存储在三个文件：
  config.txt、stu_account.txt、stu_info.txt
  分别用于存放配置信息，账户信息，学生信息*/

//功能函数
void trim_space(char *src);//排除每行前的空格，并将行中的其他空格类字符转换为空格
void system_init(char *config ,pACCOUNT *pphead_acc ,pSTU *pphead_stu);//初始化
int role_confirm(pACCOUNT phead_acc ,char *name);//角色认证，得到角色值
int show_system_menu(int role);//菜单界面
void link_save_to_file(pSTU phead ,char *dest);
void link_save_to_file_acc(pACCOUNT phead ,char *dest);
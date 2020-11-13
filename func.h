#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>//�����˻������ȥ�ڴ���ƥ��
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

//����ʵ��
typedef struct stu_account_tag//ѧ���˻���Ϣ����¼
{
	char m_passwd[PWD_LEN];
	char m_name[20];
	int m_role;
	struct stu_account_tag *m_next;
}ACCOUNT,*pACCOUNT;

typedef struct stu_info_tag//�û���Ϣ����ʾ
{
	int m_id;
	char m_name[NAME_LEN];
	char m_gender;
	double m_scores[5];
	struct stu_info_tag *m_next;
}STU,*pSTU;

/*ϵͳ������Ҫ�洢�������ļ���
  config.txt��stu_account.txt��stu_info.txt
  �ֱ����ڴ��������Ϣ���˻���Ϣ��ѧ����Ϣ*/

//���ܺ���
void trim_space(char *src);//�ų�ÿ��ǰ�Ŀո񣬲������е������ո����ַ�ת��Ϊ�ո�
void system_init(char *config ,pACCOUNT *pphead_acc ,pSTU *pphead_stu);//��ʼ��
int role_confirm(pACCOUNT phead_acc ,char *name);//��ɫ��֤���õ���ɫֵ
int show_system_menu(int role);//�˵�����
void link_save_to_file(pSTU phead ,char *dest);
void link_save_to_file_acc(pACCOUNT phead ,char *dest);
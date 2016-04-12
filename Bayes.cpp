#include<iostream>
#include<fstream>
#include<map>
#include<string>
#define CPP 3
#define JAVA 3
using namespace std;
char ans[201];

char s[27]={"  '+[]&*,.<({\";#>)}!=_-|"};
char sline[201];
int numcount=0;
map< string,int > map_cpp_word;
map< string,int > map_java_word;
map< string,int > map_python_word;
map<string,int> map_flag;



int CountTime(map<string,int>map_time,char* ans)//����ĳ�������� ����г��ֵĴ���
{
	for(map<string,int>::iterator it=map_time.begin();it!=map_time.end();it++)
	{
	   if(it->first==ans)
		   return it->second;
	}
	return 0;
}

double Prob(char *ans,char* cate)//�����������
{
	int sum=0;

      if(cate=="java")
			sum=CountTime(map_java_word,ans);
	  else if(cate=="cpp")
		    sum=CountTime(map_cpp_word,ans);
	  else if(cate=="python")
			sum=CountTime(map_python_word,ans);
	  return 1.0*sum/(3); //����������Ϊÿ��������3������ 
}
double WeightProb(char *ans,char* cate,double weight=1.0,double pro=0.5)//��Ȩƽ������
{
	double basic=Prob(ans,cate);//��ָ�������������
	double total=CountTime(map_java_word,ans)+CountTime(map_cpp_word,ans)+CountTime(map_python_word,ans);//�ڸ�������ܵĳ��ִ���
	double bp=((weight*pro+total*basic)/(weight+total));
	return bp;
}
void Strfun(const char *pw)//�и�
{
  int i=0;
  while(*pw!='\0')
  {
	if(*pw =='\t')
	{
		*pw++;	continue;
	}
	if(*pw=='/'&&*(pw+1)=='/'||*pw=='\\')
	{
	i=0;break;
	}
    ans[i++]=tolower((*pw++));
  }
  ans[i]='\0';
}


bool Find(map<string,int>str,char* ans)
{
	
	map<string,int>::iterator it;
	for(it=str.begin();it!=str.end();it++)
		if(it->first==ans)break;
	
	
	if(it==str.end())
		return false;
	else
		return true;
}
bool CheckStr(char * an)//������ �Լ� �ǡ�\����ͷ�Ķ���true;
{
  if(an[0]=='\\')
		 return false;
  for(int i=0;i<strlen(an);i++)
  {
     if(isdigit(an[i])==false)
		 return true;
  }
         return false;
}
void show(map<string,int>str)
{
	for(map<string,int>::iterator it=str.begin();it!=str.end();it++)
	{
	   cout<<it->first<<"  "<<it->second<<endl;
	}
}


int main(){
ofstream fout("out.txt");
char *pw;
char filename[15],category[10];
while(numcount++<9)//��ȡ�Ÿ��ļ��ֱ�Ϊjava,c++,python��Ϊѵ�������ļ�
{
cout<<"category:"<<endl;
scanf("%s",category);
ifstream fin(category);
cout<<category<<endl;
int count=0;
fin.getline(sline,201);

while(!fin.eof()){
		pw=strtok(sline,s); //��ȡ�ַ���sline�е��׸�����
		while(pw!=0){
			count++;
			Strfun(pw);
			if(strlen(ans)<2||CheckStr(ans)==false){
			pw=strtok(0,s);
			}
			else
			{
				if(numcount<4)
				{
					if(!Find(map_flag,ans)&&!Find(map_java_word,ans))//��δ���ֹ��ĵ���
					{
						map_java_word[ans]=1;
						map_flag[ans]=1;
					}
					else if(Find(map_java_word,ans)&&!Find(map_flag,ans))
					{
					map_java_word[ans]++;
					map_flag[ans]=1;
					}
				}
				else if(numcount>=4&&numcount<7)
				{
					if(!Find(map_flag,ans)&&!Find(map_cpp_word,ans))//��δ���ֹ��ĵ���bingqie
					{
						map_cpp_word[ans]=1;
						map_flag[ans]=1;
					}
					else if(Find(map_cpp_word,ans)&&!Find(map_flag,ans))
					{
					map_cpp_word[ans]++;
					map_flag[ans]=1;
					}
				}
				else if(numcount>=7)
				{
				   	if(!Find(map_flag,ans)&&!Find(map_python_word,ans))//��δ���ֹ��ĵ���bingqie
					{
						map_python_word[ans]=1;
						map_flag[ans]=1;
					}
					else if(Find(map_python_word,ans)&&!Find(map_flag,ans))
					{
					map_python_word[ans]++;
					map_flag[ans]=1;
					}
				}
			pw=strtok(0,s); //��ȡ�ַ���sline�е���һ������
			}			
		}
		fin.getline(sline,201);
	}	
	map_flag.erase(map_flag.begin(),map_flag.end());//���

	fin.close();
	fout.close();

}
//show(map_bad_word);
cout<<"===================================="<<endl;
//show(map_good_word);
//show(map_python_word);


cout<<"weight:"<<WeightProb("with","python");//���Լ�������������
while(1){
cout<<"================��ʼ������������===================="<<endl;
cout<<"cin Test File name:"<<endl;
scanf("%s",category);
double pJava=1,pCpp=1,pPython=1,max;
ifstream fin(category);//��������ļ����ļ���
cout<<category<<endl;
fin.getline(sline,201);
while(!fin.eof())
{
		pw=strtok(sline,s); //��ȡ�ַ���sline�е��׸�����
		while(pw!=0){			
			Strfun(pw);
			if(strlen(ans)<2||CheckStr(ans)==false)
			{
				pw=strtok(0,s);
			}
			else
			{
			   pJava*=WeightProb(ans,"java");
			   pJava*=2;//�ʵ�������ʹpJava���ڶ�ȡ
			   pCpp*=WeightProb(ans,"cpp");
			   pCpp*=2;
			   pPython*=WeightProb(ans,"python");
			   pPython*=2;
			
			}
			pw=strtok(0,s);
		}
		fin.getline(sline,201);
}
cout<<"Java:"<<pJava<<"  Cpp:"<<pCpp<<"  Python:"<<pPython<<endl;
cout<<"��������"<<endl;
max=pJava>pCpp?pJava:pCpp;
max=max>pPython?max:pPython;

if (max==pJava)
	cout<<"Java"<<endl;
else if(max==pCpp)
	cout<<"C++"<<endl;
else if (max==pPython)
	cout<<"Python"<<endl;
}
	return 0;
}
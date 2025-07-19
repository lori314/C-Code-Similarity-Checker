#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define M 20480
typedef struct _function{
	char name[30];
	char *data;
	int len;
}function;
typedef struct _program{
	char name[30];
	char data[M];
}program;
program program_list[100];
function function_list[100];
char function_order[100][30];
int list_num=0,order_num=0,program_num=0;
char str[M];
char buffer[M];
char keepwords[500][20];
char stack[200];
int top=-1;
int mode=0;
const char Const[6]="FUNC";
int cmp(const void *p,const void *q){
	char *a=(char *)p;
	char *b=(char *)q;
	int len_a=strlen(a);
	int len_b=strlen(b);
	if(len_a>len_b) return 1;
	else if(len_a<len_b) return -1;
	else return 0;
}
int ccmp(const void *p,const void *q){
	char *a=(char *)p;
	char *b=(char *)q;
	if (strcmp(a,b)>0) return 1;
	else if (strcmp(a,b)<0) return -1;
	else return 0;
}
int search(char *p,int len){
	int start;
	int end;
	int i;
	char ch=*p;
	if(len==2){
		start=0;
		end=1;
	}
	else if(len==3){
		start=2;
		end=11;
	}
	else if(len==4){
		start=12;
		end=44;
	}
	else if(len==5){
		start=45;
		end=70;
	}
	else if(len==6){
		start=71;
		end=118;
	}
	else if(len==7){
		start=119;
		end=153;
	}
	else if(len==8){
		start=154;
		end=164;
	}
	else if(len==9){
		start=165;
		end=165;
	}
	else return 0;
	for(i=start;i<=end;i++){
		if(ch==*keepwords[i]){
			if(strncmp(p,keepwords[i],len)==0){
				return 1;
			}
		}
	}
	return 0;
}
void wash_cat(char *p){
	int i;
	int flag=0;
	char *start=p;
	char temp[30];
	while(*start=='\t'||*start==' '){
		start++;
	}
	char *end=start;
	while(*start!='\n'){
		if(*start>='a'&&*start<='z'){
			while(1){
				if((*end>='a'&&*end<='z')||(*end>='A'&&*end<='Z')||(*end>='0'&&*end<='9')||*end=='_'){
					end++;
				}
				else if(*end=='('){
					if(search(start,end-start)==1){
						strncat(str,start,end-start);
					}
					else{
						if(mode==0){
							strncpy(temp,start,end-start);
							temp[end-start]='\0';
							//printf("*%s*",temp);
							if(strcmp(temp,"main")==0){
								mode=1;
							}
							else{
								mode=2;
							}
							strcpy(function_list[list_num].name,temp);
							memset(temp,0,sizeof(temp));
						}
						if(mode==1){
							strncpy(temp,start,end-start);
							temp[end-start]='\0';
							for(i=0;i<order_num;i++){
								if(strcmp(temp,function_order[i])==0)	flag=1;
							}
							if(flag!=1){
								strcpy(function_order[i],temp);
								order_num++;
							}
							flag=0;
							memset(temp,0,sizeof(temp));
						}
						strcat(str,Const);
					}
					start=end;
					break;
				}
				else if(*end==' '||*end=='\n'||*end==')'||*end==';'||*end==':'||*end=='{'){
					if(search(start,end-start)==1){
						strncat(str,start,end-start);
					}
					start=end;
					break;
				}
				else{
					start=end;
					break;
				}
			}
		}
		else if((*start>='A'&&*start<='Z')||*start=='_'){
			while(1){
				if((*end>='a'&&*end<='z')||(*end>='A'&&*end<='Z')||(*end>='0'&&*end<='9')||*end=='_'){
					end++;
				}
				else if(*end=='('){
					if(mode==0){
						strncpy(temp,start,end-start);
						temp[end-start]='\0';
						//printf("*%s*",temp);
						if(strcmp(temp,"main")==0){
							mode=1;
							}
						else{
							mode=2;
						}
						strcpy(function_list[list_num].name,temp);
						memset(temp,0,sizeof(temp));
					}
					if(mode==1){
						strncpy(temp,start,end-start);
						temp[end-start]='\0';
						for(i=0;i<order_num;i++){
							if(strcmp(temp,function_order[i])==0)	flag=1;
							}
						if(flag!=1){
							strcpy(function_order[i],temp);
							order_num++;
						}
						flag=0;
						memset(temp,0,sizeof(temp));
					}
					strcat(str,Const);
					start=end;
					break;
				}
				else{
					start=end;
					break;
				}
			}
		}
		else{
			if(*start!=' '&&*start!='\t')	strncat(str,start,1);
			if(*start=='{'){
				if(top==-1){
					function_list[list_num].data=str+strlen(str)-1;
				}
				stack[++top]='{';
			}
			if(*start=='}'){
				stack[top--]=0;
				if(top==-1){
					mode=0;
					function_list[list_num].len=str+strlen(str)-function_list[list_num].data;
					list_num++;
				}
			}
			start++;
			end=start;
		}
	}
	return;
}
void cat(){
	int i,j;
	for(i=0;i<order_num;i++){
		for(j=0;j<list_num;j++){
			if(strcmp(function_list[j].name,function_order[i])==0){
				strncat(program_list[program_num].data,function_list[j].data,function_list[j].len);
			}
		}
	}
	program_list[program_num].data[strlen(program_list[program_num].data)]='\0';
	printf("%s\n",program_list[program_num].data);
	printf("%d",strlen(program_list[program_num].data));
	program_num++;
	memset(str,0,sizeof(str));
	memset(function_list,0,sizeof(function_list));
	memset(function_order,0,sizeof(function_order));
	list_num=0;
	order_num=0;
}
int main(){
	int i=0;
	int keepwords_num;
	char ch;
	FILE *fp;
	FILE *f_in;
	fp=fopen("keepwords.txt","r");
	f_in=fopen("codes.txt","r");
	while(fscanf(fp,"%s",keepwords[i])!=EOF){
		i++;
	}
	keepwords_num=i;
	qsort(keepwords,i,sizeof(keepwords[0]),cmp);
	qsort(keepwords,2,sizeof(keepwords[0]),ccmp);
	qsort(keepwords+2,10,sizeof(keepwords[0]),ccmp);
	qsort(keepwords+12,33,sizeof(keepwords[0]),ccmp);
	qsort(keepwords+45,26,sizeof(keepwords[0]),ccmp);
	qsort(keepwords+71,48,sizeof(keepwords[0]),ccmp);
	qsort(keepwords+119,35,sizeof(keepwords[0]),ccmp);
	qsort(keepwords+154,10,sizeof(keepwords[0]),ccmp);
	i=0;
	fgets(program_list[program_num].name,sizeof(program_list[program_num].name),f_in);
	while(fgets(program_list[program_num].name,sizeof(program_list[program_num].name),f_in)!=NULL){
		//printf("#%s#",program_list[program_num].name);
		while(1){
			fgets(buffer,sizeof(buffer),f_in);
			ch=fgetc(f_in);
			wash_cat(buffer);
			if(ch=='\f'){
				break;
			}
			else{
				ungetc(ch,f_in);
			}
			memset(buffer,0,sizeof(buffer));
		}
		ch=fgetc(f_in);
		//printf("%s",str);
		printf("\n");
		cat();
	}
//	i=0;
//	while(function_list[i].data!=NULL){
//		strncpy(buffer,function_list[i].data,function_list[i].len);
//		printf("%s\n",function_list[i].name);
//		printf("%s\n",buffer);
//		memset(buffer,0,sizeof(buffer));
//		i++;
//	}
//	printf("|%d|",list_num);
//	for(i=0;i<order_num;i++){
//		printf("%s\n",function_order[i]);
//	}
	//printf("%d",editdistDP(program_list[0].data,program_list[1].data));
	return 0;
}

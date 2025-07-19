#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define M 20480
char keepwords[500][20];
int keepwords_num[30];
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
	if(len>=2&&len<=9){
		start=keepwords_num[len-2];
		end=keepwords_num[len-1]-1;
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
int main(){
	
	int i=0;
	int j;
	int k=0;
	char test[50]="int";
	FILE *fp;
	FILE *f_in;
	fp=fopen("keepwords.txt","r");
	f_in=fopen("codes.txt","r");
	keepwords_num[k++]=0;
	while(fscanf(fp,"%s",keepwords[i])!=EOF){
		i++;
	}
	qsort(keepwords,i,sizeof(keepwords[0]),cmp);
	for(j=0;j<i;j++){
		if(j!=0&&strlen(keepwords[j])>strlen(keepwords[j-1])) keepwords_num[k++]=j;
	}
	for(j=1;j<k;j++){
		printf("%d\n",keepwords_num[j]);
		qsort(keepwords+keepwords_num[j-1],(keepwords_num[j]-keepwords_num[j-1]),sizeof(keepwords[0]),ccmp);
	}
	for(j=0;j<i;j++){
		printf("%s\n",keepwords[j]);
	}
	printf("%d",search(test,strlen(test)));
	return 0;
}



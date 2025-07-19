/*
字符串编辑距离(Edit Distance)，是俄罗斯科学家Vladimir Levenshtein提出的概念。两个字符串之间的最小距离就是指把一个字符串转换为另一个字符串时，所需要的最小编辑操作(插入、删除、替换)的次数。
编辑操作包含以下3种：
替换（substitution），将一个字符替换为另一个字符
插入（insertion），插入一个字符
删除（deletion），删除一个字符
下面给出了一个基于动态规划算法的编辑距离计算函数editdistDP 的C语言实现，该函数参数为2个字符串，返回值为2个字符串的编辑距离，函数实现如下：
*/

#define max2(a,b) ((a)>(b)?(a):(b))
int **Dp, MaxDP=3300;								//for dynamic programming
int min3(int a, int b, int c)
{
    int min = a < b ? a : b;
    return min < c ? min : c;
}
void error2(char *s)
{
    fprintf(stderr,"%s\n",s); 
    exit(-1); 
}
void initDP()
{		
    int i;
    Dp = (int **)malloc(MaxDP*sizeof(int *));
    for(i=0; i<MaxDP; i++)
    Dp[i] = (int *)malloc(MaxDP*sizeof(int));	
}
int editdistDP(char *str1, char *str2) 
{
    int i,j;
    int len1, len2;
    static int flag=0;
	
    (flag++) ? Dp : initDP(); 
    len1 = strlen(str1)+1; len2 = strlen(str2)+1;
    (max2(len1,len2)>=MaxDP) ? error2("DP memory error!") : len1;
    for (i=0; i<=len1; i++) {
        for (j=0; j<=len2; j++) {
            if (i==0)
                Dp[i][j] = j;
            else if (j==0)
                Dp[i][j] = i;
            else if (str1[i-1] == str2[j-1])
                Dp[i][j] = Dp[i-1][j-1];
            else
                Dp[i][j] = 1 + min3(Dp[i][j-1], Dp[i-1][j], Dp[i-1][j-1]);
        }
    }
    return Dp[len1][len2];
}
int main(){
	char a[1000]="{FUNC();char*=(char*)calloc(,sizeof(char));char*=(char*)calloc(,sizeof(char));scanf("",);scanf("",);int=FUNC();int=FUNC();int*=(int*)calloc(,sizeof(int));FUNC(,,);FUNC(,,);return0;}{for(int=0;<;++){for(int=0;<;++){[][].=;}}*=fopen("","");int,,,,,,;struct;fscanf(,"",&);for(=0;<;++){fscanf(,"",&,&);=-1;=-1;for(=0;<;++){fscanf(,"",.,&(.));=FUNC();if(!=-1){[][].=1;[][].=1;[][].=;[][].=;}=;}}fclose();return;}{for(int=0;<;++){if(strcmp([].,)==0){return;}}return-1;}{int,,=0,;char[]={0};int[]={0};for(=0;<;++){[]=[][].;[]=;}[]=0;[]=1;for(=0;<-1;++){=;for(=0;<;++){if((![])&&([]<)){=;=[];}}[]=1;if(==){return;}for(=0;<;++){if((![])&&([][].>0)&&(+[][].<[])){[]=+[][].;[]=;}}}}{char[80]={0},[80]={0};int[80]={0},=0,=-1,=0;int;do{[++]=;}while((=[])!=);[++]=;=[[-1]][[-2]].;sprintf(,"",[[-1]].,);strcpy(,);=1;for(=-2;>0;--,++){if([[]][[-1]].!=){=[[]][[-1]].;sprintf(,"",,[[]].,);strcat(,);=0;}}sprintf(,"",,[[]].);strcat(,);puts();}";
	char b[1000]="{FUNC();char*=(char*)calloc(,sizeof(char));char*=(char*)calloc(,sizeof(char));scanf("",);scanf("",);int=FUNC();int=FUNC();int*=(int*)calloc(,sizeof(int));FUNC(,,);FUNC(,,);return0;}{for(int=0;<;++){for(int=0;<;++){[][].=;}}*=fopen("","");int,,,,,,;struct;fscanf(,"",&);for(=0;<;++){fscanf(,"",&,&);=-1;=-1;for(=0;<;++){fscanf(,"",.,&(.));=FUNC();if(!=-1){[][].=1;[][].=1;[][].=;[][].=;}=;}}fclose();return;}{for(int=0;<;++){if(strcmp([].,)==0){return;}}return-1;}{int,,=0,;char[]={0};int[]={0};for(=0;<;++){[]=[][].;[]=;}[]=0;[]=1;for(=0;<-1;++){=;for(=0;<;++){if((![])&&([]<)){=;=[];}}[]=1;if(==){return;}for(=0;<;++){if((![])&&([][].>0)&&(+[][].<[])){[]=+[][].;[]=;}}}}{char[80]={0},[80]={0};int[80]={0},=0,=-1,=0;int;{[++]=;}while((=[])!=);[++]=;=[[-1]][[-2]].;sprintf(,"",[[-1]].,);strcpy(,);=1;for(=-2;>0;--,++){if([[]][[-1]].!=){=[[]][[-1]].;sprintf(,"",,[[]].,);strcat(,);=0;}}sprintf(,"",,[[]].);strcat(,);puts();}";
}

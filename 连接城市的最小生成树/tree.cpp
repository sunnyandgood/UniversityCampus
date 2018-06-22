#include<stdio.h>
#define FINITY 5000        //用5000代表无穷大
#define M 20               //预定义的最大顶点数
typedef char vertextype;   //顶点值类型
typedef int edgetype;      //权值类型

//图的结构体
typedef struct
{
	vertextype vexs[M];    //顶点信息域
	edgetype edges[M][M];  //图的邻接矩阵（边的权值）
	int n,e;               // 图的顶点总数和边数
}Mgraph;

//最小生成树的边的结构体
 typedef struct edgedata
 {
 	 int  beg,en;          //起点、终点
 	 int length;           //路径长度
 }edge;

 void menu();                                    //主菜单
 void creat(Mgraph *g,char *s,int c);            //建立网络的邻接矩阵算法
 void GetEdge(Mgraph g,edge edges[]);            //从图g的邻接矩阵中读取图的所有边信息
 void QuickSort(edge edges[],int left,int right);//对边进行快速排序
 void kruskal(Mgraph g);
 void prim(Mgraph g);

int main()
{
	int number;
	Mgraph g;
    char filename[20];
	int edit=1;
    menu();
    while(edit)
    {
        printf("\n<--------------------------------->\n");
        printf("\n请输入您要选择的功能键：\n");
        scanf("%d",&number);
        switch(number)
        {
            case 1:
                printf("请输入图的文件名：\n");
                getchar();
                gets(filename);
                creat(&g,filename,0);
                kruskal(g);
                break;
            case 2:
                printf("请输入图的文件名：\n");
                getchar();
                gets(filename);
                creat(&g,filename,0);
                prim(g);
                break;
            case 3:
               break;
            case 4:
               edit=0;
               printf("功能选择已结束，请按任意键结束程序。\n");
               printf("\n--------------------------------->\n");
               break;
            default:
                printf("输入有误！！！请重新输入！");
                break;
        }
    }
    return 0;
}

 void menu()
 {
    printf("          **********************************************************\n");
	printf("          *                                                        *\n");
	printf("          *    --------------------欢迎使用--------------------    *\n");
	printf("          *                                                        *\n");
	printf("          *                  连接城市的最小生成树                  *\n");
	printf("          *                                                        *\n");
    printf("          **********************************************************\n");
	printf("          *              学  院：计算机科学与技术学院              *\n");
	printf("          *              专  业：计算机科学与技术专业              *\n");
	printf("          *              班  级：     16070641班                   *\n");
	printf("          *                                                        *\n");
	printf("          *             指导老师：     师智斌                      *\n");
	printf("          *             小组成员： 王仁洪  李泳锋                  *\n");
	printf("          *                        李  康  张瑀卿                  *\n");
    printf("          **********************************************************\n");
	printf("          *        功能（算法的选择）：                            *\n");
	printf("          *             1、使用kruskal算法求解最小生成树           *\n");
	printf("          *             2、使用prim算法求解最小生成树              *\n");
	printf("          *             3、继续重新选择算法并求解                  *\n");
	printf("          *             4、退出选择,程序结束                       *\n");
	printf("          **********************************************************\n");
	printf("          *                                                        *\n");
	printf("          *             ---------感谢您的使用----------            *\n");
	printf("          * <注意>：                                               *\n");
	printf("          *                                                        *\n");
	printf("          * H---哈尔滨  W---乌鲁木齐  T---太原  C---重庆  F---福州 *\n");
	printf("          *                                                        *\n");
	printf("          **********************************************************\n");
	printf("\n\n");
 }


 //建立网络的邻接矩阵算法
void creat(Mgraph *g,char *s,int c)
{
	int i,j,k,w;
	FILE *rf;
	rf=fopen(s,"r");
	if(rf)
    {
         //读取图中的顶点数和边数
		fscanf(rf,"%d%d",&g->n,&g->e);
		 //读取图中所有的顶点
		for(i=0;i<g->n;i++)
        {
            fscanf(rf,"%ls",&g->vexs[i]);
        }
		// 初始化邻接矩阵
		for(i=0;i<g->n;i++)
        {
            for(j=0;j<g->n;j++)
            {
                if(i==j)
					g->edges[i][j]=0;
				else
					g->edges[i][j]=FINITY;
            }
        }
		//读入网络的边
		for(k=0;k<g->e;k++)
		{
			fscanf(rf,"%d%d%d",&i,&j,&w);
			g->edges[i][j]=w;
			if(c==0)g->edges[j][i]=w;
		}
        fclose(rf);
    }
	else
        g->n=0;
}


 //从图g的邻接矩阵中读取图的所有边信息
void GetEdge(Mgraph g,edge edges[])
{
	int i,j,k=0;
    for (i=0;i<g.n;i++)
    {
        for (j=0;j<i;j++)
        {
            if (g.edges[i][j]!=0 && g.edges[i][j]<FINITY)
            {
               edges[k].beg=i;
               edges[k].en=j;
               edges[k++].length=g.edges[i][j];
            }
        }
    }
}


 //对边进行快速排序
 void QuickSort(edge edges[],int left,int right)
 {
	edge x;//定义用作比较记录的变量
	int i,j;
	if(left<right)
	{//将第一个作为比较标准值
		i=left;
		j=right;
		x=edges[i];
		while(i<j)
		{
			while(i<j && x.length<edges[j].length)
			{
                j--;//从右向左找排序码小于标准值的位置
			}
            if(i<j)
            {
                edges[i++]=edges[j];//找到并将第j个元素置于第i个元素位置处，重置i
            }
			while(i<j && x.length>edges[i].length)
            {
                i++;//从左向右找排序码大于标准值的位置
            }
            if(i<j)
            {
                edges[j--]=edges[i];//找到并且将第i个元素放于第j个位置处，并重置j
            }
		}
		edges[i]=x;//i=j,最终位置已找到。将标准值放入最终位置
		QuickSort(edges,left,i-1);i=j,//最终位置已找到。将标准值放入最终位置
		QuickSort(edges,i+1,right);//对标准值右部递归调用此函数
	}
}


 //利用kruskal算法求解最小生成树和代价
 void kruskal(Mgraph g)
 {
 	int i,j,k=0,ltfl;
 	int sum=0;//最小生成树的代价
 	int cnvx[M]; //设置每个顶点的连通分量编号
 	edge edges[M*M];//用于存放图的所有边
 	edge tree[M];//存放最小生成树的边

    //从图g的邻接矩阵中读取图的所有边信息
 	GetEdge(g,edges);
 	//使边升序排序
	QuickSort(edges,0,g.e-1);
	//设置每个顶点的连通分量为其顶点编号
	for(i=0;i<g.n;i++)
	    cnvx[i]=i;
	//开始构造最小生成树
	for(i=0;i<g.n-1;i++)
	{
		//找到属于两个连通分量的权值最小的边
		while(cnvx[edges[k].beg]==cnvx[edges[k].en])
			k++;
		tree[i]=edges[k];
		//通过修顶点连通分量值将两个连通分量合并成一个
		ltfl=cnvx[edges[k].en];
		for(j=0;j<g.n;j++)
			if(cnvx[j]==ltfl)
				cnvx[j]=cnvx[edges[k].beg];
		k++;
	 }
	 printf("最小生成树是：\n");
	 for(j=0;j<g.n-1;j++)
	 {
	 	printf("%c---%c%6d\n",g.vexs[tree[j].beg],g.vexs[tree[j].en],tree[j].length);
	 	sum+=tree[j].length;
	 }
	 printf("利用kruskal算法求解最小生成树的代价是：%d\n",sum);
 }

 //利用prim算法求解最小生成树和代价
void prim(Mgraph g)
{
	edge x;
	edge tree[M-1];
	int sum=0;        //最小生成树的代价
	int d, min, j, k, s, v;
	//建立初始入选点，并初始化生成树的边集tree
	//从0顶点开始
	for (v = 1; v <=g.n - 1; v++)
	{
		tree[v - 1].beg = 0;
		tree[v - 1].en = v;
		tree[v - 1].length = g.edges[0][v];
	}
	//依次求当前（第k条）最小两栖边，并加入tree中
	for (k = 0; k <= g.n - 3; k++)
	{
		//选择排序
		min = tree[k].length;
		s = k;
		for (j = k + 1; j <= g.n - 2;j++)
		if (tree[j].length < min)
		{
			min = tree[j].length;
			s = j;
		}
		//入选顶点v
		v = tree[s].en;

		x = tree[s];  tree[s] = tree[k]; tree[k]=x;
		//由于加入新顶点，修改两栖边的基本信息
		for (j = k + 1; j <= g.n - 2; j++)
		{
			d = g.edges[v][tree[j].en];
			if (d < tree[j].length)
			{
				tree[j].length = d;  tree[j].beg = v;
			}
		}
	}
	printf("最小生成树是 ：\n");
	for (j = 0; j <=g.n - 2; j++)
    {
        printf("%c---%c  %d\n", g.vexs[tree[j].beg], g.vexs[tree[j].en], tree[j].length);
        sum+=tree[j].length;
    }
    printf("利用prim算法求解最小生成树的代价是：%d\n",sum);
    printf("根结点是： %c\n", g.vexs[0]);
}

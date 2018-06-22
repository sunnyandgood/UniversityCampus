#include<stdio.h>
#define FINITY 5000        //��5000���������
#define M 20               //Ԥ�������󶥵���
typedef char vertextype;   //����ֵ����
typedef int edgetype;      //Ȩֵ����

//ͼ�Ľṹ��
typedef struct
{
	vertextype vexs[M];    //������Ϣ��
	edgetype edges[M][M];  //ͼ���ڽӾ��󣨱ߵ�Ȩֵ��
	int n,e;               // ͼ�Ķ��������ͱ���
}Mgraph;

//��С�������ıߵĽṹ��
 typedef struct edgedata
 {
 	 int  beg,en;          //��㡢�յ�
 	 int length;           //·������
 }edge;

 void menu();                                    //���˵�
 void creat(Mgraph *g,char *s,int c);            //����������ڽӾ����㷨
 void GetEdge(Mgraph g,edge edges[]);            //��ͼg���ڽӾ����ж�ȡͼ�����б���Ϣ
 void QuickSort(edge edges[],int left,int right);//�Ա߽��п�������
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
        printf("\n��������Ҫѡ��Ĺ��ܼ���\n");
        scanf("%d",&number);
        switch(number)
        {
            case 1:
                printf("������ͼ���ļ�����\n");
                getchar();
                gets(filename);
                creat(&g,filename,0);
                kruskal(g);
                break;
            case 2:
                printf("������ͼ���ļ�����\n");
                getchar();
                gets(filename);
                creat(&g,filename,0);
                prim(g);
                break;
            case 3:
               break;
            case 4:
               edit=0;
               printf("����ѡ���ѽ������밴�������������\n");
               printf("\n--------------------------------->\n");
               break;
            default:
                printf("�������󣡣������������룡");
                break;
        }
    }
    return 0;
}

 void menu()
 {
    printf("          **********************************************************\n");
	printf("          *                                                        *\n");
	printf("          *    --------------------��ӭʹ��--------------------    *\n");
	printf("          *                                                        *\n");
	printf("          *                  ���ӳ��е���С������                  *\n");
	printf("          *                                                        *\n");
    printf("          **********************************************************\n");
	printf("          *              ѧ  Ժ���������ѧ�뼼��ѧԺ              *\n");
	printf("          *              ר  ҵ���������ѧ�뼼��רҵ              *\n");
	printf("          *              ��  ����     16070641��                   *\n");
	printf("          *                                                        *\n");
	printf("          *             ָ����ʦ��     ʦ�Ǳ�                      *\n");
	printf("          *             С���Ա�� ���ʺ�  ��Ӿ��                  *\n");
	printf("          *                        ��  ��  �Ŭr��                  *\n");
    printf("          **********************************************************\n");
	printf("          *        ���ܣ��㷨��ѡ�񣩣�                            *\n");
	printf("          *             1��ʹ��kruskal�㷨�����С������           *\n");
	printf("          *             2��ʹ��prim�㷨�����С������              *\n");
	printf("          *             3����������ѡ���㷨�����                  *\n");
	printf("          *             4���˳�ѡ��,�������                       *\n");
	printf("          **********************************************************\n");
	printf("          *                                                        *\n");
	printf("          *             ---------��л����ʹ��----------            *\n");
	printf("          * <ע��>��                                               *\n");
	printf("          *                                                        *\n");
	printf("          * H---������  W---��³ľ��  T---̫ԭ  C---����  F---���� *\n");
	printf("          *                                                        *\n");
	printf("          **********************************************************\n");
	printf("\n\n");
 }


 //����������ڽӾ����㷨
void creat(Mgraph *g,char *s,int c)
{
	int i,j,k,w;
	FILE *rf;
	rf=fopen(s,"r");
	if(rf)
    {
         //��ȡͼ�еĶ������ͱ���
		fscanf(rf,"%d%d",&g->n,&g->e);
		 //��ȡͼ�����еĶ���
		for(i=0;i<g->n;i++)
        {
            fscanf(rf,"%ls",&g->vexs[i]);
        }
		// ��ʼ���ڽӾ���
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
		//��������ı�
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


 //��ͼg���ڽӾ����ж�ȡͼ�����б���Ϣ
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


 //�Ա߽��п�������
 void QuickSort(edge edges[],int left,int right)
 {
	edge x;//���������Ƚϼ�¼�ı���
	int i,j;
	if(left<right)
	{//����һ����Ϊ�Ƚϱ�׼ֵ
		i=left;
		j=right;
		x=edges[i];
		while(i<j)
		{
			while(i<j && x.length<edges[j].length)
			{
                j--;//����������������С�ڱ�׼ֵ��λ��
			}
            if(i<j)
            {
                edges[i++]=edges[j];//�ҵ�������j��Ԫ�����ڵ�i��Ԫ��λ�ô�������i
            }
			while(i<j && x.length>edges[i].length)
            {
                i++;//������������������ڱ�׼ֵ��λ��
            }
            if(i<j)
            {
                edges[j--]=edges[i];//�ҵ����ҽ���i��Ԫ�ط��ڵ�j��λ�ô���������j
            }
		}
		edges[i]=x;//i=j,����λ�����ҵ�������׼ֵ��������λ��
		QuickSort(edges,left,i-1);i=j,//����λ�����ҵ�������׼ֵ��������λ��
		QuickSort(edges,i+1,right);//�Ա�׼ֵ�Ҳ��ݹ���ô˺���
	}
}


 //����kruskal�㷨�����С�������ʹ���
 void kruskal(Mgraph g)
 {
 	int i,j,k=0,ltfl;
 	int sum=0;//��С�������Ĵ���
 	int cnvx[M]; //����ÿ���������ͨ�������
 	edge edges[M*M];//���ڴ��ͼ�����б�
 	edge tree[M];//�����С�������ı�

    //��ͼg���ڽӾ����ж�ȡͼ�����б���Ϣ
 	GetEdge(g,edges);
 	//ʹ����������
	QuickSort(edges,0,g.e-1);
	//����ÿ���������ͨ����Ϊ�䶥����
	for(i=0;i<g.n;i++)
	    cnvx[i]=i;
	//��ʼ������С������
	for(i=0;i<g.n-1;i++)
	{
		//�ҵ�����������ͨ������Ȩֵ��С�ı�
		while(cnvx[edges[k].beg]==cnvx[edges[k].en])
			k++;
		tree[i]=edges[k];
		//ͨ���޶�����ͨ����ֵ��������ͨ�����ϲ���һ��
		ltfl=cnvx[edges[k].en];
		for(j=0;j<g.n;j++)
			if(cnvx[j]==ltfl)
				cnvx[j]=cnvx[edges[k].beg];
		k++;
	 }
	 printf("��С�������ǣ�\n");
	 for(j=0;j<g.n-1;j++)
	 {
	 	printf("%c---%c%6d\n",g.vexs[tree[j].beg],g.vexs[tree[j].en],tree[j].length);
	 	sum+=tree[j].length;
	 }
	 printf("����kruskal�㷨�����С�������Ĵ����ǣ�%d\n",sum);
 }

 //����prim�㷨�����С�������ʹ���
void prim(Mgraph g)
{
	edge x;
	edge tree[M-1];
	int sum=0;        //��С�������Ĵ���
	int d, min, j, k, s, v;
	//������ʼ��ѡ�㣬����ʼ���������ı߼�tree
	//��0���㿪ʼ
	for (v = 1; v <=g.n - 1; v++)
	{
		tree[v - 1].beg = 0;
		tree[v - 1].en = v;
		tree[v - 1].length = g.edges[0][v];
	}
	//������ǰ����k������С���ܱߣ�������tree��
	for (k = 0; k <= g.n - 3; k++)
	{
		//ѡ������
		min = tree[k].length;
		s = k;
		for (j = k + 1; j <= g.n - 2;j++)
		if (tree[j].length < min)
		{
			min = tree[j].length;
			s = j;
		}
		//��ѡ����v
		v = tree[s].en;

		x = tree[s];  tree[s] = tree[k]; tree[k]=x;
		//���ڼ����¶��㣬�޸����ܱߵĻ�����Ϣ
		for (j = k + 1; j <= g.n - 2; j++)
		{
			d = g.edges[v][tree[j].en];
			if (d < tree[j].length)
			{
				tree[j].length = d;  tree[j].beg = v;
			}
		}
	}
	printf("��С�������� ��\n");
	for (j = 0; j <=g.n - 2; j++)
    {
        printf("%c---%c  %d\n", g.vexs[tree[j].beg], g.vexs[tree[j].en], tree[j].length);
        sum+=tree[j].length;
    }
    printf("����prim�㷨�����С�������Ĵ����ǣ�%d\n",sum);
    printf("������ǣ� %c\n", g.vexs[0]);
}

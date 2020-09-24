#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<list>
#include<algorithm>
#include<math.h>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<iomanip>
#define MAXN 1002001
#define LL long long
#define eps 1e-8
#define inf 0x3f3f3f3f
using namespace std;
template <class T>
struct hufnode
{
    T wei;//Ȩֵ
    int id;
    struct hufnode *prt;//ָ�򸸽���ָ���򣨽��Ԫ�ص��±꣩
    struct hufnode *lch;//��ָ���򣨽��Ԫ�ص��±꣩
    struct hufnode *rch;//��ָ���򣨽��Ԫ�ص��±꣩
};
//���������±�һ���ǷǸ�����������˿�����-1��Ϊ��ָ��ֵ
template <class T>
class huffman_BT
{
    int nn;//Ҷ�ӽ��ĸ���
    hufnode<T>*BT;//���Ŷ�����˳��洢�ռ���׵�ַ
public:
    huffman_BT()
    {
        BT=NULL;   //���캯���������Ŷ��������г�ʼ��
    }
    void creat_hufm_BT(int n,T w[]);//�������Ŷ�����
    void select(hufnode<T>*p,int k,int *i,int *j);
    void prt_hufm_BT();
};
template <class T>
void huffman_BT<T>::creat_hufm_BT(int n,T w[])
{
    //n��Ҷ�ӽ��ĸ�����w��Ҷ�ӽ���Ȩֵ����
    hufnode<T> *p;
    int k,i,j,m;
    nn=n;
    m=n*2;
    BT=new hufnode<T>[m];//�������Ŷ������洢�ռ�
    p=BT;
    for(k=0; k<m; k++)
    {
        if(k!=0)
        {
            (p+k)->prt=p;
            (p+k)->wei=w[k];
        }
        else p->prt = NULL;
        (p+k)->lch=NULL;
        (p+k)->rch=NULL;
        (p+k)->id = k;
    }
    for(k=n+1; k<m; k++)
    {
        //�������Ŷ�����
        select(p,k,&i,&j);//��ǰK-1�������ѡ��Ȩֵ��С�����������i��j
        (p+i)->prt=p+k;
        (p+j)->prt=p+k;//�ϲ������µĶ�����
        (p+k)->lch=p+j;
        (p+k)->rch=p+i;
        (p+k)->wei=(p+i)->wei+(p+j)->wei;
    }
}
template <class T>
void huffman_BT<T>::select(hufnode<T>*p,int k,int *i,int *j)
{
    //��ǰK-1�������ѡ��Ȩֵ��С�����������i��j
    T w;
    int n=1;
    while(n<k&&(p+n)->prt->id!=0) n++;//Ѱ��ָ�򸸽��ָ��Ϊ�յ���ʼ���
    w=(p+n)->wei;
    *i=n;
    while(n<k)
    {
        if((((p+n)->wei)<w)&&((p+n)->prt->id==0))
        {
            *i=n;
            w=(p+n)->wei;
        }
        n++;
    }
    n=1;
    while((n<k&&(p+n)->prt->id!=0)||(n==(*i))) n++;
    w=(p+n)->wei;
    *j=n;
    while(n<k)
    {
        if(((p+n)->wei<w)&&(n!=(*i))&&((p+n)->prt->id==0))
        {
            *j=n;
            w=(p+n)->wei;
        }
        n++;
    }
    if((p+*i)->wei==(p+*j)->wei)//���ݾ���Ҫ���
    {
        n = (*i);
        *i = *j;
        *j = n;
    }
}
template <class T>
void huffman_BT<T>::prt_hufm_BT()
{
    hufnode <T>*p;
    hufnode <T>*q;
    int k,t;
    p=BT;
    char str[3000];
    for(k=1; k<=nn; k++)
    {
        int len = 0;
        t = k;
        q = (p+k)->prt;
        while(t!=2*nn-1)
        {
            if(q->lch->id == t)
                str[len++]= '0';
            else str[len++] = '1';
            t = q->id;
            q = q->prt;
        }
        for (int i = 0; i<len/2; i++)
        {
            char temp = str[i];
            str[i] = str[len-i-1];
            str[len-i-1] = temp;
        }
        for(int i=0; i<len; i++)
            printf("%c",str[i]);
        printf("\n");
    }
}

int main()
{
    int *w;
    huffman_BT<int> b;
    int sum;
    while(scanf("%d",&sum)!=EOF)
    {
        w=new int[sum+1];
        for(int i=1; i<=sum; i++)
         scanf("%d",&w[i]);
        b.creat_hufm_BT(sum,w);
        b.prt_hufm_BT();
    }
    return 0;
}


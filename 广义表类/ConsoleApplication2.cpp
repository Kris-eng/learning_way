#include <iostream>

#define atom_node 0

using namespace std;
typedef enum
{
    atom,
    list
} NodeTag;
typedef struct GLNode
{
    NodeTag tag;
    int num;
    union
    {
        char data;
        struct GLNode* slink;
    };
    struct GLNode* next;
} *Glist;
Glist memory1, memory2;   //临时存储全局变量
int len = 0;


class general_list
{
public:
    Glist root;
    general_list();
    ~general_list();
    Glist creat_list(Glist GL);
    void add_endnum(Glist GL, int num, Glist GL2);
    void adjust_num(Glist GL);
    void remove(Glist GL, int num);
    void print_list(Glist GL);
    void find_bynum(Glist GL, int num, bool flag);
    void destory(Glist GL);
    void depth(Glist GL, int* maxdh);
    void lenth(Glist GL);
    void find_bys(Glist GL, char x);
    general_list &operator +(general_list &b)
    {
        int a;
     /*   while (1)
        {
            if (this->root==NULL)
            {
                a = this->root->num;
            }
            
        }*/
        lenth(root);
        add_endnum(this->root, 4, b.root);
        print_list(this->root);
        return *this;
    }

private:
    int i = 0;
    int j = 0;
};

general_list::general_list()
{
    root = 0;
    root = creat_list(root);
   
}

general_list::~general_list()
{
   // destory(root);
}


Glist general_list::creat_list(Glist GL)  //创建广义表
{
    char ch;
    scanf_s("%c", &ch,1);
    if (ch != '\0')
    {
 /*       while (GL==NULL)
        {
            GL = (struct GLNode*)malloc(sizeof(struct GLNode));
        }*/
        GL = (struct GLNode*)malloc(sizeof(struct GLNode));

        GL->num = i;

        if (ch == '(')
        {
            GL->tag = list;
            GL->slink = creat_list(GL->slink);
        }
        else
        {
            i++;
            GL->tag = atom;
            GL->data = ch;
            GL->num = i;
        }
    }
    else
    {
        GL = NULL;
    }
    scanf_s("%c", &ch,1);
    if (ch == ',')
    {
        GL->next = creat_list(GL->next);
    }
    else
    {
        GL->next = NULL;
    }
    return GL;
}
Glist GL_add;
void general_list::add_endnum(Glist GL, int num, Glist GL2)   //增加元素
{

    GL_add = GL2;
    if (GL != NULL)
    {
        if (GL->tag == atom && GL->num == num)
        {

            // flag = true;
            Glist P;
            P = GL->next;
            GL->next = GL_add;
            GL->next->next = P;
            cout << "sucess" << endl;
            //free(P);
            //free(GL_add);
        }
        else
        {
            if (GL->tag == list)
            {
                add_endnum(GL->slink, num, GL2);
            }
            add_endnum(GL->next, num, GL2);
        }
    }
}
//int j = 0;
void general_list::adjust_num(Glist GL)   //调整序号
{
    if (GL != NULL)
    {
        if (GL->tag == list)
        {
            if (GL->slink == NULL)
                ;
            else
            {
                adjust_num(GL->slink);
            }
        }
        else
            GL->num = ++j;
        if (GL->next != NULL)
            adjust_num(GL->next);
    }
    j = 0;
}
void general_list::remove(Glist GL, int num)  //删除元素
{
    if (GL != NULL)
    {
        if (GL->tag == atom && GL->num == num - 1)
        {
            Glist a;
            a = GL->next->next;
            // free(GL->next);
            GL->next = a;
            //free(a);
        }
        else
        {
            if (GL->tag == list)
            {
                remove(GL->slink, num);
            }
            remove(GL->next, num);
        }
    }
}
void general_list::print_list(Glist GL)  //打印广义表
{
    if (GL != NULL)
    {
        if (GL->tag == list)
        {
            printf("(");
            if (GL->slink == NULL)
            {
                cout << "  ";
            }
            else
                print_list(GL->slink);
        }
        else
            printf("%c (%d)", GL->data, GL->num);
        if (GL->tag == list)
            printf(")");
        if (GL->next != NULL)
        {
            printf(",");
            print_list(GL->next);
        }
    }
    else
        cout << "空" << endl;
}
void general_list::find_bynum(Glist GL, int num, bool flag)  //通过序号查找
{
    if (GL != NULL)
    {
        if (GL->tag == atom && GL->num == num)
        {
            cout << "sucess" << endl;
            flag = true;
            memory1 = GL;
            cout << GL->data;
        }
        else
        {
            if (GL->tag == list)
            {
                find_bynum(GL->slink, num, flag);
            }
            find_bynum(GL->next, num, flag);
        }
    }
}
void general_list::destory(Glist GL)       //   销毁广义表
{
    if (GL == NULL)
    {

        if (GL->tag == list)
        {
            Glist b;
            b = GL;
            GL = NULL;
            free(GL);
            destory(b->slink);
            b = NULL;
            free(b);
        }
        else
        {
            Glist c;
            c = GL;
            GL = NULL;
            free(GL);
            destory(c->next);
            c = NULL;
            free(c);

        }
    }
}

void general_list::find_bys(Glist GL, char x)   //通过字符串查找
{
    if (GL != NULL)
    {
        //cout<<"666";
        //int **p;
        //*p=&GL->data;

        cout << GL->num << "  " << GL->tag << "  " << GL->data << "  " << "  " << x << endl;

        if ((!(GL->tag)) && (GL->data == x))
        {

            if (GL->data == x)
            {
                //cout<<"666";
                cout << GL->num << endl;
            }
            
        }
        else
        {
            if (GL->tag == 1)
                find_bys(GL->slink, x);
            find_bys(GL->next, x);
        }
    }
}

void general_list::depth(Glist GL, int* maxdh)  //求深度
{
    int h; 
    if (GL->tag == 0)
        *maxdh = 0;
    else
    {
        GL = GL->slink;
        *maxdh = 0;
        do
        {
            depth(GL, &h);
            if (h > *maxdh)
                *maxdh = h;
            GL = GL->next;
        } while (GL != NULL);
        *maxdh = *maxdh + 1;

    }

}
//int len=0;
void general_list::lenth(Glist GL )
{
    //int h;
    cout << 666 << endl;
    if (GL->next!=NULL)
    {
        len++;
       //cout << 666 << endl;
        lenth(GL->next);
    }
    else
    {
        //cout <<666<< endl;
        len = 0;
    }
}
int main(void)
{

    general_list t1;   
    cout << "请输入一个广义表："<<endl;
    bool flag = false;
    t1.print_list(t1.root);
    cout << endl;
    
    general_list t2;
    cout << "请输入第二个广义表添加在1表末尾：" << endl;
    t1.add_endnum(t1.root, 1, t2.root);
    t1.adjust_num(t1.root);
    
    t1.print_list(t1.root);
    cout << endl;
    t1.remove(t1.root, 2);
    t1.adjust_num(t1.root);
    t1.print_list(t1.root);
    cout << endl;
    t1 = t1 + t2;
    cout << "广义表重载相加："<<endl;
    t1.adjust_num(t1.root);
    t1.print_list(t1.root);
    cout << endl;
    cout << "通过序号查找："<<endl;
    t1.find_bynum(t1.root, 2, flag);
    cout << endl;
    t1.find_bys(t1.root, '3');
    int h;   
    t1.lenth(t1.root);
    cout << "len:" << len << endl;
    t1.depth(t1.root,&h);
    cout <<"深度为：" << h << endl;
    t1.lenth(t1.root);
    cout <<"len:" << len << endl;
    printf("finish");
    system("pause");
}
/*
 * File Processing, 2020
 * BST.cpp
 * BST implementation
 */
#define max(a, b)   (((a) > (b)) ? (a) : (b))
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <tchar.h>



// ���
typedef struct BSTNode
{
    int key;
    struct BSTNode* left, * right;
}BSTNode;


BSTNode* getNode(int k) //----------------------------------------------getNode()����
{
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    node->key = k;
    node->left = node->right = NULL;
    return node;
}

int noNodes(BSTNode* node) //-------------------------------------------noNodes()����
{
    int count = 0;
    if (node != NULL)
    {
        count = 1 + noNodes(node->left) + noNodes(node->right);
    }
    return count;
}


int height(BSTNode* node) //--------------------------------------------height()����
{
    int h = 0;
    if (node != NULL)
    {
        h = 1 + max(height(node->left), height(node->right));
    }
    return h;
}

BSTNode* minNode(BSTNode* node) //-------------------------------------minNode()������ subTree���� �ּҰ��� ���ϴ� �Լ� ����
{
    while (node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

BSTNode* maxNode(BSTNode* node) //-------------------------------------maxNode()���� subTree���� �ִ밪�� ���ϴ� �Լ� ����
{
    while (node->right != NULL)
    {
        node = node->right;
    }
    return node;
}


void insertBST(BSTNode** root, int key)//-------------------------------insertBST() ���Ծ˰��� ����
{
    BSTNode* q, * p;    // q�� �θ���, p�� q�� �ڽ�
    BSTNode* n;        // n�� newNode

    p = *root;
    q = NULL;
    // �켱 Ž��
    while (p != NULL)
    {
        if (key == p->key)
        {
            return;
        }
        q = p;
        if (key < p->key)
        {
            p = p->left;
        }
        else
        {
            p = p->right;
        }
    }

    n = getNode(key); //getNode()�Լ��� �̿��� ������ ���ο� Node����

    if (n == NULL)
    {
        return;
    }

    if (q != NULL) //Link
    {
        if (key < q->key)
        {
            q->left = n;
        }
        else
        {
            q->right = n;
        }
    }
    else
    {
        *root = n;
    }
}

// ��� ����
void deleteBST(BSTNode*root, int key)//-------------------------------deleteBST() �����˰��� ����
{
    BSTNode* q, * p, * c; //q�� �θ���, p�� q�� �ڽĳ��
    BSTNode* r, * s; //������ 2�϶��� ����ؼ� ���� ���� s�� r�� �θ���


    q = NULL;
    p = *root;
    while ((p != NULL) && (p->key != key))
    {
        q = p;
        p = (key < p->key) ? p->left : p->right;
    }

    if (p == NULL)
    {
        printf("�ش� Ű�� ���� ��尡 �������� �ʽ��ϴ�.");
        return;
    }

    // case1 . ������ 0 �϶�
    if ((p->left == NULL) && (p->right == NULL))
    {
        if (q != NULL)
        {
            if (q->left == p)
            {
                q->left = NULL;
            }
            else
            {
                q->right = NULL;
            }
        }
        else    // ���� �θ��尡 NULL�̸� �����Ǵ� ��� = root
        {
            *root = NULL;
        }
    }
    // case2 . ������ 1 �϶�
    else if ((p->left == NULL) || (p->right == NULL))
    {
        c = (p->left != NULL) ? p->left : p->right;
        if (q != NULL)
        {
            if (q->left == p)
            {
                q->left = c;
            }
            else
            {
                q->right = c;
            }
        }
        else    // ���� �θ��尡 NULL�̸� �����Ǵ� ��� = root
        {
            *root = c;
        }
    }
    // case3 . ������ 2 �϶�
    else if ((!(p->left == NULL)) && (!(p->right == NULL)))
    {
        // ������ ����Ʈ���� ���̰� ���� ����Ʈ���� ���̺��� Ŭ ���,������ ����Ʈ������ �İ��ڸ� ã�´�
        if (height(p->right) > height(p->left)) {
            s = p;
            r = p->right;
            while (r->left != NULL)
            {
                s = r;
                r = s->left;
            }
            r = minNode(r);
            if (s->left == r)
            {
                s->left = r->right;
                p->key = r->key;
            }
            else
            {
                s->right = r->right;
                p->key = r->key;
            }
        }
        else if (height(p->right) < height(p->left)) {
        // ���� ����Ʈ���� ���̰� ������ ����Ʈ���� ���̺��� Ŭ ���,���� ����Ʈ������ �ļ��� Ž��
            s = p;
            r = p->left;
             while (r->right != NULL)
             {
                 s = r;
                 r = s->right;
             }
             r = maxNode(r);
             if  (s->right == r)
             {
                 s->right = r->left;
                 p->key = r->key;
             }
             else
             { 
                 s->left = r->left;
                 p->key = r->key;
             }
        }
        else if (height(p->right) == height(p->left)) {   // ���� ����Ʈ���� ���̰� ������ ����Ʈ���� ���̿� ���� ����� ������ ������ ũ�ų� ���� ���,���� ����Ʈ������ �ļ��ڸ� ã�´�
             if (noNodes(p->left) >= noNodes(p->right)) {
                s = p;
                r = p->left;
                while (r->right != NULL)
                {
                    s = r;
                    r = s->right;
                }
                r = maxNode(r);
                if (s->right == r)
                {
                    s->right = r->left;
                    p->key = r->key;
                }
                else
                {
                    s->left = r->left;
                    p->key = r->key;
                }
             }
             else {
                 s = p;
                 r = p->right;
                 while (r->left != NULL)
                 {
                     s = r;
                     r = s->left;
                 }
                 r = minNode(r);
                 if (s->left == r)
                 {
                     s->left = r->right;
                     p->key = r->key;
                 }
                 else
                 {
                     s->right = r->right;
                     p->key = r->key;
                }
            }
        }
    }
}


// ���� ��ȸ
void inorderBST(BSTNode* root)
{
    if (root)
    {
        inorderBST(root->left);         // ���� ����Ʈ�� ��ȸ
        printf("%d  ", root->key);  // ��� �湮
        inorderBST(root->right);      // ������ ����Ʈ�� ��ȸ
    }
}



int _tmain(int argc, _TCHAR* argv[])
{
    BSTNode* n1 = NULL;
    //����
    printf("\n");
    printf("���Խ���");
    printf("\n""\n");

    insertBST(&n1, 25);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 500);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 33);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 49);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 17);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 403);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 29);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 105);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 39);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 66);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 305);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 44);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 19);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 441);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 390);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 12);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 81);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 50);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 100);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 999);
    inorderBST(n1);
    printf("\n");

    printf("\n");
    printf("��������");
    printf("\n""\n");

    //���� ����
    deleteBST(&n1, 25);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 500);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 33);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 49);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 17);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 403);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 29);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 105);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 39);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 66);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 305);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 44);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 19);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 441);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 390);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 12);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 81);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 50);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 100);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 999);
    inorderBST(n1);
    printf("���� �����Ϸ�");
    printf("\n"); //������ delete�� ������ "���������Ϸ�" ���� ���


    //�����

    printf("\n");
    printf("���Խ���");
    printf("\n""\n");

    insertBST(&n1, 25);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 500);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 33);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 49);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 17);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 403);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 29);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 105);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 39);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 66);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 305);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 44);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 19);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 441);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 390);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 12);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 81);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 50);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 100);
    inorderBST(n1);
    printf("\n");
    insertBST(&n1, 999);
    inorderBST(n1);
    printf("\n");

    printf("\n");
    printf("��������");
    printf("\n""\n");

    //���� ����
    deleteBST(&n1, 999);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 100);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 50);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 81);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 12);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 390);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 441);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 19);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 44);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 305);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 66);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 39);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 105);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 29);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 403);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 17);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 49);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 33);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 500);
    inorderBST(n1);
    printf("\n");
    deleteBST(&n1, 25);
    inorderBST(n1);
    printf("���� �����Ϸ�");
    printf("\n"); //������ delete�� ������ "���������Ϸ�" ���� ���
    return 0;
}

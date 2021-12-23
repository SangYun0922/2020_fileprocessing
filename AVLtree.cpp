/*
 * File Processing, 2020
 * AVLtree.cpp
 * AVLtree implementation
 */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <tchar.h>

#define max(a, b)   (((a) > (b)) ? (a) : (b))

// ���
typedef struct Node
{
    int key, bf;
    struct Node* left, * right;
} Node;

typedef Node* Tree;

int balance(Node* k)
{
    if (k == NULL)
        return 0;
    else
        return k->bf;
}



Node* getNode(int k) //----------------------------------------------getNode()����
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = k;
    node->bf = 0;
    node->left = node->right = NULL;
    return node;
}

int noNodes(Node* node) //-------------------------------------------noNodes()����
{
    int count = 0;
    if (node != NULL)
    {
        count = 1 + noNodes(node->left) + noNodes(node->right);
    }
    return count;
}

int height(Node* node) //--------------------------------------------height()����
{
    int h = 0;
    if (node == NULL)
        return 0;
    else
    {
        h = 1 + max(height(node->left), height(node->right));
        return h;
    }
}

int height_subtract(Node* k) //--------------------------------------���ʼ���Ʈ���� �����ʼ���Ʈ���� �� 
{
    return height(k->left) - height(k->right);
}

Node* minNode(Node* node) //-------------------------------------minNode()������ subTree���� �ּҰ��� ���ϴ� �Լ� ����
{
    while (node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

Node* maxNode(Node* node) //-------------------------------------maxNode()���� subTree���� �ִ밪�� ���ϴ� �Լ� ����
{
    while (node->right != NULL)
    {
        node = node->right;
    }
    return node;
}

void updateBF(Tree* T, Node* y, Node** x, Node** p) {
    Node* r = *T; //s�� �θ��� r�� q�� �ڽĳ��
    Node* s = NULL;
    while (s != y)
    {
        r->bf = height_subtract(r);
        if ((r->bf >= 2) || (r->bf <= -2)) { 
            *x = r;
            *p = s;
        }
        s = r;
        if (r->key > y->key)
        {
            r = r->left;
        }
        else if (r->key < y->key)
        {
            r = r->right;
        }
    }
}

void rotateLL(Tree* T, Node* x, Node* p) {
    Node* c = NULL; //x�� �ڽĳ��
    c = x->left; //c�� x�� �����ڽ�
    x->left = c->right; //x�� ���������͸� c�� ������ ����Ʈ���� ����
    c->right = x; //c�� ������ �����ʹ� x�� ����Ű����

    if (p == NULL) { //case1. x�� �θ����� p�� NULL�϶�,
        *T = c;//c�� ��Ʈ���
        c->bf = height_subtract(c); // bf������
        x->bf = height_subtract(x);// bf������
    }

    else {
        if (p->left == x) { //case2. x�� p�� ���� child�϶�,
            p->left = c; //�θ��� p�� ���������Ͱ� c�� ����Ű����
            c->bf = height_subtract(c);// bf������
            x->bf = height_subtract(x);// bf������
            p->bf = height_subtract(p);// bf������
        }

        else if (p->right == x) { //case3. x�� p�� ������ child�϶�,
            p->right = c; //�θ��� p�� �����������Ͱ� c�� ����Ű����
            c->bf = height_subtract(c);// bf������
            x->bf = height_subtract(x);// bf������
            p->bf = height_subtract(p);// bf������
        }
    }
}

void rotateRR(Tree* T, Node* x, Node* p) {
    Node* c = NULL; //x�� �ڽĳ��
    c = x->right; //c�� x�� ������ �ڽ�
    x->right = c->left;//x�� ������ �����͸� c�� ���� ����Ʈ���� ����
    c->left = x; //c�� ���������ʹ� x�� ����Ű����

    if (p == NULL) { //case1. x�� �θ����� p�� NULL�϶�,
        c->bf = height_subtract(c);// bf������
        x->bf = height_subtract(x);// bf������
        *T = c; //c�� ��Ʈ���
    }

    else {
        if (p->left == x) { //case2. x�� p�� ���� child�϶�,
            p->left = c; //�θ��� p�� ���������Ͱ� c�� ����Ű����
            c->bf = height_subtract(c);// bf������
            x->bf = height_subtract(x);// bf������
            p->bf = height_subtract(p);// bf������

        }

        else if (p->right == x) { //case3. x�� p�� ������ child�϶�,
            p->right = c; //�θ��� p�� �����������Ͱ� c�� ����Ű����
            c->bf = height_subtract(c);// bf������
            x->bf = height_subtract(x);// bf������
            p->bf = height_subtract(p);// bf������
        }
    }

}

void rotateLR(Tree* T, Node* x, Node* p) {
    rotateRR(&x, x->left, x);
    rotateLL(T, x, p);

}

void rotateRL(Tree* T, Node* x, Node* p) {
    rotateLL(&x, x->right, x);
    rotateRR(T, x, p);
}

Node* insertBST(Tree* T, int newKey) {
    Node* q, * p;    // q�� �θ���, p�� q�� �ڽ�
    Node* n;        // n�� newNode

    p = *T;
    q = NULL;
    // �켱 Ž��
    while (p != NULL)
    {
        if (newKey == p->key)
        {
            return NULL;
        }
        q = p;
        if (newKey < p->key)
        {
            p = p->left;
        }
        else
        {
            p = p->right;
        }
    }
    n = getNode(newKey); //getNode()�Լ��� �̿��� ������ ���ο� Node����

    if (q != NULL) //Link
    {
        if (newKey < q->key)
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
        *T = n;
    }
    return n;
}

void insertAVL(Tree* T, int newKey) {
    /**
     * print "NO" if not rotates
     * print "LL" if rotates LL
     * print "RR" if rotates RR
     * print "LR" if rotates LR
     * print "RL" if rotates RL
     */
    Node* s = nullptr;  // t�� �θ��� s�� t�� �ڽ�
    Node* t = nullptr;
    Node* u = insertBST(T, newKey);
    updateBF(T, u, &s, &t);


    if (balance(s) >= 2)
    {
        if (balance(s->left) < 0)
        {
            rotateLR(T, s, t);
            printf("LR");
        }
        else {
            rotateLL(T, s, t);
            printf("LL");
        }
    }
    else if (balance(s) <= -2)
    {
        if (balance(s->right) > 0)
        {
            rotateRL(T, s, t);
            printf("RL");
        }
        else {
            rotateRR(T, s, t);
            printf("RR");
        }
    }
    else if (s == NULL)
    {
        printf("NO");
    }
}

Node* deleteBST(Tree* T, int deleteKey) {
    Node* q, * p, * c; //q�� �θ���, p�� q�� �ڽĳ��
    Node* r, * s; //������ 2�϶��� ����ؼ� ���� ���� s�� r�� �θ���

    q = NULL;
    p = *T;

    while ((p != NULL) && (p->key != deleteKey))
    {
        q = p;
        p = (deleteKey < p->key) ? p->left : p->right;
    }

    if (p == NULL)
    {
        printf("�ش� Ű�� ���� ��尡 �������� �ʽ��ϴ�.");
        return q;
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
            return q;
        }
        else    // ���� �θ��尡 NULL�̸� �����Ǵ� ��� = root
        {
            *T= NULL;
            return q;
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
            return q;
        }
        else    // ���� �θ��尡 NULL�̸� �����Ǵ� ��� = root
        {
            *T = c;
            return q;
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
            return s;
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
            return s;
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
                return s;
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
                return s;
            }
        }
    }
}

void deleteAVL(Tree* T, int deleteKey) {
    /**
     * print "NO" if not rotates
     * print "LL" if rotates LL
     * print "RR" if rotates RR
     * print "LR" if rotates LR
     * print "RL" if rotates RL
     */
    /**
    Node* p = NULL; // q�� �θ���, p�� q�� �ڽ�
    Node* q = NULL;
    Node* r = NULL;
    r = deleteBST(T, deleteKey);
    updateBF(T, r, &p, &q); **/

    Node* s = nullptr;  // t�� �θ��� s�� t�� �ڽ�
    Node* t = nullptr;
    Node* u = deleteBST(T, deleteKey);
    updateBF(T, u, &s, &t);


    if (balance(s) >= 2)
    {
        if (balance(s->left) < 0)
        {
            rotateLR(T, s, t);
            printf("LR");
        }
        else {
            rotateLL(T, s, t);
            printf("LL");
        }
    }
    else if (balance(s) <= -2)
    {
        if (balance(s->right) > 0)
        {
            rotateRL(T, s, t);
            printf("RL");
        }
        else {
            rotateRR(T, s, t);
            printf("RR");
        }
    }

    else if (s == NULL)
    {
        printf("NO");
    }
}

void inorderAVL(Tree T) {
    if (T)
    {
        inorderAVL(T->left);
        printf("%d  ", T->key);
        inorderAVL(T->right);
    }
}

int main() {
    /* Do not modify the code below */
        int testcase[] = { 40, 11, 77, 33, 20, 90, 99, 70, 88, 80, 66, 10, 22, 30, 44, 55, 50, 60, 25, 49 };
        Tree T = NULL;
        // insertion
        for (int i = 0; i < 20; i++) { printf("%d ", testcase[i]); insertAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }
        // deletion 
        for (int i = 0; i < 20; i++) { printf("%d ", testcase[i]); deleteAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }
        T = NULL;
        // reinsertion
        for (int i = 0; i < 20; i++) { printf("%d ", testcase[i]); insertAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }
        // redeletion
        for (int i = 19; 0 <= i; i--) { printf("%d ", testcase[i]); deleteAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }
}






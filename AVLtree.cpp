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

// 노드
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



Node* getNode(int k) //----------------------------------------------getNode()구현
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = k;
    node->bf = 0;
    node->left = node->right = NULL;
    return node;
}

int noNodes(Node* node) //-------------------------------------------noNodes()구현
{
    int count = 0;
    if (node != NULL)
    {
        count = 1 + noNodes(node->left) + noNodes(node->right);
    }
    return count;
}

int height(Node* node) //--------------------------------------------height()구현
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

int height_subtract(Node* k) //--------------------------------------왼쪽서브트리와 오른쪽서브트리의 차 
{
    return height(k->left) - height(k->right);
}

Node* minNode(Node* node) //-------------------------------------minNode()오른쪽 subTree에서 최소값을 구하는 함수 구현
{
    while (node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

Node* maxNode(Node* node) //-------------------------------------maxNode()왼쪽 subTree에서 최대값을 구하는 함수 구현
{
    while (node->right != NULL)
    {
        node = node->right;
    }
    return node;
}

void updateBF(Tree* T, Node* y, Node** x, Node** p) {
    Node* r = *T; //s는 부모노드 r은 q의 자식노드
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
    Node* c = NULL; //x의 자식노드
    c = x->left; //c는 x의 왼쪽자식
    x->left = c->right; //x의 왼쪽포인터를 c의 오른쪽 서브트리로 연결
    c->right = x; //c의 오른쪽 포인터는 x를 가리키게함

    if (p == NULL) { //case1. x의 부모노드인 p가 NULL일때,
        *T = c;//c가 루트노드
        c->bf = height_subtract(c); // bf재조정
        x->bf = height_subtract(x);// bf재조정
    }

    else {
        if (p->left == x) { //case2. x가 p의 왼쪽 child일때,
            p->left = c; //부모노드 p의 왼쪽포인터가 c를 가리키게함
            c->bf = height_subtract(c);// bf재조정
            x->bf = height_subtract(x);// bf재조정
            p->bf = height_subtract(p);// bf재조정
        }

        else if (p->right == x) { //case3. x가 p의 오른쪽 child일때,
            p->right = c; //부모노드 p의 오른쪽포인터가 c를 가리키게함
            c->bf = height_subtract(c);// bf재조정
            x->bf = height_subtract(x);// bf재조정
            p->bf = height_subtract(p);// bf재조정
        }
    }
}

void rotateRR(Tree* T, Node* x, Node* p) {
    Node* c = NULL; //x의 자식노드
    c = x->right; //c는 x의 오른쪽 자식
    x->right = c->left;//x의 오른쪽 포인터를 c의 왼쪽 서브트리로 연결
    c->left = x; //c의 왼쪽포인터는 x를 가리키게함

    if (p == NULL) { //case1. x의 부모노드인 p가 NULL일때,
        c->bf = height_subtract(c);// bf재조정
        x->bf = height_subtract(x);// bf재조정
        *T = c; //c가 루트노드
    }

    else {
        if (p->left == x) { //case2. x가 p의 왼쪽 child일때,
            p->left = c; //부모노드 p의 왼쪽포인터가 c를 가리키게함
            c->bf = height_subtract(c);// bf재조정
            x->bf = height_subtract(x);// bf재조정
            p->bf = height_subtract(p);// bf재조정

        }

        else if (p->right == x) { //case3. x가 p의 오른쪽 child일때,
            p->right = c; //부모노드 p의 오른쪽포인터가 c를 가리키게함
            c->bf = height_subtract(c);// bf재조정
            x->bf = height_subtract(x);// bf재조정
            p->bf = height_subtract(p);// bf재조정
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
    Node* q, * p;    // q는 부모노드, p는 q의 자식
    Node* n;        // n은 newNode

    p = *T;
    q = NULL;
    // 우선 탐색
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
    n = getNode(newKey); //getNode()함수를 이용해 삽입할 새로운 Node생성

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
    Node* s = nullptr;  // t는 부모노드 s는 t의 자식
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
    Node* q, * p, * c; //q는 부모노드, p는 q의 자식노드
    Node* r, * s; //차수가 2일때에 대비해서 따로 정의 s는 r의 부모노드

    q = NULL;
    p = *T;

    while ((p != NULL) && (p->key != deleteKey))
    {
        q = p;
        p = (deleteKey < p->key) ? p->left : p->right;
    }

    if (p == NULL)
    {
        printf("해당 키를 가진 노드가 존재하지 않습니다.");
        return q;
    }

    // case1 . 차수가 0 일때
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
        else    // 만약 부모노드가 NULL이면 삭제되는 노드 = root
        {
            *T= NULL;
            return q;
        }
    }
    // case2 . 차수가 1 일때
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
        else    // 만약 부모노드가 NULL이면 삭제되는 노드 = root
        {
            *T = c;
            return q;
        }
    }
    // case3 . 차수가 2 일때
    else if ((!(p->left == NULL)) && (!(p->right == NULL)))
    {
        // 오른쪽 서브트리의 높이가 왼쪽 서브트리의 높이보다 클 경우,오른쪽 서브트리에서 후계자를 찾는다
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
            // 왼쪽 서브트리의 높이가 오른쪽 서브트리의 높이보다 클 경우,왼쪽 서브트리에서 후속자 탐색
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
        else if (height(p->right) == height(p->left)) {   // 왼쪽 서브트리의 높이가 오른쪽 서브트리의 높이와 같고 노드의 개수가 왼쪽이 크거나 같은 경우,왼쪽 서브트리에서 후속자를 찾는다
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
    Node* p = NULL; // q는 부모노드, p는 q의 자식
    Node* q = NULL;
    Node* r = NULL;
    r = deleteBST(T, deleteKey);
    updateBF(T, r, &p, &q); **/

    Node* s = nullptr;  // t는 부모노드 s는 t의 자식
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






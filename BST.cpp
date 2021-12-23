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



// 노드
typedef struct BSTNode
{
    int key;
    struct BSTNode* left, * right;
}BSTNode;


BSTNode* getNode(int k) //----------------------------------------------getNode()구현
{
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    node->key = k;
    node->left = node->right = NULL;
    return node;
}

int noNodes(BSTNode* node) //-------------------------------------------noNodes()구현
{
    int count = 0;
    if (node != NULL)
    {
        count = 1 + noNodes(node->left) + noNodes(node->right);
    }
    return count;
}


int height(BSTNode* node) //--------------------------------------------height()구현
{
    int h = 0;
    if (node != NULL)
    {
        h = 1 + max(height(node->left), height(node->right));
    }
    return h;
}

BSTNode* minNode(BSTNode* node) //-------------------------------------minNode()오른쪽 subTree에서 최소값을 구하는 함수 구현
{
    while (node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

BSTNode* maxNode(BSTNode* node) //-------------------------------------maxNode()왼쪽 subTree에서 최대값을 구하는 함수 구현
{
    while (node->right != NULL)
    {
        node = node->right;
    }
    return node;
}


void insertBST(BSTNode** root, int key)//-------------------------------insertBST() 삽입알고리즘 구현
{
    BSTNode* q, * p;    // q는 부모노드, p는 q의 자식
    BSTNode* n;        // n은 newNode

    p = *root;
    q = NULL;
    // 우선 탐색
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

    n = getNode(key); //getNode()함수를 이용해 삽입할 새로운 Node생성

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

// 노드 삭제
void deleteBST(BSTNode*root, int key)//-------------------------------deleteBST() 삭제알고리즘 구현
{
    BSTNode* q, * p, * c; //q는 부모노드, p는 q의 자식노드
    BSTNode* r, * s; //차수가 2일때에 대비해서 따로 정의 s는 r의 부모노드


    q = NULL;
    p = *root;
    while ((p != NULL) && (p->key != key))
    {
        q = p;
        p = (key < p->key) ? p->left : p->right;
    }

    if (p == NULL)
    {
        printf("해당 키를 가진 노드가 존재하지 않습니다.");
        return;
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
        }
        else    // 만약 부모노드가 NULL이면 삭제되는 노드 = root
        {
            *root = NULL;
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
        }
        else    // 만약 부모노드가 NULL이면 삭제되는 노드 = root
        {
            *root = c;
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


// 중위 순회
void inorderBST(BSTNode* root)
{
    if (root)
    {
        inorderBST(root->left);         // 왼쪽 서브트리 순회
        printf("%d  ", root->key);  // 노드 방문
        inorderBST(root->right);      // 오른쪽 서브트리 순회
    }
}



int _tmain(int argc, _TCHAR* argv[])
{
    BSTNode* n1 = NULL;
    //삽입
    printf("\n");
    printf("삽입시작");
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
    printf("삭제시작");
    printf("\n""\n");

    //정순 삭제
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
    printf("정순 삭제완료");
    printf("\n"); //마지막 delete가 끝나면 "정순삭제완료" 문구 출력


    //재삽입

    printf("\n");
    printf("삽입시작");
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
    printf("삭제시작");
    printf("\n""\n");

    //역순 삭제
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
    printf("역순 삭제완료");
    printf("\n"); //마지막 delete가 끝나면 "역순삭제완료" 문구 출력
    return 0;
}

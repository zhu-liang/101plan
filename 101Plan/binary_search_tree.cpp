//
//  binary_search_tree.cpp
//  101Plan
//
//  Created by zl on 22/01/17.
//  Copyright © 2017年 zhu-liang. All rights reserved.
//

#include "binary_search_tree.hpp"
#include <stack>
#include <list>

using namespace std;

typedef int KeyType;
typedef struct Node
{
    KeyType key;
    Node* left;
    Node* right;
    Node* parent;
}NODE, *PNODE;

// 往二叉树中插入节点
void insert(PNODE* root, KeyType key)
{
    //初始化要插入的节点
    PNODE p = new Node();
    p->key = key;
    p->left = p->right = p->parent = NULL;
    
    //空树时，直接作为根节点
    if (NULL == *root) {
        *root = p;
        return;
    }
    
    //插入到当前节点的 左孩子， 如果左孩子节点为空，且要插入的键值比当前根节点的键值要小
    if ((*root)->left == NULL && (*root)->key > key)
    {
        p->parent = *root;
        (*root)->left = p;
        return;
    }
    
    //插入到当前节点的 右孩子， 如果右孩子节点为空， 且要插入的键值比当前节点的键值大
    if ((*root)->right == NULL && (*root)->key < key)
    {
        p->parent = *root;
        (*root)->right = p;
        return;
    }
    
    //继续递归， 根据键值比较，选择往左边走，还是往右边走
    if ((*root)->key > key ) {
        insert(&(*root)->left, key);
    } else if ((*root)->key < key) {
        insert(&(*root)->right, key);
    } else {
        return;
    }
}

// 查找键值为key的节点，如果查找成功返回指向该节点的指针，否则返回null
PNODE search(PNODE root, KeyType key)
{
    if (NULL == root)
        return NULL;
    if (root->key > key) {
        return search(root->left, key);
    } else if (root->key < key) {
        return search(root->right, key);
    } else {
        return root;
    }
}
// 查找键值为key的节点，非递归实现
PNODE search_nr(PNODE root, KeyType key)
{
    PNODE p = root;
    if (NULL == root)
        return NULL;
    
    while(p) {
        if (p->key == key) {
            return p;
        }
        else if (p->key > key) {
            p = p->left;
        } else if (p->key < key) {
            p = p->right;
        }
    }
    
    return NULL;
}

// 查找最小键值节点，空树返回NULL
PNODE searchMin(PNODE root)
{
    if (NULL == root) {
        return NULL;
    } else if (root->left == NULL) {
        return root;
    } else {
        return searchMin(root->left);
    }
}

// 查找最大键值节点，空树返回NULL
PNODE searchMax(PNODE root)
{
    if (NULL == root) {
        return NULL;
    } else if (root->right == NULL) {
        return root;
    } else {
        return searchMax(root->right);
    }
}

// 查找前驱节点
PNODE searchPredecessor(PNODE p)
{
    if (NULL == p)
        return NULL;
    if (p->left) {
        return searchMax(p);
    } else {
        while(p->parent != NULL && NULL != p) {
            if(p->parent->right == p) {
                break;
            } else {
                p = p->parent;
            }
        }
        return p->parent;
    }
}

// 查找后继节点
PNODE searchSuccessor(PNODE p)
{
    if (NULL == p)
        return NULL;
    if (p->right) {
        return searchMin(p->right);
    } else {
        while(NULL != p->parent && p)
        {
            if(p->parent->left == p )
                break;
            else {
                p = p->parent;
            }
        }
        return p->parent;
    }
}

// 删除节点, 成功返回1， 不成功返回0
int deleteNode(PNODE* root, KeyType key)
{
    // 首先查找要删除的节点
    PNODE p = search(*root, key);
    
    if(!p)
        return 0;
    
    //1. 叶子节点直接删除
    if (p->left == NULL && p->right == NULL)
    {
        if (p->parent == NULL) {
            *root = NULL;
        }
        if(p->parent->right == p) {
            p->parent->right = NULL;
        }
        else if (p->parent->left == p) {
            p->parent->left = NULL;
        }
        delete p;
    }
    //2. 该节点只有左子树
    else if (p->left != NULL && p->right == NULL)
    {
        p->left->parent = p->parent;
        //2.1 该节点是根节点
        if (p->parent == NULL) {
            *root = p->left;
        } else if (p->parent->left == p) //2.2 该节点是父节点的左孩子
        {
            p->parent->left = p->left;
        } else if (p->parent->right == p) //2.3 该节点是父节点的右孩子
        {
            p->parent->right = p->left;
        }
        delete p;
    }
    //3. 该节点只有右子树
    else if (p->left ==NULL && p->right != NULL)
    {
        p->right->parent = p->parent;
        //3.1 该节点是根节点
        if (p->parent == NULL) {
            *root = p->right;
        }
        //3.2 该节点是父节点的左孩子
        else if (p->parent->left == p) {
            p->parent->left = p->right;
        }
        //3.3 该节点是父节点的右孩子
        else if (p->parent->right == p) {
            p->parent->right = p->right;
        }
        delete p;
    }
    //4. 该节点既有左孩子又有右孩子
    else {
        //4.1找到后继节点，后继节点肯定没有左孩子！！
        PNODE q = searchSuccessor(p);
        KeyType temp = q->key;
        deleteNode(root, temp);
        p->key = temp;
    }
    return 1;
}

void create(PNODE* root, KeyType* keyArray, int iLength)
{
    for(int i = 0; i < iLength; i++)
    {
        insert(root, keyArray[i]);
    }
}

// 遍历二叉树， 打印出所有节点键值 , 先序
void printAll_Pre(PNODE root)
{
    if (root) {
        printf("%d\n", root->key);
        printAll_Pre(root->left);
        printAll_Pre(root->right);
    }
}

// 遍历二叉树，先序，非递归
void printAll_Pre_nr(PNODE root)
{
    std::stack<PNODE> s;
    PNODE p = root;
    
    while (p != NULL || !(s.empty()))
    {
        while(p)
        {
            s.push(p);
            printf("%d\n", p->key);
            p = p->left;
        }
        
        if (!s.empty()) {
            PNODE ptemp = s.top();
            s.pop();
            p = ptemp->right;
        }
    }
}

// 遍历二叉树，中序， 递归
void printAll_Mid(PNODE root)
{
    if(root) {
        printAll_Mid(root->left);
        printf("%d\n", root->key);
        printAll_Mid(root->right);
    }
}

// 遍历二叉树，中序， 非递归
void printAll_Mid_nr(PNODE root)
{
    std::stack<PNODE> s;
    PNODE p = root;
    
    while( NULL != p || !(s.empty()))
    {
        while(p) {
            s.push(p);
            p = p->left;
        }
        
        if(!s.empty())
        {
            PNODE pTemp = s.top();
            s.pop();
            printf("%d\n", pTemp->key);
            p = pTemp->right;
        }
    }
}

// 遍历二叉树，后序，递归
void printAll_Post(PNODE root)
{
    if(root) {
        printAll_Mid(root->left);
        printAll_Mid(root->right);
        printf("%d\n", root->key);
    }
}

typedef struct Node_With_Info {
    PNODE p;
    bool  isFirstOnStackTop;
    
    Node_With_Info(PNODE pValue, bool boolval):p(pValue), isFirstOnStackTop(boolval) {}
} NODEINFO, *PNODEINFO;

// 遍历二叉树， 后序， 非递归
void printAll_Post_nr(PNODE root)
{
    std::stack<PNODEINFO> s;
    PNODE p = root;
    
    while(NULL !=p || !s.empty())
    {
        while(p)
        {
            PNODEINFO pTemp = new NODEINFO(p, true);
            s.push(pTemp);
            p = p->left;
        }
        
        if (!s.empty()) {
            PNODEINFO temp = s.top();
            s.pop();
            if (temp->isFirstOnStackTop) {
                temp->isFirstOnStackTop = false;
                s.push(temp);
                p = temp->p->right;
            } else {
                delete temp;
                printf("%d\n", temp->p->key);
                p = NULL;
            }
        }
    }
}

/* 不成功 http://blog.csdn.net/sgbfblog/article/details/7783935 待分析
int iIndex = 0;
KeyType pArray[] = {1, 2, 4, 5, 3, 6, 7, -1};
// 已先序遍历的结果创建树，不一定是BST
void createTree(PNODE* root)
{
    if (pArray[iIndex] == -1)
        *root = NULL;
    else {
        *root = new NODE();
        (*root)->key = pArray[iIndex];
        createTree(&(*root)->left);
        createTree(&(*root)->right);
    }
}
*/

void LevelTraverse(PNODE p, int iHeight)
{
    if(NULL == p || iHeight < 1)
        return;
    
    if(iHeight == 1) {
        printf("%d    ", p->key);
        return;
    }
    
    LevelTraverse(p->left, iHeight - 1);
    LevelTraverse(p->right, iHeight - 1);
}

int calculateHeight(PNODE p)
{
    if(!p)
        return 0;
    else {
        int i  = calculateHeight(p->left);
        int j  = calculateHeight(p->right);
        return 1 + (i > j ? i : j);
    }
}

void PrintByLevel(PNODE p)
{
    int iHeight = calculateHeight(p);
    
    for (int i = 1; i <= iHeight; i++)
    {
        LevelTraverse(p, i);
        printf("\n");
    }
}

void testListSTL()
{
    typedef list<int>::iterator IntListIter;
    list<int> l1;
    list<int> l2;
    l1.insert(l1.end(), 1);
    l1.insert(l1.end(), 2);
    l1.insert(l1.end(), 3);
    l1.insert(l1.end(), 4);
    l1.insert(l1.end(), 5);
    
    l2.insert(l2.end(), 6);
    l2.insert(l2.end(), 5);
    l2.insert(l2.end(), 9);
    l2.insert(l2.end(), 8);
    l2.insert(l2.end(), 10);
    l2.insert(l2.end(), 22);
    
    //为何不能成功
    //l1.insert(l1.end(), l2.begin() + l2.size()/2, l2.end());
    

    for(IntListIter iter = l1.begin(); iter!= l1.end() ;iter++)
    {
        printf("Value = %d\n", *iter);
    }
    
    for(IntListIter iter = l2.begin(); iter!= l2.end(); iter++)
    {
        printf("L2 Value = %d\n", *iter);
    }
    
    printf("----\n");
    l1.splice(l1.end(), l2, find(l2.begin(), l2.end(), 5),
              find(l2.rbegin(), l2.rend(), 10).base());
    
    for(IntListIter iter = l1.begin(); iter!= l1.end() ;iter++)
    {
        printf("L1 Value = %d\n", *iter);
    }
}

int performBinarySearchTreeTest()
{
    int i;
    PNODE root=NULL;
    KeyType nodeArray[11]={15,6,18,3,7,17,20,2,4,13,9};
    create(&root,nodeArray,11);
    for(i=0;i<2;i++)
        deleteNode(&root,nodeArray[i]);
    printf("%d\n",searchPredecessor(root)->key);
    printf("%d\n",searchSuccessor(root)->key);
    printf("%d\n",searchMin(root)->key);
    printf("%d\n",searchMax(root)->key);
    printf("%d\n",search_nr(root,13)->key);
    printf("%d\n",search(root,13)->key);
    printf("--前序递归--\n");
    printAll_Pre(root);
    printf("---前序非递归--\n");
    printAll_Pre_nr(root);
    printf("--中序递归--\n");
    printAll_Mid(root);
    printf("---中序非递归--\n");
    printAll_Mid_nr(root);
    
    // 奇怪的， 后序递归和非递归不一致！，说明非递归还是写的有问题。。。
    printf("--后序递归--\n");
    printAll_Post(root);
    printf("--后序非递归--\n");
    printAll_Post_nr(root);
    printf("--=--\n");
    
    // 按层递归打印二叉树
    PrintByLevel(root);
    
    testListSTL();
    return 0;
}

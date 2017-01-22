//
//  binary_search_tree.cpp
//  101Plan
//
//  Created by zl on 22/01/17.
//  Copyright © 2017年 zhu-liang. All rights reserved.
//

#include "binary_search_tree.hpp"

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
    } else if (root->left == NULL) {
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
    printf("%d\n",search(root,13)->key);
    return 0;
}

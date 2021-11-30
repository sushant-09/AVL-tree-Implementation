#include<bits/stdc++.h>
using namespace std;
template<typename T> class Avl
{
    public:
    class Node
    {
        public:
        T key;
        Node* left;
        Node* right;
        int height,count,lc,rc;
        Node()
        {
            left=NULL;
            right=NULL;
            height=0;
            count=0;
            lc=0;
            rc=0;
        }
    };
    Node* root;
    Avl()
    {
        root=NULL;
    }
    Node* createNode(T key)
    {
        Node* node=new Node();
        node->key=key;
        node->left=NULL;
        node->right=NULL;
        node->height=1;
        node->count=1;
        node->lc=0;
        node->rc=0;
        return(node);
    }
    Node* insert(Node* root, T key)
    {
        if(root==NULL)
            return createNode(key);
        if(root->key==key)
        {
            root->count++;
            return root;
        }
        if(key<root->key)
        {
            root->left=insert(root->left,key);
            // (root->lc)++;
            root->lc=root->left->count+root->left->lc+root->left->rc;
        }
        else if(key>root->key)
        {
            root->right=insert(root->right,key);
            // (root->rc)++;
            root->rc=root->right->count+root->right->rc+root->right->lc;
        }
        int lheight=root->left?root->left->height:0;
        int rheight=root->right?root->right->height:0;
        root->height=1+max(lheight,rheight);
        if((lheight-rheight)>1 && key<root->left->key)
            return ll(root);
        if((rheight-lheight)>1 && key>root->right->key)
            return rr(root);
        if((lheight-rheight)>1 && key>root->left->key)
            return lr(root);
        if((rheight-lheight)>1 && key<root->right->key)
            return rl(root);
        return root;
    }
    Node* lr(Node *node)
    {
        node->left=rr(node->left);
        return ll(node);
    }
    Node* rl(Node *node)
    {
        node->right=ll(node->right);
        return rr(node);
    }
    Node* ll(Node *node)
    {
        Node* leftnode=node->left;
        Node* temp=leftnode->right;
        leftnode->right=node;
        node->left=temp;
        if(temp)
            node->lc=temp->count+temp->lc+temp->rc;
        else
            node->lc=0;
        leftnode->rc=node->count+node->rc+node->lc;
        node->height=1+max(node->left?node->left->height:0,node->right?node->right->height:0);
        leftnode->height=1+max(leftnode->left?leftnode->left->height:0,leftnode->right?leftnode->right->height:0);
        return leftnode;
    }
    Node* rr(Node* node)
    {  
        Node* rightnode=node->right;
        Node* temp=rightnode->left;
        rightnode->left=node;
        node->right=temp;
        if(temp)
            node->rc=temp->count+temp->rc+temp->lc;
        else
            node->rc=0;
        rightnode->lc=node->count+node->lc+node->rc;
        node->height=1+max(node->left?node->left->height:0,node->right?node->right->height:0);
        rightnode->height=1+max(rightnode->left?rightnode->left->height:0,rightnode->right?rightnode->right->height:0);
        return rightnode;  
    }
    void insert(T key)
    {
        root=insert(root,key);
    }
    int checkBalance(Node* root)
    {
        if(root)
        {
            int lheight=root->left?root->left->height:0;
            int rheight=root->right?root->right->height:0;
            return (lheight-rheight);
        }
        return 0;
    }
    Node* deleteVal(Node* root, T key)
    {
        if(!root)
            return root;
        if(key==root->key && root->count>1)
        {
            (root->count)--;
            return root;
        }
        else
        {
            if(key<root->key)
            {
                root->left=deleteVal(root->left,key);
                (root->lc)--;
            }
            else if(key>root->key)
            {
                root->right=deleteVal(root->right,key);
                (root->rc)--;
            }
            else
            {
                if(root->left==NULL && root->right==NULL)
                {
                    free(root);
                    return NULL;
                }
                else if(root->left==NULL)
                {
                    Node* temp=root->right;
                    free(root);
                    return temp;
                }
                else if(root->right==NULL)
                {
                    Node* temp=root->left;
                    free(root);
                    return temp;
                }
                else
                {
                    Node* temp=root->right;
                    while(temp->left!=NULL)
                        temp=temp->left;
                    root->key=temp->key;
                    root->right=deleteVal(root->right,temp->key);
                    (root->rc)--;
                }
            }
        }
        int lheight=root->left?root->left->height:0;
        int rheight=root->right?root->right->height:0;
        root->height=1+max(lheight,rheight);
        if((lheight-rheight)>1 && checkBalance(root->left)>=0)
            return ll(root);
        if((rheight-lheight)>1 && checkBalance(root->right)<=0)
            return rr(root);
        if((lheight-rheight)>1 && checkBalance(root->left)<0)
            return lr(root);
        if((rheight-lheight)>1 && checkBalance(root->right)>0)
            return rl(root);
        return root;
    }
    void deleteVal(T key)
    {
        root=deleteVal(root, key);
    }
    bool search(Node* root, T key)
    {
        if(root)
        {
            if(root->key==key)
                return true;
            else if(key<root->key)
                return search(root->left,key);
            else
                return search(root->right,key);
        }
        return false;
    }
    bool search(T key)
    {
        return search(root,key);
    }
    int countOccurrence(Node* root, T key)
    {
        if(root)
        {
            if(root->key==key)
                return root->count;
            else if(key<root->key)
                return countOccurrence(root->left,key);
            else
                return countOccurrence(root->right,key);
        }
        return 0;
    }
    int countOccurrence(T key)
    {
        return countOccurrence(root,key);
    }
    T lowerBound(T key)
    {
        Node* temp=root;
        T lb=root->key;
        while(temp)
        {
            if(key<temp->key)
            {
                lb=temp->key;
                temp=temp->left;
            }
            else if(key>temp->key)
            {
                temp=temp->right;
            }
            else
            {
                lb=temp->key;
                return lb;
            }
        }
        return lb;
    }
    T upperBound(T key)
    {
        Node* temp=root;
        T ub=root->key;
        while(temp)
        {
            if(key<temp->key)
            {
                ub=temp->key;
                temp=temp->left;
            }
            else
                temp=temp->right;
        }
        return ub;
    }
    void inorder(Node* root)
    {
        if(root)
        {
            inorder(root->left);
            for(int i=0; i<root->count; i++)
                cout<<root->key<<" ";
            inorder(root->right);
        }
    }
    void inorder()
    {
        inorder(root);
    }
    T kthlargest(Node* root, int k)
    {
        if(root->rc>k)
            return kthlargest(root->right,k);
        else
        {
            if(k>=root->rc && k<=root->rc+root->count)
                return root->key;
            else
                return kthlargest(root->left,k-root->rc);
        }
    }
    T kthlargest(int k)
    {
        k--;
        return kthlargest(root,k);
    }
    int lessThan(T key)
    {
        Node* temp=root;
        int result=0;
        while(1)
        {
            if(key<temp->key)
            {
                temp=temp->left;
            }
            else if(key>temp->key)
            {
                result+=(temp->count+temp->lc);
                temp=temp->right;
            }
            else
            {
                result+=(temp->lc);
                break;
            }
        }
        return result;
    }
    int greaterThan(T key)
    {
        Node* temp=root;
        int result=0;
        while(1)
        {
            if(key>temp->key)
            {
                temp=temp->right;
            }
            else if(key<temp->key)
            {
                result+=(temp->count+temp->rc);
                temp=temp->left;
            }
            else
            {
                result+=(temp->rc);
                break;
            }
        }
        return result;
    }
    int countInRange(T low, T high)
    {
        int total=root->rc+root->lc+root->count;
        int l=lessThan(low);
        int h=greaterThan(high);
        return (total-l-h);
    }
    T closest(T key)
    {
        Node* temp=root;
        T mindiff=root->key-key;
        T result=key;
        while(1)
        {
            if(temp)
            {
                if(temp->key==key)
                {
                    return key;
                }
                else if(key<temp->key)
                {
                    if(abs(temp->key-key)<(mindiff>0?mindiff:-mindiff))
                    {
                        mindiff=temp->key-key;
                        result=temp->key;
                    }
                    temp=temp->left;
                }
                else
                {
                    if(abs(temp->key-key)<(mindiff>0?mindiff:-mindiff))
                    {
                        mindiff=temp->key-key;
                        result=temp->key;
                    }
                    temp=temp->right;
                }
            }
            else
            {
                break;
            }
        }
        return result;
    }
};
int main()
{
    Avl<int> a;
    a.insert(10);
    a.insert(20);
    a.insert(2);
    a.insert(3);
    a.insert(5);
    a.insert(1);
    a.insert(1);
    a.insert(7);
    cout<<a.countOccurrence(1)<<endl;
    cout<<a.countInRange(1,3)<<endl;
    return 0;
}
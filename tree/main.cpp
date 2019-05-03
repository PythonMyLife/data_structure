#include "linkQueue.h"

template<class T>
class bTree {
    public:
        virtual void clear() = 0;
        virtual bool isEmpty() const = 0;
        virtual T Root(T flag) const = 0;
        virtual T parent(T x, T flag) const = 0;
        virtual T lchild(T x, T flag) const = 0;
        virtual T rchild(T x, T flag) const = 0;
        virtual void delLeft(T x) = 0;
        virtual void delRight(T x) = 0;
        virtual void preOrder() const = 0;
        virtual void midOrder() const = 0;
        virtual void postOrder() const = 0;
        virtual void levelOrder() const = 0;
};

template<class T>
class binaryTree:public bTree<T> {
    template<class X>
    friend void printTree(const binaryTree<X> &t, X flag);

    private:
        struct Node {
            Node *left, *right;
            T data;

            Node():left(NULL),right(NULL) {}
            Node(T item, Node *L = NULL, Node *R = NULL):data(item), left(L), right(R) {}
            ~Node() {}
        };

        struct one {
            Node * p;
            int num;
        };

        Node *root;

    public:
        binaryTree():root(NULL) {}
        binaryTree(T x) {root = new Node(x);}
        ~binaryTree();
        void clear();
        bool isEmpty() const;
        T Root(T flag) const;
        T lchild(T x, T flag) const;
        T rchild(T x, T flag) const;
        void delLeft(T x);
        void delRight(T x);
        void preOrder() const;
        void midOrder() const;
        void postOrder() const;
        void levelOrder() const;
        void createTree(T flag);
        bool judge();     //判断是否为完全二叉树
        bool symmetry(binaryTree<T>::Node *t1,binaryTree<T>::Node *t2);  //判断两个树是否对称
        bool mirror(binaryTree<T> &t);
        T parent(T x, T flag) const {return flag;}

    private:
        Node *find(T x, Node *t) const;
        void clear(Node *&t);
        void preOrder(Node *t) const;
        void midOrder(Node *t) const;
        void postOrder(Node *t) const;
};


template<class T>
bool binaryTree<T>::judge()
{
    linkQueue<one> que;
    one now,child;
    int count = 1,last = 1;

    if(root == NULL) return true;
    now.p = root;
    now.num = 1;
    que.enQueue(now);
    while(!que.isEmpty()){
        now = que.deQueue();
        if(now.p -> left != NULL){
            ++count;
            child.p = now.p -> left;
            last = child.num = now.num * 2;
            que.enQueue(child);
        }
        if(now.p -> right != NULL){
            ++count;
            child.p = now.p -> right;
            last = child.num = now.num * 2 + 1;
            que.enQueue(child);
        }
    }
    return count == last;
}

template<class T>
bool binaryTree<T>::symmetry(binaryTree<T>::Node *t1,binaryTree<T>::Node *t2)
{
    if(t1 == NULL && t2 ==NULL) return true;
    else if((t1 == NULL && t2 != NULL) || (t1 != NULL && t2 == NULL)) return false;
    else{
        if(t1->data != t2->data) return false;
        else return symmetry(t1->left, t2->right) && symmetry(t1->right, t2->left);
    }
}

template<class T>
bool binaryTree<T>::mirror(binaryTree<T> &t)
{
    return symmetry(root,t.root);
}

template<class T>
bool binaryTree<T>::isEmpty() const {
    return root == NULL;
}

template<class T>
T binaryTree<T>::Root(T flag) const {
    if (root == NULL) return flag;
    else return root->data;
}

template<class T>
void binaryTree<T>::clear(binaryTree<T>::Node *&t) {
    if (t == NULL) return;
    clear(t->left);
    clear(t->right);
    delete t;
    t = NULL;
}

template<class T>
void binaryTree<T>::clear() {
    clear(root);
}

template<class T>
binaryTree<T>::~binaryTree() {
    clear(root);
}

template<class T>
void binaryTree<T>::preOrder(binaryTree<T>::Node *t) const {
    if (t == NULL) return;
    cout << t-> data << ' ';
    preOrder(t->left);
    preOrder(t->right);
}

template<class T>
void binaryTree<T>::preOrder() const {
    cout << "\n 前序遍历：";
    preOrder(root);
}

template<class T>
void binaryTree<T>::postOrder(binaryTree<T>::Node *t) const {
    if (t == NULL) return;
    postOrder(t->left);
    postOrder(t->right);
    cout << t->data << ' ';
}

template<class T>
void binaryTree<T>::postOrder() const {
    cout << "\n 后序遍历：";
    postOrder(root);
}

template<class T>
void binaryTree<T>::midOrder(binaryTree<T>::Node *t) const {
    if (t == NULL) return;
    midOrder(t->left);
    cout << t->data << ' ';
    midOrder(t->right);
}

template<class T>
void binaryTree<T>::midOrder() const {
    cout << "\n 后序遍历：";
    midOrder(root);
}

template<class T>
void binaryTree<T>::levelOrder() const {
    linkQueue<Node *> que;
    Node *tmp;

    cout << "\n 层次遍历：";
    que.enQueue(root);

    while (!que.isEmpty()) {
        tmp = que.deQueue();
        cout << tmp->data << ' ';
        if (tmp->left) que.enQueue(tmp->left);
        if (tmp->right) que.enQueue(tmp->right);
    }
}

template<class T>
typename binaryTree<T>::Node* binaryTree<T>::find(T x, binaryTree<T>::Node *t) const {
    Node *tmp;
    if (t == NULL) return NULL;
    if (t->data == x) return t;
    if (tmp = find(x, t->left)) return tmp;
    else return find(x, t->right);
}

template<class T>
void binaryTree<T>::delLeft(T x) {
    Node *tmp = find(x, root);
    if (tmp == NULL) return;
    clear(tmp->left);
}

template<class T>
void binaryTree<T>::delRight(T x) {
    Node *tmp = find(x, root);
    if (tmp == NULL) return;
    clear(tmp->right);
}

template<class T>
T binaryTree<T>::lchild(T x, T flag) const {
    Node *tmp = find(x, root);
    if (tmp == NULL || tmp->left == NULL) return flag;

    return tmp->left->data;
}

template<class T>
T binaryTree<T>::rchild(T x, T flag) const {
    Node *tmp = find(x, root);
    if (tmp == NULL || tmp->right == NULL) return flag;

    return tmp->right->data;
}

template<class T>
void binaryTree<T>::createTree(T flag) {
    linkQueue<Node *> que;
    Node *tmp;
    T x, ldata, rdata;

    cout << "\n 输入根结点：";
    cin >> x;
    root = new Node(x);
    que.enQueue(root);

    while (!que.isEmpty()) {
        tmp = que.deQueue();
        cout << "\n 输入" << tmp->data << "的两个儿子（" << flag << "表示空结点）：";
        cin >> ldata >> rdata;
        if (ldata != flag) que.enQueue(tmp->left = new Node(ldata));
        if (rdata != flag) que.enQueue(tmp->right = new Node(rdata));
    }

    cout << "create completed!\n";
}

template<class X>
void printTree(const binaryTree<X> &t, X flag) {
    linkQueue<X> q;
    q.enQueue(t.root->data);
    cout << endl;
    while (!q.isEmpty()) {
        X p, l, r;
        p = q.deQueue();
        l = t.lchild(p, flag);
        r = t.rchild(p, flag);
        cout << p << " " << l << " " << r << endl;
        if (l != flag) q.enQueue(l);
        if (r != flag) q.enQueue(r);
    }
}

int main()
{
    binaryTree<char> tree1;
    binaryTree<char> tree2;

    tree1.createTree('@');
    cout << ((tree1.judge())?("tree1是完全二叉树！\n"):("tree1不是完全二叉树！\n"));
    tree2.createTree('@');
    cout << ((tree1.mirror(tree2))?("两树互为镜像！\n"):("两树不互为镜像！\n"));


    return 0;
}

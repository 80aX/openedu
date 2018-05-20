// Удаление поддеревьев

// Дано некоторое двоичное дерево поиска. Также даны запросы на удаление из 
// него вершин, имеющих заданные ключи, причем вершины удаляются целиком 
// вместе со своими поддеревьями.

// После каждого запроса на удаление выведите число оставшихся вершин в дереве.

// В вершинах данного дерева записаны ключи — целые числа, по модулю 
// не превышающие 10^9. Гарантируется, что данное дерево является двоичным 
// деревом поиска, в частности, для каждой вершины дерева V выполняется 
// следующее условие:

// все ключи вершин из левого поддерева меньше ключа вершины V;
// все ключи вершин из правого поддерева больше ключа вершины V.
// Высота дерева не превосходит 25, таким образом, можно считать, 
// что оно сбалансировано.


#include <fstream>


class tree_node
{
    public:
        tree_node() {
            key = 0;
            left_child = 0;
            rigth_child = 0;
            parent = 0;
        }
        
        ~tree_node () {}
        
        tree_node(int k, tree_node *l, tree_node *r, tree_node *p) {
            key = k;
            left_child = l;
            rigth_child = r;
            parent = p;
        }
        
        int get_key() {
            return key;
        }
        
        tree_node *get_left_child() {
            return left_child;
        }
        
        tree_node *get_rigth_child() {
            return rigth_child;
        }
        
        tree_node *get_parent() {
            return parent;
        }
        
        void set_key(int k) {
            key = k;
        }
        
        void set_left_child(tree_node *l) {
            left_child = l;
        }
        
        void set_rigth_child(tree_node *r) {
            rigth_child = r;
        }
        
        void set_parent(tree_node *p) {
            parent = p;
        }
    
    private:
        int key;
        tree_node *left_child;
        tree_node *rigth_child;
        tree_node *parent;
};


class binary_tree
{
    public:
        binary_tree() {
            n = 0;
            tree = 0;
        }
        
        ~binary_tree() {
            delete [] tree;
        }
        
        tree_node *search(tree_node *x, int k) {
            if (x == 0 || k == x -> get_key())
                return x;
            else if (k < x -> get_key())
                return search(x -> get_left_child(), k);
            else
                return search(x -> get_rigth_child(), k);
        }
        
        void remove(tree_node *z) {
            tree_node *current_parent = z -> get_parent();
            
            if (current_parent -> get_left_child() == z)
                current_parent -> set_left_child(0);
            else
                current_parent -> set_rigth_child(0);
        }
        
        int preorder(tree_node *x) {
            if (x == 0)
                return 0;
            
            return 1 + preorder(x -> get_left_child())
                        + preorder(x -> get_rigth_child());
        }
        
        void processing() {
            std::ifstream fin("input.txt");
            std::ofstream fout("output.txt");
            
            fin >> n;
            tree = new tree_node [n];
            
            for (int i = 0; i < n; ++i)
                tree[i] = tree_node();
            
            for (int i = 0; i < n; ++i) {
                int k, l, r;
                fin >> k >> l >> r;
                
                tree[i].set_key(k);
                if (l != 0) {
                    tree[i].set_left_child(&tree[l - 1]);
                    tree[l - 1].set_parent(&tree[i]);
                }
                if (r != 0) {
                    tree[i].set_rigth_child(&tree[r - 1]);
                    tree[r - 1].set_parent(&tree[i]);
                }
            }
            
            int m, k, total_nodes = n;
            fin >> m;
            
            for (int i = 0; i < m; ++i) {
                fin >> k;
                
                tree_node *node_to_remove = search(&tree[0], k);
                
                if (node_to_remove != 0) {
                    total_nodes -= preorder(node_to_remove);
                    remove(node_to_remove);
                }
                fout << total_nodes << "\n";
            }
        }
    
    private:
        int n;
        tree_node *tree;
};


int main()
{
    binary_tree test;
    test.processing();
    
    return 0;
}

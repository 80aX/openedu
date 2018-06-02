// Проверка сбалансированности

// АВЛ-дерево является сбалансированным в следующем смысле: для любой вершины 
// высота ее левого поддерева отличается от высоты ее правого поддерева не 
// больше, чем на единицу.
// Дано двоичное дерево поиска. Для каждой его вершины требуется определить 
// ее баланс. Все ключи различны. Гарантируется, что данное дерево является 
// деревом поиска.


#include <fstream>


class tree_node
{
    public:
        tree_node() {
            key = 0;
            height = 0;
            balance = 0;
            left_child = 0;
            rigth_child = 0;
        }
        
        ~tree_node() {}
        
        tree_node(int k, int h, int b, tree_node *l, tree_node *r) {
            key = k;
            height = h;
            balance = b;
            left_child = l;
            rigth_child = r;
        }
        
        void set_key(int k) {
            key = k;
        }
        
        void set_height(int h) {
            height = h;
        }
        
        void set_balance(int b) {
            balance = b;
        }
        
        void set_left_child(tree_node *l) {
            left_child = l;
        }
        
        void set_rigth_child(tree_node *r) {
            rigth_child = r;
        }
        
        int get_key() {
            return key;
        }
        
        int get_height() {
            return height;
        }
        
        int get_balance() {
            return balance;
        }
        
        tree_node *get_left_child() {
            return left_child;
        }
        
        tree_node *get_rigth_child() {
            return rigth_child;
        }
        
    private:
        int key;
        int height;
        int balance;
        tree_node *left_child;
        tree_node *rigth_child;
};


class avl_tree
{
    public:
        avl_tree() {
            n = 0;
            tree = 0;
        }
        
        ~avl_tree() {
            delete [] tree;
        }
        
        int tree_calculation(tree_node *node) {
            if (node == 0)
                return -1;
            
            int hl = tree_calculation(node -> get_left_child());
            int hr = tree_calculation(node -> get_rigth_child());
            
            node -> set_balance(hr - hl);
            node -> set_height(1 + (hl > hr ? hl : hr));
            return node -> get_height();
        }
        
        void tree_building() {
            std::ifstream fin("input.txt");
            
            fin >> n;
            tree = new tree_node [n];
            
            for (int i = 0; i < n; ++i)
                tree[i] = tree_node();
            
            for (int i = 0; i < n; ++i) {
                int k, l, r;
                fin >> k >> l >> r;
                
                tree[i].set_key(k);
                if (l != 0)
                    tree[i].set_left_child(&tree[l - 1]);
                if (r != 0)
                    tree[i].set_rigth_child(&tree[r - 1]);
            }
        }
        
        void processing() {
            std::ofstream fout("output.txt");
            
            tree_building();
            tree_calculation(&tree[0]);
            
            for (int i = 0; i < n; ++i)
                fout << tree[i].get_balance() << '\n';
        }
        
    private:
        int n;
        tree_node *tree;
};


int main()
{
    avl_tree test;
    test.processing();
    
    return 0;
}

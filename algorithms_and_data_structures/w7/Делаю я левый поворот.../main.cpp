// Делаю я левый поворот...

// Для балансировки АВЛ-дерева при операциях вставки и удаления производятся левые 
// и правые повороты. Левый поворот в вершине производится, когда баланс этой вершины 
// больше 1, аналогично, правый поворот производится при балансе, меньшем −1.

// Дано дерево, в котором баланс корня равен 2. Сделайте левый поворот.


#include <fstream>


class tree_node
{
    public:
        tree_node() {
            key = 0;
            pos = 0;
            height = 0;
            balance = 0;
            left_child = 0;
            rigth_child = 0;
        }
        
        ~tree_node() {}
        
        tree_node(int k, int p, int h, int b, tree_node *l, tree_node *r) {
            key = k;
            pos = p;
            height = h;
            balance = b;
            left_child = l;
            rigth_child = r;
        }
        
        void set_key(int k) {
            key = k;
        }
        
        void set_pos(int p) {
            pos = p;
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
        
        int get_pos() {
            return pos;
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
        
        // tree_node& operator=(const tree_node &right) {
            // if (this == &right)
                // return *this;
            
            // this -> key = right.key;
            // this -> pos = right.pos;
            // this -> height = right.height;
            // this -> balance = right.balance;
            // this -> left_child = right.left_child;
            // this -> rigth_child = right.rigth_child;
        // }
        
    private:
        int key;
        int pos;
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
            tree_result = 0;
        }
        
        ~avl_tree() {
            delete [] tree;
            delete [] tree_result;
        }
        
        void printout() {
            std::ofstream fout("output.txt");
            
            fout << n << '\n';
            
            for (int i = 0; i < n; ++i) {
                tree_node *l_child = tree_result[i].get_left_child();
                tree_node *r_child = tree_result[i].get_rigth_child();
                int current_key = tree_result[i].get_key();
                
                if (l_child == 0 && r_child == 0)
                    fout << current_key << " 0 0\n";
                else if (l_child == 0)
                    fout << current_key << " 0 " << r_child -> get_pos() << '\n';
                else if (r_child == 0)
                    fout << current_key << ' ' << l_child -> get_pos() << " 0\n";
                else
                    fout << current_key << ' ' << l_child -> get_pos() << ' '
                                                << r_child -> get_pos() << '\n';
            }
        }
        
        int preorder_mod(tree_node *node, int counter) {
            tree_node *l_child = node -> get_left_child();
            tree_node *r_child = node -> get_rigth_child();
            
            counter++;
            node -> set_pos(counter);
            tree_result[counter - 1] = *node;
            
            if (l_child == 0 && r_child == 0) {
                return counter;
            } else if (l_child == 0) {
                counter = preorder_mod(r_child, counter);
            } else if (r_child == 0) {
                counter = preorder_mod(l_child, counter);
            } else {
                counter = preorder_mod(l_child, counter);
                counter = preorder_mod(r_child, counter);
            }
        }
        
        tree_node *small_left_pivot() {
            tree_node *temp_a = &tree[0];
            tree_node *temp_b = temp_a -> get_rigth_child();
            tree_node *temp_y = temp_b -> get_left_child();
            
            temp_b -> set_left_child(temp_a);
            temp_a -> set_rigth_child(temp_y);
            
            return temp_b;
        }
        
        tree_node *big_left_pivot() {
            tree_node *temp_a = &tree[0];
            tree_node *temp_b = temp_a -> get_rigth_child();
            tree_node *temp_c = temp_b -> get_left_child();
            tree_node *temp_x = temp_c -> get_left_child();
            tree_node *temp_y = temp_c -> get_rigth_child();
            
            temp_c -> set_left_child(temp_a);
            temp_c -> set_rigth_child(temp_b);
            temp_a -> set_rigth_child(temp_x);
            temp_b -> set_left_child(temp_y);
            
            return temp_c;
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
            tree_result = new tree_node [n];
            
            for (int i = 0; i < n; ++i)
                tree[i] = tree_node();
            
            for (int i = 0; i < n; ++i) {
                int k, l, r;
                fin >> k >> l >> r;
                
                tree[i].set_key(k);
                tree[i].set_pos(i + 1);
                if (l != 0)
                    tree[i].set_left_child(&tree[l - 1]);
                if (r != 0)
                    tree[i].set_rigth_child(&tree[r - 1]);
            }
        }
        
        void processing() {
            tree_building();
            tree_calculation(&tree[0]);
            tree_node *new_root;
            
            if (tree[0].get_rigth_child() -> get_balance() == -1)
                new_root = big_left_pivot();
            else
                new_root = small_left_pivot();
            
            preorder_mod(new_root, 0);
            printout();
        }
        
    private:
        int n;
        tree_node *tree;
        tree_node *tree_result;
};


int main()
{
    avl_tree test;
    test.processing();
    
    return 0;
}

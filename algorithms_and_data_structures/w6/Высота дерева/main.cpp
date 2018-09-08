// Высота дерева

// Высотой дерева называется максимальное число вершин дерева в цепочке, 
// начинающейся в корне дерева, заканчивающейся в одном из его листьев, и 
// не содержащей никакую вершину дважды.

// Так, высота дерева, состоящего из единственной вершины, равна единице. 
// Высота пустого дерева (да, бывает и такое!) равна нулю.

// Дано двоичное дерево поиска. В вершинах этого дерева записаны ключи — 
// целые числа, по модулю не превышающие 10^9. Для каждой вершины дерева V 
// выполняется следующее условие:

// все ключи вершин из левого поддерева меньше ключа вершины V;
// все ключи вершин из правого поддерева больше ключа вершины V.

// Найдите высоту данного дерева.


#include <fstream>


class tree_node
{
    public:
        tree_node()
        {
            key = 0;
            left_child = 0;
            rigth_child = 0;
        }
        
        ~tree_node () {}
        
        tree_node(int k, tree_node *l, tree_node *r)
        {
            key = k;
            left_child = l;
            rigth_child = r;
        }
        
        int get_key()
        {
            return key;
        }
        
        tree_node *get_left_child()
        {
            return left_child;
        }
        
        tree_node *get_rigth_child()
        {
            return rigth_child;
        }
        
        void set_key(int k)
        {
            key = k;
        }
        
        void set_left_child(tree_node *l)
        {
            left_child = l;
        }
        
        void set_rigth_child(tree_node *r)
        {
            rigth_child = r;
        }
    
    private:
        int key;
        tree_node *left_child;
        tree_node *rigth_child;
};


class binary_tree
{
    public:
        binary_tree()
        {
            n = 0;
            tree = 0;
        }
        
        ~binary_tree()
        {
            delete [] tree;
        }
        
        void build()
        {
            std::ifstream fin("input.txt");
            
            fin >> n;
            tree = new tree_node [n];
            
            for (int i = 0; i < n; ++i)
                tree[i] = tree_node();
            
            for (int i = 0; i < n; ++i)
            {
                int k, l, r;
                fin >> k >> l >> r;
                
                tree[i].set_key(k);
                if (l != 0)
                    tree[i].set_left_child(&tree[l - 1]);
                if (r != 0)
                    tree[i].set_rigth_child(&tree[r - 1]);
            }
        }
        
        int height_finding(tree_node *x)
        {
            int leftheight, rigthheight;
            
            if (x == 0)
            {
                return 0;
            }
            else
            {
                leftheight = height_finding(x -> get_left_child());
                rigthheight = height_finding(x -> get_rigth_child());
                return 1 + (leftheight > rigthheight ? leftheight : rigthheight);
            }
        }
        
        void processing()
        {
            std::ofstream fout("output.txt");
            
            int result = n;
            
            if (n > 3)
                result = height_finding(&tree[0]);
            
            fout << result << "\n";
        }
    
    private:
        int n;
        tree_node *tree;
};


int main()
{
    binary_tree test;
    test.build();
    test.processing();
    
    return 0;
}

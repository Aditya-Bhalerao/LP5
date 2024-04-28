#include <iostream>
#include <stack>
#include <vector>
#include <omp.h>

using namespace std;

struct TreeNode {
    int val;         
    TreeNode* left;  
    TreeNode* right; 

    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

bool dfs(TreeNode* root, int target_val) {
    stack<TreeNode*> s;
    s.push(root);
    bool found = false;

    while (!s.empty()) {
        vector<int> visited_nodes; 
        #pragma omp parallel shared(found) 
        {
            vector<TreeNode*> local_stack; 
            #pragma omp single 
            {
                local_stack.push_back(s.top());
                s.pop();
            }
            while (!local_stack.empty()) {
                TreeNode* node = local_stack.back();
                local_stack.pop_back();
                visited_nodes.push_back(node->val); 

                if (node->val == target_val) {
                    #pragma omp critical
                    {
                        found = true; 
                    }
                }

                if (node->right) {
                    local_stack.push_back(node->right);
                }

                if (node->left) {
                    local_stack.push_back(node->left);
                }
            }
        }
        
        cout << "Visited nodes: ";
        for (int i = 0; i < visited_nodes.size(); i++) {
            cout << visited_nodes[i] << " ";
        }
        cout << endl;
        if (found) {
            return true;
        }
    }

    return false;
}

int main() {
   
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    int target_val = 8;

    bool found = dfs(root, target_val);

    if (found) {
        cout << "Node with value " << target_val << " found in the tree!" << endl;
    } else {
        cout << "Node with value " << target_val << " not found in the tree." << endl;
    }

    return 0;
}

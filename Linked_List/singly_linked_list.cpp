#include <iostream>
using namespace std;

struct Node
{
	int value;
	Node *next;
};

Node* Insert(Node *root, int val)
{
    // Create the temp node
    Node *temp = (Node*) malloc(sizeof(Node));
    if(temp == NULL)
    {
        cerr << "Something went wrong while allocating memory\n";
        return NULL;
    }
    temp->value = val;
    temp->next = NULL;
    // The list is empty
    if(root == NULL)
    {
        root = temp;
    }
    else
    {
        Node *it = root;
        while(it->next != NULL)
            it = it->next;
        it->next = temp;
    }
    return root;
}

void DisplayList(Node *root)
{
    // Check if the list is empty
    if(root == NULL)
    {
        cerr << "The list is empty" << endl;
        return;
    }
    // Iterate through the list
    Node *it = root;
    while(it != NULL)
    {
        cout << it->value << " ";
        it = it->next;
    }
    cout << endl;
}

Node* Search(Node *root, int val)
{
    if(root == NULL)
    {
        cerr << "This list is empty.\n";
        return NULL;
    }
    Node *it = root;
    while(it != NULL)
    {
        if(it->value == val)
        {
            return it;
        }
        else
        {
            it = it->next;
        }
    }
    return NULL;
}

Node* Delete(Node *root, int val)
{
    if(root == NULL)
    {
        cerr << "The list is empty.\n";
        return NULL;
    }
    
    Node *n = Search(root, val);
    if(n == NULL)
    {
        cerr << val << " is not found.\n";
        return root;
    }
    
    Node *it = root;
    // Check if the node is root
    if(it->value == val)
    {
        // 2nd item exists
        if(it->next != NULL)
        {
            // root is going to be the 2nd item
            root = it->next;
        }
        else
        {
            root = NULL;
        }
    }
    else
    {
        while(it->next->value != val)
            it = it->next;

        it->next = n->next;
        free(n);
    }
    return root;
}

int main()
{
    Node *root = (Node*) malloc(sizeof(Node));
    root = NULL;

    root = Insert(root, 5);
    root = Insert(root, 7);
    root = Insert(root, 1);

    DisplayList(root);

    Node *n = Search(root, 1);
    if(n != NULL)
    {
        cout << n->value << " is found.\n";
    }
    
    root = Delete(root, 7);
    DisplayList(root);
    root = Insert(root, 10);
    DisplayList(root);
    root = Delete(root, 10);
    DisplayList(root);
    root = Insert(root, 4);
    DisplayList(root);
    root = Delete(root, 5);
    DisplayList(root);

    // Free the momory
    free(root);

    return 0;
}
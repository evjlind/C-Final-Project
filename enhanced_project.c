//Evan Lindeman
//ECE 1125
#define MAX_SIZE 200
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct value
{
    char title[MAX_SIZE], prof[MAX_SIZE];
    int crn;
};

struct tree_node 
{
    struct value *value;
    int key;
    struct tree_node* left;
    struct tree_node* right;
}; //defines the symbol table


//Symbol table functions
struct tree_node* insert(struct tree_node *root, int x, struct value *y);
struct tree_node* del(struct tree_node *root, int x);
struct tree_node* search(struct tree_node *root, int x);
void modify(struct tree_node *root, int x, struct value *y);
void display(struct tree_node *root);

//utility functions
struct tree_node* find_minimum(struct tree_node *root);
struct tree_node* new_node(int key, struct value *value);
struct tree_node* array_to_tree(int key_arr[],char value_arr[MAX_SIZE][MAX_SIZE],int start, int end);
void string_in(char *string, int length);
struct value* build_val();

int main(){
    int user_input, i,new_key;
    int active = 1;
    struct value* new_value;
    struct tree_node* found=NULL;
    //this section is to poopulate the tree with the default classes given on the GW schedule of classes page
    int ee_class_codes[] = {6050, 6035, 6030, 6025, 6015, 6010, 4990, 4925, 4662, 4610, 4435, 4425, 4415, 4320, 4155, 4150, 4145, 3915, 3525, 3410, 3135, 3125, 2210, 2140, 2115, 2110, 1120, 1020}; //initial ordered lsit of class codes
    char class_names[][MAX_SIZE] = {{"Research"},{"Introduction to Computer Networks"},{"Device Electronics"},{"Signals and Transforms in Engineering"},{"Stochastic Processes in Engineering"},{"Linear Systems Theory"},{"Research"},{"Electrical and Computer Engineering Capstone Project Lab III"},{"Power Electronics"},{"Electrical Energy Conversion"},{"Photonics and Fiber Optics"},{"Communications Laboratory"},{"Introduction to Computer Networks"},{"Fields and Waves II"},{"Sensors, Networks, and Applications"},{"ASIC Design and Testing of VSLI Circuits"},{"Microfabrication and Nanofabrication Technology"},{"Electrical and Computer Engineering Capston Project Lab I"},{"Introduction to Embedded Systems"},{"Communications Engineering"},{"Digital Design with FPGAs"},{"Analog Electronics Design"},{"Circuits, Signals, and Systems"},{"Design of Logic Systems"},{"Engineering Electronics"},{"Circuit Theory"},{"C Programming for Electrical and Computer Engineering"},{"Introduction to Electrical and Computer Engineering II"}}; //initial corresponding class names to class codes
    i = sizeof(ee_class_codes)/sizeof(ee_class_codes[0]);
    struct tree_node* symbol_table = array_to_tree(ee_class_codes,class_names,0,i-1);
    //user input section
    while(active){
        printf("Schedule Lookup Operations Menu:\n1.Add Class (Insert)\n2.Remove Class (delete)\n3.Search (may initially have placeholder info)\n4.Modify\n5.Display\n6.Exit\n");
        scanf("%d",&user_input);
        printf("\n");
        switch (user_input){
        case 1:
            printf("Enter the class number of the new class: ");
            scanf("%d",&new_key);
            if(search(symbol_table,new_key)==NULL){
                new_value = build_val();
                insert(symbol_table,new_key,new_value);
                printf("\nInsert Sucessful\n\n");}
            else
                printf("Class code already exists\n\n");
            break;
        case 2:
            printf("Enter the class number to delete: ");
            scanf("%d",&new_key);
            found = search(symbol_table,new_key);
            if (found!=NULL){
                del(symbol_table,new_key);
                printf("\nDelete Sucessful\n\n");}
            else
                printf("Error: Class not found\n\n");
            break;
        case 3:
            printf("Enter the class number to search: ");
            scanf("%d",&new_key);
            found = search(symbol_table,new_key);
            if (found!=NULL){
                printf("ECE %d: %s\nProfessor: %s\nCRN: %d\n",found->key,found->value->title,found->value->prof,found->value->crn);}
            else
                printf("Error: Class not found\n\n");
            break;
        case 4:
            printf("Enter a class number to modify: ");
            scanf("%d",&new_key);
            found = search(symbol_table, new_key);
            if(found!=NULL){
                new_value = build_val();
                modify(found,new_key,new_value);
                printf("\nModify Sucessful\n\n");}
            else
                printf("Class not found\n\n");
            break;
        case 5:
            display(symbol_table);
            printf("\n");
            break;
        case 6:
            active = 0;
            break;
        default:
            printf("Please enter a valid response.\n\n");
            break;
        }
    }
    return 0;
}

struct value* build_val(){
    struct value* n = (struct value*)malloc(sizeof(struct value));
    char p[MAX_SIZE], t[MAX_SIZE];
    int crn;
    printf("Enter the class title:\t");
    fflush(stdin);
    string_in(t, MAX_SIZE);
    printf("Enter the professor:\t");
    fflush(stdin);
    string_in(p,MAX_SIZE);
    printf("Enter the CRN:\t");
    fflush(stdin);
    scanf("%d",&crn);
    n -> crn = crn;
    strcpy(n->title,t);
    strcpy(n->prof,p);
    return n;
}

struct tree_node* array_to_tree(int key_arr[],char value_arr[MAX_SIZE][MAX_SIZE],int start, int end){
    if (start>end)
        return NULL;
    struct value* n = (struct value*)malloc(sizeof(struct value));
    int mid = (start+end)/2;
    strcpy(n->prof,"NULL");
    strcpy(n->title,value_arr[mid]);
    n->crn = 9999;
    struct tree_node *root = new_node(key_arr[mid],n);
    root -> left = array_to_tree(key_arr,value_arr,start,mid-1);
    root -> right = array_to_tree(key_arr,value_arr,mid+1,end);
    return root;
}

struct tree_node* find_minimum(struct tree_node *root)
{
    if(root == NULL)
        return NULL;
    else if(root->right != NULL)
        return find_minimum(root->right); // right most element will be minimum
    return root;
}

struct tree_node* new_node(int key, struct value *value){
    struct tree_node* n = (struct tree_node*)malloc(sizeof(struct tree_node));
    n -> key = key;
    n -> value = value;
    n -> left = NULL;
    n -> right = NULL;
    return n;
}

void string_in(char *string, int length){
    int x;
    fgets(string,length,stdin);
    for(x=0;x<=length;x++){
        if(string[x]=='\n'){
            string[x]='\0';
            break;
        }
    }
}

struct tree_node* insert(struct tree_node *root, int x, struct value *y){
    if(root==NULL){
        return new_node(x,y);}
    else if(x<root->key){
        root->right = insert(root->right, x,y);}
    else{
        root->left = insert(root->left,x,y);}
    return root;
}

struct tree_node* del(struct tree_node *root, int x){
    //searching for the item to be deleted
    if(root==NULL)
        return NULL;
    if (x<root->key)
        root->right = del(root->right, x);
    else if(x>root->key)
        root->left = del(root->left, x);
    else
    {
        //No Children
        if(root->left==NULL && root->right==NULL)
        {
            free(root);
            return NULL;
        }
        //One Child
        else if(root->left==NULL || root->right==NULL)
        {
            struct tree_node *temp;
            if(root->left==NULL)
                temp = root->right;
            else
                temp = root->left;
            free(root);
            return temp;
        }
        //Two Children
        else
        {
            struct tree_node *temp = find_minimum(root->left);
            root->key = temp->key;
            root->left = del(root->left, temp->key);
        }
    }
    return root;
}

struct tree_node* search(struct tree_node *root, int x){
    if(root==NULL || root->key==x) //if root->key is x then the element is found
        return root;
    else if(x<root->key) // x is smaller, so we will search the right subtree
        return search(root->right, x);
    else //x is greater than the key, so we will search the left subtree
        return search(root->left,x);
}

void modify(struct tree_node *root, int x, struct value *y){
    strcpy(root->value->title,y->title);
    strcpy(root->value->prof,y->prof);
    root->value->crn = y->crn;
}

void display(struct tree_node *root){
    if(root!=NULL){
        display(root->left);
        printf("ECE %d: %s\n",root->key,root->value->title);
        display(root->right);
    }
}
//even farther step with this program is to use files (possilby multiple files for different departments)
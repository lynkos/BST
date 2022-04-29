/*
* Name: Kiran Brahmatewari
* PID: 5467937
*
* I affirm that I wrote this program myself without any help
* from any other people or sources from the internet
*
* bstsort.c creates a Binary Search Tree and sorts it,
* depending on the given command line arguments
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#define SIZE 100

/* Node definition */
typedef struct node {
    struct node *left; // Pointer to left subtree
    char data[SIZE]; // Node value
    struct node *right; // Pointer to right subtree
} Node; // Synonym for struct node

/* Function prototypes */
Node *new_node(char *value);
int upper_cmp(const char *s1, const char *s2);
int reg_cmp(const char *s1, const char *s2);
Node *insert(Node *root, char *value, int cflag);
void print_inorder(Node *root, FILE *output);
void delete(Node *root);

/* Create new node to initialize tree */
Node *new_node(char *value) {
    Node *temp = (Node *)malloc(sizeof(Node));
    strcpy(temp -> data, value);
    temp -> left = temp -> right = NULL;
    return temp;
}

/* Compares string pointers when -c flag == 1 */
int upper_cmp(const char *s1, const char *s2) {
    while(*s1 && toupper(*s1) == toupper(*s2)) {        
        s1++;
        s2++;
    }

    return toupper(*s1) - toupper(*s2);
}

/* Compares string pointers when -c flag != 1 */
int reg_cmp(const char *s1, const char *s2) {
    while(*s1 && *s1 == *s2) {
        s1++;
        s2++;
    }
    
    return *s1 - *s2;
}

/* Inserts node into tree */
Node *insert(Node *root, char *value, int cflag) {
    // If tree is empty...
    if(root == NULL)
        return new_node(value); // Create new node
    
    // Compare the strings in upper case
    if(cflag == 1) {
        if(upper_cmp(root -> data, value) < 0) {
            root -> right = insert(root -> right, value, cflag);
        }

        else if(upper_cmp(root -> data, value) > 0) {
            root -> left = insert(root -> left, value, cflag);
        }
    }

    // Compare the strings as they are given
    else {
        if(reg_cmp(root -> data, value) < 0) {
            root -> right = insert(root -> right, value, cflag);
        }

        else if(reg_cmp(root -> data, value) > 0) {
            root -> left = insert(root -> left, value, cflag);
        }
    }
 
    return root;
}

/* Performs inorder traversal of given tree and outputs it */
void print_inorder(Node *root, FILE *output) {
    if(root != NULL) {
        print_inorder(root -> left, output);
        fprintf(output, "%s", root -> data);
        print_inorder(root -> right, output);
    }
}

/* Deletes and reclaims tree from memory using postorder traversal */
void delete(Node *root) {
    if(root != NULL) {
        delete(root -> left);
        delete(root -> right);
        free(root);
    }
}

/* Main function */
int main(int argc, char *argv[]) {
    FILE *input = stdin; // Input
    FILE *output = stdout; // Output
    int curr, cflag = 0;
    Node *root = NULL; // Initialize tree
    char contents[SIZE]; // String buffer to store input
	char *sentence; // String pointer to store input

    // Get command line arguments
    while((curr = getopt(argc, argv, "co:")) != -1) {
        switch(curr) {
            case 'c':
                cflag = 1;
                break;

            case 'o':
                output = fopen(optarg, "w");
                break;
            
            case '?':
                printf("Usage: bstsort [-c] [-o output_file_name] [input_file_name]\n");
                return -1;
        }
    }    

    // If input file is given
    if(optind < argc) {
        input = fopen(argv[optind], "r");

        // If input file not found, print error and exit
        if(input == NULL) {
            printf("Error: Could not open file %s\n", argv[optind]);
            return -1;
        }
    }

    // While not EOF and not end of input for stdin (i.e. empty line)
	while(fgets(contents, sizeof(contents), input) != NULL && reg_cmp(contents, "\n") != 0) {
		// Dynamically allocate memory for sentences
		sentence = (char *)malloc(strlen(contents));

        // Make sentence uppercase if -c flag is used
        if(cflag == 1) {
            for(int i = 0; i < SIZE; i++) {
                // Convert each char in sentence to uppercase
                contents[i] = toupper(contents[i]);
            }
        }

        // Copy sentence from buffer to string pointer
        strcpy(sentence, contents);
		
        // Insert sentence into the tree
        root = insert(root, sentence, cflag);
	}

    // Print inorder traversal of tree
    print_inorder(root, output);

    // Free memory
    delete(root);

    // Close input and output
    fclose(input);
    fclose(output);

    return 0;
}
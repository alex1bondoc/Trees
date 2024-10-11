#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct n {
    struct n *children[27];
    char *s;
    int height;
    int nrKids;
}Tree;

Tree* createNode(char *s){
    Tree *tree = (Tree*)malloc(sizeof(Tree));
    for(int i=0;i<27;++i){
        tree->children[i] = NULL;
    }
    tree->s = calloc(10, sizeof(char));
    strcpy(tree->s, s);
    tree->height = 0;
    tree->nrKids = 0;
    return tree;
}
void addSuffix(Tree *tree, char *s){
    int len = strlen(s);
    for(int i=len-1;i>=0;--i){
        Tree *aux = tree;
        int l = strlen(s+i);
        for(int j=0;j<l;++j){
            if(aux->children[(s+i)[j]-'a'] == NULL){
                char string[2];
                string[0] = (s+i)[j];
                string[1] = '\0';
                aux->children[(s+i)[j]-'a'] = createNode(string);
                aux->children[(s+i)[j]-'a']->height = aux->height+1;
                aux->nrKids++;
            }
            aux = aux->children[(s+i)[j]-'a'];
        }
        aux->children[26] = createNode("$");
        aux->nrKids++;
        aux->children[26]->height = aux->height+1;
    }
}

int searchSuffix(Tree *tree, char *s){
    int len = strlen(s);
    Tree *aux = tree;
    int i = 0;
    for(i=0;i<len;++i){
        if(aux->children[s[i]-'a'] == NULL){
            return 0;
        }
        else{
            aux = aux->children[s[i]-'a'];
        }
    }
    if(i==len && aux->children[26] != NULL){
        return 1;
    }
    return 0;
}

void freeTree(Tree *tree){
    for(int i=0;i<27;++i){
        if(tree->children[i]!=NULL){
            freeTree(tree->children[i]);
            tree->children[i] = NULL;
        }
    }
    free(tree->s);
    free(tree);
}
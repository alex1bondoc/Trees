#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

int main(int argc, char *argv[]){
    Tree *tree = createNode(" ");
    int n, m;
    tree->children[26] = createNode("$");
    tree->children[26]->height = 1;
    tree->nrKids =1;
    char *s = calloc(10, sizeof(char));

    if(strcmp(argv[1],"-c1")==0){
        FILE *fin = fopen(argv[2],"r");
        FILE *fout = fopen(argv[3], "w");
        fscanf(fin,"%d", &n);
        for(int l = 0;l<n;++l){
            fscanf(fin,"%s", s);
            addSuffix(tree, s);
        }
        Queue *q = createQueue();
        enque(q, tree->children[26]);
        for(int i=0;i<26;++i){
            if(tree->children[i]){
                enque(q, tree->children[i]);
            }
        }
        
        while(q->size>0){
            int size = q->size;
            for(int i=0;i<size;++i){
                Tree *aux = q->front->data; 
                fprintf(fout,"%s ", aux->s);
                if(aux->children[26])
                    enque(q, aux->children[26]);
                for(int j=0;j<26;++j){
                    if(aux->children[j]!=NULL)
                        enque(q, aux->children[j]);
                }
                deque(q);
            }
            fprintf(fout,"\n");
        }
        
        freeTree(tree);
        freeQ(q);
        free(s);
        fclose(fin);
        fclose(fout);
        
    }
    else if(strcmp(argv[1], "-c2")==0){
        int k = atoi(argv[2]);
        FILE *fin = fopen(argv[3],"r");
        FILE *fout = fopen(argv[4], "w");
        fscanf(fin,"%d", &n);
        for(int l = 0;l<n;++l){
            fscanf(fin,"%s", s);
            addSuffix(tree, s);
        }
        Queue *q = createQueue();
        int maxKids = 1;
        enque(q, tree->children[26]);
        for(int i=0;i<26;++i){
            if(tree->children[i]){
                maxKids++;
                enque(q, tree->children[i]);
            }
        }    
        int nrLeaf = 1, nr = 0;
        while(q->size>0){
            int size = q->size;
            for(int i=0;i<size;++i){
                Tree *aux = q->front->data; 
                if(aux->nrKids > maxKids)
                    maxKids = aux->nrKids;
                if(aux->children[26]){
                    nrLeaf++;
                    if(aux->height == k)
                        nr++;
                    enque(q, aux->children[26]);
                }
                for(int j=0;j<26;++j){
                    if(aux->children[j]!=NULL)
                        enque(q, aux->children[j]);
                }
                deque(q);
            }
        }
        fprintf(fout,"%d\n%d\n%d\n", nrLeaf, nr, maxKids);
        freeTree(tree);
        freeQ(q);
        free(s);
        fclose(fin);
        fclose(fout);
    }
    else if(strcmp("-c3",argv[1]) == 0){
        FILE *fin = fopen(argv[2],"r");
        FILE *fout = fopen(argv[3], "w");
        fscanf(fin,"%d%d", &n, &m);
        for(int l = 0;l<n;++l){
            fscanf(fin,"%s", s);
            addSuffix(tree, s);
        }
        for(int i=0;i<m;++i){
            fscanf(fin,"%s",s);
            fprintf(fout,"%d\n", searchSuffix(tree, s));
        }
        freeTree(tree);
        free(s);
        fclose(fin);
        fclose(fout);
    }
    else {
        FILE *fin = fopen(argv[2],"r");
        FILE *fout = fopen(argv[3], "w");
        fscanf(fin,"%d", &n);
        for(int l = 0;l<n;++l){
            fscanf(fin,"%s", s);
            addSuffix(tree, s);
        }
        Queue *q = createQueue();
        for(int i=0;i<26;++i){
            if(tree->children[i]){
                enque(q, tree->children[i]);
            }
        }
        while(q->size>0){
            int size = q->size;
            for(int i=0;i<size;++i){
                Tree *aux = q->front->data; 
                int poz = -1;
                while(aux->nrKids == 1 && aux->children[26] == NULL){
                    for(int i=0;i<26;++i){
                        if(aux->children[i]!=NULL)
                            poz = i;
                    }
                    strcat(aux->s, aux->children[poz]->s);
                    aux->nrKids = aux->children[poz]->nrKids;
                    for(int i=0;i<27;++i){
                        if(i!=poz)
                            aux->children[i] = aux->children[poz]->children[i];
                    }
                    aux->children[poz] = aux->children[poz]->children[poz];
                    free(aux->children[poz]->s);
                    free(aux->children[poz]);
                }
                for(int j=0;j<26;++j){
                    if(aux->children[j]!=NULL)
                        enque(q, aux->children[j]);
                }
                deque(q);
            }
        }
        enque(q, tree->children[26]);
        for(int i=0;i<26;++i){
            if(tree->children[i]){
                enque(q, tree->children[i]);
            }
        }
        
        while(q->size>0){
            int size = q->size;
            for(int i=0;i<size;++i){
                Tree *aux = q->front->data; 
                fprintf(fout,"%s ", aux->s);
                if(aux->children[26])
                    enque(q, aux->children[26]);
                for(int j=0;j<26;++j){
                    if(aux->children[j]!=NULL)
                        enque(q, aux->children[j]);
                }
                deque(q);
            }
            fprintf(fout,"\n");
        }
        freeTree(tree);
        freeQ(q);
        free(s);
        fclose(fin);
        fclose(fout);
    }

}
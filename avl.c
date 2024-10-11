/*
*	Created by Nan Mihai on 11.04.2023
*	Copyright (c) 2023 Nan Mihai. All rights reserved.
*	Laborator 7 - Structuri de date și algoritmi
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2022-2023, Seria CD
*/
#include "avl.h"

Tree createTree(T value) {
	Tree tree = (Tree)malloc(sizeof(Tree));
	tree->value = value;
	tree->height = 0;
	tree->right = tree->left = NULL;
	return tree;
}

int max(int a, int b) {
	if (a > b)
		return a;
	return b;
}

int height(Tree root) {
	if(root == NULL){
		return -1;
	}
	else return 1+ max(height(root->right), height(root->left));
}

int balancedFactor(Tree root) {
	if(root == NULL){
		return 0;
	}
	else return height(root->right) - height(root->left);
}

void updateHeight(Tree root) {
	if(root != NULL)
		root->height = height(root);
}

Tree leftRotation(Tree x) {
	Tree z = x->right;
	x->right = z->left;
	z->left = x;
	x->height = max(height(x->left), height(x->right))+1;
	z->height = max(height(z->left), height(z->right))+1;
	return z;
}

Tree rightRotation(Tree x) {
	Tree z = x->left;
	x->left = z->right;
	z->right = x;
	x->height = max(height(x->left), height(x->right))+1;
	z->height = max(height(z->left), height(z->right))+1;
	return z;
}

Tree insert(Tree root, T value) {
	
	if(root == NULL){
		root = createTree(value);
		return root;
	}
	if(root->value > value){
		root->left = insert(root->left, value);
	}
	else if(root->value < value){
		root->right = insert(root->right, value);
	}
	else return root;
	root->height = max(height(root->right), height(root->left))+1;
	int bf = balancedFactor(root);
	if(bf<-1 && value < root->left->value)
		return rightRotation(root);
	if(bf>1 && value > root->right->value)
		return leftRotation(root);
	if(bf<-1 && value > root->left->value){
		root->left = leftRotation(root->left);
		return rightRotation(root);
	}
	if(bf>1 && value < root->right->value){
		root->right = rightRotation(root->right);
		return leftRotation(root);
	}
	return root;
}

Tree minimum(Tree root) {
	if(root == NULL)
		return NULL;
	while(root->left != NULL){
		root = root->left;
	}
	return root;
}

Tree delete(Tree root, T value) {
	if(root == NULL)
		return NULL;
	if(value < root->value){
		root->left = delete(root->left, value);
	}
	else if(value > root->value){
		root->right = delete(root->right, value);
	}
	else {
		if(root->right == NULL || root->left == NULL){
			Tree tmp = root;
			if(root->left != NULL){
				root = root->left;
			}
			else root = root->right;
			free(tmp);
		}
		else{
			Tree tmp = minimum(root->right);
			root->value = tmp->value;
			root->right = delete(root->right, tmp->value);
		}
	}
	if(root == NULL)
		return NULL;
	root->height = 1+ max(height(root->left), height(root->right));
	int bf = balancedFactor(root);
	if(bf<-1 && balancedFactor(root->left)<=0)
		return rightRotation(root);
	if(bf>1 && balancedFactor(root->left)>=0){
		root->left = leftRotation(root->left);
		return rightRotation(root);
	}
	if(bf>1 && balancedFactor(root->right) >=0){
		return(leftRotation(root));
	}
	if (bf<-1 && balancedFactor(root->right) <=0){
		root->right = rightRotation(root->right);
		return leftRotation(root);
	}
	return root;
}

Tree freeTree(Tree root) {
	if(root!=NULL){
		Tree left = root->left;
		Tree right = root->right;
		free(root);
		root = NULL;
		freeTree(left);
		freeTree(right);
		return root;
	}
}
/*
 *  triemaker.c
 *  
 *  Created by Javid Mann on 09/06/2023.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "triemaker.h"

struct TrieNode root = {
	.terminal = '?',
	.index = 0
};

struct TrieNode* nodes[350];
int nodesIndex = 1;
int fileEnd = 0;
char writeToFile[2000];

int
printNodes(FILE* file, struct TrieNode* node, int start) {
	int i, x, y;
	int length, children, childStart;
	
	length = findNodeLength(node);
	fileEnd = start + length;
	children = (length-2)/3;
	
	writeToFile[start + 0] = node -> terminal;
	writeToFile[start + 1] = node -> index;
	
	for (x=0; x<children; x++) {
		childStart = printNodes(file, node -> entry[x].next, fileEnd);
		writeToFile[start + (x*3)+2] = node -> entry[x].letter - 96;
		writeToFile[start + (x*3)+3] = (childStart+49152) & 0xff;
		writeToFile[start + (x*3)+4] = (childStart+49152) >>8 & 0xff;
	}
	return start;
}

int
findNodeLength(struct TrieNode* node) {
	int i;
	int length = 2;
	for(i=0; i<15; i++) {
		if (node -> entry[i].letter == 0) {
			break;
		}
		else {
			length+=3;
		}
	}
	return length;
}

int
findNodeLengthRecursive(struct TrieNode* node, int length) {
	int currentLength = findNodeLength(node);
	int children = (currentLength-2)/3;
	int x;
	
	length = length + currentLength;
	
	for (x=0; x<children; x++) {
		length = findNodeLengthRecursive(node -> entry[x].next, length);
	}
	return length;
}

int
main(int argc, char *argv[]) {
	int i, x, y, z;
	int existsInNode;
	char currentChar;
	struct TrieNode* currentNode = &root;
	
	FILE *write_ptr;
	
	root.entry = (struct Character *) malloc(15*sizeof(struct Character));
	
	for (i=0; i<15; i++) {
		root.entry[i].letter = 0;
	}
	
	for (i=0; i<500; i++) {
		nodes[i] = 0;
	}
	
	nodes[0] = &root;
	
	for (i=0; i<=128; i++) {
		x=0;
		currentNode = &root;
		currentChar = words[i][x];
		while (currentChar != 0) {
			existsInNode = 0;
			for (y=0; y<15; y++) {
				if (currentNode -> entry[y].letter == 0) {
					break;
				}
				if (currentNode -> entry[y].letter == currentChar) {
					existsInNode = 1;
					break;
				}
			}
			if (existsInNode) {
				currentNode = currentNode -> entry[y].next;
			}
			else {
				currentNode -> entry[y].letter = currentChar;
				currentNode -> entry[y].next = (struct TrieNode *) malloc(sizeof(struct TrieNode));
				currentNode -> entry[y].next -> entry = (struct Character *) malloc(15*sizeof(struct Character));
				currentNode -> entry[y].next -> terminal = '?';
				currentNode -> entry[y].next -> index = 0;
				for (z=0; z<15; z++) {
					currentNode -> entry[y].next -> entry[z].letter = 0;
				}
				currentNode = currentNode -> entry[y].next;
				nodes[nodesIndex] = currentNode;
				nodesIndex++;
			}
			x++;
			currentChar = words[i][x];
		}
		currentNode -> terminal = '#';
		currentNode -> index = (char) i;
	}

	
	/*for (i=0; i<500; i++) {
		if (nodes[i] == 0) {
			break;
		}
		for (y=0; y<15; y++) {
			printf("%d ", nodes[i]);
			printf("%c ", nodes[i] -> entry[y].letter);
			printf("%d\n", nodes[i] -> entry[y].next);
		}
		printf("\n\n");
	}
	printf("%d\n", i);*/
	
	write_ptr = fopen("trie.bin","wb");  // w for write, b for binary
	printNodes(write_ptr, &root, 0);
	fwrite(writeToFile,1552,1,write_ptr);
	fclose(write_ptr);
	
	return 0;
}
// Huffman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdbool>
#include <omp.h>

#define MAX_FILE_SIZE 1000
int lenght[27] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int chunkoffset[4] = {0,0,0,0};
int bitsinchunk[4] = {0,0,0,0};

struct heapnode {
	float fr;
	char ch;
	struct heapnode* left;
	struct heapnode* right;

};
struct minheap {
	int size;
	int capacity;
	struct heapnode** arr;
};
struct minheap* createMinHeap(int size, float* frequency, char* names) {
	//printf("\n address of frequency:%d", frequency);
	if (size == 0) {
		return 0;
	}
	else {
		struct minheap* heap=(struct minheap*)malloc(sizeof(struct minheap));
		heap->size = 0;
		heap->capacity = size;
		heap->arr = (struct heapnode**)malloc(sizeof(struct heapnode*)*size);
		int i;
		for (i = 0; i < size; i++) {
			struct heapnode* temp = (struct heapnode*)malloc(sizeof(struct heapnode));
			//printf("\nfr:%f", frequency[i]);
			temp->fr = frequency[i];
			temp->ch = names[i];
			temp->left = NULL;
			temp->right = NULL;
			heap->arr[i] = temp;
			heap->size += 1;
		}
		return heap;
	}
}
void printheap(struct minheap* h, int size) {
	int i;
	for (i = 0; i < size; i++) {
		printf("\ncharacter:%c frequency:%f", h->arr[i]->ch, h->arr[i]->fr);
	}

}
int minchild(struct minheap* h, int size, int pos) {
	int child1, child2;
	child1 = (2 * pos) + 1;
	child2 = (2 * pos) + 2;
	if (child2 > size - 1) {
		return child1;
	}
	else {
		if (h->arr[child1]->fr < h->arr[child2]->fr) {
			return child1;
		}
		else if (h->arr[child1]->fr > h->arr[child2]->fr) {
			return child2;
		}
		else {
			return child1;
		}
	}
}
void downheapify(struct minheap* h, int size, int pos) {
	int min;
	
	while (1) {
		if (pos >= (size - 1) / 2) {
			break;
		}
		if (h->arr[pos]->fr >= h->arr[minchild(h, size, pos)]->fr) {
			min = minchild(h, size, pos);
			struct heapnode* temp;
			temp = h->arr[pos];
			h->arr[pos] = h->arr[min];
			h->arr[min] = temp;
			pos = min;
			continue;
		}
		else {
			break;
		}

	}


}
void minheapify(struct minheap* h, int size) {
	int i;
	int last = size - 1;
	int first = 0;
	int start = (last - 1) / 2;
	for (i = start; i >= first; i--) {
		downheapify(h, size, i);

	}

}
struct heapnode* getmin(struct minheap* h, int size) {
	struct heapnode* temp;
	temp = h->arr[0];
	h->size -= 1;
	if (h->size < 0) {
		return NULL;
	}
	if (h->size == 0) {
		//h->arr[0] = NULL;
		return temp;
	}
	else if (h->size == 1) {
		h->arr[0] = h->arr[1];
		//h->arr[1] = NULL;
		return temp;
	}
	else if (h->size == 2) {
		int m = minchild(h, 3, 0);
		h->arr[0] = h->arr[m];
		if (m == 1) {
			h->arr[1] = h->arr[2];
		}
		//h->arr[m] = NULL;
		return temp;
	}
	h->arr[0] = h->arr[size - 1];

	downheapify(h, h->size, 0);
	return temp;
}

void addtoheap(struct minheap* h, int size, struct heapnode* node) {
	h->arr[size] = node;
	h->size += 1;
	if (h->size == 1) {
		return;
	}
	int current = (h->size) - 1;
	int parant = (current - 1)/2;
	while (1) {
		if (current == 0) {
			break;
		}
		else if (h->arr[parant]->fr > h->arr[current]->fr) {
			struct heapnode* temp;
			temp = h->arr[parant];
			h->arr[parant] = h->arr[current];
			h->arr[current] = temp;
			current = parant;
			if (current != 0) {
				parant = (current - 1) / 2;
				continue;
			}
		}
		else {
			break;
		}
	}
}
void huffman(struct minheap* h, int size) {
	struct heapnode* min1;
	struct heapnode* min2;
	
	while (h->size > 1) {
		min1 = getmin(h, h->size);
		min2 = getmin(h, h->size);
		if (min2 == NULL) {
			continue;
		}
		struct heapnode* newnode = (struct heapnode*)malloc(sizeof(struct heapnode));
		newnode->fr = (min1->fr) + (min2->fr);
		newnode->ch = '\0';
		newnode->left = min2;
		newnode->right = min1;
		addtoheap(h, h->size, newnode);
	}
	printf("\nfirst node after building tree:%f", h->arr[0]->fr);
}
void copystring(char* a, char* b, int d) {
	int i;
	for (i = 0; i < d; i++) {
		char x;
		x = b[i];
		a[i] = x;
	}
	a[d] = '\0';
}

int findstr(char a) {
	const char* list = "abcdefghijklmnopqrstuvwxyz ";
	for (int i = 0; i < 27; i++) {
		if (a == list[i]) {
			if (i == 0) {
				return 27;
			}
			return i;
		}
	}
	return 0;
}

void buildpath(struct heapnode* node, char** encoding, char* temp, int depth) {
	int index;
	if (index = findstr(node->ch)) {
		char* code = (char*)malloc(sizeof(char)*depth+1);
		copystring(code, temp, depth);
		printf("\nprinting %c : %s", node->ch, code);
		if (index == 27) {
			encoding[0] = code;
			lenght[0] = depth;
			return;
		}
		encoding[index] = code;
		lenght[index] = depth;
		return;
	}
	if (node->left != NULL) {
		temp[depth] = '0';
		buildpath(node->left, encoding, temp, depth + 1);
		temp[depth] = '\0';
	}
	if (node->right != NULL) {
		temp[depth] = '1';
		buildpath(node->right, encoding, temp, depth + 1);
		temp[depth] = '\0';
	}
	else {
		return;
	}
}


void getencoding(struct heapnode* start,char** encoding) {
	char* l=(char*)malloc(sizeof(char)*27);
	char* r = (char*)malloc(sizeof(char) * 27);
	int depth = 0;
	if (start->left != NULL) {
		l[0] = '0';
		buildpath(start->left, encoding,l,depth+1);
	}
	if (start->right != NULL) {
		r[0] = '1';
		buildpath(start->right, encoding, r,depth+1);
	}
}

void printencoding(char** encoding,int size) {
	const char* a = "abcdefghijklmnopqrstuvwxyz ";
	int i;
	printf("\n*********************printing encoding***************** ");
	for (i = 0; i < size; i++) {
		if (encoding[i] == "\0") {
			continue;
		}
		printf("\n%c : %s", a[i], encoding[i]);
	}
}
struct filepointer {
	char* buff;
	int pos;
	int size;
};
struct filepointer* getfile(const char* name) {
	FILE* f;
	struct filepointer* fp=(struct filepointer*)malloc(sizeof(struct filepointer));
	fp->buff = (char*)malloc(sizeof(char) * MAX_FILE_SIZE);
	fp->pos = 0;
	char temp;
	fopen_s(&f,name, "r");
	while ((temp = fgetc(f)) != EOF) {
		if (temp == '\n')
			continue;
		fp->buff[fp->pos] = temp;
		fp->pos += 1;
	}
	fp->buff[fp->pos] = EOF;
	fp->size = fp->pos;
	fp->pos = 0;
	fclose(f);
	return fp;
}

void printBuff(struct filepointer* fp) {
	int i;
	for (i = 0; i < fp->size; i++) {
		printf("%c", fp->buff[i]);
	}
}
int getSize(struct filepointer* fp) {
	omp_set_num_threads(4);
	int size = 0;
	
#pragma omp parallel
	{
		extern int lenght[27];
		extern int chunkoffset[4];
		extern int bitsinchunk[4];
		int tid = omp_get_thread_num();
		chunkoffset[tid] = 0;
		bitsinchunk[tid] = 0;
#pragma omp for schedule(static) nowait
		for (int i = 0; i < fp->size; ++i) {
			int index = (fp->buff[i]) - 97;
			if (index == -65)
				index = 26;
			bitsinchunk[(i/((fp->size)/4))] += lenght[index];
		}
#pragma omp barrier
//#pragma omp for schedule(static) nowait
		
	}
	for (int i = 0; i < 3; ++i) {
		chunkoffset[i + 1] = size + bitsinchunk[i];
		size += bitsinchunk[i];
	}
	size += bitsinchunk[3];
	return size;
}
int writeparallel(struct filepointer* fp,int size,char** encoding,const char* fileName) {
	extern int lenght[27];
	extern int bitsinchunk[4];
	extern int chunkoffset[4];
	int noBytes = size / 8;
	if (size % 8 != 0)
		noBytes += 1;

	bool* buffer = (bool*)malloc(sizeof(bool)*noBytes);
	FILE* f;
	fopen_s(&f, fileName, "wb");
#pragma omp parallel
	{
	int tid = omp_get_thread_num();
	int buffchunkponiter = 0;
#pragma omp for schedule(static) nowait
	for (int i = 0; i < fp->size; ++i) {
		int index = (fp->buff[i]) - 97;
		if (index == -65)
			index = 26;
		for (int j = 0; j < lenght[index]; j++) {
			char t;
			t = encoding[index][j];
			if (t == '0') {
				buffer[chunkoffset[tid] + buffchunkponiter] = false;
				buffchunkponiter += 1;
			}
			else if (t == '1') {
				buffer[chunkoffset[tid] + buffchunkponiter] = true;
				buffchunkponiter += 1;
			}
		}
	}
	}
	printf("\nprinting compressed string\n");
	for (int i = 0; i < size; i++) {
		if (buffer[i] == true) {
			printf("%d", 1);
		}
		else if (buffer[i] == false) {
			printf("%d", 0);
		}
		else {
			continue;
		}
	}
	if (fwrite(buffer, sizeof(bool)*noBytes, 1, f)) {
		//free(buffer);
		fclose(f);
		return 1;
	}
	else {
		//free(buffer);
		fclose(f);
		return 0;
	}
	
}
int main() {
	int i;
	char names[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' ' };
	//const char* names[27] = { "a","b","c","d"," " };
	float freq[27];
	char** encoding =(char**)malloc(sizeof(char*)*27);
	for (i = 0; i < 27; i++) {
		//freq[i] = (float)(26 - i + 1) / 27;
		freq[i] = 27-i;
		//printf("\n%f", freq[i]);
	}
	//printf("\naddress of freq:%d", freq);
	struct minheap* heap = createMinHeap(27, freq, names);
	printf("\n***********before heapifying************");
	printheap(heap, 27);
	//printf("\ntest: %d",a);
	minheapify(heap, 27);

	printf("\n***********after heapifying *************\n");
	printheap(heap, 27);
	printf("\n*************starting building huffman tree****************");
	//printf("hsize%d", heap->size);
	huffman(heap, 27);

	//get encoding
	getencoding(heap->arr[0], encoding);
	printencoding(encoding, 27);

	//gettinng and printing file
	struct filepointer* fp;
	fp = getfile("file1.txt");
	printf("\n");
	printBuff(fp);

	printf("\nprinting lenght array\n");
	for (i = 0; i < 27; ++i) {
		printf("\n%c : %d", names[i], lenght[i]);
	}

	//trying to do mess writing to file
	int size;
	size = getSize(fp);
	if (writeparallel(fp,size, encoding, "file2.txt")) {
		printf("\nsuccess");	}
	else {
		printf("\nfailed to write");
	}
	return 0;
}


// Run program: Ctrl + F27 or Debug > Start Without Debugging menu
// Debug program: F27 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   27. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

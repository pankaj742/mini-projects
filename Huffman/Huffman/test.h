#pragma once
#include <cstdio>;
#include <cstdlib>;


//struct heapnode {
//	float fr;
//	const char* ch;
//	struct heapnode* left;
//	struct heapnode* right;
//
//};
//struct minheap {
//	int size;
//	int capacity;
//	struct heapnode** arr;
//};
//struct minheap* createMinHeap(int size, float* frequency, const char** names) {
//	printf("\n address of frequency:%d", frequency);
//	if (size == 0) {
//		return 0;
//	}
//	else {
//		struct minheap* heap = (struct minheap*)malloc(sizeof(struct minheap));
//		heap->size = 0;
//		heap->capacity = size;
//		heap->arr = (struct heapnode**)malloc(sizeof(struct heapnode*)*size);
//		int i;
//		for (i = 0; i < size; i++) {
//			struct heapnode* temp = (struct heapnode*)malloc(sizeof(struct heapnode));
//			printf("\nfr:%f", frequency[i]);
//			temp->fr = frequency[i];
//			temp->ch = names[i];
//			temp->left = NULL;
//			temp->right = NULL;
//			heap->arr[i] = temp;
//			heap->size += 1;
//		}
//		return heap;
//	}
//}
//void printheap(struct minheap* h, int size) {
//	int i;
//	for (i = 0; i < size; i++) {
//		printf("\ncharacter:%s frequency:%f", h->arr[i]->ch, h->arr[i]->fr);
//	}
//
//}
//int minchild(struct minheap* h, int size, int pos) {
//	int child1, child2;
//	child1 = (2 * pos) + 1;
//	child2 = (2 * pos) + 2;
//	if (child2 > size - 1) {
//		return child1;
//	}
//	else {
//		if (h->arr[child1]->fr < h->arr[child2]->fr) {
//			return child1;
//		}
//		else if (h->arr[child1]->fr > h->arr[child2]->fr) {
//			return child2;
//		}
//		else {
//			return child1;
//		}
//	}
//}
//void downheapify(struct minheap* h, int size, int pos) {
//	int min;
//
//	while (1) {
//		if (pos >= (size - 1) / 2) {
//			break;
//		}
//		if (h->arr[pos]->fr >= h->arr[minchild(h, size, pos)]->fr) {
//			min = minchild(h, size, pos);
//			struct heapnode* temp;
//			temp = h->arr[pos];
//			h->arr[pos] = h->arr[min];
//			h->arr[min] = temp;
//			pos = min;
//			continue;
//		}
//		else {
//			break;
//		}
//
//	}
//
//
//}
//void minheapify(struct minheap* h, int size) {
//	int i;
//	int last = size - 1;
//	int first = 0;
//	int start = (last - 1) / 2;
//	for (i = start; i >= first; i--) {
//		downheapify(h, size, i);
//
//	}
//
//}
//struct heapnode* getmin(struct minheap* h, int size) {
//	struct heapnode* temp;
//	temp = h->arr[0];
//	h->size -= 1;
//	if (h->size == 0) {
//		//h->arr[0] = NULL;
//		return temp;
//	}
//	else if (h->size == 1) {
//		h->arr[0]= h->arr[1];
//		//h->arr[1] = NULL;
//		return temp;
//	}
//	else if (h->size == 2) {
//		int m = minchild(h, 3, 0);
//		h->arr[0] = h->arr[m];
//		if (m == 1) {
//			h->arr[1] = h->arr[2];
//		}
//		//h->arr[m] = NULL;
//		return temp;
//	}
//	h->arr[0] = h->arr[size - 1];
//
//	downheapify(h, h->size, 0);
//	return temp;
//}
//void addtoheap(struct minheap* h, int size, struct heapnode* node) {
//	h->arr[size] = node;
//	h->size += 1;
//	if (h->size == 1) {
//		return;
//	}
//	int current = (h->size) - 1;
//	int parant = (current - 1) / 2;
//	while (1) {
//		if (current == 0) {
//			break;
//		}
//		else if (h->arr[parant]->fr > h->arr[current]->fr) {
//			struct heapnode* temp;
//			temp = h->arr[parant];
//			h->arr[parant] = h->arr[current];
//			h->arr[current] = temp;
//			current = parant;
//			if (current != 0) {
//				parant = (current - 1) / 2;
//				continue;
//			}
//		}
//		else {
//			break;
//		}
//	}
//}
//void huffman(struct minheap* h, int size) {
//	struct heapnode* min1;
//	struct heapnode* min2;
//
//	while (h->size > 1) {
//		min1 = getmin(h, h->size);
//		min2 = getmin(h, h->size);
//		struct heapnode* newnode = (struct heapnode*)malloc(sizeof(struct heapnode));
//		newnode->fr = (min1->fr) + (min2->fr);
//		newnode->left = min2;
//		newnode->right = min1;
//		addtoheap(h, h->size, newnode);
//	}
//	printf("\nfirst node:%f", h->arr[0]->fr);
//}
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
	printf("\n address of frequency:%d", frequency);
	if (size == 0) {
		return 0;
	}
	else {
		struct minheap* heap = (struct minheap*)malloc(sizeof(struct minheap));
		heap->size = 0;
		heap->capacity = size;
		heap->arr = (struct heapnode**)malloc(sizeof(struct heapnode*)*size);
		int i;
		for (i = 0; i < size; i++) {
			struct heapnode* temp = (struct heapnode*)malloc(sizeof(struct heapnode));
			printf("\nfr:%f", frequency[i]);
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
	int parant = (current - 1) / 2;
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
	printf("\nfirst node:%f", h->arr[0]->fr);
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
		char* code = (char*)malloc(sizeof(char)*depth + 1);
		copystring(code, temp, depth);
		printf("\nprinting %c : %s", node->ch, code);
		if (index == 27) {
			encoding[0] = code;
		}
		encoding[index] = code;
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


void getencoding(struct heapnode* start, char** encoding) {
	char* l = (char*)malloc(sizeof(char) * 27);
	char* r = (char*)malloc(sizeof(char) * 27);
	int depth = 0;
	if (start->left != NULL) {
		l[0] = '0';
		buildpath(start->left, encoding, l, depth + 1);
	}
	if (start->right != NULL) {
		r[0] = '1';
		buildpath(start->right, encoding, r, depth + 1);
	}
}

void printencoding(char** encoding, int size) {
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


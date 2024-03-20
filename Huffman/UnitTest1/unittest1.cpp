#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Huffman/test.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		struct minheap* h;
		TEST_METHOD(TestMinHeap)
		{
			// TODO: Your test code here
			char names[27] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' ' };
			float freq[27] = { 1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0,14.0,15.0,16.0,17.0,18.0,19.0,20.0,21.0,22.0,23.0,24.0,25.0,26.0,27.0};
			h = createMinHeap(27, freq, names);
			minheapify(h, 27);
			for (int i = 0; i <= 12; i++) {
				int child1, child2;
				child1 = i * 2 + 1;
				child2 = i * 2 + 2;
				int child1freq = h->arr[child1]->fr;
				int child2freq = h->arr[child2]->fr;
				if ((h->arr[i]->fr <= child1freq) && (h->arr[i]->fr <= child2freq)) {
					continue;
				}
				else {
					Assert::Fail;
				}
			}
		}
		TEST_METHOD(TestInsertExtract) {
			this->TestMinHeap();
			struct heapnode* a[27];
			for (int i = 0; i < 27; i++) {
				a[i] = getmin(h, 27 - i);
				Assert::AreEqual(a[i]->fr, (float)i + 1);
			}
			for (int i = 26; i >=0; i--) {
				addtoheap(h, h->size, a[i]);
				Assert::AreEqual(h->arr[0]->fr, a[i]->fr);
			}
		}
		TEST_METHOD(TestHuffmanTree) {
			this->TestInsertExtract();
			huffman(h, 27);
			int sum = (27 * 28) / 2;
			Assert::IsTrue((h->arr[0]->fr == sum) && (h->arr[0]->left != NULL) && (h->arr[0]->right != NULL));
		
		}
		TEST_METHOD(TestFindStr) {
			char* l = "abcdefghijklmnopqrstuvwxyz ";
			int t,i;
			for (i = 1; i < 27; i++) {
				t=findstr(l[i]);
				Assert::AreEqual(t, i);
			}
			//special case in the context of coding for a very difficult to find
			Assert::AreEqual(findstr('a'),27);
		}
		TEST_METHOD(testgetencoding) {
			char** encoding=(char**)malloc(sizeof(char*)*27);
			this->TestHuffmanTree();
			getencoding(h->arr[0], encoding);
			int i;
			for (i = 0; i < 27; i++) {
				Assert::IsNotNull(encoding[i]);
			}
		}

	};
}
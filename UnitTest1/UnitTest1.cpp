#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab12.5/lab12.5.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(TestPushPop)
        {
            Elem* stack = nullptr;
            push(stack, "hello");
            push(stack, "world");

            Assert::AreEqual("world", pop(stack).c_str());
            Assert::AreEqual("hello", pop(stack).c_str());
            Assert::AreEqual("", pop(stack).c_str()); 
        }

        TEST_METHOD(TestWordCount)
        {
            WordCount* head = nullptr;

            incrementWordCount(head, "hello");
            incrementWordCount(head, "world");
            incrementWordCount(head, "hello");

            Assert::IsNotNull(head);
            Assert::AreEqual("hello", head->word.c_str()); 
            Assert::AreEqual(2, head->count); 

            Assert::IsNotNull(head->next);
            Assert::AreEqual("world", head->next->word.c_str());
            Assert::AreEqual(1, head->next->count);

            cleanUpWordCount(head);
        }

        TEST_METHOD(TestFileReading)
        {
            Elem* top = nullptr;
            const string testFilename = "testfile.txt";

            ofstream out(testFilename);
            out << "hello\nworld\nhello\n";
            out.close();

            readWordsFromFile(testFilename, top);

            Assert::AreEqual("hello", pop(top).c_str());
            Assert::AreEqual("world", pop(top).c_str());
            Assert::AreEqual("hello", pop(top).c_str()); 
            Assert::AreEqual("", pop(top).c_str()); 

            remove(testFilename.c_str());
        }
	};
}
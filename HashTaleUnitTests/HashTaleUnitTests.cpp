#include "pch.h"
#include "CppUnitTest.h"
#include "..\HashTable\HashTable.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HashTableUnitTests
{
	TEST_CLASS(HashTableUnitTests)
	{
	public:
		
		TEST_METHOD(ConstructorTests)
		{
			HashTable a;
			Assert::IsTrue(a.size() == 0);
		}
		TEST_METHOD(CopyTests)
		{
			HashTable a, b, c;
			Value v;
			v.age = 1;
			v.weight = 2;
			a.insert("Example", v);
			b = std::move(a);
			Assert::IsTrue(b.contains("Example"));
			Assert::IsTrue(a.empty() == 1);
			c.insert("SecondExample", v);
			b = c;
			Assert::IsFalse(b.contains("Example"));
			Assert::IsTrue(b.contains("SecondExample"));
			Assert::IsTrue(c.empty() == 0);
		}
		TEST_METHOD(SwapTests)
		{
			HashTable a, b;
			Value v, v1;
			v.age = 1;
			v.weight = 2;
			v1.age = 11;
			v1.weight = 22;
			a.insert("Example", v);
			b.insert("Example2", v1);
			a.swap(b);
			Assert::IsFalse(a.contains("Example"));
			Assert::IsTrue(a.contains("Example2"));
			Assert::IsTrue(b.contains("Example"));
			Assert::IsFalse(b.contains("Example2"));
		}
		TEST_METHOD(ClearTests)
		{
			HashTable a;
			Value v, v1;
			v.age = 1;
			v.weight = 2;
			v1.age = 11;
			v1.weight = 22;
			a.insert("Example", v);
			a.insert("Example2", v1);
			a.clear();
			Assert::IsTrue(a.empty() == 1);
		}
		TEST_METHOD(EraseTests)
		{
			HashTable a;
			Value v, v1;
			v.age = 1;
			v.weight = 2;
			v1.age = 11;
			v1.weight = 22;
			a.insert("Example", v);
			a.insert("Example2", v1);
			a.erase("Example");
			Assert::IsFalse(a.contains("Example"));
			Assert::IsTrue(a.contains("Example2"));
		}
		TEST_METHOD(InsertTests)
		{
			HashTable a;
			for (int i = 0; i < 1009; ++i)
			{
				Value v;
				v.age = i;
				v.weight = 2 * i;
				a.insert(std::to_string(i), v);
				Assert::IsTrue(a.contains(std::to_string(i)) == 1);
				Value v1 = a.at(std::to_string(i));
				Assert::IsTrue(v1.age == i);
				Assert::IsTrue(v1.weight == 2 * i);
			}
		}
		TEST_METHOD(ContainsTests)
		{
			HashTable a;
			Value v, v1;
			v.age = 1;
			v.weight = 2;
			v1.age = 11;
			v1.weight = 22;
			a.insert("Example", v);
			a.insert("Example2", v1);
			Assert::IsTrue(a.contains("Example2"));
			Assert::IsTrue(a.contains("Example"));
			a.erase("Example2");
			Assert::IsTrue(a.contains("Example"));
			Assert::IsFalse(a.contains("Example2"));
		}
		TEST_METHOD(SQBracketsTests)
		{
			HashTable a;
			Value v, v1;
			v.age = 1;
			v.weight = 2;
			v1.age = 11;
			v1.weight = 22;
			a.insert("Example", v);
			a.insert("Example2", v1);
			Value v2 = a["Example"];
			Value v3 = a["Example3"];
			Assert::IsTrue(v2.age == 1);
			Assert::IsTrue(v2.weight == 2);
			Assert::IsTrue(v3.age == 0);
			Assert::IsTrue(v3.weight == 0);
		}
		TEST_METHOD(AtTests)
		{
			HashTable a;
			Value v, v1;
			v.age = 1;
			v.weight = 2;
			v1.age = 11;
			v1.weight = 22;
			a.insert("Example", v);
			a.insert("Example2", v1);
			Value v3 = a.at("Example");
			const Value v2 = a.at("Example2");
			Assert::IsTrue(v3.age == 1);
			Assert::IsTrue(v3.weight == 2);
			Assert::IsTrue(v2.age == 11);
			Assert::IsTrue(v2.weight == 22);
		}
		TEST_METHOD(SizeTests)
		{
			HashTable a;
			Assert::IsTrue(a.size() == 0);
			Value v, v1;
			v.age = 1;
			v.weight = 2;
			v1.age = 11;
			v1.weight = 22;
			a.insert("Example", v);
			a.insert("Example2", v1);
			Assert::IsTrue(a.size() == 2);
		}
		TEST_METHOD(EmptyTests)
		{
			HashTable a;
			Assert::IsTrue(a.empty() == 1);
			Value v, v1;
			v.age = 1;
			v.weight = 2;
			v1.age = 11;
			v1.weight = 22;
			a.insert("Example", v);
			a.insert("Example2", v1);
			Assert::IsTrue(a.empty() == 0);
		}
		TEST_METHOD(EqualTests)
		{
			HashTable a, b;
			Value v, v1;
			v.age = 1;
			v.weight = 2;
			v1.age = 11;
			v1.weight = 22;
			a.insert("Example", v);
			a.insert("Example2", v1);
			b.insert("Example", v);
			b.insert("Example2", v1);
			Assert::IsTrue((a == b) == 1);
			Assert::IsTrue((a != b) == 0);
			b.erase("Example");
			Assert::IsTrue((a == b) == 0);
			Assert::IsTrue((a != b) == 1);
		}
	};
}

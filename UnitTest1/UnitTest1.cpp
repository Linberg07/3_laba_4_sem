#include "pch.h"
#include "CppUnitTest.h"
#include "../3laba/list.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(push_test)
		{
			list<int> list;
			list.push(1);
			list.push(2);
			Assert::IsTrue(list[1] == 2);
		}

		TEST_METHOD(pop_test)
		{
			list<int> list;
			list.push(1);
			list.push(2);
			list.push(3);
			list.pop();
			Assert::IsTrue(list[1] == 2);
		}

	};
}
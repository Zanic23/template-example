#pragma once
#include "value.h"
#include <vector>
#include "ValueType.h"
#include "ValueRegistration.h"
#include <type_traits>
#include "Parser.h"

namespace jbon {
	template <typename T>
	class Array :
		public TemplateValueTypeContract<Array<T>>
	{
	private:
	//implemented functions
		static Array<T> * create(std::string str)
		{
			return new Array<T>;
		}
		static bool isSameType(std::string str)
		{
		...
		}
		static std::pair<char, char> getSurroundingDelimeters()
		{
		...
		}

	public:
		Array() {}
		~Array() {}

		std::string serialize()
		{
			...
		}
	};
}

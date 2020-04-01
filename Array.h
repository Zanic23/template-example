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
			auto textValues = jbonSplit(str.substr(1, str.size() - 2), ',');

			for (const auto& funcPair : *Registrants::getRegistrations()) {
				if (funcPair.first(textValues[0])) {
					return new Array<T>;
				}
			}
		}
		static bool isSameType(std::string str)
		{
			return str.at(0) == '[' && str.at(str.size() - 1) == ']';
		}
		static std::pair<char, char> getSurroundingDelimeters()
		{
			return std::pair<char, char>('[', ']');
		}

	public:
		Array() {}
		~Array() {}

		std::string serialize()
		{
			std::string body = "";
			for (auto& value : values) {
				//body += value.serialize() + ", ";
			}
			return "[" + body + "]";
		}
	};
}

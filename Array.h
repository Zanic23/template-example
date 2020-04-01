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
		std::vector<T> values;
		friend class ValueTypeContract<Array<T>>;
		friend class ValueRegistration<Array<T>>;
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
		typedef typename std::vector<T>::iterator iterator;
		typedef typename std::vector<T>::const_iterator const_iterator;
		iterator begin() { return values.begin(); }
		iterator end() { return values.end(); }

		void erase(iterator it) { values.erase(it); }
		int size() { return values.size(); }
		bool empty() { values.empty(); }
		T& operator[](const int index) { return values.at[index]; }
		T& at(const int index) { return values.at(index); }

		using type = T;
		Array(std::string str)
		{
			auto textValues = jbonSplit(str.substr(1, str.size() - 2), ',');
			for (auto textValue : textValues) {
				values.push_back(Parser::parse<T>(textValue));
			}
		}
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

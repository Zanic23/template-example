//example
template <typename T>
class Array :
	public TemplateValueTypeContract<Array<T>>
{
private:
//dummy returns
	static Array<T> * create(std::string str) { return new Array<T>; }
	static bool isSameType(std::string str) { return true; }
	static std::pair<char, char> getSurroundingDelimeters() { return {',',','}; }
	std::string serialize() { return ""; }
};

//TEMPLATE
class ValueType {
private:
	virtual bool virtualIsSameType(std::string str) = 0;
	virtual ValueType * virtualCreate(std::string str) = 0;
	virtual std::pair<char,char> virtualGetSurroundingDelimeters() = 0;
	virtual std::string serialize() = 0;
public:
	virtual ~ValueType() {}
};

//specialized template contract
template <template<typename U> class T>
class TemplateValueTypeContract :
	public ValueType
{
private:
	using ClassSubType = U;
	//register the class
	static inline ValueRegistration<T<U>> registered;
	//these wont ever actually be used, but they require the child to implement the static methods
	bool virtualIsSameType(std::string str) {
		return T<ClassSubType>::isSameType(str);
	}
	//should return malloced pointer of child
	ValueType * virtualCreate(std::string str) {
		return T<ClassSubType>::create(str);
	}
	std::pair<char, char> virtualGetSurroundingDelimeters() {
		return T<ClassSubType>::getSurroundingDelimeters();
	}
public:
	virtual ~TemplateValueTypeContract() {}
};

//EXAMPLE
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

//USAGE

class ValueType;
//struct that contains all the information about a current registered classes
struct Registrants {
	typedef std::vector<std::pair<std::function<bool(std::string)>,
		std::function<ValueType*(std::string)>>> vec_t;
	typedef std::vector<std::pair<char, char>> delimeters_t;
private:
	//never deleted because itll get chopped randomly with smart ptrs
	static inline vec_t * registrations;
	static inline delimeters_t * delimeters;
};

template <template <typename U> class T>
class ValueRegistration :
	public Registrants
{
public:
	ValueRegistration() {

		auto pair = std::make_pair(&T<U>::isSameType, createFunction(T<U>::create));
		getRegistrations()->push_back(pair);
		getDelimeters()->push_back(T<U>::getSurroundingDelimeters());
	}
};

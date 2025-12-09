#include "Serialization.hpp"
#include "Data.hpp"

int main()
{
	Data smt;
	uintptr_t ptr;
	Data* smt2;

	ptr = Serialization::serialize(&smt);
	smt2 = Serialization::deserialize(ptr);

	std::cout << "Original address of Data object: " << &smt
			  << "\nSerialized value: " << ptr
			  << "\nDeserialized value: " << smt2
			  << "\nComparison of original address and deserialized value is: "
			  << (&smt == smt2 ? "values are equal!\n" : "values are DIFFERENT!\n");
	
	return (0);
}
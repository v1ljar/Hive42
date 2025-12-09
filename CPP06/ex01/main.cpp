// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/12/09 11:35:33 by vuljas            #+#    #+#             //
//   Updated: 2025/12/09 11:35:34 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Serializer.hpp"
#include "Data.hpp"

int main()
{
	Data smt;
	uintptr_t ptr;
	Data* smt2;

	ptr = Serializer::serialize(&smt);
	smt2 = Serializer::deserialize(ptr);

	std::cout << "\n\t\t[ First object tests ]\n"
			  << "Original address of Data object: " << &smt
			  << "\nSerialized value: " << ptr
			  << "\nDeserialized value: " << smt2
			  << "\nComparison of original address and deserialized value is: "
			  << (&smt == smt2 ? "values are equal!\n" : "values are DIFFERENT!\n");

	Data other = smt;
	uintptr_t other_ptr;
	Data* other2;

	other_ptr = Serializer::serialize(&other);
	other2 = Serializer::deserialize(other_ptr);
	std::cout << "\n\t\t[ Other object tests ]\n"
			  << "Original address of Data object: " << &other
			  << "\nSerialized value: " << other_ptr
			  << "\nDeserialized value: " << other2
			  << "\nComparison of original address and deserialized value is: "
			  << (&other == other2 ? "values are equal!\n" : "values are DIFFERENT!")
			  << "\nComparison of addresses of both structures is: "
			  << (smt2 == other2 ? "values are equal!\n" : "values are DIFFERENT!")
			  << std::endl;
	return (0);
}

#pragma once
#include <chrono>
#include <random>

//header only Random namespace implements a self seeding Mersenne Twister.
namespace Random
{
	//returns a seeded Mersenne Twister.
	//note: prefer to return a std::seed_seq(to initialize a std::mt19937),
	//but std::seed can't be coppied, therefore can't be returned by value.
	//instead we use std::mt19937, seed it and return the std::mt19937(whic can be copied)

	//inline keyword avoids ODR rule
	inline std::mt19937 generate()
	{
		std::random_device rd{};

		//create seed_seq with clock and 7 random numbers from std::random_device
		std::seed_seq ss{
			static_cast<std::seed_seq::result_type>
			(std::chrono::steady_clock::now().time_since_epoch().count()),
			rd(), rd(), rd(), rd(), rd(), rd(), rd() };

		return std::mt19937{ ss };
	}

	//global std::mt19937 object, inline means we only have one global instance for entire program
	inline std::mt19937 mt{ generate() }; // generates a seeded mt19937 and 
	//copies it into our global object

	//generate a random int between [min, max] (inclusive)
	//also handles cases where the two arguments have different types
	//but can be converted to int
	inline int get(int min, int max)
	{
		return std::uniform_int_distribution{ min, max }(mt);
	}

	//the following function templates can be used to generate random numbers in other cases
	//See https://www.learncpp.com/cpp-tutorial/function-template-instantiation/
	// You can ignore these if you don't understand them

	//generate a random value beteween [min, max] (inclusive)
	/* min and max must have the same type
	return value has same type as min and max
	supported types: short, int long, long long,
	insigned short, unsigned int, unsigned long, or unsigned long long */
	//sample call: Random::get(1L, 6L);       returns long
	//sample call: Random::get(1u, 6u);		  returns unsigned int
	template <typename T>
	T get(T min, T max)
	{
		return std::uniform_int_distribution<T>{min, max}(mt);
	}


	// Generate a random value between [min, max] (inclusive)
	// * min and max can have different types
		// * return type must be explicitly specified as a template argument
	// * min and max will be converted to the return type
	// Sample call: Random::get<std::size_t>(0, 6);  // returns std::size_t
	// Sample call: Random::get<std::size_t>(0, 6u); // returns std::size_t
	// Sample call: Random::get<std::int>(0, 6u);    // returns int
	template <typename R, typename S, typename T>
	R get(S min, T max)
	{
		return get<R>(static_cast<R>(min), static_cast<R>(max));
	}
}
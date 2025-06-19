#pragma once

#include "MonoidV2.hpp"

#include <cassert>
#include <string>

void monoid_empty()
{
	Monoid<int, int> a;

	int actual = a.evaluate(1);

	assert(1 == actual);
}

constexpr int plusOne(int a)
{
	return a + 1;
}

void monoid_composed()
{
	auto addOne = [](int a) {return a + 1;};
	Monoid<int, int> a(addOne);

	int actual = a.evaluate(1);

	assert(plusOne(1) == actual);
}

void monoid_compose_single()
{
	auto addOne = [](int a) {return a + 1; };
	Monoid<int, int> a = 
		Monoid<int, int>()
		.compose(Monoid<int, int>(addOne));

	int actual = a.evaluate(1);

	assert(plusOne(1) == actual);
}

constexpr int addOneMulTwoMinTwo(int a)
{
	return (a + 1) * 2 - 2;
}

void monoid_compose_multiple()
{
	auto addOne = [](int a) {return a + 1; };
	auto mulTwo = [](int a) {return a * 2; };
	auto minTwo = [](int a) {return a - 2; };
	Monoid<int, int> a =
		Monoid<int, int>()
		.compose(Monoid<int, int>(addOne))
		.compose(Monoid<int, int>(mulTwo))
		.compose(Monoid<int, int>(minTwo));

	int actual = a.evaluate(1);

	assert(addOneMulTwoMinTwo(1) == actual);
}

void monoid_compose_multiple_types()
{
	auto addOne = [](int a) {return static_cast<float>(a + 1); };
	auto mulTwo = [](float a) {return static_cast<char>(a * 2); };
	auto minTwo = [](char a) {return static_cast<double>(a - 2); };
	Monoid<int, double> a =
		Monoid<int, int>()
		.compose(Monoid<int, float>(addOne))
		.compose(Monoid<float, char>(mulTwo))
		.compose(Monoid<char, double>(minTwo));

	double actual = a.evaluate(1);

	assert(addOneMulTwoMinTwo(1) == actual);
}

void monoid_compose_multiple_types_with_object()
{
	auto addOne = [](int a) {return static_cast<float>(a + 1); };
	auto mulTwo = [](float a) {return std::to_string(a * 2); };
	auto minTwo = [](const std::string& a) {return atof(a.c_str()) - 2; };
	Monoid<int, double> a =
		Monoid<int, int>()
		.compose(Monoid<int, float>(addOne))
		.compose(Monoid<float, std::string>(mulTwo))
		.compose(Monoid<std::string, double>(minTwo));

	double actual = a.evaluate(1);

	assert(addOneMulTwoMinTwo(1) == actual);
}

void monoid_test()
{
	monoid_empty();
	monoid_composed();
	monoid_compose_single();
	monoid_compose_multiple();
	monoid_compose_multiple_types();
	monoid_compose_multiple_types_with_object();
}

template<class T>
bool comp_vectors(const std::vector<T>& v1, const std::vector<T>& v2)
{
	return std::equal(v1.begin(), v1.end(), v2.begin());
}

void multioid_empty()
{
	MonoidComposite<int, int> a;

	auto actual = a.evaluateWhole({ 1, 2, 3, 4, 5 });

	assert(comp_vectors({ 1, 2, 3, 4, 5 }, actual));
}

void multioid_from_monoid()
{
	auto addOne = [](int a) {return a + 1; };
	Monoid<int, int> monoid(addOne);
	MonoidComposite<int, int> a(monoid);

	auto actual = a.evaluateWhole({ 1, 2, 3, 4, 5 });

	assert(comp_vectors({ 2, 3, 4, 5, 6 }, actual));
}

void multioid_from_composed_monoid()
{
	auto addOne = [](int a) {return static_cast<float>(a + 1); };
	auto mulTwo = [](float a) {return static_cast<char>(a * 2); };
	auto minTwo = [](char a) {return static_cast<double>(a - 2); };
	Monoid<int, double> monoid =
		Monoid<int, int>()
		.compose(Monoid<int, float>(addOne))
		.compose(Monoid<float, char>(mulTwo))
		.compose(Monoid<char, double>(minTwo));
	MonoidComposite<int, double> a(monoid);

	auto actual = a.evaluateWhole({ 1, 2, 3, 4, 5 });

	assert(comp_vectors({ addOneMulTwoMinTwo(1), addOneMulTwoMinTwo(2), addOneMulTwoMinTwo(3), addOneMulTwoMinTwo(4),addOneMulTwoMinTwo(5) }, actual));
}

void multioid_from_func()
{
	VectorUnaryOp<int, int> reverse = [](const std::vector<int>& x)
	{
		std::vector<int> res(x);
		std::reverse(res.begin(), res.end());

		return res;
	};

	MonoidComposite<int, int> a(reverse);

	auto actual = a.evaluateWhole({ 1, 2, 3, 4, 5 });

	assert(comp_vectors({5, 4, 3, 2, 1 }, actual));
}

void multioid_from_monoid_and_func()
{
	auto addOne = [](int a) {return a + 1; };
	VectorUnaryOp<int, int> reverse = [addOne](const std::vector<int>& x)
	{
		std::vector<int> res(x);
		std::transform(res.begin(), res.end(), res.begin(), addOne);
		std::reverse(res.begin(), res.end());

		return res;
	};
	Monoid<int, int> monoid(addOne);
	MonoidComposite<int, int> a(reverse, monoid);

	auto actual = a.evaluateWhole({ 1, 2, 3, 4, 5 });

	assert(comp_vectors({ plusOne(5), plusOne(4), plusOne(3), plusOne(2), plusOne(1)}, actual));
}

void monoid_compose_single_monoid();
void monoid_compose_single_multioid();
void monoid_compose_multiple_monoids();
void monoid_compose_multiple_multioids();
void monoid_compose_multiple_monoids_and_multioids();

void multioid_test()
{
	multioid_empty();
	multioid_from_monoid();
	multioid_from_composed_monoid();
	multioid_from_func();
	multioid_from_monoid_and_func();

}

void test()
{
	monoid_test();
	multioid_test();
}
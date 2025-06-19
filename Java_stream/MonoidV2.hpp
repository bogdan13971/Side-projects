#pragma once

#include "FunctionTypes.hpp"

template<class T>
const UnaryOperation<T, T> identity = [](const T& x) -> T {return x; };

template<class T, class R>
class Monoid;

template<class InitVal, class CurVal>
class Monoid
{
public:
	UnaryOperation<InitVal, CurVal> func;

public:
	Monoid()
		:func{ identity<InitVal> }
	{}

	Monoid(const Monoid& other)
		:func{ other.func }
	{}

	Monoid(UnaryOperation<InitVal, CurVal> func)
		:func{ func }
	{}

	Monoid(Monoid&& other) noexcept
		:func{ std::move(other.func)}
	{}

	CurVal evaluate(const InitVal& val)
	{
		return func(val);
	}

	template<class NewVal>
	Monoid<InitVal, NewVal> compose(const Monoid<CurVal, NewVal>& other)
	{
		auto newFun = [prevFun = this->func, nextFun = other.func](const InitVal& initVal) -> NewVal
		{
			return nextFun(prevFun(initVal));
		};

		return Monoid<InitVal, NewVal>(newFun);
	}
};

template<class T, class R>
using VectorUnaryOp = UnaryOperation<std::vector<T>, std::vector<R>>;

template<class T>
const static VectorUnaryOp<T, T> identityOther = [](const std::vector<T>& x) -> std::vector<T> {return x; };

template<class T, class R>
const static VectorUnaryOp<T, T> evaluateOther = 
[](const std::vector<T>& values, Monoid<T, R> monoid) -> std::vector<R> 
{
	std::vector<R> res;
	for (const T& val : values)
	{
		R r = monoid.evaluate(val);
		res.push_back(std::move(r));
	}

	return res;
};


template<class InitVal, class CurVal>
class MonoidComposite
{
public:
	UnaryOperation<InitVal, CurVal> monoidFunc;
	VectorUnaryOp<InitVal, CurVal> multioidFunc;
	VectorUnaryOp<InitVal, CurVal> evalFunc;

	MonoidComposite()
		:monoidFunc{identity<InitVal>},
		multioidFunc{identityOther<InitVal>},
		evalFunc{evaluateOther<InitVal, CurVal>}
	{}

	MonoidComposite(UnaryOperation<InitVal, CurVal> monoidFunc, VectorUnaryOp<InitVal, CurVal> multioidFunc, VectorUnaryOp<InitVal, CurVal> evalFunc)
		:monoidFunc{ monoidFunc },
		multioidFunc{ multioidFunc },
		evalFunc{ evalFunc }
	{}

	template<class NewVal>
	MonoidComposite<InitVal, NewVal> compose(UnaryOperation<CurVal, NewVal> monoidFunc)
	{
		UnaryOperation<InitVal, NewVal> newMonoidFunc = 
			[curMonoidFunc = this->monoidFunc, monoidFunc](const InitVal& val) 
		{
			CurVal res1 = curMonoidFunc(val);
			NewVal res2 = monoidFunc(res1);
			return res2;
		};

		VectorUnaryOp<InitVal, NewVal> newMultioidFunc = identity<NewVal>;
		VectorUnaryOp<InitVal, NewVal> evalFunc;
	}

	template<class NewVal>
	MonoidComposite<InitVal, NewVal> compose(const MonoidComposite<CurVal, NewVal>& other)
	{
		Monoid<InitVal, NewVal> newMonoid = monoid.compose(other.monoid);

		auto newFun = [prevFun = this->func, otherFun = other.func](const std::vector<InitVal>& initVals)->std::vector<NewVal>
		{
			std::cout << "Evaluating when composed with composite ...\n";
			return otherFun(prevFun(initVals));
		};

		return MonoidComposite<InitVal, NewVal>(newFun, newMonoid);
	}

	std::vector<CurVal> evaluate(const std::vector<InitVal>& vals)
	{
		std::vector<CurVal> res;
		res.reserve(vals.size());
		for (size_t i = 0; i < vals.size(); ++i)
		{
			CurVal opt = monoid.evaluate(vals[i]);
			res.push_back(std::move(opt));
		}

		return res;
	}

	std::vector<CurVal> evaluateWhole(const std::vector<InitVal>& vals)
	{
		return func(vals);
	}
};
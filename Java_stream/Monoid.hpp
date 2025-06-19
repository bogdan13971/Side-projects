//#pragma once
//
//#include <optional>
//
//#include "FunctionTypes.hpp"
//#include "Meta.h"
//
//template<class T, class R>
//const static UnaryOperation<T, R> identity = [](const T& x) -> R {return x; };
//
//template<class T, class R>
//class Monoid;
//
//template<class InitVal, class CurVal>
//class Monoid
//{
//public:
//	OptFunc<InitVal, CurVal> func;
//
//public:
//	Monoid()
//		:func{ create(identity<InitVal, CurVal>) }
//	{}
//
//	Monoid(OptFunc<InitVal, CurVal> func)
//		:func{ func }
//	{}
//
//	std::optional<CurVal> evaluate(const InitVal& val)
//	{
//		return func(val);
//	}
//
//	template<class NewVal>
//	Monoid<InitVal, NewVal> compose(UnaryOperation<CurVal, NewVal> f)
//	{
//		auto optFun = create(f);
//		auto newFun = composeIn(func, optFun);
//
//		return Monoid<InitVal, NewVal>(newFun);
//	}
//
//	Monoid<InitVal, CurVal> compose(UnaryOperation<CurVal, bool> f)
//	{
//		auto optFun = create(f);
//		auto newFun = composeIn(func, optFun);
//
//		return Monoid<InitVal, CurVal>(newFun);
//	}
//};
//
//template<class InitVal>
//class Monoid<InitVal, void>
//{
//public:
//	VoidOptFunc<InitVal> func;
//
//public:
//	Monoid(VoidOptFunc<InitVal> func)
//		:func{ func }
//	{}
//
//	void evaluate(const InitVal& val)
//	{
//		func(val);
//	}
//};
//
//template<class T, class R>
//using VectorUnaryOp = UnaryOperation<std::vector<T>, std::vector<R>>;
//
//template<class T, class R>
//const static VectorUnaryOp<T, R> identityOther = [](const std::vector<T>& x) -> std::vector<R> {return x; };
//
//template<class InitVal, class CurVal>
//class MonoidComposite
//{
//public:
//	Monoid<InitVal, CurVal> monoid;
//	VectorUnaryOp<InitVal, CurVal> func;
//
//	MonoidComposite()
//		:func{ identityOther<InitVal, CurVal> }
//		//,monoid{ identity<InitVal> }
//	{}
//
//	MonoidComposite(VectorUnaryOp<InitVal, CurVal> func, Monoid<InitVal, CurVal> monoid)
//		:func{ func },
//		monoid{monoid}
//	{}
//
//	template<class NewVal>
//	MonoidComposite<InitVal, NewVal> compose(const MonoidComposite<CurVal, NewVal>& other)
//	{
//		auto tempfunc = [this, &other](const std::vector<InitVal>& x) -> std::vector<NewVal>
//		{
//			auto res = this->func(x);
//			return other.func(res);
//		};
//
//		MonoidComposite<InitVal, NewVal> mon(tempfunc);
//
//		return mon;
//	}
//
//	template<class NewVal>
//	MonoidComposite<InitVal, NewVal> compose(const Monoid<CurVal, NewVal>& other)
//	{
//		//auto tempfunc = [this, other](const std::optional<InitVal>& x) -> std::optional<NewVal>
//		//{
//		//	std::optional<CurVal> res = this->monoid.func(x);
//		//	std::optional<NewVal> res2 = other.func(res);
//
//		//	return res2;
//		//};
//
//		auto tempfunc2 = [this, other, tempfunc](const std::vector<InitVal>& x) -> std::vector<NewVal>
//		{
//			std::vector<NewVal> res;
//			res.reserve(x.size());
//			for (size_t i = 0; i < x.size(); ++i)
//			{
//				auto opt = tempfunc(x[i]);
//				if (opt.has_value())
//				{
//					res.push_back(std::move(opt.value()));
//				}
//			}
//
//			return res;
//		};
//
//		//Monoid<InitVal, NewVal> monoid{tempfunc};
//		Monoid<InitVal, NewVal> monoid2 = (this->monoid).compose<NewVal>(other);
//		MonoidComposite<InitVal, NewVal> mon(tempfunc2, monoid2);
//
//		return mon;
//	}
//
//	std::vector<CurVal> evaluate(const std::vector<InitVal>& vals) const
//	{
//		std::vector<CurVal> res;
//		res.reserve(vals.size());
//		for (size_t i = 0;i<vals.size();++i)
//		{
//			std::optional<CurVal> opt = monoid.evaluate(vals[i]);
//			if (opt.has_value())
//			{
//				res.push_back(std::move(opt));
//			}
//		}
//
//		return res;
//	}
//};
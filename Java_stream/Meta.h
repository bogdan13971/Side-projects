#pragma once

#include <optional>

#include "FunctionTypes.hpp"
#include <iostream>

//#define DEBUG

template<class T, class R>
using OptFunc = std::function<std::optional<R>(const std::optional<T>&)>;

template<class T>
using VoidOptFunc = std::function<void(const std::optional<T>&)>;

template<class T, class R>
struct OptFunCreator;

template<class T>
struct VoidOptFunCreator;

template<class T, class R>
struct Dispatcher;

template<class T, class R>
struct Dispatcher
{
	using value_type = OptFunCreator<T, R>;
	using return_type = OptFunc<T, R>;
};

template<class T>
struct Dispatcher<T, void>
{
	using value_type = VoidOptFunCreator<T>;
	using return_type = VoidOptFunc<T>;
};

template<class T>
struct Dispatcher<T, bool>
{
	using value_type = OptFunCreator<T, bool>;
	using return_type = OptFunc<T, T>;
};

template<class OldT, class T, class R>
static OptFunc<OldT, R> composeIn(OptFunc<OldT, T> prev, OptFunc<T, R> op)
{
	return [prev, op](const std::optional<OldT>& x) -> std::optional<R>
	{
		return op(prev(x));
	};
}

template<class OldT, class T>
static VoidOptFunc<OldT> composeIn(OptFunc<OldT, T> prev, VoidOptFunc<T> op)
{
	return [prev, op](std::optional<OldT> x) -> void
	{
		op(prev(x));
	};
}

template<class T, class R>
struct OptFunCreator
{
	static OptFunc<T, R> create(std::function<R(const T&)> fun)
	{
		auto a = 
		[fun](const std::optional<T>& x) -> std::optional<R>
		{
#ifdef DEBUG
			std::cout << typeid(T).name() << " -> " << typeid(R).name() << ": ";
#endif // DEBUG

			if (!x.has_value())
			{
#ifdef DEBUG
				std::cout << "None\n";
#endif // DEBUG

				return std::nullopt;
			}

			const T& val = x.value();
			//std::cout << "Here\n";
			R res = fun(val);

#ifdef DEBUG
			std::cout << val << " -> " << res << "\n";
#endif // DEBUG

			return std::optional<R>(res);
				//(fun(val));
		};

		//std::cout << "type of a is : " << typeid(a).name() << "\n";

		return a;
	}
};

template<class T>
struct OptFunCreator<T, bool>
{
	static OptFunc<T, T> create(std::function<bool(const T&)> fun)
	{
		return [fun](const std::optional<T>& x) -> std::optional<T>
		{
#ifdef DEBUG
			std::cout << typeid(T).name() << " -> " << typeid(bool).name() << ": ";
#endif // DEBUG

			if (!x.has_value())
			{
#ifdef DEBUG
				std::cout << "None\n";
#endif // DEBUG
				return std::nullopt;
			}

			T val = x.value();
			bool res = fun(val);

#ifdef DEBUG
			std::cout << std::boolalpha;
			std::cout << val << " -> " << res << "\n";
#endif // DEBUG

			if (!res)
			{
				return std::nullopt;
			}

			return val;
		};
	}
};

template<class T>
struct VoidOptFunCreator
{
	static VoidOptFunc<T> create(std::function<void(T)> fun)
	{
		return [fun](std::optional<T> x) -> void
		{
#ifdef DEBUG
			std::cout << typeid(T).name() << " -> " << typeid(void).name() << ": ";
#endif // DEBUG

			if (!x.has_value())
			{
#ifdef DEBUG
				std::cout << "None\n";
#endif // DEBUG
				return;
			}

			T val = x.value();

			fun(val);

#ifdef DEBUG
			std::cout << val << "\n";
#endif // DEBUG
		};
	}
};

template<class T, class R>
auto create(UnaryOperation<T, R> func) -> typename Dispatcher<T, R>::return_type
{
	using CreatorType = typename Dispatcher<T, R>::value_type;
	return CreatorType::create(func);
}


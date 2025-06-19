#pragma once
#include <functional>
#include <vector>

template<class R>
using NoOperation = std::function<R()>;

template<class T, class R>
using UnaryOperation = std::function<R(const T&)>;

template<class T, class R>
using BinaryOperator = std::function<R(const T&, const T&)>;

template<class T, class R>
using CollectorValue = std::function<R(typename std::vector<T>::iterator, typename std::vector<T>::iterator)>;

template<class T, class A, template <typename T, typename A> class C>
using CollectorContainer = std::function<C<T, A>(typename std::vector<T>::iterator, typename std::vector<T>::iterator)>;

template<class T>
using Supplier = NoOperation<T>;

template<class T>
using Consumer = UnaryOperation<T, void>;

template<class T>
using Predicate = UnaryOperation<T, bool>;

template<class T, class U>
using Mapper = UnaryOperation<T, U>;

template<class T>
using Comparator = BinaryOperator<T, bool>;

template<class T>
using Reducer = BinaryOperator<T, T>;

template<class T>
struct inner_type
{
	using value_type = typename T::value_type;
};
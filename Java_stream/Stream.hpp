//#pragma once 
//
//#include "Monoid.hpp"
//#include <vector>
//#include <set>
//
//template<class InitVal, class CurVal = InitVal>
//class Stream
//{
//public:
//	Monoid<InitVal, CurVal> monoid;
//	std::vector<InitVal> values;
//	
//	Stream(const std::vector<InitVal>& values)
//		:values{values}
//	{}
//
//	Stream(Monoid<InitVal, CurVal>&& monoid, std::vector<InitVal>&& values)
//		:monoid{ std::move(monoid) },
//		values{std::move(values)}
//	{}
//
//public:
//	template<class NewVal>
//	Stream<InitVal, NewVal> map(Mapper<CurVal, NewVal> mapper)
//	{
//		auto newMonoid = monoid.compose(mapper);
//		return Stream<InitVal, NewVal>(std::move(newMonoid), std::move(values));
//	}
//
//	void for_each(Consumer<CurVal> consumer)
//	{
//		auto newMonoid = monoid.compose(consumer);
//		for (const InitVal& val : values)
//		{
//			newMonoid.evaluate(val);
//		}
//	}
//
//	Stream<InitVal, CurVal> filter(Predicate<CurVal> predicate)
//	{
//		auto newMonoid = monoid.compose(predicate);
//		return Stream<InitVal, CurVal>(std::move(newMonoid), std::move(values));
//	}
//
//	//not final, should be lazy
//	size_t count()
//	{
//		size_t count = 0;
//		for (const InitVal& val : values)
//		{
//			auto res = monoid.evaluate(val);
//			if (res.has_value())
//			{
//				count++;
//			}
//		}
//		
//		return count;
//	}
//
//	CurVal reduce(CurVal identity, Reducer<CurVal> reducer)
//	{
//		CurVal result = identity;
//		for (const InitVal& val : values)
//		{
//			auto res = monoid.evaluate(val);
//			if (res.has_value())
//			{
//				result = reducer(result, res.value());
//			}
//		}
//
//		return result;
//	}
//
//	template<class T>
//	T collect()
//	{
//		T collector;
//		for (const InitVal& val : values)
//		{
//			auto res = monoid.evaluate(val);
//			if (res.has_value())
//			{
//				collector.push_back(res.value());
//			}
//		}
//
//		return collector;
//	}
//
//	Stream<CurVal, CurVal> sort(Comparator<CurVal> comparator)
//	{
//		std::set<CurVal> sorted;
//
//		for (const InitVal& val : values)
//		{
//			auto res = monoid.evaluate(val);
//			if (res.has_value())
//			{
//				sorted.insert(res.value());
//			}
//		}
//
//		auto move_begin = std::make_move_iterator(sorted.begin());
//		auto move_end = std::make_move_iterator(sorted.end());
//		std::vector<CurVal> newValues(move_begin, move_end);
//
//		return Stream<CurVal, CurVal>(Monoid<CurVal>(), std::move(newValues));
//	}
//
//	Stream<CurVal, CurVal> limit(size_t size)
//	{
//		std::vector<CurVal> newValues;
//		newValues.reserve(size);
//		size_t currentSize = 0;
//		for (const InitVal& val : values)
//		{
//			auto res = monoid.evaluate(val);
//			if (res.has_value())
//			{
//				currentSize++;
//				if (currentSize == size + 1)
//				{
//					break;
//				}
//				newValues.push_back(res.value());
//			}
//		}
//
//		return Stream<CurVal, CurVal>(Monoid<CurVal>(), std::move(newValues));
//	}
//
//	Stream<CurVal, CurVal> skip(size_t size)
//	{
//		std::vector<CurVal> newValues;
//		newValues.reserve(size);
//		size_t currentSize = 0;
//		for (const InitVal& val : values)
//		{
//			auto res = monoid.evaluate(val);
//			if (res.has_value())
//			{
//				currentSize++;
//				if (currentSize >= size)
//				{
//					newValues.push_back(res.value());
//				}
//			}
//		}
//
//		return Stream<CurVal, CurVal>(Monoid<CurVal>(), std::move(newValues));
//	}
//
//	Stream<CurVal, CurVal> distinct()
//	{
//		std::vector<CurVal> newValues;
//		std::set<CurVal> unique;
//		for (const InitVal& val : values)
//		{
//			auto res = monoid.evaluate(val);
//			if (res.has_value())
//			{
//				const auto it = unique.find(res.value());
//				if (it == unique.end())
//				{
//					newValues.push_back(res.value());
//					unique.insert(it, res.value());
//				}
//			}
//		}
//
//		return Stream<CurVal, CurVal>(Monoid<CurVal>(), std::move(newValues));
//	}
//
//	CurVal findFirst()
//	{
//		for (const InitVal& val : values)
//		{
//			auto res = monoid.evaluate(val);
//			if (res.has_value())
//			{
//				return res.value();
//			}
//		}
//	}
//
//	CurVal findLast()
//	{
//		for (auto it = values.rbegin(); it != values.rend(); ++it)
//		{
//			auto res = monoid.evaluate(*it);
//			if (res.has_value())
//			{
//				return res.value();
//			}
//		}
//	}
//
//	//auto flatMap() -> Stream<typename inner_type<T>::value_type>
//	//{
//	//	using R = typename inner_type<T>::value_type;
//
//	//	R new_container;
//
//	//	for (auto& line : container)
//	//	{
//	//		auto move_begin_it = std::make_move_iterator(std::begin(line));
//	//		auto move_end_it = std::make_move_iterator(std::end(line));
//
//	//		new_container.insert(std::end(new_container), move_begin_it, move_end_it);
//	//	}
//
//	//	return Stream<R>(std::move(new_container));
//	//}
//
//	//Stream<T>& concat(const Stream<T>& other)
//	//{
//	//	auto begin_it = std::begin(other.container);
//	//	auto end_it = std::end(other.container);
//
//	//	std::copy(begin_it, end_it, std::back_inserter(container));
//
//	//	return *this;
//	//}
//
//	//Stream<T>& concat_move(Stream<T>&& other)
//	//{
//	//	auto move_begin_it = std::make_move_iterator(std::begin(other.container));
//	//	auto move_end_it = std::make_move_iterator(std::end(other.container));
//
//	//	std::copy(move_begin_it, move_end_it, std::back_inserter(container));
//	//	
//	//	return *this;
//	//}
//
//	//template<class U>
//	//U collect()
//	//{
//	//	auto move_begin_it = std::make_move_iterator(std::begin(container));
//	//	auto move_end_it = std::make_move_iterator(std::end(container));
//
//	//	return U(move_begin_it, move_end_it);
//	//}
//
//	//template<size_t N>
//	//Stream<T>& generate(Supplier<ValType> supplier)
//	//{
//	//	for (size_t i = 0; i < N; i++)
//	//	{
//	//		container.push_back(supplier());
//	//	}
//
//	//	return *this;
//	//}
//};
//
////template<class ValType, class AllocType, template <typename, typename> class ContType>
////Stream<ValType, AllocType> make_stream(const ContType<ValType, AllocType>& cont)
////{
////	std::vector<ValType> temp_container(std::begin(cont), std::end(cont));
////
////	return Stream<ValType>(std::move(temp_container));
////}
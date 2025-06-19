#pragma once

#include "FunctionTypes.hpp"

Compose<Mapper, Filter, All, Terminal>
Compose<Mapper<int, void>, Predicate<double>

template<class Val, class Map = Val, class Filter = Val, class Terminal = Val>
struct Composer
{
	Map mapper;

	Composer(Map mapper)
		: mapper{ mapper }
	{}

	template<class R>
	Composer<R, Mapper<Val, R>> map(Mapper<Val, R> map)
	{
		auto new_map = [&, map](const Val& val)
		{
			return 
		};
	}
};


Composer<int> a;
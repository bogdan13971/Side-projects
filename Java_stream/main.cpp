#include "Stream.hpp"
#include <vector>
#include <iostream>
#include <list>
#include <functional>
#include <algorithm>

#include "FunctionTypes.hpp"
//#include "Monoid.hpp"
#include "MonoidV2.hpp"
#include <cassert>

#include <optional>
#include "Obj.h"
#include "Monoid.hpp"

#include "Test.h"

int main()
{
	//test();

	//return 0;
	/*UnaryOperation<int, int> unar = [](int a)->int {std::cout << "Adding one\n";  return a + 1; };
	UnaryOperation<float, float> unar1 = [](float a)->float {std::cout << "Adding one\n"; return a + 1; };
	UnaryOperation<int, double> unar2 = [](const int& a)->double {return a * 1; };
	UnaryOperation<double, float> unar3 = [](double a)->float {return static_cast<float>(a - 0); };
	UnaryOperation<float, int> unar4 = [](float a)->int { return static_cast<int>(a + 10); };
	UnaryOperation<float, bool> pref1 = [](float f)->bool {return f > 5; };
	UnaryOperation<int, void> cons = [](int i)->void {std::cout << i << "\n\n"; };
	UnaryOperation<int, Obj> toObj = [](int i)->Obj {return Obj{ i }; };
	UnaryOperation<Obj, int> fromObj = [](const Obj& o)->int {return o.a; };
	UnaryOperation<Obj, Obj> fromObjtoObj = [](const Obj& o)->Obj {return Obj{ o.a + 6 }; };
	Reducer<int> reducer = [](int a, int b)->int {return a + b; };
	Comparator<int> comparator = [](int a, int b)->bool {return a < b; };*/

	VectorUnaryOp<int, int> reverse = [](const std::vector<int>& x)
	{
		std::cout << "Reversing...\n";
		std::vector<int> res(x);
		std::reverse(res.begin(), res.end());

		return res;
	};

	/*VectorUnaryOp<float, float> sort = [](const std::vector<float>& x)
	{
		std::cout << "Sorting...\n";
		std::vector<float> res(x);
		std::sort(res.begin() + 1, std::next(res.begin(), res.size() - 1));

		return res;
	};

	auto addOne = Monoid(unar);
	auto mulTwo = Monoid(unar2);
	auto minOne = Monoid(unar3);*/
	//auto addOneMulTwoMinOne = addOne.compose(mulTwo).compose(minOne);

	//auto addOneMulTwoCompMinOne = MonoidComposite(std::move(addOne)).compose(mulTwo).compose(minOne);
	auto revComp = MonoidComposite(reverse);
	//auto sortComp = MonoidComposite(sort);

	//auto reallyAddOne = Monoid(unar1);

	auto newComp =
		MonoidComposite<int, int>()
		.compose(Monoid<int, int>([](int a)->int {
				std::cout << "f1 on " << a << " \n";  return a + 0; }))
		.compose(revComp)
		.compose(Monoid<int, int>([](int a)->int {
				std::cout << "f2 on " << a << " \n";  return a + 0; }))
		.compose(Monoid<int, int>([](int a)->int {
				std::cout << "f3 on " << a << " \n\n";  return a + 0; }));

	//std::cout << addOneMulTwoMinOne.evaluate(10)<<"\n";

	auto res = newComp.evaluateWhole({ 1, 2, 3});
	std::for_each(res.begin(), res.end(), [](const auto& e) {std::cout << e << ", "; }); std::cout << "\n";

	//auto b = a.compose(unar)
	//	.compose(unar2)
	//	.compose(unar3);
	//	//.compose(pref1)
	//	//.compose(unar4)
	//	//.compose(cons);

	//auto d = aother.compose(unar4).compose(unar2);

	//auto c = acos.compose(b).compose(d);

	//std::cout<< c.monoid.evaluate(10).value();
	//std::cout << c.monoid.evaluate(10).value();
	
	//Stream<int> stream({5, 4, 3, 1, 2, 6, 3, 4, 3});
	//auto stream2 = stream;
		//.map(unar)
		//.map(unar2)
		//.map(unar3)
		//.filter(pref1)
		//.map(unar4)
		//.distinct();
		//.sort(comparator)
		//.skip(2);
		//.limit(3);
		//.map(cons);

	//stream2.for_each(cons);
	//std::cout << stream2.findFirst();
	//stream.collect<std::vector<int>>();

	//std::cout << stream2.reduce(0, reducer);

	return 0;

	//using FunctorType = typename Functor<int, double, char>::value;
	//std::vector<int> vec = { 4, 5, 3, 7 , 6, 1, 2 };
	//Rec<int> rec{vec};
	//auto a = rec.map(unar2).map(unar3).filter(pref1).map(unar4).collect();
	//for (int as : a)
	//{
	//	std::cout << as << " ";
	//}
	//a.functors;

	//std::cout << a.evaluate();

	//auto op = a.getOp<1>();

	//std::cout << op(1.42);

	//auto res = ;
	//consume<decltype(a)::LastVal, int, decltype(a)::FuncType, 0, 4>(12, a.functors);
	//std::cout << res;
	//assert(res == 26);
	//auto alt = rec.add(unar3).add(unar4).add(unar2);

	//decltype(rec)::FUn

	//auto aha = alt.subtract().subtract().subtract();

	//print(a);
	//printAll(alt);

	//Monoid<int> a = create(100);
	
	//a = map(a, unar);
	//auto doble = map(a, unar2);

	//std::cout << doble.get();

	//ComparatorFunctor<int> comp([](int a, int b) {return a < b; });
	//std::set<int, decltype(comp.func)> sortSet(comp.func);
	//auto a =
		//make_stream(vec).map(unar).mapTo(unar2).mapTo(unar3);
	//	//.map([](int a) {return a + 0; })
	//	//.map([](int a) {return a * 1; })
	//	//.mapTo<double>([](int a)->double {return a + 0.01; })
	//	//.map([](double a) {return a + 0.1; })
	//	.filter([](int a) {return a > 3; })
	//	//.map([](int a) {return a + 0; })
	//	//.map([](int a) {return a * 1; })
	//	//.filter([](int a) {return a >= 6; })
	//	//.count();
	//	.sort([](int a, int b) {return a < b;})
	//	.for_each([](double a) {std::cout << a << "\n"; });
	//std::cout << a << "\n";
	//BaseFunctor<int>* b;
	//b = new SupplierFunctor<int>([]() {return 13; });
	//b = new ConsumerFunctor<int>([](int a)->void{std::cout << a << "\n"; });
	//b = new PredicateFunctor<int>([](int a)->bool {return a % 2 == 0; });
	//b = new MapperFunctor<int, double>([](int a)->double {return a / 2.0; });
	//b = new ComparatorFunctor<int>([](int a, int b)->bool {return a > b; });
	//static_cast<ComparatorFunctor<int>*>(b)->other_param = 12;
	//b = new ReducerFunctor<int>([](int a, int b)->int {return a + b; });
	//static_cast<ReducerFunctor<int>*>(b)->other_param = 12;
	//b = new CollectorValueFunctor<int, int>([](std::vector<int>::iterator begin, std::vector<int>::iterator end)->int {return std::distance(begin, end);});
	//static_cast<CollectorValueFunctor<int, int>*>(b)->begin = vec.begin();
	//static_cast<CollectorValueFunctor<int, int>*>(b)->end = vec.end();
	/*b = new CollectorContainerFunctor<int, std::allocator<int>, std::list>([](std::vector<int>::iterator begin, std::vector<int>::iterator end) ->std::list<int> {return std::list<int>(begin, end); });
	static_cast<CollectorContainerFunctor<int, std::allocator<int>, std::list>*>(b)->begin = vec.begin();
	static_cast<CollectorContainerFunctor<int, std::allocator<int>, std::list>*>(b)->end = vec.end();
	b->apply(23);

	switch (b->type)
	{
	case FunctionType::SUPPLIER: std::cout << "supplied: " << static_cast<SupplierFunctor<int>*>(b)->ret << "\n"; break;
	case FunctionType::CONSUMER: std::cout << "consumed \n"; break;
	case FunctionType::PREDICATE: std::cout << "predicate: " << static_cast<PredicateFunctor<int>*>(b)->ret << "\n"; break;
	case FunctionType::MAPPER: std::cout << "mapped to: " << static_cast<MapperFunctor<int, double>*>(b)->ret << "\n"; break;
	case FunctionType::COMPARATOR: std::cout << "compared: " << static_cast<ComparatorFunctor<int>*>(b)->ret << "\n"; break;
	case FunctionType::REDUCER: std::cout << "reduced " << static_cast<ReducerFunctor<int>*>(b)->ret << "\n"; break;
	case FunctionType::COLLECTOR_VALUE: std::cout << "collected value " << static_cast<CollectorValueFunctor<int, int>*>(b)->ret << "\n"; break;
	case FunctionType::COLLECTOR_CONTAINER: std::cout<<typeid(static_cast<CollectorContainerFunctor<int, std::allocator<int>, std::list>*>(b)->ret).name() << "\n";
		for (int i : static_cast<CollectorContainerFunctor<int, std::allocator<int>, std::list>*>(b)->ret) std::cout << i << ", ";
		break;
	}*/

}


//
//template<class T>
//struct A {};
//
//int main()
//{
//	std::vector<int> vec{5, 6, 7, 2, 3, 5, 1};
//
//	Mapper<int, double> mapper = [](int e)->double {return e + 1.0; };
//	Consumer<double> consumer = [](double e) {std::cout << e << ", "; };
//	Predicate<int> predicate = [](int e) {return e % 2 == 0; };
//	Comparator<int> comparator = [](int e1, int e2) {return e1 < e2; };
//	BinaryOperator<int> binary_operator = [](int e1, int e2)->int {return e1 + e2; };
//	Supplier<int> supplier = []()->int {return 13; };
//
//	A<int> a;
//
//	make_stream(vec);
//
//	//auto stream1 = make_stream(vec)
//	//	//.filter(predicate)
//	//	//.map(mapper)
//	//	.sort(comparator);
//	//	//.distinct()
//	//	//.skip(9)
//	//	//.for_each(consumer);
//	//	//.collect<int, std::list<int>>();
//
//	//std::vector<std::vector<int>> mat;
//	//mat.push_back({ 1, 2, 3 });
//	//mat.push_back({ 4, 5, 6 });
//	//mat.push_back({ 7, 8, 9 });
//
//	////auto l = 
//	//	make_stream(mat)
//	//	.flatMap()
//	//	.concat_move(std::move(stream1))
//	//	//.collect < std::list<int>>();
//	//	.generate<5>(supplier)
//	//	.for_each(consumer);
//	//	//.for_each([](const std::vector<int>& vec) {for (int e : vec) std::cout << e << " ,"; std::cout << "\n"; });
//
//	return 0;
//}


//
////this is for composing map functions
//template<class OldT, class T, class R>
//UnaryOperation<OldT, R> getComposeMap(UnaryOperation<OldT, T> prev, UnaryOperation<T, R> op)
//{
//	return [prev, op](const OldT& oldT) -> R
//	{
//		T inter = prev(oldT);
//		return op(inter);
//	};
//}
//
////composing predicates
//template<class T>
//UnaryOperation<T, bool> getComposePred(UnaryOperation<T, bool> prev, UnaryOperation<T, bool> op)
//{
//	return [prev, op](const T& oldT) -> bool
//	{
//		return prev(oldT) && op(oldT);
//	};
//}
//
//
//template<class OldT, class T, class R>
//struct FuncComposer;
//
//template<class OldT, class T, class R>
//struct FuncComposer
//{
//	static OptFunc<OldT, R> getComposeFunc(OptFunc<OldT, T> prev, OptFunc<T, R> op)
//	{
//		return [prev, op](std::optional<OldT> old) -> std::optional<R>
//		{
//			if (!old.has_value())
//			{
//				return std::nullopt;
//			}
//
//			T val = old.value();
//			R res = fun(val);
//
//			return { std::make_any<R>(res) };
//		};
//	}
//};
//
//template<class OldT, class R>
//struct FuncComposer<OldT, bool, R>
//{
//	static UnaryOperation<OldT, R> getComposeFunc(UnaryOperation<OldT, bool> prev, UnaryOperation<OldT, R> op)
//	{
//		return [prev, op](const OldT& oldT) -> R
//		{
//			bool inter = prev(oldT);
//			if (inter)
//			{
//				return op(oldT);
//			}
//			else
//			{
//				return R();
//			}
//		};
//	}
//};
//
//template<class OldT, class T, class R>
//UnaryOperation<OldT, R> getComposeFunc(UnaryOperation<OldT, T> prev, UnaryOperation<T, R> op)
//{
//	return FuncComposer<OldT, T, R>::getComposeFunc(prev, op);
//}
//

//static Fun compose(Fun f1, Fun f2)
//{
//	return [f1, f2](std::optional<std::any> x)
//	{
//		return f2(f1(x));
//	};
//}
//using Fun = std::function<std::optional<std::any>(std::optional<std::any>)>;
//static Fun identity = [](std::optional<std::any> x) -> std::optional<std::any> {return { x }; };
//
//
//template<class T, class R>
//static Fun create(std::function<R(T)> fun)
//{
//	return [fun](std::optional<std::any> x) -> std::optional<std::any>
//	{
//		if (!x.has_value())
//		{
//			return std::nullopt;
//		}
//
//		T val = std::any_cast<T>(x.value());
//		R res = fun(val);
//
//		return { std::make_any<R>(res) };
//	};
//}
//
//template<class T>
//static Fun createBool(std::function<bool(T)> fun)
//{
//	return [fun](std::optional<std::any> x) -> std::optional<std::any>
//	{
//		if (!x.has_value())
//		{
//			return std::nullopt;
//		}
//
//		T val = std::any_cast<T>(x.value());
//		bool res = fun(val);
//
//		if (!res)
//		{
//			return std::nullopt;
//		}
//
//		return { std::make_any<T>(val) };
//	};
//}
//
//template<class T>
//static Fun createTerminal(std::function<void(T)> fun)
//{
//	return [fun](std::optional<std::any> x) -> std::optional<std::any>
//	{
//		if (!x.has_value())
//		{
//			return std::nullopt;
//		}
//
//		T val = std::any_cast<T>(x.value());
//
//		fun(val);
//
//		return std::nullopt;
//	};
//}
//
//template<class T>
//static void printRes(std::optional<std::any> x)
//{
//	if (!x.has_value())
//	{
//		std::cout << "No value";
//		return;
//	}
//
//	std::cout << std::any_cast<T>(x.value());
//}
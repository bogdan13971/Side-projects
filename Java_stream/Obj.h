#pragma once

#include <iostream>

struct Obj
{
	static int cted;
	static int dted;
	static int copy_cted;
	static int assigned;
	static int mov_cted;
	static int mov_ass;

	int a;

	Obj(int a) :a{ a } { cted++; std::cout << "Ctor\n"; };

	Obj(const Obj& other) :a{ other.a } { copy_cted++; std::cout << "Copy Ctor\n"; };
	Obj(Obj&& other) noexcept :a{ std::move(other.a) } { mov_cted++; std::cout << "Move Ctor\n"; };

	Obj& operator=(const Obj& other) { a = other.a; assigned++; std::cout << "Copy ass\n"; return *this; };
	Obj& operator=(Obj&& other) noexcept { a = std::move(other.a); mov_ass++; std::cout << "Move ass\n"; return *this; };

	~Obj() { dted++; std::cout << "Dtor\n"; }
};

int Obj::cted = 0;
int Obj::dted = 0;
int Obj::copy_cted = 0;
int Obj::assigned = 0;
int Obj::mov_cted = 0;
int Obj::mov_ass = 0;



#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <iostream>

#define ll long long


class Interval
{
	ll from;
	ll to;
	bool prob;

	friend std::ostream& operator <<(std::ostream& os, const Interval& I) { os << '[' << I.from << ", " << I.to << ']'; return os; }

public:

	Interval(ll from=0, ll to=0) : from(from), to(to), prob(false) { if (from>to) { prob = true; } }

	const ll&GetFrom() const { return from; }
	const ll& GetTo() const { return to; }
	bool isFunctionable() const { return !prob; }

	bool DoesContain(const Interval& Int) const
	{ 
		if (prob || Int.prob) {  return false; }
		
		if (Int.from >= from && Int.from <= to) { return true; }

		if (Int.to >= from && Int.from <= from) { return true; }
	
		return false;
	
	}

	bool operator == (const Interval& x) const { return (x.from == from && x.to == to); }
	bool operator !=(const Interval& x) const { return !(*this == x); }

	bool operator <=(const Interval& x) const { return ((*this == x) || (this->from < x.from) || (this->from == x.from && this->to < x.to )); }
	bool operator >=(const Interval& x) const { return (*this == x || !(*this <= x)); }

	bool operator <(const Interval& x) const { return (*this != x && *this <= x); }

	bool operator >(const Interval& x) const { return (*this != x && *this >= x); }

};

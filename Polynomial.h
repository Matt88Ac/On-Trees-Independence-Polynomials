#pragma once

/* To compute the independence polynomial, declare:  IndeP( TreeGraph_type your_Graph )  */




#include "Tree_G.h"
#include <iostream>
#include <string>

using namespace std;

#define ull unsigned long long



// Class of Monomial objects, which will eventually assemble the Independence Polynomial; 
class Mono
{
	friend ostream& operator <<(ostream&, const Mono&);

public:
	Mono(ull c = 0, int d = 0) : deg(d), coef(c) {};

	bool operator <=(const Mono& m) const { return ((m.deg > deg) || (m.deg == deg && m.coef > coef)); }
	bool operator >=(const Mono& m) const { return ((m.deg < deg) || (m.deg == deg && m.coef < coef)); }
	bool operator ==(const Mono& m) const { return ((m.deg == deg && m.coef == coef)); }
	void operator +=(const Mono& m) { this->coef += m.coef; }
	Mono operator+(const Mono& m) const { Mono tmp(this->coef + m.coef, deg); return tmp; }
	void operator *=(const Mono& m) { this->deg += m.deg; this->coef *= m.coef; }
	Mono operator*(const Mono& m) const { Mono tmp(this->coef*m.coef, deg + m.deg); return tmp; }

	operator string() const;

	bool isAddAble(const Mono& m) const { return deg == m.deg; }

	~Mono() {};

	int deg;
	ull coef;

};


Mono::operator string() const
{
	if (coef == 0) { return "0"; }

	if (coef == 1)
	{
		if (deg == 1) { return "X"; }
		else if (deg > 1) { return (string)("X^" + to_string(deg)); }
		return "1";
	}

	else
	{	
		if (deg == 1) { return (string)(to_string(coef)  + "*X"); }
		else if (deg > 1) { return (string)(to_string(coef) + "X^" + to_string(deg)); }
		return to_string(coef);
	}

	return "";
}


ostream& operator <<(ostream& os, const Mono& x)
{
	if (x.coef == 0) { os << "0"; return os; }

	if (x.coef == 1)
	{
		if (x.deg == 1) { os << "X";  return os; }
		else if (x.deg > 1) { os << "X^" << x.deg;  return os; }
		os << "1";
	}

	else
	{
		if (x.deg == 1) { os << x.coef << "*X";  return os; }
		else if (x.deg > 1) { cout << x.coef << "*X^" << x.deg;  return os; }
		os << x.coef;
	}

	return os;

}



void swap(Mono& a, Mono&b)
{
	Mono tmp = a;
	a = b;
	b = tmp;
}



// Class pupose is holding the Independence Polynomial of the given graph.
class IndeP
{
	friend ostream& operator <<(ostream&, const IndeP&);
public:
	IndeP(const TreeGraph& T) : size(0), gonna_save_some_time(false) { IndeP X;  *this = ComputeTree(T, X); }

	IndeP() : size(0) {};

	void operator+=(const Mono&);
	void operator+=(const IndeP&);

	IndeP operator+(const Mono&);
	IndeP operator+(const IndeP&);

	void operator *=(const Mono&);
	void operator *=(const IndeP&);

	IndeP operator*(const Mono&);
	IndeP operator*(const IndeP&);

	operator string() const;
	
	bool isUni() const;

	IndeP ComputeTree(const TreeGraph&, IndeP&);

	IndeP TimeSaver(const TreeGraph&);


	~IndeP() { Holder.clear(); Holder.shrink_to_fit(); size = 0; };


protected:
	vector<Mono> Holder;

	int size;
	bool gonna_save_some_time;


};


bool IndeP::isUni() const
{

	int i, length = (int)Holder.size();
	bool flag = false;

	for ( i = 0; i < length-1; i++)
	{
		if (Holder[i].coef > Holder[i + 1].coef && !flag) { flag = true; }
		
		if (Holder[i].coef < Holder[i + 1].coef && flag) { return false; }
	
	}

	return true;

}




IndeP::operator string() const
{

	string poly;
	if (!size) { return "0"; }

	for (int i = 0; i < (int)Holder.size() - 1; i++) { poly += (string)Holder[i] + " + "; }

	poly += (string)Holder[(int)Holder.size() - 1];

	return poly;

}




ostream& operator <<(ostream& os, const IndeP& P)
{
	os << "I(G;X) = ";

	if (P.size == 0)
	{
		os << endl;
		return os;
	}

	for (int i = 0; i < (int)P.Holder.size() - 1; i++)
	{
		os << P.Holder[i] << " + ";
	}

	os << P.Holder[P.size - 1];
	return os;

}




void IndeP::operator+=(const Mono& m)
{
	if (size == 0)
	{
		this->Holder.push_back(m);
		this->size++;
		return;
	}


	for (int i = 0; i < (int)Holder.size(); i++)
	{
		if (Holder[i].isAddAble(m))
		{
			Holder[i] += m;
			return;
		}
	}

	Holder.push_back(m);
	size++;

	for (int j = 0; j < (int)Holder.size() - 1; j++)
	{
		if (Holder[j] >= Holder[j + 1]) { swap(Holder[j], Holder[j + 1]); }
	}



}




void IndeP::operator+=(const IndeP& P)
{
	if (size == 0) { size = P.size; Holder = P.Holder; return; }
	if (P.size == 0) { return; }
	for (int i = 0; i < (int)P.Holder.size(); i++) { *this += P.Holder[i]; }


}




IndeP IndeP::operator+(const Mono& m)
{
	IndeP tmp;
	tmp.size = this->size;
	tmp.Holder = this->Holder;
	tmp += m;

	return tmp;
}




IndeP IndeP::operator+(const IndeP& P)
{
	IndeP tmp;
	tmp.size = this->size;
	tmp.Holder = this->Holder;
	tmp += P;

	return tmp;

}




void IndeP::operator*=(const Mono& m)
{
	if (size == 0) { return; }

	if (m == Mono(0, 0)) { Holder.clear(); size = 0; }

	for (int i = 0; i < (int)Holder.size(); i++) { Holder[i] *= m; }

}


void IndeP::operator*=(const IndeP& P)
{

	if (P.size == 0) { Holder.clear(); size = 0; }
	if (size == 0) { return; }

	IndeP tmpo;

	for (int i = 0; i < (int)P.Holder.size(); i++) { tmpo += *this * P.Holder[i]; }

	*this = tmpo;

	tmpo.~IndeP();
}




IndeP IndeP::operator*(const Mono& m)
{
	IndeP tmp;
	tmp.Holder = this->Holder;
	tmp.size = size;

	if (size == 0) { return tmp; }

	if (m == Mono(0, 0))
	{
		tmp.Holder.clear();
		tmp.size = 0;
		return tmp;
	}

	tmp *= m;
	return tmp;
}





IndeP IndeP::operator*(const IndeP& P)
{
	IndeP tmp;
	tmp.size = size;
	tmp.Holder = Holder;
	if (size == 0)
	{
		return tmp;
	}

	if (P.size == 0)
	{
		tmp.Holder.clear();
		tmp.size = 0;
		return tmp;
	}

	tmp *= P;

	return tmp;
}





IndeP IndeP::TimeSaver(const TreeGraph& T)
{
	int k1 = 0, k2 = 0;

	int i = 0;

	const vector<vertex> tmpo = T.GetV();

	for (i = 0; i < (int)tmpo.size(); i++)
	{
		if (tmpo[i].degree == 0) { k1++; }
		else if (tmpo[i].degree == 1) { k2++; }

		else { gonna_save_some_time = false; return *this; }

	}

	if (!k1 && !k2) { gonna_save_some_time = false; return *this; }

	this->gonna_save_some_time = true;

	IndeP x;
	bool flag = false;


	for (i = 0; i < k1; i++)
	{
		IndeP tmp;
		tmp += Mono(1, 0);
		tmp += Mono(1, 1);

		if (!flag) { x += tmp; flag = true; }
		else { x *= tmp; }

		tmp.~IndeP();

	}

	for (i = 0; i < (k2 / 2); i++)
	{
		IndeP tmp;
		tmp += Mono(1, 0);
		tmp += Mono(2, 1);

		if (!flag) { x += tmp; flag = true; }
		else { x *= tmp; }

		tmp.~IndeP();

	}

	return x;

}



IndeP IndeP::ComputeTree(const TreeGraph& T, IndeP& curr)
{

	if (T.getsize() == 0)
	{
		IndeP tmp;
		tmp += Mono(1, 0);
		return tmp;
	}


	if (T.isKn())
	{
		IndeP tmp;
		tmp += Mono(T.getsize(), 1);
		tmp += Mono(1, 0);

		return tmp;
	}

	IndeP x = TimeSaver(T);

	if (gonna_save_some_time) { gonna_save_some_time = false; return x; }


									// T-v,v in V							T-N[V], v in V
	curr = ComputeTree(TreeGraph(T, T.getMax(), true), curr) + ComputeTree(TreeGraph(T, T.getMax(), false), curr)*Mono(1, 1);

	return curr;

}

#pragma once

/* To compute the independence polynomial, declare:  IndeP( TreeGraph_type your_Graph )  */




#include "RandomTreeGenerator.h"
#include <iostream>
#include <string>
#include <sstream>

#define ull unsigned long long



// Class pupose is holding the Independence Polynomial of the given graph.
class IndeP
{
	friend std::ostream& operator <<(std::ostream&, const IndeP&);
public:
	IndeP(const Tree& T) :  gonna_save_some_time(false) {
		this->Holder.push_back(0);
		IndeP X;  *this = ComputeTree(T, X);
		//this->Math_Format_Clique_Poly = "1*X^0 + " + to_string(T.getsize()) + "*X^1 + " + to_string(T.getsize() - 1) + "*X^2";

	}


	IndeP() : gonna_save_some_time(false) {};

	void operator+=(const IndeP&);

	IndeP operator+(const IndeP&);

	void operator *=(const IndeP&);

	IndeP operator*(const IndeP&);

	const std::string& GetCliquePoly() const { return this->Math_Format_Clique_Poly; }

	bool isUni() const;

	IndeP ComputeTree(const Tree&, IndeP&);

	IndeP TimeSaver(const Tree&);

	const int& GetAlphaT() const { return Holder.size(); }



	~IndeP() { Holder.clear(); Holder.shrink_to_fit();  };




protected:
	std::vector<ull> Holder;
	std::string Math_Format_Clique_Poly;
	bool gonna_save_some_time;


};



bool IndeP::isUni() const
{

	int i, length = (int)Holder.size();
	bool flag = false;

	for (i = 0; i < length - 1; i++)
	{
		int p = i + 1;
		if (Holder[i] > Holder[p] && !flag) { flag = true; }

		if (Holder[i] < Holder[p] && flag) { return false; }

	}

	return true;

}






std::ostream& operator <<(std::ostream& os, const IndeP& P)
{
	os << "I(G;X) = ";


	std::vector<ull> tmp = P.Holder;

	if (P.Holder.size() == 0)
	{
		os << std::endl;
		return os;
	}

	
	while (tmp[tmp.size() - 1] == 0) {
		tmp.pop_back();
	}
	
	int ip = tmp.size() - 1;
	
	for (int i = 0; i < ip; i++)
	{
		if (tmp[i] == 0) {
			continue;
		}
		
		
		if (tmp[i] == 1) {
			if (i > 1) {
				os << "X^" << i << " + ";
				continue;
			}

			else if (i == 1) {
				os << "X" << " + ";
				continue;
			}
			os << tmp[i] << " + ";
		}

		else {
			if (i > 1) {
				os << tmp[i] << "X^" << i << " + ";
				continue;
			}

			else if (i == 1) {
				os << tmp[i] << "X" << " + ";
				continue;
			}

			os << tmp[i] << " + ";
		}
	}

	if (tmp[ip] == 1){
		os << "X^" << ip;
	}

	else{
		os << tmp[ip] << "X^" << ip;
	}
	
	return os;

}


void IndeP::operator+=(const IndeP& m)
{
	int size2 = (int)m.Holder.size(), size1 = this->Holder.size(), i = 0;

	if (size2 > size1) {
		for (i = 0; i < size1; i++)
		{
			this->Holder[i] = this->Holder[i] + m.Holder[i];
		}

		for (i; i < size2; i++)
		{
			this->Holder.push_back(m.Holder[i]);
		}
	}

	else {

		for (i = 0; i < size2; i++)
		{
			this->Holder[i] = this->Holder[i] + m.Holder[i];
		}
	}

}




IndeP IndeP::operator+(const IndeP& m)
{
	IndeP tmp;
	tmp.Holder = this->Holder;
	
	int size2 = (int)m.Holder.size(), size1 = tmp.Holder.size(),i=0;

	if (size2 > size1) {
		for (i = 0; i < size1; i++)
		{
			tmp.Holder[i] = tmp.Holder[i] + m.Holder[i];
		}

		for ( i ; i < size2; i++)
		{
			tmp.Holder.push_back(m.Holder[i]);
		}
	}

	else {

		for (i = 0; i < size2; i++)
		{
			tmp.Holder[i] = tmp.Holder[i] + m.Holder[i];
		}
	}

	return tmp;
}





void IndeP::operator*=(const IndeP& P)
{
	
	const std::vector<ull> t = P.Holder;


	int s1 = t.size();
	int s2 = this->Holder.size();

	std::vector<ull> ttmp = std::vector<ull>(s1+s2);

	for (int i = 0; i < s2; i++)
	{
		for (int j = 0; j < s1; j++)
		{
			ttmp[i + j] = ttmp[i+j] + this->Holder[i] * t[j];
		}
	}

	this->Holder = ttmp;
}



IndeP IndeP::operator*(const IndeP& P)
{
	IndeP tmp;
	tmp.Holder = this->Holder;
	int size = this->Holder.size();
	if (size == 0)
	{
		return tmp;
	}

	tmp *= P;

	return tmp;
}





IndeP IndeP::TimeSaver(const Tree& T)
{
	int k1 = 0, k2 = 0;

	int i = 0;

	const std::vector<Vert> tmpo = T.Vert_Info;

	for (i = 0; i < (int)tmpo.size(); i++)
	{
		if (tmpo[i].Neighbours.size() == 0) { k1++; }
		else if (tmpo[i].Neighbours.size() == 1) { k2++; }

		else { gonna_save_some_time = false; return *this; }

	}

	if (!k1 && !k2) { gonna_save_some_time = false; return *this; }

	this->gonna_save_some_time = true;

	IndeP x;
	bool flag = false;


	for (i = 0; i < k1; i++)
	{
		IndeP tmp, t;
		std::vector<ull> m;
		m.push_back(ull(1));
		m.push_back(ull(0));
		t.Holder = m;


		tmp += t;
		t.Holder[0] = 0;
		t.Holder[1] = 1;
		tmp += t;

		if (!flag) { x += tmp; flag = true; }
		else { x *= tmp; }

		tmp.~IndeP();

	}

	for (i = 0; i < (k2 / 2); i++)
	{
		IndeP tmp, t;
		std::vector<ull> m;
		m.push_back(ull(1));
		m.push_back(ull(0));
		t.Holder = m;


		tmp += t;
		t.Holder[0] = ull(0);
		t.Holder[1] = ull(2);
		tmp += t;

		if (!flag) { x += tmp; flag = true; }
		else { x *= tmp; }

		tmp.~IndeP();

	}

	return x;

}



IndeP IndeP::ComputeTree(const Tree& T, IndeP& curr)
{

	if (T.vert == 0)
	{
		IndeP tmp;
		tmp.Holder.push_back(ull(1));
		return tmp;
	}


	/*if (T.isKn())
	{
		IndeP tmp;
		tmp.Holder.push_back(ull(1));
		tmp.Holder.push_back(ull(T.vert));

		return tmp;
	}*/

	IndeP /*x = TimeSaver(T),*/ tmp;

	//if (gonna_save_some_time) { gonna_save_some_time = false; return x; }
	tmp.Holder.push_back(ull(0));
	tmp.Holder.push_back(ull(1));

	// T-v,v in V							T-N[V], v in V
	curr = ComputeTree(Tree(T, T.Max_Degree, true), curr) + ComputeTree(Tree(T, T.Max_Degree, false), curr) * tmp;

	return curr;

}



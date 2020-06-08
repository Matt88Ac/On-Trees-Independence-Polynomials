#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "Cpp_SIPL.h"
#include <sstream>



struct Vert {
	Vert() {}
	Vert(int const &Vert_index, std::vector<int> neigh) {
		this->Vert_index = Vert_index;
		this->Neighbours = neigh;
	}
	int Vert_index;
	std::vector<int> Neighbours;
};


struct Tree {

	std::vector<std::pair<int, int> > Tree_Edges;
	std::vector<int> Degrees;
	std::vector<Vert> Vert_Info;
	Matrix<int> Adj_Matrix;
	std::vector<Pixel> Vert_Colors;

	int Max_Degree;
	int vert;
	void Remove_Vert(int const index) {

	

		for (int i = 0; i < vert; i++) {
			if (Adj_Matrix[index][i] == 1) {
				Degrees[i]--;
			}
		}



		for (int i = 0; i < Vert_Info.size(); i++) {
			for (int j = 0; j < Vert_Info[i].Neighbours.size(); j++) {

				if (Vert_Info[i].Neighbours[j] == index) {
					Vert_Info[i].Neighbours.erase(Vert_Info[i].Neighbours.begin() + j);
					j--;
					break;
				}

			}

			for (int j = 0; j < Vert_Info[i].Neighbours.size(); j++) {

				if (Vert_Info[i].Neighbours[j] > index) {
					Vert_Info[i].Neighbours[j]--;
				}

			}



		}

		for (int i = index; i < vert; i++) {
			Vert_Info[i].Vert_index--;
		}

		this->Degrees.erase(Degrees.begin() + index);
		this->Vert_Info.erase(Vert_Info.begin() + index);
		this->Adj_Matrix.Remove_Row(index);
		this->Adj_Matrix.Remove_Column(index);
		this->vert--;
		this->Vert_Colors.erase(this->Vert_Colors.begin() + index);

		int holder = 0;
		Max_Degree = 0;
		for (int i = 0;i < Degrees.size();i++) {
			if (Degrees[i] > Max_Degree) {
				Max_Degree = Degrees[i];
				holder = i;
			}
		}
		Max_Degree = 0;


	}
	Tree(int const &edges) {
		Random_Utilitis rnd;
		int length = edges - 2;
		int *prufer = new int[length];
		vert = edges;
		for (int i = 0; i < length; i++)
		{
			prufer[i] = rnd.Random_INT(1, edges);
		}

		int vertices = edges;

		std::vector<int> vertex_set(vertices, 0);

		for (int i = 0; i < vertices - 2; i++)
			vertex_set[prufer[i] - 1] += 1;

		int j = 0;

		for (int i = 0; i < vertices - 2; i++)
		{
			for (j = 0; j < vertices; j++)
			{

				if (vertex_set[j] == 0)
				{

					vertex_set[j] = -1;
					Tree_Edges.push_back(std::pair<int, int>((j + 1), prufer[i]));
					vertex_set[prufer[i] - 1]--;

					break;
				}
			}
		}

		j = 0;
		int pa = -1, pb = -1;
		// For the last element 
		for (int i = 0; i < vertices; i++)
		{
			if (vertex_set[i] == 0 && j == 0)
			{


				pa = (i + 1);
				j++;
			}
			else if (vertex_set[i] == 0 && j == 1)
				pb = (i + 1);
		}

		Tree_Edges.push_back(std::pair<int, int>(pa, pb));


		Adj_Matrix = Matrix<int>(vert, vert);


		for (int i = 0; i < Tree_Edges.size(); i++) {
			Adj_Matrix[Tree_Edges[i].second - 1][Tree_Edges[i].first - 1] = 1;
			Adj_Matrix[Tree_Edges[i].first - 1][Tree_Edges[i].second - 1] = 1;

		}
		Max_Degree = 0;
		int holder = 0;
		for (int i = 0; i < vert; i++) {
			std::vector<int> N;
			int count = 0;
			for (int j = 0; j < vert; j++) {
				if (Adj_Matrix[i][j] == 1) {
					N.push_back(j);
					count++;
				}
			}

			this->Vert_Info.push_back(Vert(i, N));

			if (count > holder) {
				holder = count;
				Max_Degree = i;
			}
			//Max_Degree = count ? count > Max_Degree: Max_Degree;
			Degrees.push_back(count);
		}
		Color_Palette CSET;
		for (int i = 0; i < vert; i++) {
			Vert_Colors.push_back(CSET.Color_Serial_Number[3 + i]);
		}

		std::sort(this->Tree_Edges.begin(), this->Tree_Edges.end());



	}

	Tree(const Tree& T, int which, bool v_or_nv) {

		*this = T;

		if (v_or_nv)
		{
			this->Remove_Vert(which);
			return;
		}

		else
		{
			for (int i = 0; i < Vert_Info[which].Neighbours.size(); i++) {

				this->Remove_Vert(Vert_Info[which].Neighbours[i]);
				
					i--;
					continue;
				

			}

			

			this->Remove_Vert(which);
		}


	}



};




std::ostream &operator<<(std::ostream &out, std::pair<int, int> const &data) {
	out << "( " << data.first << ", " << data.second << " ) ";
	return out;
}
std::ostream &operator<<(std::ostream &out, std::vector<std::pair<int, int>> const &data) {
	for (int i = 0; i < data.size(); i++) {
		out << data[i];
	}
	return out;
}

std::ostream &operator<<(std::ostream &out, Vert const &data) {
	out << "Vert Index: " << data.Vert_index << "\n";
	out << "Neighbours : {";
	for (int i = 0; i < data.Neighbours.size(); i++) {
		out << data.Neighbours[i] << ", ";
	}
	out << " }\n";

	return out;
}

Image Draw_Tree(Tree  &tree,std::string filename) {

	Image TD;
	Color_Palette CSET;
	Random_Utilitis rnd;
	std::vector<std::pair<std::pair<int, int>, int> > locations(tree.vert);


	TD.Load_Blank_Canvas(tree.vert * 60, tree.vert * 60, CSET.Azure);
	bool status = false;
	int p = 0;
	for (int i = 0; i < tree.vert; i++) {


		std::pair<std::pair<int, int>, int> loc(std::pair<int, int>(rnd.Random_INT(10, tree.vert * 40), rnd.Random_INT(10, tree.vert * 40)), i);

		for (int j = 0; j < locations.size(); j++) {
			if (loc == locations[i]) {
				j = 0;
				loc = std::pair<std::pair<int, int>, int>(std::pair<int, int>(rnd.Random_INT(10, tree.vert * 40), rnd.Random_INT(10, tree.vert * 40)), i);
				break;
			}
		}
		locations[i] = (loc);



	}



	for (int i = 0; i < locations.size(); i++) {
		TD.Draw_Circle(locations[i].first.first, locations[i].first.second, tree.vert, tree.Vert_Colors[i], S_FILL);

	}


	for (int i = 0; i < tree.vert; i++) {
		for (int j = 0; j < tree.vert; j++) {
			if (tree.Adj_Matrix[i][j] == 1) {
				TD.Draw_Line(locations[i].first.first, locations[i].first.second, locations[j].first.first, locations[j].first.second, tree.Vert_Colors[i], S_AA_LINE);
			}
		}
	}

	TD.Write_Image(filename);


	return TD;


}

Image Draw_Tree_Bruteforce(Tree &tree, std::string filename) {
	Image ImageBody;
	Color_Palette CSET;
	ImageBody.Load_Blank_Canvas(std::min(tree.vert * 100,2500), std::min(tree.vert * 100,2500) + 150, CSET.Azure);
	std::random_device seed; //seed for psudo random engine 
	std::mt19937 random_number_generator(seed()); //merssene twisster using the PR seed
	std::uniform_int_distribution<size_t> indices(50, (tree.vert * 100) - 50);
	std::stringstream ss;
	std::string via;
	int Px, Py, planer_score = 0, iterdebug = 0;
	bool set = false;
	std::vector<std::pair<int, int> > positions;
	positions.reserve(tree.vert);
	ImageBody.Draw_Text(20, (tree.vert * 100) / 2, filename, CSET.Black);
	for (int i = 0; i < tree.vert; i++) {
		Px = indices(random_number_generator);
		Py = indices(random_number_generator);
		positions.push_back(std::pair<int,int>(Px, Py));

	}

	while (true) {
		for (int i = 0; i < tree.vert; i++) {
			for (int j = 0; j < i; j++) {
				if (tree.Adj_Matrix[i][j] == 1) {
					std::vector<Pixel> Path = ImageBody.Get_Line_Pixels(positions[i].second, positions[i].first, positions[j].second, positions[j].second,S_AA_LINE);
					for (int k = 0; k < Path.size(); k++) {
						if (k >= std::min(tree.vert,25) && Path[k]!= CSET.Azure) {
							positions[j].first = indices(random_number_generator);
							positions[j].second = indices(random_number_generator);
							positions[i].first = indices(random_number_generator);
							positions[i].second = indices(random_number_generator);
							set = true;
							break;
						}
					}
					if (set == true) {
						break;
					}
					else {
						ImageBody.Draw_Line(positions[i].second, positions[i].first, positions[j].second, positions[j].first, CSET.Color_Serial_Number[i + 5],S_AA_FILL);
						//ImageBody.Draw_Circle(positions[i].second, positions[i].first, std::min(tree.vert, 25), CSET.Color_Serial_Number[i + 5], S_AA_FILL);
			

						ImageBody.Update_Pixel_Matrix();
					}

					Path.clear();

				}
			}
			if (set == true) {
				break;
			}
		}
		if (set == true) {
			set = false;


			/*	ss << iterdebug;
				via = ss.str();
				ImageBody.Write_Image(via.c_str());
				ss.str(string());
				iterdebug++;*/

			for (int i = 0; i <ImageBody.Image_Height; i++) {
				for (int j = 0; j <ImageBody.Image_Width; j++) {
					ImageBody.Set_Color(i, j, CSET.Azure);
					ImageBody.Pixel_Matrix[i][j] = CSET.Azure;

				}
			}
			planer_score = 0;
		}
		else {
			planer_score++;
			if (planer_score == tree.vert) {
				break;
			}
		}
	}






	for (int i = 0; i < tree.vert; i++) {
		ImageBody.Draw_Circle(positions[i].second, positions[i].first, std::min(tree.vert,25), CSET.Color_Serial_Number[i + 5], S_AA_FILL);
		std::string v = "V " + std::to_string(i+1);
		ImageBody.Draw_Text((std::min(tree.vert * 100, 2500)) - (i+1) * 90, (std::min(tree.vert * 100, 2500))+150 - 64, v, CSET.Color_Serial_Number[i + 5]);

		for (int j = 0; j < i; j++) {
			if (tree.Adj_Matrix[i][j] == 1) {
				ImageBody.Draw_Line(positions[i].second, positions[i].first, positions[j].second, positions[j].first, CSET.Color_Serial_Number[i + 5],S_AA_LINE);
			}
		}
	}



	
	


	ImageBody.Write_Image(filename);
	return ImageBody;
}
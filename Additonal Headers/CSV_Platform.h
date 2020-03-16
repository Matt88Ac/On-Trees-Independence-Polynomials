#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <sstream>
#include<stdarg.h>

namespace Platfrom {

	class CSV {
	protected:
		std::ofstream csv_body;
		std::string f_name;
		std::vector<std::string> row_names;
		int cur_line;
		int cur_row;
		int cur_sum;
		std::vector<std::vector<int> > row_guide;
	public:
		CSV(std::string file_name);
		~CSV();
		void Add_Row_Category(std::string row_name);
		void GotoLine(int row, int colum);
		void Add_Value(std::string const &Value);
		template<class d_type> void Add_Value(d_type const &Value);
		void Print_Position_Grid();
		//void Erase_Last_Value();
	};


	CSV::CSV(std::string file_name) {
		this->f_name = file_name;
		f_name.append(".csv");
		this->csv_body.open(f_name);
		this->cur_line = 1;
		this->cur_row = 0;
		cur_sum = 0;
		row_guide.push_back(std::vector<int>());
	}
	CSV::~CSV() {
		if (this->csv_body.is_open()) {
			csv_body.close();
		}
	}

	void CSV::Add_Row_Category(std::string row_name) {
		if (row_name._Equal("$")) {
			for (int i = 0; i < row_names.size(); i++) {
				if (i == 0) {
					csv_body << row_names[i];
					cur_row++;

				}
				else {
					csv_body << "," << row_names[i];
					cur_row++;

				}

			}
			csv_body << "\n";
			cur_sum += row_guide[0][row_guide[0].size() - 1];
			this->row_guide.push_back(std::vector<int>());
			cur_line = 2;
			cur_row = 0;
		}
		else {
			row_names.push_back(row_name);
			if (cur_row == 0) {
				row_guide[cur_line - 1].push_back(row_name.length());
				cur_row++;
			}
			else {
				row_guide[cur_line - 1].push_back(row_guide[cur_line - 1][cur_row - 1] + row_name.length());
				cur_row++;
			}

		}
	}
	void CSV::GotoLine(int row, int colum) {
		this->csv_body.seekp(std::ios::beg + (row_guide[row - 1][colum] - (row_guide[row - 1][colum] - row_guide[row - 1][colum - 1])));
	}
	void CSV::Add_Value(std::string const &Value) {
		if (cur_row < row_names.size()) {
			csv_body << Value << ",";
			if (cur_row == 0) {
				row_guide[cur_line - 1].push_back(Value.length() + cur_sum);
				cur_row++;
			}
			else {
				row_guide[cur_line - 1].push_back(row_guide[cur_line - 1][cur_row - 1] + Value.length());
				cur_row++;
			}

		}
		else {
			csv_body << "\n";
			cur_sum = row_guide[row_guide.size() - 1][row_guide[row_guide.size() - 1].size() - 1];
			this->row_guide.push_back(std::vector<int>());
			cur_row = 0;
			cur_line++;
			this->Add_Value(Value);
		}
	}
	void CSV::Print_Position_Grid() {
		for (int i = 0; i < row_guide.size(); i++) {
			for (int j = 0; j < row_guide[i].size(); j++) {
				std::cout << row_guide[i][j] << ", ";
			}
			std::cout << "\n";
		}
	}
	template<class d_type> void CSV::Add_Value(d_type const &Value) {
		std::stringstream ss;
		ss << Value;
		this->Add_Value(ss.str());
	}
	/* void  CSV::Erase_Last_Value() {
		 this->GotoLine(cur_line, cur_row - 1);
		 for (int i = 0; i < row_guide[row_guide.size()-1][cur_row] - row_guide[row_guide.size() - 1][cur_row - 1]; i++) {
			 csv_body << " ";
		 }
		 row_guide[cur_line].pop_back();
	 }

*/




}



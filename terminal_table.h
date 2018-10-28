#pragma once

#include <vector>
#include <string>

namespace tmools
{

class TerminalTable {
public:
	struct Row {
		Row(int columns, const std::string& value = "");
		Row(const std::vector<std::string>& values);

		std::string& operator[](int index);
		const std::string& operator[](int index) const;

		Row& Set(int column, const std::string& string);
		Row& Append(int column, const std::string& string);
		void AddColumn(const std::string& value = "");

	
		std::vector<std::string> mValues;
	};

public:
	TerminalTable();
	TerminalTable(int nRows, int nColumns);
	~TerminalTable();

	Row& operator[](int index);
	const Row& operator[](int index) const;

	Row& AddRow();
	TerminalTable& AddColumn(const std::string& name);

	TerminalTable& SetHeader(int column, const std::string& name);	

	std::string ToString(int ident = 0) const;

	int GetNumRows() const;
	int GetNumColumns() const;

	void Sort(int column, bool desc = false);

private:
	std::vector<std::string> mHeader;
	std::vector<Row> mRows;
};


}
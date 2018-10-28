#include "terminal_table.h"
#include "exceptions.h"
#include <algorithm>
#include <memory>
#include "split.h"
#include "string_format.h"

namespace tmools
{

TerminalTable::Row::Row(int columns, const std::string& value /* = ""*/) :
	mValues(columns,value) {
}

TerminalTable::Row::Row(const std::vector<std::string>& values) :
	mValues(values) {
}

std::string& TerminalTable::Row::operator[](int index) {
	ASSERT(index >= 0 && index < (int)mValues.size(),"Index out of range");	

	return mValues[index];
}

const std::string& TerminalTable::Row::operator[](int index) const {
	ASSERT(index >= 0 && index < (int)mValues.size(),"Index out of range");	

	return mValues[index];
}

TerminalTable::Row& TerminalTable::Row::Set(int column, const std::string& string) {
	(*this)[column] = string;
	return *this;
}

TerminalTable::Row& TerminalTable::Row::Append(int column, const std::string& string) {
	(*this)[column] += string;
	return *this;

}
void TerminalTable::Row::AddColumn(const std::string& value /* = ""*/) {
	mValues.push_back(value);
}


TerminalTable::TerminalTable() {
}

TerminalTable::TerminalTable(int nRows, int nColumns) :
	mHeader(nColumns,""), mRows(nRows,Row(nColumns,""))
{
}

TerminalTable::~TerminalTable() {
}


TerminalTable::Row& TerminalTable::operator[](int index) {
	ASSERT(index >= 0 && index < GetNumRows(),"Index out of range");	

	return mRows[index];
}

const TerminalTable::Row& TerminalTable::operator[](int index) const {
	ASSERT(index >= 0 && index < GetNumRows(),"Index out of range");

	return mRows[index];
}


TerminalTable::Row& TerminalTable::AddRow() {
	mRows.push_back(Row((int)mHeader.size(),""));
	return mRows.back();
}

TerminalTable& TerminalTable::AddColumn(const std::string& name) {
	mHeader.push_back(name);

	for (auto& row : mRows) {
		row.AddColumn();
	}

	return *this;
}


TerminalTable& TerminalTable::SetHeader(int column, const std::string& name) {
	ASSERT(column >= 0 && column < GetNumColumns(),"Index out of range");	

	mHeader[column] = name;
	return *this;
}

std::string TerminalTable::ToString(int ident) const {
	std::stringstream ss;

	int nRows = GetNumRows();
	int nColumns = GetNumColumns();

	std::unique_ptr<int[]> width(new int[nColumns]);

	// calc width
	for (int i=0; i<nColumns; i++) {
		width[i] = (int)mHeader[i].length();
	}
	for (int r = 0; r<nRows; r++) {
		for (int i=0; i<nColumns; i++) {
			for (const auto& s : split(mRows[r][i],'\n')) {
				width[i] = std::max(width[i], (int)s.length());
			}
		}
	}

	// header
	for (int i=0; i<nColumns; i++) {
		int before = int(width[i]+2-mHeader[i].length())/2;
		int after = int(width[i]+2-mHeader[i].length()+1)/2;
		ss << spaces(ident + before) << mHeader[i] << spaces(after);
		if (i < nColumns-1)
			ss << "|";
	}
	ss << std::endl;

	// border
	for (int i=0; i<nColumns; i++) {
		ss << spaces(ident);
        ss << std::string(width[i]+2, '-');
		if (i < nColumns-1)
			ss << "+";
	}
	ss << std::endl;

	// data
	for (int r = 0; r < nRows; r++) {
		//cellHeight
		int cellHeight = 1;
		std::vector<std::vector<std::string>> cells(nColumns);
		for (int c = 0; c < nColumns; c++) {
			auto rs = split(mRows[r][c], '\n');
			int count = 0;
			for (auto s : rs) {
				s = strip(s);
				if (!s.empty()) {
					cells[c].push_back(s);
					count++;
				}
			}
			cellHeight = std::max(cellHeight, count);
		}
		
		for (int h = 0; h < cellHeight; h++) {
			for (int c = 0; c < nColumns; c++) {
				if (h < (int)cells[c].size()) {
                    ss << spaces(ident + 1) << cells[c][h] << spaces(width[c] - int(cells[c][h].size()) + 1);
					if (c < nColumns - 1)
						ss << "|";
				}
				else {
                    ss << spaces(ident + 2 + width[c]);
					if (c < nColumns - 1)
						ss << "|";
				}
			}
			ss << std::endl;
		}		
	}

	return ss.str();
}

int TerminalTable::GetNumRows() const
{
	return (int)mRows.size();
}

int TerminalTable::GetNumColumns() const
{
	return (int)mHeader.size();
}

void TerminalTable::Sort(int column, bool desc /*= false*/)
{
	std::sort(mRows.begin(), mRows.end(), [=](const Row& a, const Row& b) {
		return desc ? a[column] > b[column] : a[column] < b[column];
	});
}


}
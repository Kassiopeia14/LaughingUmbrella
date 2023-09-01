#pragma once

#include <vector>
#include "../modMessageBusClient/QFunction.h"
#include "QTableCell.h"

class QTable
{
public:

	QTable();
	~QTable();

	void setQFunction(int x, int y, QFunction qFunction);

	QTableCell getQFunction(int x, int y);

private:

	std::vector<QTableCell> qFunctionValues;

};

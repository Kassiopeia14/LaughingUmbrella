#include "QTable.h"

QTable::QTable() :
	qFunctionValues(100)
{
	for (auto item = qFunctionValues.begin(); item != qFunctionValues.end(); item++)
	{
		item->calculated = false;
		item->left = 0.;
		item->right = 0.;
		item->top = 0.;
		item->bottom = 0.;
	}
}

QTable::~QTable()
{
}

void QTable::setQFunction(int x, int y, QFunction qFunction)
{
	const int index = x * 10 + y;

	QTableCell& qTableCell = qFunctionValues[index];

	qTableCell.calculated = true;
	qTableCell.left = qFunction.left;
	qTableCell.right = qFunction.right;
	qTableCell.top = qFunction.top;
	qTableCell.bottom = qFunction.bottom;
}

QTableCell QTable::getQFunction(int x, int y)
{
	const int index = x * 10 + y;

	return qFunctionValues[index];
}

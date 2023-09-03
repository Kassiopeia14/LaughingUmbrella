#include "QGrid.h"

QGrid::QGrid():
	qFunctionValues(100)
{
	for (auto item = qFunctionValues.begin(); item != qFunctionValues.end(); item++)
	{
		item->left = 0.;
		item->right = 0.;
		item->top = 0.;
		item->bottom = 0.;
	}
}

QGrid::~QGrid()
{
}

void QGrid::setQFunction(int x, int y, QFunction _qFunction)
{
	const int index = x * 10 + y;

	QFunction& qFunction = qFunctionValues[index];

	qFunction.left = _qFunction.left;
	qFunction.right = _qFunction.right;
	qFunction.top = _qFunction.top;
	qFunction.bottom = _qFunction.bottom;
}

QFunction QGrid::getQFunction(int x, int y)
{
	const int index = x * 10 + y;

	return qFunctionValues[index];
}

double QGrid::getNorm() const
{
	double result = 0.;

	for (auto item = qFunctionValues.begin(); item != qFunctionValues.end(); item++)
	{
		if (abs(item->left) > result)
		{
			result = abs(item->left);
		}
		if (abs(item->right) > result)
		{
			result = abs(item->right);
		}
		if (abs(item->top) > result)
		{
			result = abs(item->top);
		}
		if (abs(item->bottom) > result)
		{
			result = abs(item->bottom);
		}		
	}

	return result;
}

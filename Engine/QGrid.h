#pragma once
#include <vector>
#include "../modMessageBusClient/QFunction.h"

class QGrid
{
public:
	QGrid();
	~QGrid();

	void setQFunction(int x, int y, QFunction qFunction);

	QFunction getQFunction(int x, int y);

	double getNorm() const;

private:

	std::vector<QFunction> qFunctionValues;

};

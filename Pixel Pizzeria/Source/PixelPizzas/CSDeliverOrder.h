pragma once
#include "CustomerState.h"
#include "Customer.h"

class CSDeliverOrder : CustomerState
{

public:

	void enter(Customer& customer, Map &map) override;
	void update(Customer& customer, Map &map) override;
	void exit(Customer& customer, Map &map) override;

};


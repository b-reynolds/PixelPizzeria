#pragma once

class Customer;

class Order
{

private:

	Customer* customer;
	bool ready;
	bool cooking;
	bool taken;

	static int orderCount;
	int id;
	

public:

	void setTaken(const bool &state);
	bool isTaken() const;

	void setCooking(const bool &state);
	bool isCooking() const;

	void setReady(const bool &state);
	bool isReady() const;

	void setCustomer(Customer& customer);
	Customer* getCustomer() const;

	int getID() const;

	Order(Customer* customer);
	~Order();

};


#include <iostream>
#include <vector>

using namespace std;

class Observer {
public:
	virtual void update() = 0;
};

class Observable {
private:
	vector<Observer*> observers;

public:
	void addObserver(Observer* obs) {
		observers.push_back(obs);
	}

	void removeObserver(Observer* obs) {
		observers.erase(remove(begin(observers), end(observers), obs),
			observers.end());
	}

protected:
	void notify() {
		for (auto obs : observers) {
			obs->update();
		}
	}
};
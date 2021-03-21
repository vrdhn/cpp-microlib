
#include "sim.hpp"

#include <iostream>

class FinishEvent : public Runnable {
      public:
	virtual void run(int time_abs,
			 std::vector<std::pair<int, std::unique_ptr<Runnable>>>
			     & /*events*/) {
		std::cout << "Time: " << time_abs << " FINISHED" << std::endl;
	}
	virtual ~FinishEvent() {}
};

class Event : public Runnable {

	int state;

      public:
	Event(int s) : state{s} {}

	virtual void
	run(int time_abs,
	    std::vector<std::pair<int, std::unique_ptr<Runnable>>> &events) {
		std::cout << "Time: " << time_abs << " STATE: " << state
			  << std::endl;
		if (state != 1)
			events.emplace_back(
			    state - 1,
			    std::make_unique<Event>(state % 2 ? 3 * state + 1
							      : state / 2));
		else
			events.emplace_back(state - 1,
					    std::make_unique<FinishEvent>());
	}

	virtual ~Event() { std::cout << "DESTROYED " << state << std::endl; }
};

class EventHandler {

      public:
	std::unique_ptr<Runnable> first() { return std::make_unique<Event>(5); }
};

int main() {

	Simulator s;
	EventHandler e;

	s.run(e.first());
}

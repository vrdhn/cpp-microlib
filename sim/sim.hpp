#include <memory>
#include <mutex>
#include <vector>

/* derivating class is should create monoshot Runnables,
 *  and add then with RELATIVE time to events.
 */
class Runnable {

      public:
	virtual void
	run(int time_abs,
	    std::vector<std::pair<int, std::unique_ptr<Runnable>>> &events) = 0;
	virtual ~Runnable() {}
};

class Simulator {

      private:
	// 1 slot per second,
	std::vector<std::vector<std::unique_ptr<Runnable>>> _runnables;
	std::mutex _runnables_mutex; // per slot for extreme thread count.

	// this is the only function needing lock here,
	void add(int time_abs, std::unique_ptr<Runnable> runnable) {
		std::lock_guard<std::mutex> lock(_runnables_mutex);
		if (int(_runnables.size()) <= time_abs)
			_runnables.resize(time_abs + 1);
		_runnables[time_abs].emplace_back(std::move(runnable));
	}

	// this can run runnable with async & thread pool some day
	void run_events(int time_abs,
			std::vector<std::unique_ptr<Runnable>> todos) {

		while (!todos.empty()) {
			auto todo = std::move(todos.back());
			todos.pop_back();
			std::vector<std::pair<int, std::unique_ptr<Runnable>>>
			    events;
			todo->run(time_abs, events);
			for (auto &event : events) {
				if (event.first == 0)
					todos.emplace_back(
					    std::move(event.second));
				else
					add(time_abs + event.first,
					    std::move(event.second));
			}
		}
	}

      public:
	void run(std::unique_ptr<Runnable> &&init) {
		add(0, std::move(init));
		int time_abs = -1;
		// .size() call doesn't need mutex.
		while (++time_abs < int(_runnables.size()))
			// important to move vector here, as add()
			// resizes the backbone vector.
			run_events(time_abs, std::move(_runnables[time_abs]));
	}
};

#include <iostream>
#include <deque>


class Task {

private:
    int deadline;
    int computeTime;
    int period;

public:
    std::string name;
    Task(int deadline, int computeTime, int period, std::string name): deadline(deadline), computeTime(computeTime), period(period),  name(std::move(name)){}
    void execute();
    int getSlackTime(int currentTime) const;
    bool isOver() const;
};

void Task::execute() {
    printf("run %s\n", name.c_str());
    computeTime--;
}


int Task::getSlackTime(int currentTime) const{
    return (deadline - currentTime - computeTime);
}

bool Task::isOver() const{
    return computeTime == 0;
}

class Scheduler {
private:
    int currentTime = 0;
    std::deque<Task> tasks;

public:
    explicit Scheduler(std::deque<Task> tasks) : tasks(std::move(tasks)) {}
    void run();

};

void Scheduler::run() {
    while (! tasks.empty()) {
        auto task = this->tasks.begin();
        auto lowestSlackTimeTask = task;
        
        while (task != this->tasks.end()) {

            if (task->isOver()) {
                task = tasks.erase(task);
            }
            else {
                int lowestSlackTime = lowestSlackTimeTask->getSlackTime(currentTime);
                int slackTime = task->getSlackTime(currentTime);

                if (lowestSlackTime > slackTime) lowestSlackTimeTask = task;

                task++;
            }
        }
        lowestSlackTimeTask->execute();

        currentTime++;
    }
}


int main() {

    std::deque<Task> tasks = {
            Task(7, 3, 20, "test1"),
            Task(4, 2, 5,  "test2"),
            Task(8, 2, 10, "test3")
    };
    Scheduler scheduler = Scheduler(tasks);
    scheduler.run();

    return 0;
}


#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "global.h"

#define SCH_MAX_TASKS		10




struct Task{
	// Pointer to the task (must be a ’ void ( void ) ’ function )
	void (*pTask)(void*);
	// Delay (ticks) until the function will ( next ) be run
	uint32_t delay ;

	// Interval (ticks) between subsequent runs .
	uint32_t period ;
	// Incremented (by scheduler) when task i s due to execute
	uint8_t runMe;
	// this is not only ID of task but also position of this task in SCH_tasks_G
	uint8_t taskID ;
};

class Scheduler{
  public:
    Task tasks[SCH_MAX_TASKS];
    Scheduler();

  //This function will be updated the remaining time of each
  //tasks that are added to a queue. It will be called in the interrupt timer,
  //for example 10 ms.
    void update();

  //This function will get the task in the queue to run
    void dispatchTasks();
  
  //This function is used to add a task to the queue.
  //It should return an ID that is corresponding with the added task
    uint8_t addTask(void(* pFunction)(), uint32_t DELAY, uint32_t PERIOD);
  
  //This function is used to delete the task based on its ID.
    uint8_t deleteTask(uint32_t taskID);
};

extern Scheduler scheduler;

#endif /* INC_SCHEDULER_H_ */
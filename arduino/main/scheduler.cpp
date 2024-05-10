#include "scheduler.h"

Scheduler scheduler;
Scheduler::Scheduler(){
  for(uint8_t i = 0; i < SCH_MAX_TASKS; i++){
    this->tasks[i].pTask = 0;
  }
}

void Scheduler::update(){
  for(uint8_t i = 0; i < SCH_MAX_TASKS; i++){
    //position i in SCH_tasks_G is empty
    if(!this->tasks[i].pTask)
      continue;
    
    //Update delay for task
    if(this->tasks[i].delay > 0){
      this->tasks[i].delay --;
      //If delay is equal to 0,
			//we update task's run_me for it run
			//and assign period for task's delay
      if(this->tasks[i].delay == 0){
        this->tasks[i].runMe = 1;
        if(this->tasks[i].period)
          this->tasks[i].delay = this->tasks[i].period;
      }
    }
  }
}



void Scheduler::dispatchTasks(void){
	for(uint8_t i = 0; i < SCH_MAX_TASKS; i++){
		if(this->tasks[i].runMe){
			//Run task
			(*this->tasks[i].pTask);
			//update run_me for inform that task was run
			this->tasks[i].runMe = 0;
			//delete task if task is one shoot task
			if(this->tasks[i].period == 0){
				this->deleteTask(i);
			}
		}
	}
}

//This function is used to add a task to the queue.
//It should return an ID that is corresponding with the added task
uint8_t Scheduler::addTask(void (* pFunction)(), uint32_t DELAY, uint32_t PERIOD){
	for(uint8_t i = 0; i < SCH_MAX_TASKS; i++){
		if(this->tasks[i].pTask == 0){
			//TODO
			this->tasks[i].pTask = pFunction;
			this->tasks[i].delay = DELAY;
			this->tasks[i].period = PERIOD;
			this->tasks[i].taskID = i;
			return i;
		}
	}
	return SCH_MAX_TASKS;
}

//This function is used to delete the task based on its ID.
uint8_t Scheduler::deleteTask(uint32_t taskID){
	if(taskID >= SCH_MAX_TASKS) return 0; //ERROR
	if(this->tasks[taskID].pTask == 0) return 0; //ERROR

	this->tasks[taskID].pTask = 0;
	this->tasks[taskID].delay = 0;
	this->tasks[taskID].period = 0;
	this->tasks[taskID].runMe = 0;
	return 1;
}
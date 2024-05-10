import uart 
import time

class Task:
  def __init__(self, delay, period, func):
    self.delay = delay
    self.func = func
    self.period = period
    self.run_me = 0

class Tasks:
  def __init__(self):
    self.tasks = list()

  def add_task(self, task):
    self.tasks.append(task)

  def remove_task(self, task):
    self.tasks.remove(task)

  def update(self):
    for task in self.tasks:
      if(task.delay >= 0):
        task.delay -= 1
        if(task.delay <= 0):
          task.delay = task.period
          task.run_me = 1

  def dispatch(self):
    for task in self.tasks:
      if(task.run_me):
        #reset flag run_me
        task.run_me = 0
        #active function of task
        task.func()
        
        if(task.period == 0):
          self.remove_task(task)
        else:
          task.delay = task.period
        
tasks = Tasks()
read_uart_task = Task(delay = 50, period = 1, func = uart.readSerial)
connect_uart_task = Task(delay = 10, period = 5, func = uart.getPort)


if __name__ == "__main__":
  
  tasks.add_task(connect_uart_task)
  tasks.add_task(read_uart_task)
  
  time.sleep(1) #time unit is 100ms
  
  while 1:
    tasks.update()
    tasks.dispatch()

    time.sleep(0.01) #time unit is 10ms
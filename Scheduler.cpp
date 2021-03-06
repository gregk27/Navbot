#include "Scheduler.h"
#include <Arduino.h>

// -------------------
// Helper functions
// -------------------

/**
* Command for delay, used by addDelay()
*/
class DelayCommand: public Command {
  private:
    unsigned int duration;
    unsigned long startTime;
  public:
    DelayCommand(unsigned int duration){this->duration = duration;}
    void init(){startTime = millis();}
    bool isFinished(){return millis()-startTime > duration;}
};

// -------------------
// Class functions
// -------------------

Scheduler *Scheduler::master = 0x0;

Scheduler::Scheduler(int maxCommands)
  :schedule(maxCommands){
  currentCommand = 0;
}

void Scheduler::addCommand(Command *command){
  schedule.add(command);
}

bool Scheduler::interrupt(Command *command){
  if(interruptCommand) return false;
  interruptCommand = command;
  interruptCommand->init();
  return true;
}

void Scheduler::addDelay(unsigned int duration){
  addCommand(new DelayCommand(duration));
}

unsigned int Scheduler::getIteration(){
  return iteration;
}

void Scheduler::init() {
  if(currentCommand >= schedule.size()) return;
  Command *c = schedule[currentCommand];
  c->init();
}

void Scheduler::periodic(){
  // Exit if schedule complete
  if(currentCommand >= schedule.size()) return;
  // Increment iteration counter
  iteration ++;
  
  Command *c = schedule[currentCommand];
  // Run interrupt command if active
  if(interruptCommand) c = interruptCommand;
  // Call periodic function
  c->periodic();
  
  // If the command is finished
  if(c->isFinished()){
    // End the current command
    c->end();
    if(interruptCommand){
      // If it's an interupt command, remove the dangling pointer
      interruptCommand = 0x0;
    } else {
      // Initialise the next
      currentCommand ++;
      // Exit if schedule complete
      if(currentCommand >= schedule.size()) return;
      Serial.print(F("Starting command: "));
      Serial.print(currentCommand+1);
      Serial.print(F("/"));
      Serial.println(schedule.size());
      c = schedule[currentCommand];
      c->init();
    }
  }
}

void Scheduler::end(){
  if(currentCommand >= schedule.size()) return;
  schedule[currentCommand]->end();
}

bool Scheduler::isFinished(){
  return currentCommand >= schedule.size();
}

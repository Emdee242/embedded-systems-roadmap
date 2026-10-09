#include "Debouncer.h"
#include "Button.h"
#include <Arduino.h>
  Debouncer::Debouncer(const Button& btn) : refButton(btn){};
  void Debouncer::update(){
    initialState = officialState;
    bool tempReadState = refButton.readPin();
    if(lastRawRead != tempReadState){
      changeDetect = millis();
      currentState = State::CHECKING;
    }
    if((millis() - changeDetect) >= refBounceTime){
      officialState = tempReadState;
      currentState = State::IDLE;
    }else{
     currentState = State::CHECKING; 
    }
    lastRawRead = tempReadState;
  }
  bool Debouncer::fall(){
  bool triggered = false;
  if(initialState == HIGH && officialState == LOW){
    triggered = true;
  }
  return triggered;
  }
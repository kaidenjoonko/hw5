#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

bool backtracking(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched, 
    size_t day,
    vector<int>& numShifts
);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    // 1. Establish d days, w possible workers
    size_t w = avail[0].size();
    size_t d = avail.size();


    sched.resize(d);

    vector<int> numShifts(w, 0);


    // 3. Start backtracking process
    if(backtracking(avail, dailyNeed, maxShifts, sched, 0, numShifts)){
        return true;
    }
    return false;
}

bool backtracking(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched, 
    size_t day,
    vector<int>& numShifts
){
  //base case
  if(day == sched.size()){
    return true;
  }

  if(sched[day].size() == dailyNeed){
    return backtracking(avail, dailyNeed, maxShifts, sched, day+1, numShifts);
  }

  for(size_t w = 0; w < avail[0].size(); w++){
    bool wAvail = avail[day][w];
    if(!wAvail) continue;

    int wNumShift = numShifts[w];
    if(maxShifts <= wNumShift) continue;

    bool wSched = false;
    for(vector<Worker_T>::iterator it = sched[day].begin(); it!=sched[day].end(); ++it){
      if(*it == w){
        wSched = true;
        break;
      }
    }
    if(wSched) continue;

    sched[day].push_back(w);
    numShifts[w]++;

    if(backtracking(avail, dailyNeed, maxShifts, sched, day, numShifts)) return true;

    sched[day].pop_back();
    numShifts[w]--;
  }
  return false;
}
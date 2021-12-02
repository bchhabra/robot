#pragma once

#ifdef PROTOTYPE

#include <NewPing.h>

#define MAX_DISTANCE 100
#define SCAN_INTERVAL 35
#define MEDIAN_ITERATIONS 5

namespace SonarSensors {

    struct {
        unsigned long nextScan = 0;
        uint8_t current = 0;
    } iteration;

    struct {
        unsigned int results[MEDIAN_ITERATIONS];
        unsigned long finalResult = 0;

        void calculateMedian() {
            unsigned int uS[MEDIAN_ITERATIONS];
            uint8_t j, it = MEDIAN_ITERATIONS;
            uS[0] = NO_ECHO;
            for (uint8_t i = 0; i < it; i++) { // Loop through iteration results.
                if (results[i] != NO_ECHO) { // Ping in range, include as part of median.
                    if (i > 0) {          // Don't start sort till second ping.
                        for (j = i; j > 0 && uS[j - 1] < results[i]; j--) { // Insertion sort loop.
                            uS[j] = uS[j - 1];                         // Shift ping array to correct position for sort insertion.
                        }
                    } else {
                        j = 0;         // First ping is sort starting point.
                    }
                    uS[j] = results[i];        // Add last ping to array in sorted position.
                } else {
                    it--;            // Ping out of range, skip and don't include as part of median.
                }
            }
            finalResult = uS[it >> 1];
        }
    } cycle;
    
    byte sensorIndex = 0;
    NewPing sensors[] = {
        NewPing(FRONT_LEFT_SONAR_TRIGGER, FRONT_LEFT_SONAR_ECHO, MAX_DISTANCE), 
        NewPing(FRONT_RIGHT_SONAR_TRIGGER, FRONT_RIGHT_SONAR_ECHO, MAX_DISTANCE)
        };
    bool obstacleFound = false;
    bool skipOneLoop = false;

    unsigned long getResult() {
        return cycle.finalResult;
    }

    void cycleComplete() {
        cycle.calculateMedian(); // calculate and store the median value
        obstacleFound = true; // signal the main loop that scan has finished
    }

    void echoCheck() {
        if (sensors[sensorIndex].check_timer()) {
            cycle.results[iteration.current] = sensors[sensorIndex].ping_result / US_ROUNDTRIP_CM;
        }
    }

    void triggerPing() {
        sensors[0].timer_stop();
        sensors[1].timer_stop();
        sensors[sensorIndex].ping_timer(echoCheck);
    }

    void reset() {
        iteration.nextScan = millis() + SCAN_INTERVAL;
        iteration.current = -1;
        sensorIndex = 0;
    }

    void setup() {
        iteration.nextScan = millis() + 1000;
        iteration.current = -1;
    }

    void loop(unsigned long currentTime) {
        if (skipOneLoop) {
            skipOneLoop = false;
            return;
        }
        if (currentTime >= iteration.nextScan) {
            iteration.nextScan = currentTime + SCAN_INTERVAL;
    
            if (iteration.current == (MEDIAN_ITERATIONS - 1)) {
                cycleComplete();
                ++sensorIndex %= 2;
                skipOneLoop = true; // give strategy the chance to run with the results of this cycle's scan before next cycle starts
                iteration.current = -1;
            } else {
                ++iteration.current %= MEDIAN_ITERATIONS;
                triggerPing();
            }
        }
    }

}
#endif

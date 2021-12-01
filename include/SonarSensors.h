#pragma once

#ifdef PROTOTYPE

#include <NewPing.h>

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
    } cycle;
    
    byte sensorIndex = 0;
    NewPing sensors[] = {NewPing(FRONT_LEFT_SONAR_TRIGGER, FRONT_LEFT_SONAR_ECHO), NewPing(FRONT_RIGHT_SONAR_TRIGGER, FRONT_RIGHT_SONAR_ECHO)};
    bool obstacleFound = false;

    void echoCheck();

    unsigned long getResult() {
        return cycle.finalResult;
    }

    unsigned long calculateMedian() { // All iterations complete, calculate the median.
        unsigned int uS[MEDIAN_ITERATIONS];
        uint8_t j, it = MEDIAN_ITERATIONS;
        uS[0] = NO_ECHO;
        for (uint8_t i = 0; i < it; i++) { // Loop through iteration results.
            if (cycle.results[i] != NO_ECHO) { // Ping in range, include as part of median.
                if (i > 0) {          // Don't start sort till second ping.
                    for (j = i; j > 0 && uS[j - 1] < cycle.results[i]; j--) { // Insertion sort loop.
                        uS[j] = uS[j - 1];                         // Shift ping array to correct position for sort insertion.
                    }
                } else {
                    j = 0;         // First ping is sort starting point.
                }
                uS[j] = cycle.results[i];        // Add last ping to array in sorted position.
            } else {
                it--;            // Ping out of range, skip and don't include as part of median.
            }
        }
        return uS[it >> 1];
    }

    void cycleComplete() {
        cycle.finalResult = calculateMedian(); // store the median value
        obstacleFound = true; // signal the main loop that scan has finished
    }

    void triggerPing() {
        sensors[0].timer_stop();
        sensors[1].timer_stop();
        sensors[sensorIndex].ping_timer(echoCheck);
    }

    void echoCheck() {
        if (sensors[sensorIndex].check_timer()) {
            cycle.results[iteration.current] = sensors[sensorIndex].ping_result / US_ROUNDTRIP_CM;
        }
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
        if (currentTime >= iteration.nextScan) {
            if (iteration.current == (MEDIAN_ITERATIONS - 1)) {
                cycleComplete();
                ++sensorIndex %= 2;
            }
            ++iteration.current %= MEDIAN_ITERATIONS;
            triggerPing();
            iteration.nextScan = currentTime + SCAN_INTERVAL;
        }
    }

    // void loop() {
    //     for (uint8_t i = 0; i < MEDIAN_ITERATIONS; i++) { // Loop through all the iterations.
    //         if (millis() >= pingTimer[i]) {          // Is it this iteration's time to ping?
    //             pingTimer[i] += SCAN_INTERVAL * MEDIAN_ITERATIONS; // Set next time this sensor will be pinged.
    //             if (i == 0 && currentIteration == MEDIAN_ITERATIONS - 1) sensorCycleComplete(); // Sensor ping cycle complete, do something with the results.
    //             currentIteration = i;        // Sensor being accessed.
    //             cm[currentIteration] = 0;    // Make distance zero in case there's no ping echo for this iteration.
    //             ping(); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).
    //             break;
    //         }
    //     }
    //   }

}
#endif

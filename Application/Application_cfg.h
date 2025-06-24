/*
 * Application_cfg.h
 *
 *  Created on: Jun 23, 2025
 *      Author: moham
 */

#ifndef APPLICATION_CFG_H_
#define APPLICATION_CFG_H_

/********************************************************
 * static configurations
 ********************************************************/

/* configure number of seats */
#define NUMBER_OF_SEATS (1U)

/* Seat IDs from pbcfg file */
#define SEAT_ONE_ID (0U)
#define SEAT_TWO_ID (1U)

/* configure modes temperatures */
#define SEAT_HEATER_LOW_TEMP ((uint32) 25U)
#define SEAT_HEATER_MEDIUM_TEMP ((uint32) 30U)
#define SEAT_HEATER_HIGH_TEMP ((uint32) 35U)

/* configure the margin between required and actual temperatures for each heater intensity */
#define SEAT_HEATER_LOW_INTENSITY_TEMP_MARGIN (2U)
#define SEAT_HEATER_MEDIUM_INTENSITY_TEMP_MARGIN (5U)
#define SEAT_HEATER_HIGH_INTENSITY_TEMP_MARGIN (10U)

/* static configuration for periodic tasks delay time */
#define LM35TEMP_SENSOR_START_CONVERSION_TASK_DELAY_MS (250U)
#define DELAY_TASK_DELAY_MS (1000U)
#define RUN_TIME_MEASURMENTS_TASK_DELAY_MS (1000U)

/* Macros to enable or disable Tasks */
#define APPLICATION_TASK_ON (1U)
#define APPLICATION_TASK_OFF (0U)

/* enable or disable run time measurements task */
#define RUN_TIME_MEASURMENT_TASK_ENABLE APPLICATION_TASK_ON


#endif /* APPLICATION_CFG_H_ */

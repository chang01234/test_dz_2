//------------------------------------------------------------------------------
// Module:      gen_pimage
//------------------------------------------------------------------------------
// Description: Automatic code generation of pimage image variables
//
//------------------------------------------------------------------------------
// Copyright:    Dometic
//
//               This source file and the information contained in it are
//               confidential and proprietary to Dometic. The reproduction or
//               disclosure, in whole or in part, to anyone outside of Dometic
//               without the written approval of a Dometic officer under a
//               Non-Disclosure Agreement is expressly prohibited.
//
//               All rights reserved
//------------------------------------------------------------------------------
#ifndef GEN_PIMAGE_H
#define GEN_PIMAGE_H

//------------------------------------------------------------------------------
// Application Specific Public Types
//------------------------------------------------------------------------------
// Process image enum for all LDIs, LDOs, LAIs, LAOs, NDIs, NDOs, NAIs, NAOs,
// and VARs included in the PImage.
//
// Entries must be stuff between xxx_START's and xxx_END's. Never remove any of
// the xxx_START and xxx_END enums. There must always be at least one entry
// between xxx_START's and xxx_END's.
//
// Where indicated, variable indexes must maintain the <eType> ordering
typedef enum
{
    // START OF AUTOMATIC CODE GENERATION - DO NOT MODIFY MANUALLY
	LDI_START = 0,

    // LDI
    LDI_IMU1_INT,                                 // [UINT8] :                  IMU1 interrupt request
    LDI_IMU2_INT,                                 // [UINT8] :                  IMU2 interrupt request
    LDI_MR2_IIFC,                                 // [UINT8] :                  MR2 index pin
    LDI_PHA_OCP,                                  // [UINT8] :                  Phase A overcurrent prot
    LDI_PHB_OCP,                                  // [UINT8] :                  Phase B overcurrent prot
    LDI_PHC_OCP,                                  // [UINT8] :                  Phase C overcurrent prot
    LDI_CAN_PWR_SNS,                              // [UINT8] :                  CAN power
    LDI_PWR_EN_BRG,                               // [UINT8] :                  Bridge power from uC
    LDI_INPUT_OCP,                                // [UINT8] :                  Battery overcurrent prot
    LDI_STO,                                      // [UINT8] :                  STO
    LDI_GPI,                                      // [UINT8] :                  General purpose input
    LDI_FILL1,                                    // [UINT8]

	LDI_END,


	LDO_START,

    // LDO
    LDO_PWR_UC_LATCH,                             // [UINT8] :                  uC power latch
    LDO_PWR_EN_BRG,                               // [UINT8] :                  Bridge power
    LDO_IMU_RESET,                                // [UINT8] :                  MTI-2 reset
    LDO_OCP_RESET,                                // [UINT8] :                  Overcurrent fault reset
    LDO_MRAM_WP,                                  // [UINT8] :                  MRAM write protect
    LDO_MRAM_HOLD,                                // [UINT8] :                  MRAM hold
    LDO_WATCH_DOG,                                // [UINT8] :                  Bridge watchdog
    LDO_GPO,                                      // [UINT8] :                  General purpose output

	LDO_END,


	LAI_START,

    // LAI
    LAI_TEMP_EXT1,                                // [IFLOAT32] :               External temp 1
    LAI_TEMP_EXT2,                                // [IFLOAT32] :               External temp 2
    LAI_PHA_TEMP,                                 // [IFLOAT32] :               Phase A temp
    LAI_PHB_TEMP,                                 // [IFLOAT32] :               Phase B temp
    LAI_PHC_TEMP,                                 // [IFLOAT32] :               Phase C temp
    LAI_BRG_VOLTS,                                // [IFLOAT32] :               Bridge voltage
    LAI_BATTERY_V,                                // [IFLOAT32] :               Battery voltage
    LAI_HEATSINK_TEMP,                            // [IFLOAT32] :               Heatsink temp
    LAI_24V_PROT_VOLTS,                           // [IFLOAT32] :               24V protect voltage
    LAI_INPUT_SNS_CURR,                           // [IFLOAT32] :               Battery current
    LAI_PHA_CURRENT,                              // [IFLOAT32] :               Phase A current
    LAI_PHB_CURRENT,                              // [IFLOAT32] :               Phase B current
    LAI_PHC_CURRENT,                              // [IFLOAT32] :               Phase C current
    LAI_PHA_VOLTS,                                // [IFLOAT32] :               Phase A voltage
    LAI_PHB_VOLTS,                                // [IFLOAT32] :               Phase B voltage
    LAI_PHC_VOLTS,                                // [IFLOAT32] :               Phase C voltage
    LAI_HW_BUILD_ID_CONTROL,                      // [IFLOAT32] :               Control board build ID
    LAI_HW_BUILD_ID_POWER,                        // [IFLOAT32] :               Power board build ID
    LAI_5V_POWER_RAIL,                            // [IFLOAT32] :               5v power rail
    LAI_5V_NEG_RAIL,                              // [IFLOAT32] :               5v neg rail voltage
    LAI_5V_PROT_RAIL,                             // [IFLOAT32] :               5v prot rail
	LAI_END,


	LAO_START,

    // LAO
    LAO_CHARGE_PUMP,                              // [IFLOAT32] :               Charge pump PWM
    LAO_PHA_A,                                    // [IFLOAT32] :               Phase A PWM
    LAO_PHA_B,                                    // [IFLOAT32] :               Phase B PWM
    LAO_PHA_C,                                    // [IFLOAT32] :               Phase C PWM

	LAO_END,


	VAR_START,

    // VAR

    // TEST
    VAR_PREDRIVER_DISABLE,                        // [IUINT16] :                >>>>>> STOP <<<<<<
    VAR_SPEED_SHUTDOWN,                           // [IUINT16] :                Speed shutdown

    // STACK AND SYSTEM STATUS VARIABLES
    VAR_RESET_REASON,                             // [IUINT16] :                Reset reason
    VAR_STACK_PEAK,                               // [IUINT16] :                Stack peak usage
    VAR_STACK_AVERAGE,                            // [IUINT16] :                Stack average usage
    VAR_1MS_TICK_COUNT_MAX,                       // [IUINT16] :                1ms tick max count


    // CAN

    // RX FIFO
    VAR_CAN_RX_QUEUE_PEAK,                        // [IUINT16] :                CAN Rx Queue Peak
    VAR_CAN_RX_QUEUE_DROP_CNT,                    // [IUINT16] :                CAN Rx Queue Drops


    // TX FIFO
    VAR_CAN_TX_QUEUE_PEAK,                        // [IUINT16] :                CAN Tx Queue Peak
    VAR_CAN_TX_QUEUE_DROP_CNT,                    // [IUINT16] :                CAN Tx Queue Drops

	VAR_END,


	VARF_START,

    // VARF

    // Motor vars
    VARF_TARGET_IQ,                               // [IFLOAT32] :               Target iq
    VARF_TARGET_ID,                               // [IFLOAT32] :               Target id
    VARF_TARGET_VOLTAGE,                          // [IFLOAT32] :               Target voltage
    VARF_FOC_ID,                                  // [IFLOAT32] :               Id
    VARF_FOC_IQ,                                  // [IFLOAT32] :               Iq
    VARF_FOC_VD,                                  // [IFLOAT32] :               Vd
    VARF_FOC_VQ,                                  // [IFLOAT32] :               Vq
    VARF_SPEED,                                   // [IFLOAT32] :               Speed
    VARF_POSITION,                                // [IFLOAT32] :               Motor elec angle
    VARF_MGL_FAIL_ANGLE,                          // [IFLOAT32] :               Mag low field fail angle
    VARF_MGH_FAIL_ANGLE,                          // [IFLOAT32] :               Mag high field fail angle

    // State vars
    VARF_MOTOR_MODE,                              // [IFLOAT32] :               Motor mode
    VARF_MOTOR_DRV_STATE,                         // [IFLOAT32] :               Motor driver state
    VARF_POS_READY,                               // [IFLOAT32] :               Position sensor ready?
    VARF_PHASE_CUR_CALIBRATED,                    // [IFLOAT32] :               Phase current calibrated?
    VARF_BATT_CUR_CALIBRATED,                     // [IFLOAT32] :               Battery current calibrated?

    // Current cal vars
    VARF_CURRENT_LOOP_TICS,                       // [IFLOAT32] :               Current loop ticks
    VARF_COMM_LOOP_TICS,                          // [IFLOAT32] :               Commutation loop ticks
    VARF_CURRENT_LOOP_PERCENT,                    // [IFLOAT32] :               Current loop percent
    VARF_COMM_LOOP_PERCENT,                       // [IFLOAT32] :               Commutation loop percent

    // Current cal vars
    VARF_CURRENT_CAL_PHASE,                       // [IFLOAT32] :               Current cal phase
    VARF_CURRENT_CAL_INDEX,                       // [IFLOAT32] :               Current cal index
    VARF_CURRENT_CAL_DUTY,                        // [IFLOAT32] :               Current cal duty
    VARF_CURRENT_CAL_CURRENT,                     // [IFLOAT32] :               Current cal value

    // IMU

    // MTI2
    VAR_MTI2_EULER_ANGLE_X,                       // [IFLOAT32] :               Euler Angle X
    VAR_MTI2_EULER_ANGLE_Y,                       // [IFLOAT32] :               Euler Angle Y
    VAR_MTI2_EULER_ANGLE_Z,                       // [IFLOAT32] :               Euler Angle Z
    VAR_MTI2_ROTATIONAL_ACCL_X,                   // [IFLOAT32] :               Rotational Speed X
    VAR_MTI2_ROTATIONAL_ACCL_Y,                   // [IFLOAT32] :               Rotational Speed Y
    VAR_MTI2_ROTATIONAL_ACCL_Z,                   // [IFLOAT32] :               Rotational Speed Z
    VAR_MTI2_ACCL_X,                              // [IFLOAT32] :               Acceleration X
    VAR_MTI2_ACCL_Y,                              // [IFLOAT32] :               Acceleration Y
    VAR_MTI2_ACCL_Z,                              // [IFLOAT32] :               Acceleration Z

	VARF_END,


	NDI_START,

    // NDI
    NDI_HIGH_RPM_EN,                              // [UINT8] :                  Enable HIGH RPM Target
    NDI_MGL_FAIL_FLAG,                            // [UINT8] :                  Mag Low field fail flag
    NDI_MGH_FAIL_FLAG,                            // [UINT8] :                  Mag High field fail flag
    NDI_VACUUM_SENSOR_TYPE,                       // [UINT8] :                  Vacuum sensor type

	NDI_END,


	NDO_START,

    // NDO
    NDO_RESERVED0,                                // [UINT8] :                  Reserved
    NDO_RESERVED1,                                // [UINT8] :                  Reserved

	NDO_END,


	NAI_START,

    // NAI
    NAI_RPM_CMD,                                  // [ISINT16] :                RPM command
    NAI_MIN_BATT_CURRENT,                         // [ISINT16] :                Min battery current
    NAI_MAX_BATT_CURRENT,                         // [ISINT16] :                Max battery current
    NAI_RESERVED0,                                // [IUINT16] :                Reserved

	NAI_END,


	NAI32_START,

    // NAI32
    NAI32_RESERVED1,                              // [IUINT32] :                Reserved

	NAI32_END,


	NAO_START,

    // NAO

    // HCU_FEEDBACK
    NAO_STATE,                                    // [IUINT16] :                HCU state
    NAO_FAULT_SEVERITY,                           // [IUINT16] :                Fault severity
    NAO_RPM_FBK,                                  // [ISINT16] :                RPM feedback
    NAO_PRESSURE,                                 // [IUINT16] :                Pressure
    NAO_HEMI_ANGLE,                               // [ISINT16] :                Hemisphere angle
    NAO_UPPER_BEARING_TEMP,                       // [ISINT16] :                Upper bearing temp

    // IMU
    NAO_ROLL_RATE_X,                              // [ISINT16] :                Roll rate X
    NAO_ROLL_RATE_Y,                              // [ISINT16] :                Roll rate Y
    NAO_ROLL_RATE_Z,                              // [ISINT16] :                Roll rate Z
    NAO_ACCL_X,                                   // [ISINT16] :                Acceleration X
    NAO_ACCL_Y,                                   // [ISINT16] :                Acceleration Y
    NAO_ACCL_Z,                                   // [ISINT16] :                Acceleration Z

	NAO_END,


	NAO32_START,

    // NAO32
    NAO32_RESERVED1,                              // [IUINT32] :                Reserved
    NAO32_RESERVED2,                              // [IUINT32] :                Reserved
	NAO32_END


    // END OF AUTOMATIC CODE GENERATION - DO NOT MODIFY MANUALLY
    // -----------------
} PIMAGE_eTABLE;


#endif // GEN_PIMAGE_H

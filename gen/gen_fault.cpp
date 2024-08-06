//------------------------------------------------------------------------------
// Module:      gen_fault
//------------------------------------------------------------------------------
// Description: Automatic code generation of fault table
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

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include <string.h>
#include "gen_fault.h"
#include "Faults.h"
#include "nmea_tools.h"
#include "nmea_pgn_n2k.h"


// <START OF AUTOMATIC CODE GENERATION>

const FAULTS_zINFO fault_info[FAULTS_TABLE_COUNT] = 
{
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//    u32Code,  u8FailureMode,                                    u8Severity,                        u8Group,                           u8StatusGroup,                bReport,       u7Reserved
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    // BATTERY FAULTS
    { 0x0,      N2KPGN_FMI_BELOW_NORMAL_RANGE_MOST_SEVERE,        FAULT_SEVERITY_CRIT_UNCONTROLLED,  FAULT_GROUP_BATTERY,               0,                            FALSE,         0 },    // FAULTS_FAULT_BATTERY_LOW_VOLTAGE= 0,
    { 0x0,      N2KPGN_FMI_ABOVE_NORMAL_RANGE_MOST_SEVERE,        FAULT_SEVERITY_CRIT_UNCONTROLLED,  FAULT_GROUP_BATTERY,               0,                            FALSE,         0 },    // FAULTS_FAULT_BATTERY_HIGH_VOLTAGE,
    { 0x0,      N2KPGN_FMI_ABOVE_NORMAL_RANGE_MOST_SEVERE,        FAULT_SEVERITY_CRIT_UNCONTROLLED,  FAULT_GROUP_BATTERY,               0,                            FALSE,         0 },    // FAULTS_FAULT_BATTERY_OVERCURRENT,
    { 0x0,      N2KPGN_FMI_DATA_INCORRECT,                        FAULT_SEVERITY_CRIT_UNCALIBRATED,  FAULT_GROUP_MOTOR,                 0,                            FALSE,         0 },    // FAULTS_FAULT_BATTERY_CURRENT_UNCAL,

    // Motor Faults
    { 0x0,      N2KPGN_FMI_ABOVE_NORMAL_RANGE_MOST_SEVERE,        FAULT_SEVERITY_CRIT_UNCONTROLLED,  FAULT_GROUP_MOTOR,                 0,                            FALSE,         0 },    // FAULTS_FAULT_MOTOR_OVERSPEED,
    { 0x0,      N2KPGN_FMI_ABOVE_NORMAL_RANGE_MOST_SEVERE,        FAULT_SEVERITY_CRIT_UNCONTROLLED,  FAULT_GROUP_MOTOR,                 0,                            FALSE,         0 },    // FAULTS_FAULT_MOTOR_PHASE_OVERCURRENT,
    { 0x0,      N2KPGN_FMI_ABOVE_NORMAL_RANGE_MOST_SEVERE,        FAULT_SEVERITY_CRIT_UNCONTROLLED,  FAULT_GROUP_MOTOR,                 0,                            FALSE,         0 },    // FAULTS_FAULT_MOTOR_CONTROL_CURRENT_ERR,
    { 0x0,      N2KPGN_FMI_ABOVE_NORMAL_RANGE_MOST_SEVERE,        FAULT_SEVERITY_CRIT_UNCONTROLLED,  FAULT_GROUP_MOTOR,                 0,                            FALSE,         0 },    // FAULTS_FAULT_MOTOR_BRIDGE_OVERTEMP,
    { 0x0,      N2KPGN_FMI_BELOW_NORMAL_RANGE_MOST_SEVERE,        FAULT_SEVERITY_CRIT_UNCONTROLLED,  FAULT_GROUP_MOTOR,                 0,                            FALSE,         0 },    // FAULTS_FAULT_MOTOR_MOTION,
    { 0x0,      N2KPGN_FMI_DATA_INCORRECT,                        FAULT_SEVERITY_CAUTION,            FAULT_GROUP_MOTOR,                 0,                            FALSE,         0 },    // FAULTS_FAULT_MOTOR_POSITION_COMM_FAIL,
    { 0x0,      N2KPGN_FMI_DATA_INCORRECT,                        FAULT_SEVERITY_CRIT_UNCALIBRATED,  FAULT_GROUP_MOTOR,                 0,                            FALSE,         0 },    // FAULTS_FAULT_MOTOR_POSITION_UNCAL,
    { 0x0,      N2KPGN_FMI_DATA_INCORRECT,                        FAULT_SEVERITY_CRIT_UNCALIBRATED,  FAULT_GROUP_MOTOR,                 0,                            FALSE,         0 },    // FAULTS_FAULT_MOTOR_PHASE_CURRENT_UNCAL,

    // Comm Faults
    { 0x0,      N2KPGN_FMI_DATA_INCORRECT,                        FAULT_SEVERITY_CAUTION,            FAULT_GROUP_COMM,                  0,                            FALSE,         0 },    // FAULTS_FAULT_COMM_GCU_HERATBEAT,
    { 0x0,      N2KPGN_FMI_DATA_INCORRECT,                        FAULT_SEVERITY_NONE,               FAULT_GROUP_COMM,                  0,                            FALSE,         0 },    // FAULTS_FAULT_COMM_PRESSURE_FAIL,
};

// <END OF AUTOMATIC CODE GENERATION>

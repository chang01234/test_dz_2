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
#ifndef GEN_FAULT_H
#define GEN_FAULT_H

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "StdDometic.h"
#include "Faults.h"


// <START OF AUTOMATIC CODE GENERATION>
typedef enum 
{
    // BATTERY FAULTS
    FAULTS_FAULT_BATTERY_LOW_VOLTAGE = 0,         
    FAULTS_FAULT_BATTERY_HIGH_VOLTAGE,            
    FAULTS_FAULT_BATTERY_OVERCURRENT,             
    FAULTS_FAULT_BATTERY_CURRENT_UNCAL,           
    // Motor Faults
    FAULTS_FAULT_MOTOR_OVERSPEED,                 
    FAULTS_FAULT_MOTOR_PHASE_OVERCURRENT,         
    FAULTS_FAULT_MOTOR_CONTROL_CURRENT_ERR,       
    FAULTS_FAULT_MOTOR_BRIDGE_OVERTEMP,           
    FAULTS_FAULT_MOTOR_MOTION,                    
    FAULTS_FAULT_MOTOR_POSITION_COMM_FAIL,        
    FAULTS_FAULT_MOTOR_POSITION_UNCAL,            
    FAULTS_FAULT_MOTOR_PHASE_CURRENT_UNCAL,       
    // Comm Faults
    FAULTS_FAULT_COMM_GCU_HERATBEAT,              
    FAULTS_FAULT_COMM_PRESSURE_FAIL,              

    FAULTS_TABLE_COUNT,
}
fault_table_t;

extern const FAULTS_zINFO fault_info[FAULTS_TABLE_COUNT];

// fault_severity_t
typedef enum 
{
    FAULT_SEVERITY_NONE = 0,                      // none
    FAULT_SEVERITY_CAUTION,                       // caution
    FAULT_SEVERITY_WARNING,                       // warning
    FAULT_SEVERITY_CRIT_UNCALIBRATED,             // uncalibrated
    FAULT_SEVERITY_CRIT_CONTROLLED,               // control stop
    FAULT_SEVERITY_CRIT_UNCONTROLLED,             // uncontrol stop
}
fault_severity_t;

// fault_group_t
typedef enum 
{
    FAULT_GROUP_BATTERY = 0,                      
    FAULT_GROUP_MOTOR,                            
    FAULT_GROUP_COMM,                             
    FAULT_GROUP_ALL,                              
}
fault_group_t;


PACKED_PUSH()
typedef struct PACKED_ATTR
{
    uint16 count;
    uint16 key_on_cycle_first;
    uint16 key_on_cycle_last;
    uint32 key_on_time_first;
    uint32 key_on_time_last;
    float32 target_rpm;
    float32 actual_rpm;
    float32 iq;
    float32 id;
    float32 battery_current;
    float32 state;
    float32 battery_voltage;
} fault_record_t;
PACKED_POP()

typedef struct
{
    uint16 version;
    uint16 reserved;
    fault_record_t record[FAULTS_TABLE_COUNT];
} fault_record_table_t;

// <END OF AUTOMATIC CODE GENERATION>

#endif  // GEN_FAULT_H

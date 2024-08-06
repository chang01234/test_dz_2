//------------------------------------------------------------------------------
// Module:      gen_config
//------------------------------------------------------------------------------
// Description: Defines and manages all configuration parameters for the device.
//
//              Byte alignment for all parameter tables must meet the following
//              conditions for compatibility with CCP.
//              - 1byte parameters must be 1byte aligned
//              - 2byte parameters must be 2byte aligned
//              - 4byte parameters must be 4byte aligned
//              - Parameter tables must be 4byte aligned
//
//              For future expandability there every parameter table should
//              contain several 4byte reserved slots. This ensures
//              the crc will not become corrupted, forcing the entire table
//              to default values, when a new parameter is added.
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
#include "gen_config.h"


// <START OF AUTOMATIC CODE GENERATION>

// Default system configuration table
const CONFIG_zSYSTEM CONFIG_zSystem_Default =
{
    0,                                                                                              // 0              - version;
    0,                                                                                              // 0              - reserved;
    0,                                                                                              // 0              - reserved2;
};

// Default foc configuration table
const CONFIG_zFOC CONFIG_zFoc_Default =
{
    0,                                                                                              // 0              - version;
    0,                                                                                              // 0              - reserved;
    5,                                                                                              // 5              - mode;
    0.9F,                                                                                           //                - antiClipScaler;
    500.0F,                                                                                         // rpm/s          - speedSlew;
    100.0F,                                                                                         // V/s            - voltageSlew;
    0.002F,                                                                                         // s              - currentTau;
    0.3F,                                                                                           // s              - speedTau;
    4900.0F,                                                                                        // rpm            - speedShutdown;
    200.0F,                                                                                         // A              - phaseCurrShutdown;
    100.0F,                                                                                         // A              - battCurrShutdown;
    200.0F,                                                                                         // A              - currErrorShutdown;
    20000,                                                                                          // 20000hz        - commutationFreq;
    10000,                                                                                          // 10000hz        - currentFreq;
    1000,                                                                                           // 1000hz         - speedFreq;
    150.0F,                                                                                         // A              - iqMax;
    80.0F,                                                                                          // A              - iBattMax;
    -50.0F,                                                                                         // A              - iBattMin;
    0.052F,                                                                                         // V/A            - currentKa;
    25.3F,                                                                                          // V*s/Vka        - currentKb;
    0.0,                                                                                            // A/rpm          - speedKp;
    0.0,                                                                                            // A*s/rpm        - speedKi;
    0.008F,                                                                                         // s              - phaseCurrTau;
};

// Default predriver configuration table
const CONFIG_zPREDRIVER CONFIG_zPredriver_Default =
{
    0,                                                                                              // 0              - version;
    200,                                                                                            // 200khz         - frequency;
    30.0F,                                                                                          // V              - overVoltage;
    10.0F,                                                                                          // V              - underVoltage;
    0,                                                                                              // 0              - reserved2;
};

// Default mr sensors configuration table
const CONFIG_zMRSENSOR CONFIG_zMrsensor_Default =
{
    0,                                                                                              // 0              - version;
    1,                                                                                              // 1              - XTrimming;
    0,                                                                                              // 0              - YTrimming;
    0,                                                                                              // 0              - mglt;
    0,                                                                                              // 0              - reserved2;
    3.5F,                                                                                           //                - sideShaftFieldRatio;
};

// Default system configuration table
const CONFIG_zOPTIONS CONFIG_zOptions_Default =
{
    0,                                                                                              // 0              - version;
    0,                                                                                              // 0              - enableDiagMsg;
    0,                                                                                              // 0              - enableMti2;
    0,                                                                                              // 0              - enableIcm42688;
    30,                                                                                             // 30sec          - calibWaitTime;
    0,                                                                                              // 0              - reserved2;
};

//------------------------------------------------------------------------------
// Public Variables
//------------------------------------------------------------------------------

CONFIG_zSYSTEM                                    CONFIG_zSystem;                                   // System table used by the application
CONFIG_zFOC                                       CONFIG_zFoc;                                      // FOC table used by the application
CONFIG_zPREDRIVER                                 CONFIG_zPredriver;                                // Predriver table used by the application
CONFIG_zMRSENSOR                                  CONFIG_zMrsensor;                                 // MR Sensors table used by the application
CONFIG_zOPTIONS                                   CONFIG_zOptions;                                  // System table used by the application

CONFIG_zSYSTEM                                    CONFIG_zSystem_Cache;                             // System table used for remote editing
CONFIG_zFOC                                       CONFIG_zFoc_Cache;                                // FOC table used for remote editing
CONFIG_zPREDRIVER                                 CONFIG_zPredriver_Cache;                          // Predriver table used for remote editing
CONFIG_zMRSENSOR                                  CONFIG_zMrsensor_Cache;                           // MR Sensors table used for remote editing
CONFIG_zOPTIONS                                   CONFIG_zOptions_Cache;                            // System table used for remote editing

//------------------------------------------------------------------------------
// Local prototypes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Function:   Config_FocRange_Auto_Gen
//------------------------------------------------------------------------------
// Purpose:    Verify and correct cache table parameter ranges.
//------------------------------------------------------------------------------
// Notes:      None.
//------------------------------------------------------------------------------
// Parameters: None.
//------------------------------------------------------------------------------
// Return:     None.
//------------------------------------------------------------------------------
void Config_FocRange_Auto_Gen( void )
{
    CAP_MIN_MAX(    CONFIG_zFoc_Cache.antiClipScaler, 0.0f, 1.0f);                                                                // Min:           Max: 
    CAP_MIN_MAX(    CONFIG_zFoc_Cache.speedShutdown, 0.0f, 4900.0f);                                                              // Min: rpm       Max: rpm
}

// <END OF AUTOMATIC CODE GENERATION>

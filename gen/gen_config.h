//------------------------------------------------------------------------------
// Module:      gen_config
//------------------------------------------------------------------------------
// Description: Automatic code generation of configuration parameters
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
#ifndef GEN_CONFIG_H
#define GEN_CONFIG_H

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "StdDometic.h"

// <START OF AUTOMATIC CODE GENERATION>
//------------------------------------------------------------------------------
// Public Types
//------------------------------------------------------------------------------

// System configuration table
typedef struct PACKED_ATTR
{
    uint16        version;                                                                          // Version
    uint16        reserved;                                                                         // Reserved
    uint32        reserved2[20];                                                                    // Reserved
}
CONFIG_zSYSTEM;

// FOC configuration table
typedef struct PACKED_ATTR
{
    uint16        version;                                                                          // Version
    uint16        reserved;                                                                         // Reserved
    uint32        mode;                                                                             // Motor control mode
    float32       antiClipScaler;                                                                   // Anti-clip scaler
    float32       speedSlew;                                                                        // rpm/s; RPM slew rate
    float32       voltageSlew;                                                                      // V/s; Voltage slew rate
    float32       currentTau;                                                                       // s; Current filter tau
    float32       speedTau;                                                                         // s; Speed filter tau
    float32       speedShutdown;                                                                    // rpm; Speed shutdown
    float32       phaseCurrShutdown;                                                                // A; Phase current shutdown
    float32       battCurrShutdown;                                                                 // A; Battery current shutdown
    float32       currErrorShutdown;                                                                // A; Current error shutdown
    uint32        commutationFreq;                                                                  // hz; Commutation freq
    uint32        currentFreq;                                                                      // hz; Current control freq
    uint32        speedFreq;                                                                        // hz; Speed control freq
    float32       iqMax;                                                                            // A; iq - max
    float32       iBattMax;                                                                         // A; Battery current - max
    float32       iBattMin;                                                                         // A; Battery current - min
    float32       currentKa;                                                                        // V/A; Current - Ka
    float32       currentKb;                                                                        // V*s/Vka; Current - Kb
    float32       speedKp;                                                                          // A/rpm; Speed - Kp
    float32       speedKi;                                                                          // A*s/rpm; Speed - Ki
    float32       phaseCurrTau;                                                                     // s; Phase current filter tau
}
CONFIG_zFOC;

// Predriver configuration table
typedef struct PACKED_ATTR
{
    uint16        version;                                                                          // Version
    uint16        frequency;                                                                        // khz; PWM frequency
    float32       overVoltage;                                                                      // V; Overvoltage level
    float32       underVoltage;                                                                     // V; Undervoltage level
    uint32        reserved2[20];                                                                    // Reserved
}
CONFIG_zPREDRIVER;

// MR Sensors configuration table
typedef struct PACKED_ATTR
{
    uint16        version;                                                                          // Version
    uint8         XTrimming;                                                                        // X-Axis Trimming
    uint8         YTrimming;                                                                        // Y-Axis Trimming
    uint8         mglt;                                                                             // Field Low Threshold
    uint16        reserved2;                                                                        // Reserved
    float32       sideShaftFieldRatio;                                                              // Side shaft field ratio
}
CONFIG_zMRSENSOR;

// System configuration table
typedef struct PACKED_ATTR
{
    uint16        version;                                                                          // Version
    uint8         enableDiagMsg;                                                                    // Diagnostic Message Enable
    uint8         enableMti2;                                                                       // Enable Mti2
    uint8         enableIcm42688;                                                                   // Enable Icm42688
    uint8         calibWaitTime;                                                                    // sec; Calib phase wait time
    uint32        reserved2;                                                                        // Reserved
}
CONFIG_zOPTIONS;

//------------------------------------------------------------------------------
// Public Variables
//------------------------------------------------------------------------------


extern CONFIG_zSYSTEM                             CONFIG_zSystem;
extern CONFIG_zFOC                                CONFIG_zFoc;
extern CONFIG_zPREDRIVER                          CONFIG_zPredriver;
extern CONFIG_zMRSENSOR                           CONFIG_zMrsensor;
extern CONFIG_zOPTIONS                            CONFIG_zOptions;

extern const CONFIG_zSYSTEM                       CONFIG_zSystem_Default;
extern const CONFIG_zFOC                          CONFIG_zFoc_Default;
extern const CONFIG_zPREDRIVER                    CONFIG_zPredriver_Default;
extern const CONFIG_zMRSENSOR                     CONFIG_zMrsensor_Default;
extern const CONFIG_zOPTIONS                      CONFIG_zOptions_Default;

extern CONFIG_zSYSTEM                             CONFIG_zSystem_Cache;
extern CONFIG_zFOC                                CONFIG_zFoc_Cache;
extern CONFIG_zPREDRIVER                          CONFIG_zPredriver_Cache;
extern CONFIG_zMRSENSOR                           CONFIG_zMrsensor_Cache;
extern CONFIG_zOPTIONS                            CONFIG_zOptions_Cache;

//------------------------------------------------------------------------------
// Public Functions
//------------------------------------------------------------------------------

extern uint8 *CONFIG_SystemAddr( void );
extern uint16 CONFIG_SystemSize( void );
extern void   CONFIG_SystemBackup( bool bBackupResult );
extern void   CONFIG_SystemRestore( bool bRestoreResult );
extern void   CONFIG_SystemRange( void );

extern uint8 *CONFIG_FocAddr( void );
extern uint16 CONFIG_FocSize( void );
extern void   CONFIG_FocBackup( bool bBackupResult );
extern void   CONFIG_FocRestore( bool bRestoreResult );
extern void   CONFIG_FocRange( void );

extern uint8 *CONFIG_PredriverAddr( void );
extern uint16 CONFIG_PredriverSize( void );
extern void   CONFIG_PredriverBackup( bool bBackupResult );
extern void   CONFIG_PredriverRestore( bool bRestoreResult );
extern void   CONFIG_PredriverRange( void );

extern uint8 *CONFIG_MrsensorAddr( void );
extern uint16 CONFIG_MrsensorSize( void );
extern void   CONFIG_MrsensorBackup( bool bBackupResult );
extern void   CONFIG_MrsensorRestore( bool bRestoreResult );
extern void   CONFIG_MrsensorRange( void );

extern uint8 *CONFIG_OptionsAddr( void );
extern uint16 CONFIG_OptionsSize( void );
extern void   CONFIG_OptionsBackup( bool bBackupResult );
extern void   CONFIG_OptionsRestore( bool bRestoreResult );
extern void   CONFIG_OptionsRange( void );


extern void Config_SystemRange_Auto_Gen( void );                                                    // System table auto-generated range check
extern void Config_FocRange_Auto_Gen( void );                                                       // FOC table auto-generated range check
extern void Config_PredriverRange_Auto_Gen( void );                                                 // Predriver table auto-generated range check
extern void Config_MrsensorRange_Auto_Gen( void );                                                  // MR Sensors table auto-generated range check
extern void Config_OptionsRange_Auto_Gen( void );                                                   // System table auto-generated range check
// <END OF AUTOMATIC CODE GENERATION>

#endif  // GEN_CONFIG_H

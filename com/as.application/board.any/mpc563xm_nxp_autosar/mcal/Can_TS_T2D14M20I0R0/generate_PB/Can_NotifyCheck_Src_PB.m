[!NOCODE!]
/**
  @file    Can_NotifyCheck_Src_PB.m
  @version 2.0.0

  @brief   AUTOSAR Can - macros.
  @details Macros
  
  Project AUTOSAR 3.0 MCAL
  Platform PA
  Peripheral FLEXCAN
  Dependencies 
  
  ARVersion 3.0.0
  ARRevision ASR_REL_3_0_REV_0003
  ARConfVariant
  SWVersion 2.0.0
  BuildVersion XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223

  (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
  All Rights Reserved.
*/
/*==================================================================================================
==================================================================================================*/
[!ENDNOCODE!]


[!/* avoid multiple inclusion */!]
[!IF "not(var:defined('CAN_NOTIFY_CHECK_SRC_PB_M'))"!]
[!VAR "CAN_NOTIFY_CHECK_SRC_PB_M"="'true'"!]

[!NOCODE!]
[!MACRO "CanRxFifoWarningNotification_PB"!]
    [!VAR "OuterLoopCounter" = "0"!]
    [!VAR "InnerLoopCounter" = "0"!]
    [!LOOP "CanConfigSet/*[1]/CanController/*"!]
        [!VAR "OuterLoopCounter" = "$OuterLoopCounter + 1"!]
        [!VAR "InnerLoopCounter" = "0"!]
        [!VAR "Matchcounter" = "0"!]
        [!IF "CanControllerRxFifoEnable = 'true'"!]
            [!VAR "Notification" = "CanRxFifoWarningNotification"!]
        [!ENDIF!]
        [!LOOP "../../../*[1]/CanController/*"!]
            [!IF "CanControllerRxFifoEnable = 'true'"!]
                [!IF "(normalize-space(CanRxFifoWarningNotification) != 'NULL_PTR') and 
                      (normalize-space(CanRxFifoWarningNotification) != '"NULL"') and 
                      (normalize-space(CanRxFifoWarningNotification) != 'NULL')"!]
                    [!VAR "InnerLoopCounter" = "$InnerLoopCounter + 1"!]
                    [!IF "$OuterLoopCounter >= $InnerLoopCounter"!]
                        [!IF "($Notification = CanRxFifoWarningNotification)"!]
                            [!VAR "Matchcounter" = "$Matchcounter + 1"!]
                        [!ENDIF!]
                    [!ENDIF!]
                [!ENDIF!]
            [!ENDIF!]
        [!ENDLOOP!]
        [!IF "$Matchcounter >= 1"!][!CODE!]
            [!IF "CanControllerRxFifoEnable = 'true'"!]
                [!"CanConfigSet/*[1]/CanController/*"!]
extern FUNC(void,CAN_CODE) [!"normalize-space(CanRxFifoWarningNotification)"!]( void);
            [!ENDIF!]
        [!ENDCODE!]
        [!ENDIF!]
    [!ENDLOOP!]
[!ENDMACRO!]

[!MACRO "CanRxFifoOverflowNotification_PB"!]
    [!VAR "OuterLoopCounter" = "0"!]
    [!VAR "InnerLoopCounter" = "0"!]
    [!LOOP "CanConfigSet/*[1]/CanController/*"!]
        [!VAR "OuterLoopCounter" = "$OuterLoopCounter + 1"!]
        [!VAR "InnerLoopCounter" = "0"!]
        [!VAR "Matchcounter" = "0"!]
        [!IF "CanControllerRxFifoEnable = 'true'"!]
            [!VAR "Notification" = "CanRxFifoOverflowNotification"!]
        [!ENDIF!]
        [!LOOP "../../../*[1]/CanController/*"!]
            [!IF "CanControllerRxFifoEnable = 'true'"!]
                [!IF "(normalize-space(CanRxFifoOverflowNotification) != 'NULL_PTR') and 
                      (normalize-space(CanRxFifoOverflowNotification) != '"NULL"') and 
                      (normalize-space(CanRxFifoOverflowNotification) != 'NULL')"!]
                    [!VAR "InnerLoopCounter" = "$InnerLoopCounter + 1"!]
                    [!IF "$OuterLoopCounter >= $InnerLoopCounter"!]
                        [!IF "($Notification = CanRxFifoOverflowNotification)"!]
                            [!VAR "Matchcounter" = "$Matchcounter + 1"!]
                        [!ENDIF!]
                    [!ENDIF!]
                [!ENDIF!]
            [!ENDIF!]
        [!ENDLOOP!]
        [!IF "$Matchcounter >= 1"!][!CODE!]
            [!IF "CanControllerRxFifoEnable = 'true'"!]
                [!"CanConfigSet/*[1]/CanController/*"!]
extern FUNC(void,CAN_CODE) [!"normalize-space(CanRxFifoOverflowNotification)"!]( void);
            [!ENDIF!]
        [!ENDCODE!]
        [!ENDIF!]
    [!ENDLOOP!]
[!ENDMACRO!]

[!MACRO "CanErrorControllerNotification_PB"!]
    [!VAR "OuterLoopCounter" = "0"!]
    [!VAR "InnerLoopCounter" = "0"!]
    [!LOOP "CanConfigSet/*[1]/CanController/*"!]
        [!VAR "OuterLoopCounter" = "$OuterLoopCounter + 1"!]
        [!VAR "InnerLoopCounter" = "0"!]
        [!VAR "Matchcounter" = "0"!]
            [!VAR "Notification" = "CanErrorControllerNotification"!]
        [!LOOP "../../../*[1]/CanController/*"!]
            [!IF "(normalize-space(CanErrorControllerNotification) != 'NULL_PTR') and 
                  (normalize-space(CanErrorControllerNotification) != '"NULL"') and 
                  (normalize-space(CanErrorControllerNotification) != 'NULL')"!]
                [!VAR "InnerLoopCounter" = "$InnerLoopCounter + 1"!]
                [!IF "$OuterLoopCounter >= $InnerLoopCounter"!]
                    [!IF "($Notification = CanErrorControllerNotification)"!]
                        [!VAR "Matchcounter" = "$Matchcounter + 1"!]
                    [!ENDIF!]
                [!ENDIF!]
            [!ENDIF!]
        [!ENDLOOP!]
        [!IF "$Matchcounter >= 1"!][!CODE!]
            [!"CanConfigSet/*[1]/CanController/*"!]
extern FUNC(void,CAN_CODE) [!"normalize-space(CanErrorControllerNotification)"!]( void);
        [!ENDCODE!]
        [!ENDIF!]
    [!ENDLOOP!]
[!ENDMACRO!]

[!ENDNOCODE!]
[!ENDIF!][!// avoid multiple inclusion ENDIF
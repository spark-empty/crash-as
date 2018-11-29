#ifndef RTE_TELLTALE_H
#define RTE_TELLTALE_H

#include "Rte.h"
#include "Rte_Type.h"

/*********************************************************************************************************************
* Init Values
*********************************************************************************************************************/
#define Rte_InitValue_TelltaleAutoCruiseStatusPort_TelltaleAutoCruiseStatus ((OnOff_T)0u)
#define Rte_InitValue_TelltaleHighBeamStatusPort_TelltaleHighBeamStatus ((OnOff_T)0u)
#define Rte_InitValue_TelltaleTPMSStatusPort_TelltaleTPMSStatus ((OnOff_T)0u)

/*********************************************************************************************************************
* API Prototypes
*********************************************************************************************************************/
Std_ReturnType Rte_Write_Telltale_TelltaleAutoCruiseStatusPort_TelltaleAutoCruiseStatus(OnOff_T data);
Std_ReturnType Rte_Write_Telltale_TelltaleHighBeamStatusPort_TelltaleHighBeamStatus(OnOff_T data);
Std_ReturnType Rte_Write_Telltale_TelltaleTPMSStatusPort_TelltaleTPMSStatus(OnOff_T data);

/*********************************************************************************************************************
* Rte_Write_<p>_<d>
*********************************************************************************************************************/
#define Rte_Write_TelltaleAutoCruiseStatusPort_TelltaleAutoCruiseStatus Rte_Write_Telltale_TelltaleAutoCruiseStatusPort_TelltaleAutoCruiseStatus
#define Rte_Write_TelltaleHighBeamStatusPort_TelltaleHighBeamStatus Rte_Write_Telltale_TelltaleHighBeamStatusPort_TelltaleHighBeamStatus
#define Rte_Write_TelltaleTPMSStatusPort_TelltaleTPMSStatus Rte_Write_Telltale_TelltaleTPMSStatusPort_TelltaleTPMSStatus
/*********************************************************************************************************************
* Runnable Telltale_run
*********************************************************************************************************************/
void Telltale_run(void);


#endif //RTE_TELLTALE_H


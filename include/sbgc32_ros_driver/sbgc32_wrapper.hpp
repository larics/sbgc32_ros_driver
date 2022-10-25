#include <driver_Linux.h>

#include <gimbalControl/gimbalControl.h>
#include <profiles/profiles.h>
#include <realtime/realtime.h>
#include <service/service.h>

class SBGC32Wrapper {
public:

  SBGC32Wrapper();
  void SetPitchYaw(double pitch_deg, double yaw_deg);
  TxRxStatus_t PrintBoardParameters(GeneralSBGC_t *generalSBGC, Profile_t slot);

private:
  GeneralSBGC_t       SBGC_1;
  ConfirmationState_t Confirm;
  Control_t           Control;
  ControlConfig_t     ControlConfig;
  BoardInfo_t         BoardInfo;
  BoardInfo3_t        BoardInfo3;
  MainParams3_t       MainParams3;
  MainParamsExt_t     MainParamsExt;
  MainParamsExt2_t    MainParamsExt2;
  MainParamsExt3_t    MainParamsExt3;
  RealTimeData_t      RealTimeData;
  BeeperSettings_t    BeeperSettings;
};

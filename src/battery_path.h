#ifndef battery_path
#define battery_path
#include <SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library.h>
/**************************** IP5306 I2C Register ********************************************/
#define _i2c_5306Address 0xea
#define _i2c_charge_register 0x70
#define _i2c_chargeState_register 0x71
#define _i2c_SYS_CTL0_register 0x00
#define _i2c_SYS_CTL1_register 0x01
#define _i2c_SYS_CTL2_register 0x02
class Battery
{
public:
  void max17048Init();
  double getVoltage();
  double getSoc();
  bool getAlert();
  bool getCharge_en();
  bool getChargeState();
  void ip5306Init();
  int8_t ip5306GetbattLevel();

private:
  double voltage = 0; // Variable to keep track of LiPo voltage
  double soc = 0;     // Variable to keep track of LiPo state-of-charge (SOC)
  bool alert;
  bool charge_en;
  bool chargeState;
};
#endif

#include <battery_path.h>
SFE_MAX1704X lipo(MAX1704X_MAX17048);
void Battery::max17048Init()
{
  // Set up the MAX17043 LiPo fuel gauge:
  if (lipo.begin() == false) // Connect to the MAX17043 using the default wire port
  {
    Serial.println(F("MAX17043 not detected. Please check wiring. Freezing."));
    while (1)
      ;
  }
  // Quick start restarts the MAX17043 in hopes of getting a more accurate
  // guess for the SOC.
  lipo.quickStart();
  // We can set an interrupt to alert when the battery SoC gets too low.
  // We can alert at anywhere between 1% - 32%:
  lipo.setThreshold(30); // Set alert threshold to 20%.

  /********************************Fuel Gauge Setup***********************************************/
}
double Battery ::getVoltage()
{
  voltage = lipo.getVoltage();
  return voltage;
}
double Battery ::getSoc()
{
  soc = lipo.getSOC();
  return soc;
}
bool Battery ::getAlert()
{
  alert = lipo.getAlert();
  return alert;
}
bool Battery ::getCharge_en()
{
  Wire.requestFrom(_i2c_5306Address, _i2c_charge_register);
  charge_en = Wire.read() >> 3;
  return charge_en;
}
bool Battery ::getChargeState()
{
  Wire.requestFrom(_i2c_5306Address, _i2c_chargeState_register);
  chargeState = Wire.read() >> 3;
  return chargeState;
}
void Battery::ip5306Init(){
    Wire.beginTransmission(_i2c_5306Address);
    Wire.write(_i2c_SYS_CTL0_register);
    Wire.write(0b10111110);
    Wire.endTransmission();
    Wire.beginTransmission(_i2c_5306Address);
    Wire.write(_i2c_SYS_CTL1_register);
    Wire.write(0b00000101);
    Wire.endTransmission();
    Wire.beginTransmission(_i2c_5306Address);
    Wire.write(_i2c_SYS_CTL2_register);
    Wire.write(0b00000000);
    Wire.endTransmission();
}
int8_t Battery:: getBatteryLevel()
{
  Wire.beginTransmission(_i2c_5306Address);
  Wire.write(0x78);
  if (Wire.endTransmission(false) == 0
   && Wire.requestFrom(0x75, 1)) {
    switch (Wire.read() & 0xF0) {
    case 0xE0: return 25;
    case 0xC0: return 50;
    case 0x80: return 75;
    case 0x00: return 100;
    default: return 0;
    }
  }
  return -1;
}
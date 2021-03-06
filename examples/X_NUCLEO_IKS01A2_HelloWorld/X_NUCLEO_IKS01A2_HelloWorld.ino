/**
 ******************************************************************************
 * @file    X_NUCLEO_IKS01A2_HelloWorld.ino
 * @author  AST
 * @version V1.0.0
 * @date    7 September 2017
 * @brief   Arduino test application for the STMicrolectronics X-NUCLEO-IKS01A2
 *          MEMS Inertial and Environmental sensor expansion board.
 *          This application makes use of C++ classes obtained from the C
 *          components' drivers.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */


// Includes.
#include <HTS221Sensor.h>
#include <LPS22HBSensor.h>
#include <LSM303AGR_ACC_Sensor.h>
#include <LSM303AGR_MAG_Sensor.h>
#include <LSM6DSLSensor.h>

#define DEV_I2C Wire
#define SerialPort Serial

// Components.
HTS221Sensor  *HumTemp;
LPS22HBSensor  *PressTemp;
LSM6DSLSensor *AccGyr;
LSM303AGR_ACC_Sensor *Acc2;
LSM303AGR_MAG_Sensor *Mag;

void setup() {
  // Led.
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize serial for output.
  SerialPort.begin(115200);
  
  // Initialize I2C bus.
  DEV_I2C.begin();

  // Initlialize components.
  HumTemp  = new HTS221Sensor (&DEV_I2C);
  HumTemp->Enable();
  PressTemp = new LPS22HBSensor (&DEV_I2C);
  PressTemp->Enable();
  AccGyr = new LSM6DSLSensor(&DEV_I2C);
  AccGyr->Enable_X();
  AccGyr->Enable_G();
  Acc2 = new LSM303AGR_ACC_Sensor(&DEV_I2C);
  Acc2->Enable();
  Mag = new LSM303AGR_MAG_Sensor(&DEV_I2C);
  Mag->Enable();
}

void loop() {
  // Led blinking.
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);

  // Read humidity and temperature.
  float humidity, temperature;
  HumTemp->GetHumidity(&humidity);
  HumTemp->GetTemperature(&temperature);
  
  // Read pressure and temperature.
  float pressure, temperature2;
  PressTemp->GetPressure(&pressure);
  PressTemp->GetTemperature(&temperature2);

  // Read accelerometer and gyroscope.
  int32_t accelerometer[3];
  int32_t gyroscope[3];
  AccGyr->Get_X_Axes(accelerometer);
  AccGyr->Get_G_Axes(gyroscope);
  
  // Read accelerometer LSM303AGR.
  int32_t accelerometer2[3];
  Acc2->GetAxes(accelerometer2);
  
  // Read magnetometer LSM303AGR.
  int32_t magnetometer[3];
  Mag->GetAxes(magnetometer);

  // Output data.
  SerialPort.print("| Hum[%]: ");
  SerialPort.print(humidity, 2);
  SerialPort.print(" | Temp[C]: ");
  SerialPort.print(temperature, 2);
  SerialPort.print(" | Pres[hPa]: ");
  SerialPort.print(pressure, 2);
  SerialPort.print(" | Temp2[C]: ");
  SerialPort.print(temperature2, 2);
  SerialPort.print(" | Acc[mg]: ");
  SerialPort.print(accelerometer[0]);
  SerialPort.print(" ");
  SerialPort.print(accelerometer[1]);
  SerialPort.print(" ");
  SerialPort.print(accelerometer[2]);
  SerialPort.print(" | Gyr[mdps]: ");
  SerialPort.print(gyroscope[0]);
  SerialPort.print(" ");
  SerialPort.print(gyroscope[1]);
  SerialPort.print(" ");
  SerialPort.print(gyroscope[2]);
  SerialPort.print(" | Acc2[mg]: ");
  SerialPort.print(accelerometer2[0]);
  SerialPort.print(" ");
  SerialPort.print(accelerometer2[1]);
  SerialPort.print(" ");
  SerialPort.print(accelerometer2[2]);
  SerialPort.print(" | Mag[mGauss]: ");
  SerialPort.print(magnetometer[0]);
  SerialPort.print(" ");
  SerialPort.print(magnetometer[1]);
  SerialPort.print(" ");
  SerialPort.print(magnetometer[2]);
  SerialPort.println(" |");
}
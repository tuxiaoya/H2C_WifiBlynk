


/*************************************************************


 *************************************************************

 *************************************************************/



#define BLYNK_PRINT Serial

#define BLYNK_USE_DIRECT_CONNECT
#define DEFAULT_Adr 0 // 0=�߼�ID  0xc0���Ӻ����м�
#define LED_BUILTIN 2 // ��ɫLED

#include "Arduino.h"
#include <HardwareSerial.h>
#include "MGHWSG2.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>


char auth[] = "591583e248bf4aeea26d291d1ff6b336";
char ssid[] = "����Ƽ�";    // 4¥wifi
char pass[] = "mgkj8190688";  // 

HardwareSerial M5310_Serial(0);
HardwareSerial DIWEN_Serial(1);
HardwareSerial HWSG_Serial(2); //RX2 16  TX2 17


boolean HWSGTxD_OK = true; // false;
BlynkTimer timer_2C;
// (uint8_t HWSGAddress, HWSG2_TYPE Type, HardwareSerial *HardwareSerialport)
MinGuang_HWSH2 HWSG2C(0,1, &HWSG_Serial); //


HWSG2_Parameters_Str Working_Par;
HWSG2_Online_Uartframe SecTick_uartf;
HWSG2_Online_Temp SecTick_Tem;

time_t H2Ctime;
// Attach virtual serial terminal to Virtual Pin VirPort_Terminal

void set_led(byte status)
{
  digitalWrite(LED_BUILTIN, status);
}

// ����BLYNK���¼�����ֻ�ܰ����ڴˣ������÷���������
#include "H2C_blynk.h"
// ����BLYNK���¼�����

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("Fucking for connections...");
  Blynk.begin(auth, ssid, pass);
  set_led(HWSGTxD_OK);

  HWSG2C.Begin(1200);
  timer_2C.setInterval(1000L, H2CTimerEvent);
  terminal.clear(); // Clear the terminal content
  // This will print Blynk Software version to the Terminal Widget when
  // your hardware gets connected to Blynk Server
  terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
  terminal.flush();
}

void loop()
{
  Blynk.run();
  timer_2C.run();
}

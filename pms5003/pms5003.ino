#include "PMS.h"
#include <ESP8266WiFi.h>
#include <stdio.h>
#include "ThingSpeak.h"

String apiKey = "************";
const char * myWriteAPIKey = "*********";
// replace with your routers SSID
const char* ssid = "*************";
// replace with your routers password
const char* password = "***";
 
const char* server = "api.thingspeak.com";
unsigned long myChannelNumber = *******;

WiFiClient client;

PMS pms(Serial);
PMS::DATA data;

void setup()
{
  Serial.begin(9600);   // GPIO1, GPIO3 (TX/RX pin on ESP-12E Development Board)
  //Serial1.begin(9600);  // GPIO2 (D4 pin on ESP-12E Development Board)
  //pms.passiveMode();    // Switch to passive mode
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  pms.wakeUp();
}

float calcAverage(int values[])
{
    int i;
    int n = 10;
    float sum = 0.0;
    float avg;

    for (i = 0; i < 10; ++i) {
        Serial.println(String(values[i]));
        if (isnan(values[i]) || values[i] == 0){
          n = n-1;
        }
        else {
          sum += values[i];  
        }
    }
    Serial.println(".");
    avg = sum / n;
    return avg;  
}

int readPM(int PM_size)
{
  int val = 0;
  if (pms.readUntil(data))
  {
      if (PM_size == 1){
        val = data.PM_AE_UG_1_0;
      }
      else if (PM_size == 2){
        val = data.PM_AE_UG_2_5;
      }
      else {
        val = data.PM_AE_UG_10_0;
      }
  }
  else
  {
    Serial.println("No data.");
  }
  return val;
}

String getValues()
{
    int i;
    int PM1_0_values[10];
    int PM2_5_values[10];
    int PM10_values[10];
    
    for (i = 0; i < 10; ++i)
    {
      PM1_0_values[i] = readPM(1);
      PM2_5_values[i] = readPM(2);
      PM10_values[i] = readPM(3);
      delay(3000);
    }
    
    float PM1_0_AVG = calcAverage(PM1_0_values);
    float PM2_5_AVG = calcAverage(PM2_5_values);
    float PM10_AVG = calcAverage(PM10_values);

    Serial.println("PM1_0_AVG: ");
    Serial.println(String(PM1_0_AVG));

    Serial.println("PM2_5_AVG: ");
    Serial.println(String(PM2_5_AVG));

    Serial.println("PM10_AVG: ");
    Serial.println(String(PM10_AVG));
    
    String postStr = apiKey;
    postStr +="&field1=";
    postStr += String(PM1_0_AVG);
    postStr +="&field2=";
    postStr += String(PM2_5_AVG);
    postStr +="&field3=";
    postStr += String(PM10_AVG);
    postStr += "\r\n\r\n";

    Serial.println(postStr);
    return postStr;
  
  
}

void sendDatas(String postStr){
    int sendCode = ThingSpeak.writeRaw(myChannelNumber, postStr, myWriteAPIKey);
    if(sendCode == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(sendCode));
      ThingSpeak.writeRaw(myChannelNumber, postStr, myWriteAPIKey);
    }
}

void loop()
{
  Serial.println("Waking up, wait 3 minutes for stable readings...");
  pms.wakeUp();
  delay(180000); // wait 3 minutes for stable readings... 
  //Serial.println("Send read request...");
  //pms.requestRead(); //only for passive mode

  Serial.println("Reading data...");

  String postString = getValues();
  Serial.println(postString);

  Serial.println("Send Data...");
  sendDatas(postString);
  
  Serial.println("Going to sleep for 60 seconds.");
  pms.sleep();

  delay(120000); //wait 2 minutes to complete the data submission to thingspeak
  ESP.deepSleep(1440e6); //sleep for 1440 seconds(24 minutes) (change only number before 'e6')

}

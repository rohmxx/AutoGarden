#include <LiquidCrystal_I2C.h>



//--------------------------------------------------------------------------------------------------------------------------------------------------
//                                                       -ESTICY- ROBOTIKA STEMBA present:
//                                                             AUTOMATIC GARDEN v1.1
//--------------------------------------------------------------------------------------------------------------------------------------------------

//#include<LiquidCrystal.h>
//#include <LiquidCrystal_I2C.h>
//LiquidCrystal lcd(2,3,4,5,6,7);
#include <ESP8266WiFi.h>
#include <Wire.h> 
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
int moisture = A0; //  pin analog yang di gunakan sensor kelembapan di pin A0
int pump = D3; //pin yang digunakan pump      
const int threshold = 50; 

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
const char* ssid = "Ora Pro Ora  Never Quit";      // Nama AP/Hotspot
const char* password = "thesmartlocksidk";  

WiFiServer server(80);

 
LiquidCrystal_I2C lcd(0x3f, 16, 2); // pin SDA = d2 , SCL = d1



void setup() {
  // put your setup code here, to run once:
  pinMode(pump, OUTPUT);
  digitalWrite(pump, 0);
  delay(5000);

 Serial.begin(9600);
  delay(1000);
//  
 Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
// Mengatur WiFi ----------------------------------------------------------
  WiFi.mode(WIFI_STA);                      // Mode Station
  WiFi.begin(ssid, password);               // Mencocokan SSID dan Password
  
  while (WiFi.status() != WL_CONNECTED  ) {
    delay(500);
    Serial.print(".");
  }
 
// Print status Connect ---------------------------------------------------
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  
lcd.begin(16,2);
 lcd.init();                     // initialize the lcd 

  // Print a message to the LCD.
  lcd.backlight();


lcd.setCursor(1,0);
lcd.println("SELAMAT DATANG ");
delay(1000);

lcd.clear();
lcd.setCursor(1,0);
lcd.print("   -ESTICY-    ");
lcd.setCursor(1,1);
lcd.println("ROBOTIKA STEMBA");
delay(1000);


lcd.clear();
lcd.setCursor(1,0);
lcd.println(" AUTO  GARDEN  ");
delay(1000);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  float analogValue = analogRead(moisture);
  float lembab;
  lembab = (100.00 - (analogValue/1024.00) * 100.00 );
  if (lembab>100) lembab = 100;
  else if (lembab<0) lembab = 0;
 
  // untuk tanah basah dan mematikan relay
  if (lembab > threshold){
    lcd.println("BASAH");
    digitalWrite(pump,0);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.println("TANAH KERING");
    lcd.setCursor (1,1);
    lcd.print ("Lembab= ");
  if(lembab<0) lembab = 0;
    lcd.print (lembab);
    lcd.print ("%");
    delay(1000);
  }

//untuk tanah kering dan menghidupkan relay 
  else if (lembab < threshold){
    lcd.println("KERING");
    digitalWrite(pump,1);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.println("TANAH BASAH" ) ;
    lcd.setCursor (1,1);
       lcd.print ("Lembab= ");
       lcd.print (lembab);
       lcd.print ("%");
       delay(1000);
       }
  

  Serial.print(lembab);
  delay(100);
  }
 //firebase-adminsdk-df7cl@auto-garden-nextgen.iam.gserviceaccount.com
/*var admin = require("firebase-admin");
Device Credentials = bHvC&XrvhUp$p9Kp
Device Id = ESTICY_STEMBA_AUTO_GARDEN
var serviceAccount = require("path/to/serviceAccountKey.json");
#define FIREBASE_AUTH "eyPHHVfcxVtw4wEXcjrRfxYPFq4R798YaEMd4hfL"
admin.initializeApp({
  credential: admin.credential.cert(serviceAccount),
  databaseURL: "https://auto-garden-nextgen-default-rtdb.firebaseio.com"
});*/

//".read": "now < 1637859600000",  // 2021-11-26
  //  ".write": "now < 1637859600000",  // 2021-11-26

//  if (analogValue > threshold) 
//  {
//    digitalWrite(pump, LOW);//
//    delay(1000);

//  } 
//  else if (analogValue < threshold )
//       {
//       digitalWrite(pump, HIGH);
//       delay(1000);
//       //lcd.clear();
//       //lcd.setCursor(1,0);
//       Serial.println("TANAH BASAH" ) ;
//       //lcd.setCursor (1,1);
//       Serial.print ("Lembab= ");
//       Serial.print (lembab);
//       Serial.print ("%");
//       delay(1000);
//       }
// Device Id = ESP8266NODEMCU
//Device Credentials = bHvC&XrvhUp$p9Kp
//Device Name = ESTICY_STEMBA_AUTO_GARDEN
//Device Description = monitoring kelembapan tanah dan menyalakan selenoid

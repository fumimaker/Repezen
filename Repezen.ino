#include <SoftwareSerial.h>
#define echoPin 2 // Echo Pin
#define trigPin 3 // Trigger Pin
#define SW 7
SoftwareSerial mySerial(10, 11); // RX, TX
double Duration = 0; //受信した間隔
double Distance = 0; //距離
boolean flg=true;
void setup() {
  Serial.begin(9600);
  pinMode( echoPin, INPUT );
  pinMode( trigPin, OUTPUT );
  pinMode(SW, INPUT_PULLUP);
  pinMode(13,OUTPUT);
  // ソフトウェアシリアルの初期化
  mySerial.begin(9600);
  // 「こんにちは。シリアルモニターで文字を入力します。」と発声する
  //mySerial.print("konnitiwa.siriaru'mo'nita-de/mo'ziwo nyuuryoku'simasu.");
  //mySerial.print("\r");
}
 
void loop() {
  char c;
  String raw = "";
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite( trigPin, HIGH ); //超音波を出力
  delayMicroseconds( 10 ); //
  digitalWrite( trigPin, LOW );
  Duration = pulseIn( echoPin, HIGH ); //センサからの入力

  if(!digitalRead(SW)){
    mySerial.print("zikandayo.baibai.");
    mySerial.print("\r");
    digitalWrite(13,HIGH);
  }
  else{
    digitalWrite(13,LOW);
  }
  
  if (Duration > 0) {
    Duration = Duration/2; //往復距離を半分にする
    Distance = Duration*340*100/1000000; // 音速を340m/sに設定
    Serial.print("Distance:");
    Serial.print(Distance);
    Serial.println(" cm");
  }
  if(Distance<25&&flg){
    mySerial.print("kusaiyo.");
    mySerial.print("\r");
  }
  else if(Distance<45&&flg){
    mySerial.print("tikaiyo");
    mySerial.print("\r");
  }
 
  // 音声合成LSIからシリアルモニターへ
  while (mySerial.available() > 0) {
    char c = mySerial.read();
    raw += c;
    delay(5);
  }
  if (raw != "") {
    if (raw == ">") {
      Serial.println("> (この記号は準備OK)");
      flg=true;
    } else if (raw == "*") {
      Serial.println("* (この記号は発声中などBusy)");
      flg=false;
    } else {
      Serial.println(raw);
      flg=false;
    }
  }
}

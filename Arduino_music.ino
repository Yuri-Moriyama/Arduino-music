/* 自主制作 */

#define LED_PIN_R 11
#define LED_PIN_B 10
#define LED_PIN_G 9
#define LED_PIN_Y 6

#define AUDIO_PIN 12
#define TC 0 // ド
#define TD 1 // レ
#define TE 2 // ミ
#define TF 3 // ファ
#define TG 4 // ソ
#define TA 5 // ラ
#define TB 6 // シ
#define TC5 7 // ド
#define TD5 8 // レ
#define TE5 9 // ミ
#define TF5 10 // ファ
#define TG5 11 // ソ
#define TA5 12 // ラ
#define TB5 13 // シ
#define TX 14 // 休符(音を鳴らさない)

//音階の周波数[Hz]：ドレミファソラシに対応。7番目の要素は休符なので音無し。
int freq[] = {262, 294, 330, 349, 392, 440, 494, 523, 587, 659, 698, 784, 880, 988, 0};

//流したいメロディを格納する配列(一次元目：音階、二次元目：その音階の出力時間)
int melody1[33][2] = {
  {TE, 250},{TG, 250},{TA, 250},{TG, 125},{TA, 125},{TB, 250},{TD, 250},
  {TE, 250},{TE, 125},{TD, 125},{TE, 250},{TG, 250},{TA, 250},{TG, 125},
  {TA, 125},{TB, 500},{TA, 500},{TE, 250},{TG, 250},{TA, 250},{TG, 125},
  {TA, 125},{TB, 250},{TD, 250},{TE, 250},{TE, 125},{TD, 125},{TE, 250},
  {TG, 250},{TA, 250},{TG, 125},{TA, 125},{TE, 500}
};

//流したいメロディを格納する配列(一次元目：音階、二次元目：その音階の出力時間)
int melody2[30][2] = {
  {TG, 1000},{TE, 1000},{TF, 1000},{TG, 1000},{TA, 1000},
  {TG, 1000},{TE, 1000},{TF, 1000},{TG, 1000},{TC5, 1000},
  {TA, 1000},{TG, 1000},{TE, 1000},{TC, 1000},{TD5, 1000},
  {TG, 1000},{TA, 1000},{TG, 1000},{TE, 1000},{TG, 1000},
  {TC5, 1000},{TD5, 1000},{TC5, 1000},{TA, 1000},{TC5, 1000},
  {TA, 1000},{TE5, 1000},{TD5, 1000},{TG, 1000},{TC5, 1000},
};

//流したいメロディを格納する配列(一次元目：音階、二次元目：その音階の出力時間)
int melody3[83][2] = {
  {TG, 250},{TC5,250},{TD5,167},{TC5,83},{TD5,167},{TC5,83},{TD5,167},
  {TC5,83},{TD5,167},{TC5,83},{TD5,250},{TE5,167},{TC5, 250},{TG, 83},
  {TG,167},{TD5,250},{TC5,83},{TD5,167},{TC5,83},{TD5,167},{TC5,83},
  {TD5,167},{TC5,83},{TD5,250},{TE5,167},{TC5, 250},{TC5,83},{TC5,125},
  {TD5,333},{TC5,167},{TA,250},{TA,250},{TC5,83},{TD5,167},{TE5,83},
  {TD5,167},{TC5,83},{TC5,83},{TC5,83},{TB,167},{TA,83},{TB,167},{TC5,83},
  {TC5,500},{TE5,63},{TC5,63},{TC5,167},{TD5,83},{TE5,250},{TF5,250},
  {TG5, 250},{TA5,250},{TG5,250},{TC5,167},{TC5,167},{TC5,63},{TD5,63},
  {TE5,187},{TF5,63},{TE5,125},{TD5,63},{TD5,63},{TC5, 437},{TG, 125},
  {TA,125},{TC5,250},{TC5,167},{TD5,83},{TE5,250},{TE5,167},{TF5,83},
  {TG5,167},{TC5,167},{TC5,83},{TE5,167},{TE5, 83},{TD5,458},{TG,125},
  {TG,125},{TG,250},{TC5,250},{TD5,167},{TC5,500}
};

//流したいメロディを格納する配列(一次元目：音階、二次元目：その音階の出力時間)
int melody4[33][2] = {
   {TG, 125},{TX, 125},{TE5, 125},{TC5, 125},{TD5, 250},
  {TG5, 125},{TX, 125},{TE5, 125},{TC5, 125},{TD5, 250},
  {TC5, 125},{TC5, 250},{TD5, 125},{TE5, 125},{TE5, 125},
  {TG5, 125},{TG5, 125},{TF5, 250},{TF5, 125},{TE5, 125},
  {TD5, 500},{TE5, 125},{TD5, 125},{TC5, 125},{TB5, 125},
  {TA5, 125},{TA5, 125},{TF5, 125},{TF5, 125},{TE5, 250},
  {TE5, 125},{TD5, 125},{TC5, 500}
};

String scale[] = {"ド","レ","ミ","ファ","ソ","ラ","シ","ド","レ","ミ","ファ","ソ"};
String recv_msg = "";   // 受信データがここに格納される

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);   //ポーレートを11520bpsに設定
  pinMode(LED_PIN_R, OUTPUT);   //ピンを出力
  pinMode(LED_PIN_B, OUTPUT);   //ピンを出力
  pinMode(LED_PIN_G, OUTPUT);   //ピンを出力
  pinMode(LED_PIN_Y, OUTPUT);   //ピンを出力
  pinMode(AUDIO_PIN, OUTPUT);   //ピンを出力
}

void loop() {
  // put your main code here, to run repeatedly:

  if( Serial.available() > 0 )   // シリアル通信ポートに何バイトかのデータが届いていたら
 {
  // 受信したデータの最初の1バイトを読み取る
  recv_msg = Serial.readStringUntil('\n');   //改行コードが来るまで文字列を溜め込む
  
  // 受信したデータを出力する
  Serial.print("I received: ");
  Serial.println(recv_msg);
 
  if(recv_msg == "春")
  {
    digitalWrite(LED_PIN_G, HIGH);    //ピンを点灯
    digitalWrite(LED_PIN_R, LOW);     //ピンを消灯
    digitalWrite(LED_PIN_B, LOW);     //ピンを消灯
    digitalWrite(LED_PIN_Y, LOW);     //ピンを消灯

    for(int i = 0; i<30; i++){
    tone(AUDIO_PIN, freq[melody2[ i ][ 0 ]],melody2[ i ][ 1 ]);   //音楽を奏でる
    delay(500);
    }
  }
  else if (recv_msg == "夏")
  {
    digitalWrite(LED_PIN_R, HIGH);    //ピンを点灯   
    digitalWrite(LED_PIN_G, LOW);     //ピンを消灯
    digitalWrite(LED_PIN_B, LOW);     //ピンを消灯
    digitalWrite(LED_PIN_Y, LOW);     //ピンを消灯
    
    for(int i = 0; i<33; i++){
       tone(AUDIO_PIN, freq[melody1[ i ][ 0 ]],melody1[ i ][ 1 ]);   //音楽を奏でる
    delay((melody1[i][1])*2);   
   }
  }
  else if (recv_msg == "冬")
  {
    digitalWrite(LED_PIN_B, HIGH);    //ピンを点灯
    digitalWrite(LED_PIN_R, LOW);     //ピンを消灯
    digitalWrite(LED_PIN_G, LOW);     //ピンを消灯
    digitalWrite(LED_PIN_Y, LOW);     //ピンを消灯
    
    for(int i = 0; i<83; i++){
    tone(AUDIO_PIN, freq[melody3[ i ][ 0 ]],melody3[ i ][ 1 ]);   //音楽を奏でる
    delay((melody3[i][1])*2);
   }
  }
  else if (recv_msg == "秋")
  {
    digitalWrite(LED_PIN_Y, HIGH);    //ピンを点灯
    digitalWrite(LED_PIN_G, LOW);     //ピンを消灯
    digitalWrite(LED_PIN_R, LOW);     //ピンを消灯
    digitalWrite(LED_PIN_B, LOW);     //ピンを消灯
    
    for(int i = 0; i<33; i++){
    tone(AUDIO_PIN, freq[melody4[ i ][ 0 ]],melody4[ i ][ 1 ]);   //音楽を奏でる
    delay((melody4[i][1])*2);
  }
  }
   else if (recv_msg == "off")
  {
    digitalWrite(LED_PIN_G, LOW);     //ピンを消灯
    digitalWrite(LED_PIN_R, LOW);     //ピンを消灯
    digitalWrite(LED_PIN_B, LOW);     //ピンを消灯
    digitalWrite(LED_PIN_Y, LOW);     //ピンを消灯
  }
  else
  {
    Serial.println("指示が間違っているよ。春,夏,秋,冬をおくって、やめたいときはoffと送ってね。");
  }
 }

}

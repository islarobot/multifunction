String readString;

String x_string;
String y_string;
int x;
int y;


//Motor B
 int enableB = 9;
 int pinB1 = 4;
 int pinB2 = 5;
 int dir = 0;
 int speed = 0;
 int interv = 3;
 
 
 int encoder = 0;
int m_direction = 0;
int sv_speed = 100;     //this value is 0~255
double pv_speed = 0;
int timer1_counter; //for timer

void setup() {

//pinMode(2,INPUT_PULLUP);
//pinMode(3,INPUT_PULLUP);
//attachInterrupt(digitalPinToInterrupt(2), detect_a, RISING);


//--------------------------timer setup
 noInterrupts();           // disable all interrupts
 TCCR1A = 0;
TCCR1B = 0;
timer1_counter = 34286;   // preload timer 65536-16MHz/256/2Hz

TCNT1 = timer1_counter;   // preload timer
 TCCR1B |= (1 << CS12);    // 256 prescaler
 TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
 interrupts();             // enable all interrupts
  //--------------------------timer setup


Serial.begin(115200);
pinMode (enableB, OUTPUT);
 pinMode (pinB1, OUTPUT);
 pinMode (pinB2, OUTPUT);
   
}

void loop() {
  
if (Serial.available() > 0) {
  

      delay(2);
      readString = Serial.readStringUntil('\n');
     
       //Serial.println (readString);
       Serial.println (pv_speed);

      x_string = readString.substring(0,3);
      y_string = readString.substring(3,6);
      
      x = x_string.toInt();
      y = y_string.toInt();

      if(y > 0){dir = 1;speed = map(y,0,90,0,255);}
      else if(y<0){dir = -1;speed = map(y,0,-90,0,255);}
      else{dir==0;}
      
    
 
}

if(dir==1)
{
 digitalWrite (pinB1, LOW);
 digitalWrite (pinB2, HIGH);
analogWrite(enableB, speed);
}
else if(dir==-1)
{
 digitalWrite (pinB1, HIGH);
 digitalWrite (pinB2, LOW);
analogWrite(enableB, speed);

}
else
{
 digitalWrite (pinB1, LOW);
 digitalWrite (pinB2, LOW);
}


}



//void detect_a() {  encoder+=1;  m_direction = digitalRead(3);}


//ISR(TIMER1_OVF_vect)      {  TCNT1 = timer1_counter;    pv_speed = 60*(encoder/200.0)/0.5;  encoder=0;}


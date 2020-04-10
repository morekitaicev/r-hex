#define U1_in 6
#define U2_in 7
#define U3_in 8
#define U1_out 9
#define U2_out 10
#define U3_out 11
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(U1_in,INPUT);
pinMode(U2_in,INPUT);
pinMode(U3_in,INPUT);
pinMode(U1_out,OUTPUT);
pinMode(U2_out,OUTPUT);
pinMode(U3_out,OUTPUT);
}
int r1,r2,r3 ; 
void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(U1_out,LOW);
digitalWrite(U2_out,LOW);
digitalWrite(U3_out,LOW);
delayMicroseconds(1);
digitalWrite(U1_out,HIGH);
digitalWrite(U2_out,HIGH);
digitalWrite(U3_out,HIGH);
delayMicroseconds(10);
r1=pulseIn(U1_in,HIGH)/58;
r2=pulseIn(U2_in,HIGH)/58;
r3=pulseIn(U3_in,HIGH)/58;

Serial.print(r1);
Serial.print(",");
Serial.print(r2);
Serial.print(",");
Serial.println(r3);

}

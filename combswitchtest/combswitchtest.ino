int anal;
int digi;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(8, INPUT_PULLUP);
  pinMode(4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  anal = analogRead(A5);
  digi = digitalRead(8);
  Serial.print(anal);
  Serial.print(" ");
  Serial.println(digi);
  if(digi == 0){
    digitalWrite(4, HIGH);}
  else{
    digitalWrite(4, LOW);}
  delay(50);
}

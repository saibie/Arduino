int ip[] = {2, 4, 6};
int op[] = {8, 10, 12};
int j = 0;

void setup() {
  // put your setup code here, to run once:
  for(int i=0; i<3; i++){
    pinMode(ip[i], INPUT_PULLUP);
    pinMode(op[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (j >= 3){j = 0;}
  digitalWrite(op[j], HIGH);
  delay(1000);
  for(int i=0; i<3; i++){
    Serial.print(ip[i]);
    Serial.print(" ");}
  Serial.println(" ");
  for(int i=0; i<3; i++){
    Serial.print(digitalRead(ip[i]));
    Serial.print(" ");}
  Serial.println(" ");
  digitalWrite(op[j], LOW);
  j++;
}

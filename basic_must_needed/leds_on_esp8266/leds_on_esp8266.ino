

int main_led = 16;
int wifi_led = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  pinMode(main_led, OUTPUT);
  pinMode(wifi_led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(main_led, HIGH);
  delay(1000);
  digitalWrite(main_led, LOW);
  delay(200);
  digitalWrite(wifi_led, HIGH);
  delay(1000);
  digitalWrite(wifi_led, LOW);
  delay(200);
}

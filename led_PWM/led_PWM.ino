//Para fins de facilidade de entendimento do código
//vou declarar variáveis para os pinos utilizados
#define yellowLed 14 //Corresponde ao GPIO14
#define greenLed 12 //GPIO12
#define redLed 13 //GPIO13
//Configuração do PWM
const int freq = 5000; //Frequência do PWM, 5000 basta para utilização de leds
const int canal = 0; //Canal do PWM, podendo ser de 0 a 15
const int canal2 = 2;
const int canal3 = 4;
const int resolution = 8; //Resolução de 8 bits, para usar valores de 0 a 255

void setup() {
  //Configurar as funcionalidades do led PWM
    ledcSetup(canal, freq, resolution);
    ledcSetup(canal2, freq, resolution);
    ledcSetup(canal3, freq, resolution);
    
  //Atribui o pino do led ao canal do PWM utilizado
  ledcAttachPin(yellowLed, canal);
  ledcAttachPin(greenLed, canal2);
  ledcAttachPin(redLed, canal3);

  Serial.begin(9600);
}

void loop() {
  AumentaBrilho(canal);
  DiminuiBrilho(canal);
  delay(50);
  
  AumentaBrilho(canal2);
  DiminuiBrilho(canal2);
  delay(50);

  
  AumentaBrilho(canal3);
  DiminuiBrilho(canal3);
  delay(50);
}


void AumentaBrilho(const int canalPWM){
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){
    ledcWrite(canalPWM, dutyCycle);
    Serial.printf("Aumentando brilho!\n");
    delay(15);
  }
}


void DiminuiBrilho(const int canalPWM){
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    ledcWrite(canalPWM, dutyCycle);
    Serial.printf("Diminuindo brilho!\n");
    delay(15);
  }
}

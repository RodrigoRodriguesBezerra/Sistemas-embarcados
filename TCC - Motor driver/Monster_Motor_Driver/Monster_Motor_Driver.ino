#include <Servo.h>

#define BRAKE 0                                    
#define CW    1
#define CCW   2
#define CS_THRESHOLD 15   // Definition of safety current (Check: "1.3 Monster Shield Example").

//MOTOR 1
#define MOTOR_A2_PIN 7
#define MOTOR_B2_PIN 8

//MOTOR 2
#define MOTOR_A1_PIN 4
#define MOTOR_B1_PIN 9

#define PWM_MOTOR_2 5
#define PWM_MOTOR_1 6

#define CURRENT_SEN_1 A2
#define CURRENT_SEN_2 A3

#define EN_PIN_1 A0
#define EN_PIN_2 A1

#define MOTOR_ESQ 0
#define MOTOR_DIR 1

#define SERVO 10 // Porta Digital 10 PWM
Servo s; // Variável Servo
int pos; // Posição Servo

int velocidade = 60;
int vel_comp;
short usSpeed = 70;  //default motor speed
unsigned short usMotor_Status = BRAKE;
 
void setup()                         
{
  pinMode(MOTOR_A1_PIN, OUTPUT);
  pinMode(MOTOR_B1_PIN, OUTPUT);

  pinMode(MOTOR_A2_PIN, OUTPUT);
  pinMode(MOTOR_B2_PIN, OUTPUT);

  pinMode(PWM_MOTOR_1, OUTPUT);
  pinMode(PWM_MOTOR_2, OUTPUT);

  pinMode(CURRENT_SEN_1, OUTPUT);
  pinMode(CURRENT_SEN_2, OUTPUT);  

  pinMode(EN_PIN_1, OUTPUT);
  pinMode(EN_PIN_2, OUTPUT);

  s.attach(SERVO);

  Serial.begin(9600);              // Initiates the serial to do the monitoring 
  s.write(45); // Inicia motor posição zero
  Serial.println("Begin motor control");
  Serial.println(); //Print function list for user selection
}

void loop() 
{
  char user_input;   
 
  if(Serial.available())
  {
    user_input = Serial.read(); //Read user input and trigger appropriate function
    digitalWrite(EN_PIN_1, HIGH);
    digitalWrite(EN_PIN_2, HIGH); 
     
    if (user_input =='q')
    {
       Stop();
    }
    else if(user_input =='w')
    {
      Forward();
    }
    else if(user_input =='s')
    {
      Re();
    }
    else if(user_input =='a')
    {
      Esquerda();
    }
    else if(user_input =='d')
    {
      Direita();
    }
    else if(user_input == '2')
    {
      IncreaseSpeed();
    }
    else if(user_input == '1')
    {
      DecreaseSpeed();
    }
    else if(user_input == '4'){
      test_servo();
    }
    else
    {
      Serial.println("Invalid option entered.");
    }
      
  }
}

float Veloc(int Vel){
  vel_comp = Vel*1.28;
  if(vel_comp > 255){
    vel_comp = 255;
  }
  else if(vel_comp < -255){
    vel_comp = -255;
  }
  
  return vel_comp;
}

void test_servo(){
  for(pos = 0; pos < 90; pos++)
  {
    s.write(pos);
    delay(15);
  }
  delay(1000);
  for(pos = 90; pos >= 0; pos--)
  {
    s.write(pos);
    delay(15);
  }
  s.write(45);
  delay(15);
}

void Stop()
{
  usMotor_Status = BRAKE;
  motorGo(MOTOR_ESQ, usMotor_Status, 0);
  motorGo(MOTOR_DIR, usMotor_Status, 0);
}
//Motor ESQ = 63
//Motor DIR = 50
void Forward()
{
  usMotor_Status = CW;
  Veloc(velocidade);
  motorGo(MOTOR_ESQ, usMotor_Status, velocidade);
  motorGo(MOTOR_DIR, usMotor_Status, vel_comp);
}

void Re()
{
  usMotor_Status = CCW;
  Veloc(velocidade);
  motorGo(MOTOR_ESQ, usMotor_Status, velocidade);
  motorGo(MOTOR_DIR, usMotor_Status, vel_comp);
}

void Direita()
{
  usMotor_Status = CCW;
  Veloc(velocidade);
  motorGo(MOTOR_ESQ, usMotor_Status, velocidade);
  motorGo(MOTOR_DIR, CW, vel_comp);
}

void Esquerda()
{
  usMotor_Status = CCW;
  Veloc(velocidade);
  motorGo(MOTOR_ESQ, CW, velocidade);
  motorGo(MOTOR_DIR, usMotor_Status, vel_comp);
}


void IncreaseSpeed()
{
  velocidade = velocidade + 10;
  if(velocidade > 255)
  {
    velocidade = 255;  
  }
  Serial.println("Velocidade = ");
  Serial.println(velocidade, "\n");
}

void DecreaseSpeed()
{
  velocidade = velocidade - 10;
  if(usSpeed < 0)
  {
    usSpeed = 0;  
  }  
  Serial.println("Velocidade = ");
  Serial.println(velocidade, "\n");
}
/*
void DecreaseSpeed()
{
  usSpeed = usSpeed - 10;
  if(usSpeed < 0)
  {
    usSpeed = 0;  
  }
 
  Serial.print("Speed -: ");
  Serial.println(usSpeed);

  motorGo(MOTOR_1, usMotor_Status, usSpeed);
  motorGo(MOTOR_2, usMotor_Status, usSpeed);  
}
*/

void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)         //Function that controls the variables: motor(0 ou 1), direction (cw ou ccw) e pwm (entra 0 e 255);
{
  if(motor == MOTOR_ESQ)
  {
    if(direct == CW)
    {
      digitalWrite(MOTOR_A1_PIN, LOW); 
      digitalWrite(MOTOR_B1_PIN, HIGH);
    }
    else if(direct == CCW)
    {
      digitalWrite(MOTOR_A1_PIN, HIGH);
      digitalWrite(MOTOR_B1_PIN, LOW);      
    }
    else
    {
      digitalWrite(MOTOR_A1_PIN, LOW);
      digitalWrite(MOTOR_B1_PIN, LOW);            
    }

    
    analogWrite(PWM_MOTOR_1, pwm); 
  }
  else if(motor == MOTOR_DIR)
  {
    if(direct == CW)
    {
      digitalWrite(MOTOR_A2_PIN, LOW);
      digitalWrite(MOTOR_B2_PIN, HIGH);
    }
    else if(direct == CCW)
    {
      digitalWrite(MOTOR_A2_PIN, HIGH);
      digitalWrite(MOTOR_B2_PIN, LOW);      
    }
    else
    {
      digitalWrite(MOTOR_A2_PIN, LOW);
      digitalWrite(MOTOR_B2_PIN, LOW);            
    }
    
    analogWrite(PWM_MOTOR_2, pwm);
  }
}

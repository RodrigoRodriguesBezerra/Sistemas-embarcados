#define FREIO 0                                    
#define CW    1 //clockwise
#define CCW   2 //counterclockwise
#define CS_THRESHOLD 15   // Definição da corrente de segurança

//MOTOR ESQUERDO
#define MOTOR_A1_PIN 7
#define MOTOR_B1_PIN 8

//MOTOR DIREITO
#define MOTOR_A2_PIN 4
#define MOTOR_B2_PIN 9

#define PWM_MOTOR_1 5
#define PWM_MOTOR_2 6

#define EN_PIN_1 A0
#define EN_PIN_2 A1

#define MOTOR_ESQ 0
#define MOTOR_DIR 1

short usSpeed = 50;
unsigned short usMotor_Status = FREIO;
 
void setup()                         
{
  pinMode(MOTOR_A1_PIN, OUTPUT);
  pinMode(MOTOR_B1_PIN, OUTPUT);

  pinMode(MOTOR_A2_PIN, OUTPUT);
  pinMode(MOTOR_B2_PIN, OUTPUT);

  pinMode(PWM_MOTOR_1, OUTPUT);
  pinMode(PWM_MOTOR_2, OUTPUT);

  pinMode(EN_PIN_1, OUTPUT);
  pinMode(EN_PIN_2, OUTPUT);

  Serial.begin(9600);              // Initiates the serial to do the monitoring 
}

void loop() 
{
  char user_input;   
  
  if(Serial.available() > 0)
  {
    user_input = Serial.read(); //Read user input and trigger appropriate function
    digitalWrite(EN_PIN_1, HIGH);
    digitalWrite(EN_PIN_2, HIGH); 
  }
  if (user_input =='1')
  {
      Stop();
  }
  else if(user_input =='2')
  {
      Giro_horario();
      
   }
   else if(user_input =='3')
   {
      Giro_anti_horario();
      
    }
    else
    {
      Serial.println("Invalid option entered.");
    }     
}

void Stop()
{
 
  usMotor_Status = FREIO;
  motorGo(MOTOR_ESQ, usMotor_Status, 0);
  motorGo(MOTOR_DIR, usMotor_Status, 0);
}

void Giro_horario()
{
  
  usMotor_Status = CW;
  motorGo(MOTOR_ESQ, usMotor_Status, usSpeed);
  motorGo(MOTOR_DIR, CCW, usSpeed);
}

void Giro_anti_horario()
{
  
  usMotor_Status = CCW;
  motorGo(MOTOR_ESQ, usMotor_Status, usSpeed);
  motorGo(MOTOR_DIR, CW, usSpeed);
}

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

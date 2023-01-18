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

unsigned short usMotor_Status = FREIO;

//VARIAVEIS DO ANDADOR
float Pi = 3.1415926535;
int X = 0, Y = 0, teta = 0;
int Raio_Roda_Dir = 7.65; //cm
int Raio_Roda_Esq = 7.65;
int b = 57; //Distância entre as rodas

//VELOCDIDADE ANGULAR E LINEAR
float wd_ref = 0.0, we_ref = 0.0;
float we, wd = 0.0;
float V, W;

//VARIAVEIS DE TEMPO
unsigned long TempoAtual;
unsigned long UltimoTempo = 0;
const unsigned long Periodo = 50;

//VARIAVEIS DE CONTROLE DA RODA ESQUERDA
float ctrlP_esq, ctrlI_esq, ctrlD_esq = 0;
float sinal_ctrl_esq = 0;
float erro_esq, ultimo_erro_esq = 0;

//VARIAVEIS DE CONTROLE DA RODA DIREITA
float ctrlP_dir, ctrlI_dir, ctrlD_dir = 0;
float sinal_ctrl_dir = 0;
float erro_dir, ultimo_erro_dir = 0;

//GANHOS A SEREM DEFINIDOS
float kp = 0.002;
float ki = 2.5;
float kd = 0.01;

//VARIAVEIS DE POSIÇÃO
float delta_x;
float delta_y;
float Theta_ref;
float Theta_Robo;
float delta_theta;
float delta_theta2;
float delta_l_ref;
float delta_l

//VARIAVEIS AUXILIARES
int cont = 0;
int comando;
int entrada = 0;
int EnvioX;
int EnvioY;
int EnvioTETA;

//PONTOS FINAIS
X_final = 0;
Y_final = 90;

//GANHOS DE CONTROLE DE POSIÇÃO(A SEREM DEFINIDOS)
float k_theta = 0.02;
float k_l = 0.015;
 
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
  
  while(Serial.available())
  {
    user_input = Serial.read(); //Read user input and trigger appropriate function
    digitalWrite(EN_PIN_1, HIGH);
    digitalWrite(EN_PIN_2, HIGH); 
  }
}

void controle_velocidade_esq(

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

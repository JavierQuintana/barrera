
String readString;
#include <Servo.h> 
#include <Servo.h> 
 
Servo myservo;        // crea un objeto tipo servo para controlar el servo 
int pos ;          // variable para almacenar la posición del servo
byte dato=0; 
int ledArriba = 3; //LED VERDE DE EDUBASICA
int ledCentro = 4; //LED AMARILLO DE EDUBASICA
int ledAbajo = 5; // LED ROJO DE EDUBASICA
///////////////// SENSOR ULTRASONIDOS ENTRADA ///////////////
int trigPinE = 4;
int echoPinE = 2;
long durationE; //tiempo de ida/vuelta
int cmE=0; //Para almacenar el valor obtenido en cm valor=0
///////////////// SENSOR ULTRASONIDOS SALIDA ///////////////
int trigPinS = 6;
int echoPinS = 5;
long durationS; //tiempo de ida/vuelta
int cmS=0; //Para almacenar el valor obtenido en cm valor=0
//////////////////////////////////////////////////////////////////

void setup(){ 
  myservo.attach(7);  // En EduBasica el servo se conecta al pin 7 
  Serial.begin(9600);
  ////////////////// configuramos como salida los leds del semáforo
  pinMode(ledArriba,OUTPUT);
  pinMode(ledAbajo,OUTPUT);
  pinMode(ledCentro,OUTPUT);
  //////////////////// configuramos las entradas y salidas de los ultrasonidos E y S
   pinMode(trigPinE, OUTPUT);
  pinMode(echoPinE, INPUT);
   pinMode(trigPinS, OUTPUT);
  pinMode(echoPinS, INPUT);
 //////////////// empezamos con el semároro en rojo
  digitalWrite(ledArriba, LOW);
  digitalWrite(ledAbajo, HIGH);
  digitalWrite(ledCentro, LOW);
  //////////////////// Cerramos la barrera al principio
  pos=140;        
  myservo.write(pos); 
}

void loop() 
{ 
  digitalWrite(trigPinE, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinE, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinE, LOW);
  durationE = pulseIn(echoPinE, HIGH);
  durationE=durationE/2;
  cmE = durationE/ 29;
  Serial.println(cmE);
  if (cmE<10){ ///////////////////////////HAY UN COCHE EN LA ENTRADA /////////////
      /////////////// PONEMOS AMARILLO EL SEMAFORO
      digitalWrite(ledArriba, LOW);
      digitalWrite(ledAbajo, LOW);
      digitalWrite(ledCentro, HIGH);
      /////////////////// ESPERAMOS A QUE DE LA ORDEN DE SUBIR BARRERA 
      if (Serial.available())
        dato= Serial.read();
      switch(dato) {//Si recibimos una  ...  85=ARRIBA  68=U=ABAJO
         case 85: //ARRIBA
           digitalWrite(ledArriba, HIGH);
           digitalWrite(ledAbajo, LOW);
           digitalWrite(ledCentro, LOW);
           pos=40;        
           myservo.write(pos); 
           delay(1000); 
           dato=0;
           break;
       }
       
  }
  ///////////////////////////////////////////////////////////////////////////
  digitalWrite(trigPinS, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinS, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinS, LOW);
  durationS = pulseIn(echoPinS, HIGH);
  durationS=durationS/2;
  cmS = durationS/ 29;
  Serial.println(cmS);
  if (cmS<10){ ///////////////////////////HAY UN COCHE EN LA SALIDA /////////////
       //////////////// ponemos con el semároro en rojo
      digitalWrite(ledArriba, LOW);
      digitalWrite(ledAbajo, HIGH);
      digitalWrite(ledCentro, LOW);
      //////////////////// Cerramos la barrera
      delay(3000);
      pos=140;        
      myservo.write(pos); 
  }
 
  
} 

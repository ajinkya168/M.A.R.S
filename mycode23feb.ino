float incoming;
//const int m2p1 = 8;
//const int m2p2 = 9;
// const int m2en1 = 10;
//const int m2en2 = 11;
//const int m2dir1 = 12;
//const int m2dir2 = 
float diff;

/*pinout TIVA-c TM4C123GXL
 1=3.3v                       //21=VBUS
 2=PB_5                         22=GND
 3=PB_0                         23=PD_0 SCL(3)
 4=PB_1                         24=PD_1 SDA(3)
 5=PE_4   SCL(2)                25=PD_2
 6=PE_5   SDA(2)                26=PD_3
 7=PB_4                         27=PE_1
 8=PA_5                         28=PE_2
 9=PA_6   SCL(1)                29=PE_3
 10=PA_7  SDA(1)                30=PF_1
 11=PA_2                        31=PF_4
 12=PA_3                        32=PD_7
 13=PA_4                        33=PD_6
 14=PB_6                        34=PC_7
 15=PB_7                        35=PC_6
 16=RESET                       36=PC5
 17=PF_0                        37=PC_4
 18=PE_0                        38=PB_3 SDA(0)
 19=PB_2 SCL(0)                 39=PF_3
 20=GND                         40=PF_2
 
 
 */


/* enable */

const int enablepositive = 24; //pd1
const int enablenegative = 4;  //pb1


/* pulse */

const int pulsepositive = 25 ; //pd2
const int pulsenegative = 5 ;  //pe4


/* direction */

const int directpositive = 26; //pd3
const int directnegative = 6;  //pe5

double angle, pulse;


void setup()
{
  Serial.begin(9600);

  /*enable*/
  pinMode(enablepositive, OUTPUT);
  pinMode(enablenegative, OUTPUT);

  /*pulse*/
  pinMode(pulsepositive, OUTPUT);
  pinMode(pulsenegative, OUTPUT);

  /*direction*/
  pinMode(directpositive, OUTPUT);
  pinMode(directnegative, OUTPUT);

  //  pinMode(m2en1, OUTPUT);
  //  pinMode(m2en2, OUTPUT);
  //  pinMode(m2p1, OUTPUT);
  //  pinMode(m2p2, OUTPUT);
  //  pinMode(m2dir2, OUTPUT);
  //  pinMode(m2dir1, OUTPUT);
}


void loop()
{

  // Serial.println("ENTER THE CURRENT ANGLE :");


  if (Serial.available() > 0)
  {
    incoming = Serial.read();
  }

  digitalWrite(enablenegative, LOW);
  //  digitalWrite(m2en2, HIGH);
  //  digitalWrite(m2p2, LOW);
  //  digitalWrite(m2dir2, LOW);
  digitalWrite(pulsenegative, LOW);
  digitalWrite(directnegative, LOW);

  if (incoming == '3')
  { 
    float x= random(-6.283,6.283);
    //  incoming = x;
    Serial.print("CURRENT ANGLE IS  ") ;
    Serial.println(x);
    //   if (x<0){
    //     Serial.print("MAGNITUDE IS ");
    //    x=x*(-1);
    //    Serial.println(x);
    //   }

    //incoming= (char)incoming;
    Serial.print("NEW ANGLE IS ");    
    //incoming = (double) incoming;
    //incoming = incoming*2;
    Serial.println(incoming-'0');


    diff= incoming - x;
    diff=diff-48;
    Serial.print("DIFF IS ");
    //Serial.println(diff-'0');
    Serial.println(diff);
    // angle = random(-6.823, 6.283);
    // diff = (int) diff;
//    diff=-3.2;



    if (diff > 0)
    {
      pulse = (diff* 800)/6.283;
      pulse = ceil(pulse);
      Serial.println(pulse);
      Serial.println("CLOCKWISE");
      digitalWrite(enablepositive, LOW);
      digitalWrite(directpositive, HIGH);
      // digitalWrite(directnegative, LOW);
      for (int i = 0; i < pulse ; i++)
      {
        digitalWrite(pulsepositive, HIGH);
        delayMicroseconds(500);
        digitalWrite(pulsepositive, LOW);
        delayMicroseconds(500);
      }

      digitalWrite(enablepositive, HIGH);
      delay(100);

    }

    else if (diff < 0)
    {

      pulse = (diff* 800)/6.283;
      pulse = ceil(pulse);
      pulse = pulse * (-1);
      Serial.println(pulse);

      Serial.println("ANTICLOCKWISE");


      digitalWrite(enablepositive, LOW);
      digitalWrite(directpositive, LOW);
      // digitalWrite(directnegative, HIGH);

      for (int i = 0;  i < pulse ; i++)
      {
        digitalWrite(pulsepositive, HIGH);
        delayMicroseconds(500);
        digitalWrite(pulsepositive, LOW);
        delayMicroseconds(500);
      }

      digitalWrite(enablepositive, HIGH);
      delay(100);

    }
  }


}



/* MazeRunner event at IIT,Bombay

Circuit:
 *Arduino Uno
 *2 Servo motors
 *IR Sensor
 *Dual H-Bridge Stepper motor driver
 *Motor IC L293D
 *Supply
 
 created 29 December 2016
 by Shivanjan Chakravorty(The Glitch)
 modified 29 December 2016
 by Shivanjan Chakravorty(The Glitch)
 
 Facebook: @fb/luckysolitaireking
 Github: github.com/Glitchfix
 LinkedIn: in.linkedin.com/in/shivanjan-chakravorty
 E-Mail: schakravorty846@gmail.com
 Phone no.: +91-96-58-965891
*/
#include<EEPROM.h>

int mlA = 5;//Motor 1 Forward for HIGH
int mlB = 6;//Motor 1 Reverse for HIGH
int mrA = 7;//Motor 2 Forward for HIGH
int mrB = 8;//Motor 2 Reverse for HIGH

int A0=A0;//Leftmost IR Sensor
int A1=A1;//Left IR Sensor
int A2=A2;//Middle IR Sensor
int A3=A3;//Right IR Sensor
int A4=A3;//Rightmost IR Sensor*/

int Reset=12;//Reset the values in EEPROM

int x=7;//RUN MODE BUTTON
int i=0;
int ls,l,m,r,rs;
int count=0;
char x;
String c='';
String chck='';

void setup()
{
  // put your setup code here, to run once:
  pinMode(Reset, INPUT);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  
  pinMode(mrA, OUTPUT);
  pinMode(mrB, OUTPUT);
  pinMode(mlA, OUTPUT);
  pinMode(mlB, OUTPUT);
  if(digitalRead(Reset)==HIGH){
	for (i = 0 ; i < EEPROM.length() ; i++) {
    	EEPROM.write(i, 0);
  	}
	i=0;
  }
}

void loop()
{
  ls=digitalRead(A0);
  l=digitalRead(A1);
  m=digitalRead(A2);
  r=digitalRead(A3);
  rs=digitalRead(A4);
  
  
if(ls==0&&l==1&&m==1&&r==0&&rs==0||ls==0&&l==1&&m==0&&r==0&&rs==0)
    {
      left();
    }
    else if(ls==0&&l==0&m==1&&r==1&&rs==0||ls==0&&l==0&m==0&&r==1&&rs==0)
    {
      right();
    }
    else if(ls==1&&l==1&m==1&&r==1&&rs==1)
    {
      solve();
      c='Q'+c;
	for (i = 0 ; i < c.length() ; i++) {
    	EEPROM.write(i, c[i]);
  	}
    }
    else if(ls==1&&l==1&&m==1&&r==0&&rs==0||ls==1&&l==1&&m==0&&r==0&&rs==0||ls==1&&l==0&&m==0&&r==0&&rs==0)
    {
	if(EEPROM[0]=='Q')
	{
		i++;
		x=EEPROM[i]; 
		travel(x);
	}
	else{
      while((ls!=0&&l!=0&&m!=1&&r!=0&&rs!=0)||(ls!=0&&l!=1&&m!=1&&r!=0&&rs!=0)||(ls!=0&&l!=1&&m!=0&&r!=0&&rs!=0))
      {
        ls=digitalRead(A0);
        l=digitalRead(A1);
        m=digitalRead(A2);
        r=digitalRead(A3);
        rs=digitalRead(A4);
        sleft();
      }
      c+='L';
	}
    }
    else if(ls==0&&l==0&&m==0&&r==0&&rs==0)
    {
      while((ls!=0&&l!=0&&m!=1&&r!=0&&rs!=0)||(ls!=0&&l!=1&&m!=1&&r!=0&&rs!=0)||(ls!=0&&l!=1&&m!=0&&r!=0&&rs!=0))
      {
        ls=digitalRead(A0);
        l=digitalRead(A1);
        m=digitalRead(A2);
        r=digitalRead(A3);
        rs=digitalRead(A4);
        sleft();
      }
      c+='B';
    }
    else if(ls==0&&l==0&&m==1&&r==1&&rs==1||ls==0&&l==0&&m==0&&r==1&&rs==1||ls==0&&l==0&&m==0&&r==0&&rs==1)
    {
	if(EEPROM[0]=='Q')
	{
		i++;
		x=EEPROM[i]; 
		travel(x);
	}
	else{
      while((ls!=0&&l!=0&&m!=1&&r!=0&&rs!=0)||(ls!=0&&l!=0&&m!=1&&r!=1&&rs!=0)||(ls!=0&&l!=0&&m!=0&&r!=1&&rs!=0))
      {
        ls=digitalRead(A0);
        l=digitalRead(A1);
        m=digitalRead(A2);
        r=digitalRead(A3);
        rs=digitalRead(A4);
        sright();
      }
      c+='R';
	}
    }
    else
    {
      fwd();
    }
}


/*MOVEMENT*/
void fwd()
{
    digitalWrite(mrA, HIGH);
    digitalWrite(mrB, LOW);
    digitalWrite(mlA, HIGH);
    digitalWrite(mlB, LOW);
}
void stop()
{
    digitalWrite(mrA, LOW);
    digitalWrite(mrB, LOW);
    digitalWrite(mlA, LOW);
    digitalWrite(mlB, LOW);
}
void left()
{
    digitalWrite(mrA, LOW);
    digitalWrite(mrB, LOW);
    digitalWrite(mlA, HIGH);
    digitalWrite(mlB, LOW);
}
void sleft()
{
    digitalWrite(mrA, LOW);
    digitalWrite(mrB, HIGH);
    digitalWrite(mlA, HIGH);
    digitalWrite(mlB, LOW);
}
void right()
{
    digitalWrite(mrA, HIGH); 
    digitalWrite(mrB, LOW);
    digitalWrite(mlA, LOW);
    digitalWrite(mlB, LOW);
}
void sright()
{
    digitalWrite(mrA, HIGH); 
    digitalWrite(mrB, LOW);
    digitalWrite(mlA, LOW);
    digitalWrite(mlB, HIGH);
}


void solve(){
	while(chck!=c){
		chck=c;
		c.replace('LBR','B');
		c.replace('LBS','R');
		c.replace('LBL','S');
		c.replace('SBL','R');
		c.replace('SBS','B');
		c.replace('RBL','B');
	}
}

void travel(char ax)
{
  if(ax=='L')
  {
    sleft();
    delay(200);
    fwd();
    delay(100);
  }
  else if(ax=='R')
  {
    sright();
    delay(200);
    fwd();
    delay(100);
  }
  else
  {
    fwd();
    delay(150);
  }
}

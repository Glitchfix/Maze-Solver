//motor 1 left
int m1a=2;
int m1b=3;
//motor 2 right
int m2a=5;
int m2b=6;

int ir=0;

//left
int lt=30;
int le=31;
//front
int ft=34;
int fe=35;
//right
int rt=38;
int re=39;

String sol="";
String cx="";
int btn;
int i;

float l;
float m;
float r;

int lx,rx;

void setup()
{
  Serial.begin(9600);
  pinMode(lt,OUTPUT);
  pinMode(le,INPUT);
  pinMode(ft,OUTPUT);
  pinMode(fe,INPUT); 
  pinMode(rt,OUTPUT);
  pinMode(re,INPUT);
  btn=digitalRead(52);
  pinMode(m1a,OUTPUT); 
  pinMode(m1b,OUTPUT);
  pinMode(m2a,OUTPUT);
  pinMode(m2b,OUTPUT);

  pinMode(53,INPUT);
}
void loop()
{
  l=leng(lt,le);
  Serial.print("\nL=");
  Serial.println(l);
  m=leng(ft,fe);
  Serial.print("M=");
  Serial.println(m);
  r=leng(rt,re);
  Serial.print("R=");
  Serial.println(r);
  ir=digitalRead(53);
  btn=digitalRead(52);
  if(ir==1)
  {
   solve();
   digitalWrite(m2a, LOW);
    digitalWrite(m2b, LOW);
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, LOW);
   while(btn==0)
   {
    btn=digitalRead(52);
    }   
  }
  if(btn==1){
   i=0;
   if(m>3)//Dead end
   {
    pid();
   }
   else
   {
    switch(sol[i])
    {
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
      case 'S':
        fwd();
        delay(200);
    }
    i++;
   }
  }
  else
  {
  if(m>3)//Dead end
  {
    pid();
  }
  else
  {
    if(l>10)
    {
      left();
      Serial.println("Left");
    }
    else if(r>10)
    {
      right();
      Serial.println("Right");
    }
    else
    {
      uturn();
      Serial.println("U-Turn");
    }
  }
  }
  
}

void left()
{
    cx='L';
    digitalWrite(m2a, HIGH);
    digitalWrite(m2b, LOW);
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, HIGH);
    delay(150);
    fwd();
}

void pid(){
  if(l>r)
    {
      lx--;
      rx++;
    }
    else if(r<l)
    {
      lx++;
      rx--;
    }
    else
    {
      lx=255;
      rx=255;
    }
    if(lx<0)
    {lx=0;}
    if(rx<0)
    {rx=0;}
    
    if(lx>255)
    {lx=255;}
    if(rx>255)
    {rx=255;}
    
    analogWrite(m1a,lx);
    analogWrite(m2a,rx);    
    analogWrite(m1b,0);
    analogWrite(m2b,0);
}

void right()
{
    cx='R';
    digitalWrite(m1a, HIGH);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, HIGH);
    delay(150);
    fwd();
}

void uturn()
{
    cx='B';
    digitalWrite(m1a, HIGH);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, HIGH);
    delay(300);
    fwd();
}

void fwd()
{
    sol+=cx;
    digitalWrite(m1a, HIGH);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, HIGH);
    digitalWrite(m2b, LOW);
    delay(300);    
}

float leng(int t,int e)
{
  int ti;
  float dist;
  /*digitalWrite(t,LOW);
  delayMicroseconds(10);
  digitalWrite(t, HIGH);
  delayMicroseconds(2);
  ti=pulseIn(e, HIGH);
  dist=ti/ 58.2;*/

  digitalWrite(t, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(t, HIGH);
  //delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(t, LOW);
  ti = pulseIn(e, HIGH);
  dist = ti / 58.2;

  
  return dist;
}

void solve()
{
  String a=sol;
  while(sol!=a){
  a=sol;
  sol.replace("LBR","B");
  sol.replace("LBS","R");
  sol.replace("LBL","S");
  sol.replace("SBL","R");
  sol.replace("SBS","B");
  sol.replace("RBL","B");
  }
}

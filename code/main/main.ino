
byte SpMaxL=92;
byte SpMaxR=86;
#define inA1 6
#define inA2 7
#define inB1 8
#define inB2 9

int trang_thai_cu = 200;

void Tien( byte speedL, byte speedR);
void doLine();
int trangThai5CamBien ();
int lechVach(int sens1, int sens2, int sens3, int sens4, int sens5);

void setup() {
  Serial.begin(9600);
  pinMode(6, OUTPUT);//Set chân in1 của dc A là output
  pinMode(7, OUTPUT);//Set chân in2 của dc A là output
  pinMode(8, OUTPUT);//Set chân in1 của dc B là output
  pinMode(9, OUTPUT);//Set chân in2 của dc B là output
  
  pinMode(A4, INPUT);//Set chân cảm biến 1 là input
  pinMode(A3, INPUT);//Set chân cảm biến 2 là input
  pinMode(A2, INPUT);//Set chân cảm biến 3 là input
  pinMode(A1, INPUT);//Set chân cảm biến 4 là input
  pinMode(A0, INPUT);//Set chân cảm biến 5 là input

  digitalWrite(inA1, HIGH);
  digitalWrite(inA2, LOW);
  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW); 
}

void loop() {
  doLine();
}

void doLine()
{
   int trang_thai = trangThai5CamBien();

 if (trang_thai == 0 && trang_thai_cu != 200) {
    trang_thai = trang_thai_cu;
 }
  switch (trang_thai)
  {
    case 200:
      Tien(SpMaxL,SpMaxR);
      break;
    case 0:
      Tien(SpMaxL,5);         // cho quay ph đến khi bắt được line
      break;
    case 1:
      Tien(SpMaxL-10,10);
      break;
    case 2:
      Tien(SpMaxL-15,5);
      break;
    case 3:
      Tien(SpMaxL - 15,0);
      break;
    case -1:
      Tien(10,SpMaxR-10);
      break;
    case -2:
      Tien(5,SpMaxR-15);
      break;
    case -3:
      Tien(0,SpMaxR - 15);
      break;
    default:
      digitalWrite(6, 0);
      digitalWrite(7, 0);
      digitalWrite(8, 0);
      digitalWrite(9, 0);
      break;
  }
  trang_thai_cu = trang_thai;
}
boolean IFSensor (byte PinNumb)
{
  // Có line là 1
  return digitalRead(PinNumb);
}

int trangThai5CamBien ()
{
  /*
      Âm là lệch phải
      Dương là lệch trái
      Mức độ lệch giảm tăng dần : 1 2 3
  */
  int sens1 = IFSensor(A4); // góc trái 
  int sens2 = IFSensor(A3);
  int sens3 = IFSensor(A2);
  int sens4 = IFSensor(A1);
  int sens5 = IFSensor(A0);

  int do_lech = lechVach(sens1, sens2, sens3, sens4, sens5);

  if (do_lech == 0){
    if ((sens1 + sens2 + sens3 + sens4 + sens5) != 0) return 200;
  }

  return do_lech;

}
int lechVach(int sens1, int sens2, int sens3, int sens4, int sens5)
{
  /*
      Âm là lệch phải
      Dương là lệch trái
      Mức độ lệch giảm tăng dần : 1 3 2
  */

  int do_lech = -2 * sens1 - sens2 + sens4 + 2 * sens5;
  switch (do_lech)
  {
    case -3:// cái này là do 2 mắt biên đều chạm vạch
      return -2;
      break;
    case -2:
      return -3;
      break;
    case -1:
      return -1;
      break;
    case 0:
      return 0;
      break;
    case 1:
      return 1;
      break;
    case 2:
      return 3;
      break;
    case 3:
      return 2;
      break;
  }

}
void Tien( byte speedL, byte speedR)
{
  analogWrite(5, speedL);
  analogWrite(10, speedR);
  digitalWrite(inA1, HIGH);
  digitalWrite(inA2, LOW);
  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW);
}

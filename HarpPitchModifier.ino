//A0 pot 0/4
//A1 pot 1/5
//A2 pot 2/6
//A3 pot 3

//D0 Serial Out
//D1 Serial In
//D2 0-3 HIGH side
//D3 4-6 HIGH side
//D4 0-3 LOW side
//D5 4-6 LOW side

//D8 SW1
//D9 LED1
//D10 SW2
//D11 LED2

#define potGroup1_Top 2;
#define potGroup2_Top 3;
#define potGroup1_Bottom 4;
#define potGroup2_Bottom 5;

#define SWBYPASS 8;
#define LEDBYPASS 9;
#define SWPITCHORDER 10;
#define LEDPITCHORDER 11;

bool PITCHORDER = false;
bool BYPASS = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(SWBYPASS, INPUT);
  pinMode(SWPITCHORDER, INPUT);
  pinMode(LEDBYPASS, OUTPUT);
  pinMode(LEDPITCHORDER, OUTPUT);
  pinMode(potGroup1_Top,INPUT);
  pinMode(potGroup1_Bottom,INPUT);
  pinMode(potGroup2_Top,INPUT);
  pinMode(potGroup2_Bottom,INPUT);
  Serial.begin(31250);
  Serial.setTimeout(10);
}

int lastPitchButtonState = LOW;
int lastBypassButtonState = LOW;

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 2) {
    byte midiCMD = Serial.read();
    byte midiPitch = Serial.read();
    byte midiVelocity Serial.read();
    byte outPitch = midiPitch;
    if (!BYPASS) {
      if (midiCMD >= 0x80 && midiCMD <= 0x9F) {
        outPitch = evaluatePitch(midiPitch);
      }
    }
    Serial.write(midiCMD);
    Serial.write(outPitch);
    Serial.write(midiVelocity);
  }
  int pitchButtonState = digitalRead(SWPITCHORDER);
  int bypassButtonState = digitalRead(SWBYPASS);
  if (lastPitchButtonState != pitchButtonState) {
    if (pitchButtonState == HIGH) {
      PITCHORDER = !PITCHORDER;
      if (PITCHORDER) {
        digitalWrite(LEDPITCHORDER,HIGH);
      } else {
        digitalWrite(LEDPITCHORDER,LOW);
      }
    }
    lastPitchButtonState = pitchButtonState;
  }
  if (lastBypassButtonState != bypassButtonState) {
    if (bypassButtonState == HIGH) {
      BYPASS = !BYPASS;
      if (BYPASS) {
        digitalWrite(LEDBYPASS,HIGH);
      } else {
        digitalWrite(LEDBYPASS,LOW);
      }
    }
    lastBypassButtonState = bypassButtonState;
  }
}

int evaluatePot(int potNumber) {
  int analogVal = 0;
  if (potNumber < 4) {
    pinMode(potGroup1_Top,OUTPUT);
    pinMode(potGroup1_Bottom,OUTPUT);
    pinMode(potGroup2_Top,INPUT);
    pinMode(potGroup2_Bottom,INPUT);
    digitalWrite(potGroup1_Top, HIGH);
    digitalWrite(potGroup1_Bottom, LOW);
  } else {
    pinMode(potGroup1_Top,INPUT);
    pinMode(potGroup1_Bottom,INPUT);
    pinMode(potGroup2_Top,OUTPUT);
    pinMode(potGroup2_Bottom,OUTPUT);
    digitalWrite(potGroup2_Top, HIGH);
    digitalWrite(potGroup2_Bottom, LOW);
  }
  switch (potNumber) {
    case 0:
    case 4:
      analogVal = analogRead(A0);
      break;
    case 1:
    case 5:
      analogVal = analogRead(A1);
      break;
    case 2:
    case 7:
      analogVal = analogRead(A2);
      break;
    case 3:
      analogVal = analogRead(A3);
      break;
  }
  if (analogVal < 340) {
    return 1;
  } else if (analogVal >= 340 && analogVal < 680) {
    return 0;
  } else {
    return -1;
  }
}

int evaluatePitch(int pitch) {
  if (PITCHORDER) {
    #Secondary Pitch Order
    # CDE | FGAB
    switch (pitch % 12) {
      case 0: //C
        return pitch + evaluatePot(0);
        break;
      case 2: //D
        return pitch + evaluatePot(1);
        break;
      case 4: //E
        return pitch + evaluatePot(2);
        break;
      case 5: //F
        return pitch + evaluatePot(3);
        break;
      case 7: //G
        return pitch + evaluatePot(4);
        break;
      case 9: //A
        return pitch + evaluatePot(5);
        break;
      case 11: //B
        return pitch + evaluatePot(6);
        break;
      default:
        return pitch;
        break;
    }
  } else {
    #Standard Pitch Order
    # DCB | EFGA
    switch (pitch % 12) {
      case 0: //C
        return pitch + evaluatePot(1);
        break;
      case 2: //D
        return pitch + evaluatePot(0);
        break;
      case 4: //E
        return pitch + evaluatePot(3);
        break;
      case 5: //F
        return pitch + evaluatePot(4);
        break;
      case 7: //G
        return pitch + evaluatePot(5);
        break;
      case 9: //A
        return pitch + evaluatePot(6);
        break;
      case 11: //B
        return pitch + evaluatePot(2);
        break;
      default:
        return pitch;
        break;
    }
  }
}

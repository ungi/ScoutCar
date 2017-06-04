
const char END_OF_LINE = 13; // CR

// Motor A

const int enA = 10;
const int in1 = 9;
const int in2 = 8;

// Motor B

const int enB = 5;
const int in3 = 7;
const int in4 = 6;


// Serial communication protocol

const char C_A = 'a';
const char C_B = 'b';
const char C_BOTH = 'c';

const char C_STOP = '0';
const char C_FORWARD = '1';
const char C_REVERSE = '2';

char MotorSelect = C_A;
char MotorDirection = C_STOP;
char MotorSpeedChar = '0';
int InputIndex = 0;


void setup()
{
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  Serial.begin(9600);
  Serial.flush();
  
}

void loop()
{
  while (Serial.available() > 0)
  {
    char input = (char) Serial.read();
    if (input == END_OF_LINE)
    {
      updateMotors();
      InputIndex = 0;
      Serial.println("Command executed");
    }
    else
    {
      switch (InputIndex)
      {
        case 0:
        { 
          MotorSelect = input;
          break;
        }
        case 1:
        {
          MotorDirection = input;
          break;
        }
        case 2:
        {
          MotorSpeedChar = input;
          break;
        }
        default:
        {
          Serial.println("Input index: " + InputIndex);
          Serial.println("Select: " + MotorSelect);
          Serial.println("Error: Unexpected input index");
          break;
        }
      }
      InputIndex ++;
    }
  }
  
}


void updateMotors()
{
  int mSpeed = 0;
  switch (MotorSpeedChar)
  {
    case '0':
    {
      mSpeed = 0;
      break;
    }
    case '1':
    {
      mSpeed = 100;
      break;
    }
    case '2':
    {
      mSpeed = 120;
      break;
    }
    case '3':
    {
      mSpeed = 140;
      break;
    }
    case '4':
    {
      mSpeed = 200;
      break;
    }
    case '5':
    {
      mSpeed = 250;
      break;
    }
    default:
    {
      mSpeed = 0;
      Serial.println("MotorSpeedChar: " + MotorSpeedChar);
      Serial.println("Error: Invalid motor speed char");
      break;
    }
  }

  if (MotorSelect == C_A)
  {
    if (MotorDirection == C_FORWARD)
    {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
    }
    if (MotorDirection == C_REVERSE)
    {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
    }
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    analogWrite(enA, mSpeed);
  }

  if (MotorSelect == C_B)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    if (MotorDirection == C_FORWARD)
    {
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
    }
    if (MotorDirection == C_REVERSE)
    {
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
    }
    analogWrite(enB, mSpeed);
  }

  if (MotorSelect == C_BOTH)
  {
    if (MotorDirection == C_FORWARD)
    {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
    }
    if (MotorDirection == C_REVERSE)
    {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
    }
    analogWrite(enB, mSpeed);
    analogWrite(enA, mSpeed);
  }

  // Todo: Remove this safety code
  delay (1000);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}


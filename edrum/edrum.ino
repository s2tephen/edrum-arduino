// Stephen Suen, Brad Eckert, Saya Date
// 2.009
// Final Presentation
// UpBeat
// December 8, 2014

////////////////////////////////////////////
///// INITIALIZATION
// intializing drum LED output
const int Crash_R = 8;
const int Crash_G = 9;
const int Crash_B = 10;

// CURRENTLY DISCONNECTED
const int HiHat_R = 30;
const int HiHat_G = 31;
const int HiHat_B = 32;

const int Ride_R = 24;
const int Ride_G = 25;
const int Ride_B = 26;
// THANK YOU

const int LeftTom_R = 2;
const int LeftTom_G = 3;
const int LeftTom_B = 4;

const int RightTom_R = 5;
const int RightTom_G = 6;
const int RightTom_B = 7;

const int Snare_R = 27;
const int Snare_G = 28;
const int Snare_B = 29;

const int FloorTom_R = 11;
const int FloorTom_G = 12;
const int FloorTom_B = 13;

const int Bass_R = 14;
const int Bass_G = 15;
const int Bass_B = 16;

// intializing piezos
//NOTE*******// 0-7 on code correspond to 1-8 on dock
// order of LED --> BGR
//ride --> A8 (piezo), 26,25,24
//big tom --> A7, 13,12,11
//right tom --> 7,6,5, A5
//bass --> 16,15,14, A3
//lefttom --> 4,3,2, A4
//snare --> 29,28,27, A9
//crash --> 10,9,8, A6
//hi-hat --> 32,31,30, A10

const int Crash_P    = A6;
const int HiHat_P    = A10;
const int Ride_P     = A8;
const int LeftTom_P  = A4;
const int RightTom_P = A5;
const int Snare_P    = A9;
const int FloorTom_P = A7;
const int Bass_P     = A3;

//setting thresholds (these need to be adjusted when setting up on drums)
int Crash_T    = 300;
int HiHat_T    = 300;
int Ride_T     = 300;
int LeftTom_T  = 330;
int RightTom_T = 280;
int Snare_T    = 235;
int FloorTom_T = 210;
int Bass_T     = 225;

// setting counter thresholds
int Crash_T2    = 80;
int HiHat_T2    = 80;
int Ride_T2     = 80;
int LeftTom_T2  = 80;
int RightTom_T2 = 100;
int Snare_T2    = 75;
int FloorTom_T2 = 75;
int Bass_T2     = 80;

// array of outputs
int sensors[8]   = {Crash_P, HiHat_P, Ride_P, LeftTom_P, RightTom_P, Snare_P, FloorTom_P, Bass_P};
int thresholds[8] = {Crash_T, HiHat_T, Ride_T, LeftTom_T, RightTom_T, Snare_T, FloorTom_T, Bass_T};
int counterThresholds[8] = {Crash_T2, HiHat_T2, Ride_T2, LeftTom_T2, RightTom_T2, Snare_T2, FloorTom_T2, Bass_T2};

int LED_R[8]     = {Crash_R, HiHat_R, Ride_R, LeftTom_R, RightTom_R, Snare_R, FloorTom_R, Bass_R};
int LED_G[8]     = {Crash_G, HiHat_G, Ride_G, LeftTom_G, RightTom_G, Snare_G, FloorTom_G, Bass_G};
int LED_B[8]     = {Crash_B, HiHat_B, Ride_B, LeftTom_B, RightTom_B, Snare_B, FloorTom_B, Bass_B};

// parser variables
boolean keepComposing = false; // conditional for compose mode
boolean sequenceReceived = false;

const char startDelimiter = '[';
const char endDelimiter   = ']';

int mode = 0;
int length = 0;
int lrdata = 0;

int tracksProcessed = 0;
int thresholdSetter[3];
int metadata[3];
int* track1 = 0;
int* track2 = 0;
int* track3 = 0;
int* lengthsMilli = 0;

// hit variables
boolean track1hit = false;
boolean track2hit = false;
boolean track3hit = false;

// setting up inputs and outputs
void setup()
{  
  pinMode(Crash_R, OUTPUT);
  pinMode(Crash_G, OUTPUT);
  pinMode(Crash_B, OUTPUT);
  
  pinMode(HiHat_R, OUTPUT);
//  pinMode(HiHat_G, OUTPUT);
  pinMode(HiHat_B, OUTPUT);
  
  pinMode(Ride_R, OUTPUT);
  pinMode(Ride_G, OUTPUT);
  pinMode(Ride_B, OUTPUT);
  
  pinMode(LeftTom_R, OUTPUT);
  pinMode(LeftTom_G, OUTPUT);
  pinMode(LeftTom_B, OUTPUT);
  
  pinMode(RightTom_R, OUTPUT);
  pinMode(RightTom_G, OUTPUT);
  pinMode(RightTom_B, OUTPUT);
  
  pinMode(Snare_R, OUTPUT);
  pinMode(Snare_G, OUTPUT);
  pinMode(Snare_B, OUTPUT);
  
  pinMode(FloorTom_R, OUTPUT);
  pinMode(FloorTom_G, OUTPUT);
  pinMode(FloorTom_B, OUTPUT);
  
  pinMode(Bass_R, OUTPUT);
  pinMode(Bass_G, OUTPUT);
  pinMode(Bass_B, OUTPUT);
  
  Serial.begin(115200); 
}

///////////////////////////////////////////////////
///// HELPER FUNCTIONS
// sets threshold of a drum
void setThreshold(int drum, int thresholdId, int value) {
  if (thresholdId == 0) {
    thresholds[drum] = value;
  }
  else if (thresholdId == 1) {
    counterThresholds[drum] = value;
  }
  String output = "[r:" + String(drum) + "," + String(thresholdId) + "," + String(value) + "]";
  Serial.println(output);
}

// sets LED of drum based on RGB values (0 or 1)
// 0, 0, 0 = off
// 1, 0, 0 = red
// 0, 1, 0 = green
// 0, 0, 1 = blue
// 0, 1, 1 = cyan
// 1, 0, 1 = magenta
// 1, 1, 0 = yellow
// 1, 1, 1 = white
void lightLED(int drum, int r, int g, int b) {
  switch (r) {
    case 0:
      digitalWrite(LED_R[drum], LOW);
      break;
    case 1:
      digitalWrite(LED_R[drum], HIGH);
      break;
  }
  switch (g) {
    case 0:
      digitalWrite(LED_G[drum], LOW);
      break;
    case 1:
      digitalWrite(LED_G[drum], HIGH);
      break;
  }
  switch (b) {
    case 0:
      digitalWrite(LED_B[drum], LOW);
      break;
    case 1:
      digitalWrite(LED_B[drum], HIGH);
      break;
  }
}

// turns off all LEDs
void resetLEDS() {
  for (int i = 0; i < 8; i++) {
    lightLED(i, 0, 0, 0);
  } 
}

// detect drum hit
boolean detectDrum(int drum, int threshold, int counterThreshold) { // differential threshold needs to be tweaked
  int counter = 0;
  for (int i = 0; i < 150; i++) {
    int a = analogRead(sensors[drum]);
    //Serial.println(a);
    if (a > threshold) {
      counter++;
    }
  }
  if (counter > counterThreshold) {
    return true;
  }
  else{
    return false;
  }
}

////////////////////////////////////////////
///// COMMS
// listen on serial port
void listening() {
  if (!sequenceReceived) {
    if (Serial.available() > 0) {
      processInput();
    }
  }
//  if (sequenceReceived) {
//    Serial.println("Sequence detected!");
//    Serial.print("mode: ");
//    Serial.println(mode);
//    Serial.print("length: ");
//    Serial.println(length);
//    
//    Serial.print("track 1:");
//    for (int i = 0; i < length; i++) {
//      Serial.print(" ");
//      Serial.print(track1[i]);
//    }
//    Serial.println("");
//    
//    Serial.print("track 2:");
//    for (int i = 0; i < length; i++) {
//      Serial.print(" ");
//      Serial.print(track2[i]);
//    }
//    Serial.println("");
//    
//    Serial.print("track 3:");
//    for (int i = 0; i < length; i++) {
//      Serial.print(" ");
//      Serial.print(track3[i]);
//    }
//    Serial.println("");
//    
//    Serial.print("lengthsMilli:");
//    for (int i = 0; i < length; i++) {
//      Serial.print(" ");
//      Serial.print(lengthsMilli[i]);
//    }
//    Serial.println("");
//    Serial.println("...done.");
//  }  
}

// builds sequence string for parsing
void processInput() {
  static String sequence = "";
  char input = Serial.read();
  switch (input) {
    case startDelimiter:
      sequence = "";
      break;
    case endDelimiter:
      // Serial.print("parsing input: ");
      // Serial.println(sequence);
      parseSequence(sequence);
      break;
    default:
      sequence += input;
      break;
   }
}

// parses strings and assigns to variables
void parseSequence(String sequence) {
  char arrayType = sequence[0];
  if (arrayType == 'r') { // threshold
    splitIntArray(sequence.substring(2), ',', 3, thresholdSetter);
    setThreshold(thresholdSetter[0], thresholdSetter[1], thresholdSetter[2]);
  }
  else if (arrayType == 'm') { // metadata
    splitIntArray(sequence.substring(2), ',', 3, metadata);
    mode = metadata[0];
    length = metadata[1];
    lrdata = metadata[2];
    delete[] track1;
    delete[] track2;
    delete[] track3;
    delete[] lengthsMilli;
  }
  else if (arrayType == 't') { // track
   if (tracksProcessed == 0) {
      track1 = new int[length];
      splitIntArray(sequence.substring(2), ',', length, track1);
    }
    else if (tracksProcessed == 1) {
      track2 = new int[length];
      splitIntArray(sequence.substring(2), ',', length, track2);
    }
    else if (tracksProcessed == 2) { // lengths
      track3 = new int[length];
      splitIntArray(sequence.substring(2), ',', length, track3);
      tracksProcessed = -1; // reset track count
    }
    tracksProcessed++;
  }
  else if (arrayType == 'l') { // lengths
    lengthsMilli = new int[length];
    splitIntArray(sequence.substring(2), ',', length, lengthsMilli);
    sequenceReceived = true;
  }
  else if (arrayType == 'e') { // lengths
    keepComposing = false;
  }
}

// turns 'x,y,z' into pdata = [x, y, z] of type int
void splitIntArray(String array, char delimiter, int length, int pdata[]) {
  String currentString = array;
  int delimiterIndex = 0;
  int i = 0;
  while (i < length) {
    delimiterIndex = currentString.indexOf(delimiter);
    pdata[i] = currentString.substring(0, delimiterIndex).toInt();
    currentString = currentString.substring(delimiterIndex + 1);
    i++;
  }
}

////////////////////////////////////////////
///// DEMO MODE
// play lights only
void demo() {
  long time = millis();
  int extraTime = 1000; // however long we want to keep the loop running
  int index = 0;
  while ((millis() - time) < lengthsMilli[length - 1] + extraTime) { // duration + extraTime
    float currentTime = millis() - time;
  
    if (index < length-1) {
      while (lengthsMilli[index] < currentTime) {
        index++;
        
      }
      //Serial.println("index");
      //Serial.println(index);
      if (currentTime + 300 > lengthsMilli[index]) {
        //Serial.println("resetting");
        resetLEDS();
        //Serial.println("done resetting");
      }
      else {
        if (track1[index] > -1) {
          lightLED(track1[index], 1, 0, 1);
        }
        if (track2[index] > -1) {
          if (lrdata == 0) {
            lightLED(track2[index], 1, 0, 1);
          }
          else {
            lightLED(track2[index], 0, 1, 1);
          }
        }
        if (track3[index] > -1) {
          if (lrdata == 0) {
            lightLED(track3[index], 1, 0, 1);
          }
          else {
            lightLED(track3[index], 1, 1, 0);
          }
        }
      }
    }
  }
  Serial.println("[e]");
  resetLEDS();
}

////////////////////////////////////////////
///// STEP BY STEP MODE
// waits for hits
void Learn()
{
//  Serial.println("LEARN MODE");
  for(int i = 0; i < length; i++)
  {
    // Start with no drums to be played
    // using binary: 0 for do not play, 1 for play  
    int hit_0 = 0;
    int hit_1 = 0;
    int hit_2 = 0;
    
//    Serial.print("  Drums to hit:");
      
    // light up correct drums to be played  
    if(track1[i] > -1)
    {
      digitalWrite(LED_G[track1[i]], HIGH);
      hit_0 = 1;
//      Serial.print(" ");
//      Serial.print(track1[i]);
    }
    
    if(track2[i] > -1)
    {
      digitalWrite(LED_G[track2[i]], HIGH);
      hit_1 = 1;
//      Serial.print(" ");
//      Serial.print(track2[i]);
    }
    
    if(track3[i] > -1)
    {
      digitalWrite(LED_G[track3[i]], HIGH);
      hit_2 = 1;
//      Serial.print(" ");
//      Serial.println(track3[i]);
    }
    
    Serial.println("");
    
    // wait until all drums in sequence have been hit 
    while(hit_0 == 1 || hit_1 == 1 || hit_2 == 1)
    {
      int start_time = millis() - time;
      if(hit_0 == 1 && analogRead(sensors[track1[i]]) > threshold[track1[i]])
      {
        hit_0 = 0;
        String output = "[h:" + String(track1[i]) + "," + String(start_time) + "]";
//        Serial.print("    ");
        Serial.println(output);
      }
        
      if(hit_1 == 1 && analogRead(sensors[track2[i]]) > threshold[track2[i]])
      {
        hit_1 = 0;
        String output = "[h:" + String(track2[i]) + "," + String(start_time) + "]";
//        Serial.print("    ");
        Serial.println(output);
      }
        
      if(hit_2 == 1 && analogRead(sensors[track3[i]]) > threshold[track3[i]])
      {
        hit_2 = 0;
        String output = "[h:" + String(track2[i]) + "," + String(start_time) + "]";
//        Serial.print("    ");
        Serial.println(output);
      }   
    }
    resetLEDS();
  }
  Serial.print("[e]");
}
////////////////////////////////////////////
///// PRACTICE MODE 
// default "karaoke" mode
void practice()
{  
  Serial.println("seq recieved");
  long time = millis();
  int extraTime = 1000; // however long we want to keep the loop running
  int index = 0;
  while ((millis() - time) < lengthsMilli[length - 1] + extraTime) { //duration + extraTime
    for (int i = 0; i < 8; i++) {
      int threshold = thresholds[i];
      int counterThreshold = counterThresholds[i]; // need to make this array with experimentally determined values
      if (detectDrum(i, threshold, counterThreshold)) {
        int t = millis() - time;
        String output = "";
        if (track1[index] == i && !track1hit) {
          output = "[h:" + String(i) + "," + String(t) + ",1]";
          track1hit = true;
          // Serial.print("Correct hit on drum ");
          // Serial.println(i);
        }
        else if (track2[index] == i && !track2hit) {
          output = "[h:" + String(i) + "," + String(t) + ",1]";
          track2hit = true;
          // Serial.print("Correct hit on drum ");
          // Serial.println(i);
        }
        else if (track3[index] == i && !track3hit) {
          output = "[h:" + String(i) + "," + String(t) + ",1]";
          track3hit = true;
          // Serial.print("Correct hit on drum ");
          // Serial.println(i);
        }
        else {
          output = "[h:" + String(i) + "," + String(t) + ",0]";
        }
        Serial.println(output);
      }
    }
    // lighting up LED sequence
    float currentTime = millis() - time;
    
    if (index < length-1) {
      while (lengthsMilli[index] < currentTime) {
        index++;
      }
      if (currentTime + 50 > lengthsMilli[index]) {
        resetLEDS();
        track1hit = false;
        track2hit = false;
        track3hit = false;
      }
      else {
        if (track1[index] > -1 && !track1hit) {
          lightLED(track1[index], 1, 0, 1);
        }
        if (track2[index] > -1 && !track2hit) {
          if (lrdata == 0) {
            lightLED(track2[index], 1, 0, 1);
          }
          else {
            lightLED(track2[index], 0, 1, 1);
          }
        }
        if (track3[index] > -1 && !track3hit) {
          if (lrdata == 0) {
            lightLED(track3[index], 1, 0, 1);
          }
          else {
            lightLED(track3[index], 1, 1, 0);
          }
        }
      }
    }
  }
  Serial.println("[e]");
  resetLEDS();
}

////////////////////////////////////////////
///// COMPOSE MODE
// listen for hits only
// TODO: fix this - gets stuck in while loop
void compose() {
  long time = millis();
   keepComposing = true;
   while (keepComposing == true) {
    for (int i = 0; i < 8; i++) {
      int threshold = thresholds[i];
      int counterThreshold = counterThresholds[i]; 
      if (detectDrum(i, threshold, counterThreshold)) {
        int t = millis() - time;
        String output = "[h:" + String(i) + "," + String(t) + ",1]";
        Serial.println(output);        
      }
    }
    listening();
  }
}

////////////////////////////////////////////
///// MAIN LOOP
// putting everything together
void loop() {
  listening();
  if (sequenceReceived) {
    resetLEDS();
    sequenceReceived = false;
    switch (mode) {
      case 0:
        Serial.print("demo");
        demo();
        break;
      case 1:
        // stepByStep();
        break;
      case 2:
        practice();
        break;
      case 3:
        // loop step by step
        break;
      case 4:
        // loop practice
        break;
      case 5:
        compose();
    }
  }
}  

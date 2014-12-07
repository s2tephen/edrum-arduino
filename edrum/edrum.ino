// Stephen Suen, Brad Eckert, Saya Date
// 2.009
// Final Presentation
// upBeat
// November 17, 2014

// number of beats -- should be a sequence field
float numberOfBeats = 8;
  /// a conditional for compose mode:
boolean keepComposing = false;

// intializing drum LED output
const int Crash_R = 40;
const int Crash_G = 42;
const int Crash_B = 44;

// CURRENTLY DISCONNECTED
const int HiHat_R = 46;
const int HiHat_G = 48;
const int HiHat_B = 50;

const int Ride_R = 31;
const int Ride_G = 33;
const int Ride_B = 35;
// THANK YOU

const int LeftTom_R = 22;
const int LeftTom_G = 24;
const int LeftTom_B = 26;

const int RightTom_R = 28;
const int RightTom_G = 30;
const int RightTom_B = 32;

const int Snare_R = 34;
const int Snare_G = 36;
const int Snare_B = 38;

const int FloorTom_R = 37;
const int FloorTom_G = 39;
const int FloorTom_B = 41;

const int Bass_R = 43;
const int Bass_G = 45;
const int Bass_B = 47;

// intializing piezos 
const int Crash_P    = A0;
const int HiHat_P    = A1;
const int Ride_P     = A2;
const int LeftTom_P  = A3;
const int RightTom_P = A4;
const int Snare_P    = A5;
const int FloorTom_P = A6;
const int Bass_P     = A7;

//setting Thresholds (these need to be adjusted when setting up on drums)
int Crash_T    = 300;
int HiHat_T    = 300;
int Ride_T     = 300;
int LeftTom_T  = 330;
int RightTom_T = 280;
int Snare_T    = 235;
int FloorTom_T = 210;
int Bass_T     = 225;

/// setting counter thresholds
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

boolean sequenceReceived = false;

const char startDelimiter = '[';
const char endDelimiter   = ']';

int mode = 0;
int bpm = 120;
int length = 0;

int tracksProcessed = 0;
int thresholdSetter[3];
int metadata[2];
int* track1 = 0;
int* track2 = 0;
int* track3 = 0;
int* lengthsMilli = 0;

//int mode = 0;
//int action = 0;
//int bpm = 30;
//int length = 8;
//
//int track1[] = {0,0,0,0,0,0,0,0};
//int track2[] = {-1,-1,-1,-1,-1,-1,-1,-1};
//int track3[] = {-1,-1,-1,-1,-1,-1,-1,-1};
//float lengths[] = {1,2,3,4,5,6,7,8};
//float lengthsMilli[] = {0,2000,4000,6000,8000,10000,12000,14000};

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
  pinMode(HiHat_G, OUTPUT);
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
//supplementary functions
// sets the threshold of drum to value
void setThreshold(int drum, int value) {
  thresholds[drum] = value;
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

/////////////////////////////////////////////////
// Detecting Drum hit
boolean detectDrum(int drum, int threshold, int counterThreshold) { // differential threshold needs to be tweaked
  int counter = 0;
  for(int i=0;i<150;i++){
    int a = analogRead(sensors[drum]);
    //Serial.println(a);
    if (a>threshold){
      counter+=1;
    }
  }
  //Serial.println("counter is ");
  //Serial.println("checking drum ");
  //Serial.println(drum);
  //Serial.println(counter);
  if(counter>counterThreshold){
    return true;
  }
  else{
    return false;
  }
}

////////////////////////////////////////////
///// COMMS (OLD)
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
//      Serial.print("parsing input: ");
//      Serial.println(sequence);
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
    splitIntArray(sequence.substring(2), ',', 2, metadata);
    mode = metadata[0];
    length = metadata[1];
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
///// MODE 1: 
//// This is I guess "learn mode" which I need some time to upload again


////////////////////////////////////////////
///// MODE 2: FOLLOW 
//
void Play()
{  
  long time = millis();
  // Serial.println("PLAY MODE");
  float duration = (numberOfBeats*3600)/bpm;
  int extraTime = 1000; // however long we want to keep the loop running
  float del = 1/64; // this is the time we want the note to be off for
        int index = 0;
  while ((millis()-time) < lengthsMilli[length - 1] + extraTime){//<duration+extraTime){
                //Serial.println(millis()-time);
    for(int i=0; i<8; i++){
      int threshold = thresholds[i];
      int counterThreshold = counterThresholds[i]; // need to make this array with experimentally determined values
      if(detectDrum(i,threshold,counterThreshold)){
        int t = millis()-time;
        String output = "";
        if (track1[index] == i && !track1hit) {
          output = "[h:" + String(i) + "," + String(t) + ",1]";
          track1hit = true;
//          Serial.print("Correct hit on drum ");
//          Serial.println(i);
        }
        else if (track2[index] == i && !track2hit) {
          output = "[h:" + String(i) + "," + String(t) + ",1]";
          track2hit = true;
//          Serial.print("Correct hit on drum ");
//          Serial.println(i);
        }
        else if (track3[index] == i && !track3hit) {
          output = "[h:" + String(i) + "," + String(t) + ",1]";
          track3hit = true;
//          Serial.print("Correct hit on drum ");
//          Serial.println(i);
        }
        else {
          output = "[h:" + String(i) + "," + String(t) + ",0]";
        }
        Serial.println(output);
      }
    }
    //Lighting up LED sequence
    float current_beat = (millis()-time)*float(bpm)/3600.0;
      float currentTime = millis()-time;
      //Serial.println("we are on this beat");
      //Serial.print(current_beat);
      //boolean found = false;
    
    if(index<length){
      //Serial.println("i'm in this loop now");
      while(lengthsMilli[index] < currentTime){
        index +=1;
        //Serial.println("updating index");
        //Serial.print(index);
      }
      //Serial.println("index");
      //Serial.println(index);
      if(index == 10000){
      }
      else{
        //if(current_beat + del > lengths[index]){
        if(currentTime + 300 > lengthsMilli[index]){
          resetLEDS();
          track1hit = false;
          track2hit = false;
          track3hit = false;
        }
        else{
          if(track1[index]>-1 && !track1hit){
            lightLED(track1[index],1,0,1);
          }
          if(track2[index]>-1 && !track2hit){
            lightLED(track2[index],1,0,1);
          }
          if(track3[index]>-1 && !track3hit){
            lightLED(track3[index],1,0,1);
          }
        }
      }
    }
  }
  Serial.println("[e]");
  resetLEDS();
}

void compose() {
  long time = millis();
   keepComposing = true;
   while (keepComposing == true){
    for(int i=0; i<8; i++) {
      int threshold = thresholds[i];
      int counterThreshold = counterThresholds[i]; 
      if(detectDrum(i,threshold,counterThreshold)) {
        int t = millis()-time;
        String output = "[h:" + String(i) + "," + String(t) + ",1]"; // this is what i thought you wanted me to print.
        Serial.println(output);        
      }
    }
    listening();
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////
void demo(){
  long time = millis();
  // Serial.println("DEMO MODE");
  float duration = (numberOfBeats*3600)/bpm;
  int extraTime = 1000; // however long we want to keep the loop running
  float del = 1/64; // this is the time we want the note to be off for
  int index = 0;
  while ((millis()-time) < lengthsMilli[length - 1] + extraTime){//<duration+extraTime)
    float currentTime = millis()-time;
  
    if(index<length){
      //Serial.println("i'm in this loop now");
      while(lengthsMilli[index] < currentTime){
        index +=1;
        //Serial.println("updating index");
        //Serial.print(index);
      }
      //Serial.println("index");
      //Serial.println(index);
      //if(current_beat + del > lengths[index])
      if(currentTime + 300 > lengthsMilli[index]){
        resetLEDS();
      }
      else{
        if(track1[index]>-1){
          lightLED(track1[index],1,0,1);
        }
        if(track2[index]>-1){
          lightLED(track2[index],1,0,1);
        }
        if(track3[index]>-1){
          lightLED(track3[index],1,0,1);
        }
      }
    }
  }
  Serial.println("[e]");
  resetLEDS();
}

///////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////
///// Begin Program   

// how long to wait before program loops  
//const int delay_loop = 1000000000;

void loop(){
  listening();
  if (sequenceReceived) {
    resetLEDS();
    sequenceReceived = false;
    if (mode == 0) {
      Play();
    }
    if(mode==1){
      demo();
    }
    if(mode ==3){
      compose(); // for this mode you need to allow the user to say "stop" else it will keep running
    }
    
  }
}  

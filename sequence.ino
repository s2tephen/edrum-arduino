class Sequence {
  public:
    Sequence(int metadata[], int tracks[]);
    ~Sequence();
    void demo(int start, int stop);
    void waitMode(int start, int stop);
    void practice(int start, int stop);
    Sequence record();
    void stop();
};

Sequence::Sequence(int metadata[], int tracks[]) {
  int mode = metadata[0];
  int action = metadata[1];
  int bpm = metadata[2];
  int length = metadata[3];

  int tracksProcessed = 0;
  int metadata[4];
  int* track1 = tracks[0];
  int* track2 = tracks[1];
  int* track3 = tracks[2];
  float* lengths = 0; //TODO Stephen take a look idk what this is
}

Sequence::~Sequence() {}

void Sequence::waitMode(int start, int stop) {
  Serial.println("WAIT MODE");
  for(int i = start; i < stop; i++)
  {
    // Start with no drums to be played
    // using binary: 0 for do not play, 1 for play
    int hit_0 = 0;
    int hit_1 = 0;
    int hit_2 = 0;

    Serial.print("  Drums to hit:");

    // light up correct drums to be played
    if(track1[i] > -1)
    {
      digitalWrite(LED_G[track1[i]], HIGH);
      hit_0 = 1;
      Serial.print(" ");
      Serial.print(track1[i]);
    }

    if(track2[i] > -1)
    {
      digitalWrite(LED_G[track2[i]], HIGH);
      hit_1 = 1;
      Serial.print(" ");
      Serial.print(track2[i]);
    }

    if(track3[i] > -1)
    {
      digitalWrite(LED_G[track3[i]], HIGH);
      hit_2 = 1;
      Serial.print(" ");
      Serial.println(track3[i]);
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
        Serial.print("    ");
        Serial.println(output);
      }

      if(hit_1 == 1 && analogRead(sensors[track2[i]]) > threshold[track2[i]])
      {
        hit_1 = 0;
        String output = "[h:" + String(track2[i]) + "," + String(start_time) + "]";
        Serial.print("    ");
        Serial.println(output);
      }

      if(hit_2 == 1 && analogRead(sensors[track3[i]]) > threshold[track3[i]])
      {
        hit_2 = 0;
        String output = "[h:" + String(track2[i]) + "," + String(start_time) + "]";
        Serial.print("    ");
        Serial.println(output);
      }
    }

    // turn off all drums
    digitalWrite(LED_G[0], LOW);
    digitalWrite(LED_G[1], LOW);
    digitalWrite(LED_G[2], LOW);
    digitalWrite(LED_G[3], LOW);
    digitalWrite(LED_G[4], LOW);
    digitalWrite(LED_G[5], LOW);
    digitalWrite(LED_G[6], LOW);
    digitalWrite(LED_G[7], LOW);

    digitalWrite(LED_R[0], LOW);
    digitalWrite(LED_R[1], LOW);
    digitalWrite(LED_R[2], LOW);
    digitalWrite(LED_R[3], LOW);
    digitalWrite(LED_R[4], LOW);
    digitalWrite(LED_R[5], LOW);
    digitalWrite(LED_R[6], LOW);
    digitalWrite(LED_R[7], LOW);

    digitalWrite(LED_B[0], LOW);
    digitalWrite(LED_B[1], LOW);
    digitalWrite(LED_B[2], LOW);
    digitalWrite(LED_B[3], LOW);
    digitalWrite(LED_B[4], LOW);
    digitalWrite(LED_B[5], LOW);
    digitalWrite(LED_B[6], LOW);
    digitalWrite(LED_B[7], LOW);

    delay(500);
  }

  Serial.println("[e]");
}


void Sequence::demo(int start, int stop) {
  boolean songEnd = false;
  for(int i=start; i < stop; i++ ){
      int led_time = (lengths[i]/bpm)*60000;
 //Turning on LEDs of corresponding drums
      if (track1[i] > -1)
      {
        digitalWrite(LED_G[track1[i]], HIGH);
      }
      if(track2[i] > -1)
      {
        digitalWrite(LED_G[track2[i]], HIGH);
      }
      if(track3[i] > -1)
      {
        digitalWrite(LED_G[track3[i]], HIGH);
      }


//
//    //How long LED Stays on
      delay(led_time/2); //This delay would change based on size of note later intialized in an array
//
//    //turning off LEDs
      if (track1[i] > -1)
      {
        digitalWrite(LED_G[track1[i]], LOW);
      }
      if(track2[i] > -1)
      {
       digitalWrite(LED_G[track2[i]], LOW);
      }
      if(track3[i] > -1)
     {
       digitalWrite(LED_G[track3[i]], LOW);
     }
     delay(led_time/2); // this delay is part of the shared delay; delay between notes
     if(i==length-1){
       delay(3000);
       songEnd == true;
     }
    }
  }

///// MODE 2: FOLLOW
///// this mode currently does not allow for accuracy readings, can be implemented later on now
///// that we know how to do simulateous hit detection (refer to mode 1)

// Values to change, discuss with andrew for appropriate rhythem
//const float led_time_actual = 400; // how long led stays on
//const float note_delay_actual = 200; // timing between notes (ie time between different leds turning on)
//const float speed_multiplier = 2; // speed you want to play at relative to "actual" playing speed
//
//float led_time = led_time_actual / speed_multiplier;
//float note_delay = note_delay_actual / speed_multiplier;
//
void Sequnece::practice(int start, int stop) {
  boolean songEnd = false;
  for(int i=start; i < stop; i++ ) {
    int led_time = (lengths[i]/bpm)*60000;
    //Turning on LEDs of corresponding drums
    if (track1[i] > -1)
    {
      digitalWrite(LED_G[track1[i]], HIGH);
    }
    if(track2[i] > -1)
    {
      digitalWrite(LED_G[track2[i]], HIGH);
    }
    if(track3[i] > -1)
    {
      digitalWrite(LED_G[track3[i]], HIGH);
    }

    //How long LED Stays on
    delay(led_time/2); //This delay would change based on size of note later intialized in an array

    //turning off LEDs
    if (track1[i] > -1)
    {
      digitalWrite(LED_G[track1[i]], LOW);
    }
    if(track2[i] > -1)
    {
     digitalWrite(LED_G[track2[i]], LOW);
    }
    if(track3[i] > -1)
    {
      digitalWrite(LED_G[track3[i]], LOW);
    }
    delay(led_time/2); // this delay is part of the shared delay; delay between notes
    if(i==length-1){
      delay(3000);
      songEnd == true;
    }
  }
  //keep getting feedback till the song ends
  while(songEnd == false) {
    feedback();
  }
}

void Sequence::stop() {
  //TODO
}

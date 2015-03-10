/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

int blip_length_ms = 200;
int blip_interval_ms = 50;
int letter_interval_ms = 150;

void morse_string(char* str);
void morse_char(char c);
void morse_short();
void morse_long();
void morse_blip(int div);
void led_on();
void led_off();

unsigned char blip_table[36] = {
   72, 144, 148, 112,  32, 132, 120, 128, // A - H
   64, 142, 116, 136,  88,  80, 124, 140, // I - P
  154, 104,  96,  48, 100, 130, 108, 146, // Q - X
  150, 152, // Y, Z
  
  // 1, 2, 3, 4, 5, 6, 7, 8, 9, 0
  175, 167, 163, 161, 160, 176, 184, 188, 190, 191
};


// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  morse_str("SOS");
}

void morse_str(char* str) {
  char c;
  int index = 0;
  while (c = str[index++]) {
    morse_char(c);
    delay(letter_interval_ms);
  }
}

void morse_char(char c) {
  if (c < 'A' || c > 'Z') {
     return;
  }
 
  unsigned char blip = blip_table[c - 'A'];
  
  int count_mask = 0xE0;
  int blip_mask = 0x1F;
  
  int count = (blip & count_mask) >> 5;
  int packed = (blip & blip_mask);
  
  int blips[5];
  blips[0] = packed >> 4 & 0x01;
  blips[1] = packed >> 3 & 0x01;
  blips[2] = packed >> 2 & 0x01;
  blips[3] = packed >> 1 & 0x01;
  blips[4] = packed >> 0 & 0x01;
  
  for (int i = 0; i < count; ++i) {
    if (blips[i]) {
      morse_long();
    } else {
      morse_short();
    }
  }
}

void morse_blip(int div) {
  led_on();
  delay(blip_length_ms / div);
  led_off();
  delay(blip_interval_ms);
}

void morse_short() {
  morse_blip(2);
}

void morse_long() {
  morse_blip(1);
}

void led_on() {
  digitalWrite(led, HIGH);
}

void led_off() {
  digitalWrite(led, LOW);
}

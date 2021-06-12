/*
 * GC Injector CLI
 * Programmer: Christian Wagner
 * Date Modified: 06/12/2021
 * Version: 1.0
 */
// globals
int serial_read = 0;
String serial_str = "";
char serial_in = ' ';

// prototypes
void(* resetFunc) (void) = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("GC Injector Version 1 CLI");
  Serial.println();
  Serial.print("> ");
}

void loop() {
  // state machine for serial reading
  if(Serial.available() > 0) {
    serial_in = Serial.read();
    if(serial_in == 13) {
      serial_read = 1;
    } else {
      Serial.print(serial_in);
      serial_str += serial_in;
    }
  } else if (serial_read == 1) {
    Serial.println('\n');
    // serial data came in
    // parse and do stuff
    serial_str.trim();
    if(serial_str.compareTo("help") == 0) {
      Serial.println("---------- Help Menu ----------");
      Serial.println(" help     poweroff     restart     reset");
    } else if (serial_str.compareTo("restart") == 0) {
      // reset arduino
      // TODO: also call reset
      Serial.println("Restarting...");
      Serial.println();
      delay(1000);
      resetFunc();
    } else if (serial_str.compareTo("reset") == 0) {
      // reset this CLI and motor settings
      // TODO: figure this out
    } else {
      Serial.print("Error: ");
      Serial.print(serial_str);
      Serial.println(" - command not found.");
    }
    Serial.print('\n');
    Serial.print("> ");
    serial_str = "";
    serial_read = 0;
  }
  //delay(500);
}

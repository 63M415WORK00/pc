// Define the pin numbers for the RGB LED
int redPin = 9;    // Connect to the red pin of the LED
int greenPin = 6; // Connect to the green pin of the LED
int bluePin = 3;  // Connect to the blue pin of the LED

// Function to set the color on the RGB LED


void setup() {
  // Set the RGB pins as output
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // Display color 1 (red)
  digitalWrite(redPin, 0);
  digitalWrite(greenPin, 0);
  digitalWrite(bluePin, 0);
  delay(1000);

  digitalWrite(redPin, 0);
  digitalWrite(greenPin, 1);
  digitalWrite(bluePin, 1);
  delay(1000);

  digitalWrite(redPin, 0);
  digitalWrite(greenPin, 0);
  digitalWrite(bluePin, 1);
  delay(1000);

  digitalWrite(redPin, 1);
  digitalWrite(greenPin, 0);
  digitalWrite(bluePin, 1);
  delay(1000);

  digitalWrite(redPin, 1);
  digitalWrite(greenPin, 0);
  digitalWrite(bluePin, 0);
  delay(1000);

  digitalWrite(redPin, 1);
  digitalWrite(greenPin, 1);
  digitalWrite(bluePin, 0);
  delay(1000);

  digitalWrite(redPin, 0);
  digitalWrite(greenPin, 1);
  digitalWrite(bluePin, 0);
  delay(1000);
}

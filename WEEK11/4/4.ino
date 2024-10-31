// Define the pin numbers for each segment
const int segment_a = 2; 
const int segment_b = 3; 
const int segment_c = 4;
const int segment_d = 5;
const int segment_e = 6;
const int segment_f = 7;
const int segment_g = 8;

// Define the pin numbers for the common pins of the two digits
const int common1 = 12; // Common pin for the first digit (left digit)
const int common2 = 13; // Common pin for the second digit (right digit)

// Define the number array for displaying digits 0-9 on the 7-segment display
int num_array[10][7] = {  
  { 1,1,1,1,1,1,0 },    // 0
  { 0,1,1,0,0,0,0 },    // 1
  { 1,1,0,1,1,0,1 },    // 2
  { 1,1,1,1,0,0,1 },    // 3
  { 0,1,1,0,0,1,1 },    // 4
  { 1,0,1,1,0,1,1 },    // 5
  { 1,0,1,1,1,1,1 },    // 6
  { 1,1,1,0,0,0,0 },    // 7
  { 1,1,1,1,1,1,1 },    // 8
  { 1,1,1,0,0,1,1 }};   // 9

// Array to store the number sequences: 66, 07, 00, 65
int number_sequence[4][2] = { {6, 6}, {0, 7}, {0, 0}, {6, 5} };

void setup() { 
  // Set pin modes for each segment
  pinMode(segment_a, OUTPUT);   
  pinMode(segment_b, OUTPUT);   
  pinMode(segment_c, OUTPUT);   
  pinMode(segment_d, OUTPUT);   
  pinMode(segment_e, OUTPUT);   
  pinMode(segment_f, OUTPUT);   
  pinMode(segment_g, OUTPUT);

  // Set pin modes for the common pins
  pinMode(common1, OUTPUT);
  pinMode(common2, OUTPUT);
}

void loop() {
  // Loop through the number sequence
  for (int i = 0; i < 4; i++) {
    // แสดงตัวเลขสลับกันเป็นเวลา 1 วินาที
    showNumberForTime(number_sequence[i][0], number_sequence[i][1], 1000);
  }
}

// ฟังก์ชันแสดงตัวเลขสองหลักเป็นเวลาที่กำหนด
void showNumberForTime(int left_digit, int right_digit, int duration) {
  unsigned long startTime = millis();  // เก็บเวลาที่เริ่มแสดงผล

  while (millis() - startTime < duration) {
    // แสดงหลักซ้าย
    digitalWrite(common2, HIGH);       // ปิดหลักขวา
    displayDigit(left_digit);          // แสดงหลักซ้าย
    digitalWrite(common1, LOW);        // เปิดหลักซ้าย
    delay(5);                          // รอเล็กน้อย

    // แสดงหลักขวา
    digitalWrite(common1, HIGH);       // ปิดหลักซ้าย
    displayDigit(right_digit);         // แสดงหลักขวา
    digitalWrite(common2, LOW);        // เปิดหลักขวา
    delay(5);                          // รอเล็กน้อย
  }
}

// Function to display a specific digit on the 7-segment display
void displayDigit(int digit) {
  // Set each segment according to the num_array for the given digit
  digitalWrite(segment_a, num_array[digit][0]);
  digitalWrite(segment_b, num_array[digit][1]);
  digitalWrite(segment_c, num_array[digit][2]);
  digitalWrite(segment_d, num_array[digit][3]);
  digitalWrite(segment_e, num_array[digit][4]);
  digitalWrite(segment_f, num_array[digit][5]);
  digitalWrite(segment_g, num_array[digit][6]);
}

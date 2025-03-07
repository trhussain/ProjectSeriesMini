
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C  // Check your OLED's address if different

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int earX = 10;    // Initial X position
int earY = 10;    // Initial Y position
int xSpeed = 2;   // Speed in X direction
int ySpeed = 2;   // Speed in Y direction

void displaySetup() {
    Wire.begin(22, 23); // SDA / SCL
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }

    //display.setBrightness(255);  // SSD1306 no attribute for this 
    display.clearDisplay();
    display.display();
}

void playBouncingEarsAnimation() {
    display.clearDisplay();

    // Draw ears (two circles)
    display.fillCircle(earX, earY, 8, SSD1306_WHITE);  // Left Ear
    display.fillCircle(earX + 20, earY, 8, SSD1306_WHITE);  // Right Ear

    // Draw face
    display.fillCircle(earX + 10, earY + 15, 10, SSD1306_WHITE);

    // Bouncing logic
    earX += xSpeed;
    earY += ySpeed;

    if (earX <= 0 || earX + 20 >= SCREEN_WIDTH) xSpeed = -xSpeed;
    if (earY <= 0 || earY + 15 >= SCREEN_HEIGHT) ySpeed = -ySpeed;

    display.display();
    delay(50);
}


void fillScreenMaxBrightness() {
    display.clearDisplay();  // Clear any previous content
    display.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
    display.display();  // Refresh the display
}

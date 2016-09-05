#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define WIFI_AP "Your wifi SSID"
#define WIFI_PASSWORD "Your wifi password"
#define SCRIPT_URL "http://your.server.com/weather_script.php"

// SCL GPIO5
// SDA GPIO4
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 48)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void showData(String caption, String caption2, String value, String units) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.clearDisplay();
  display.println(caption);
  display.setCursor(0,10);
  display.println(caption2);
  display.setTextSize(2);
  display.setCursor(0,20);
  display.println(value);
  display.setTextSize(1);
  display.setCursor(0,40);
  display.println(units);
  display.display();
  delay(1);
}

void showDataSmall(String caption, String caption2, String value, String units) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.clearDisplay();
  display.println(caption);
  display.setCursor(0,10);
  display.println(value);
  display.setTextSize(1);
  display.setCursor(0,30);
  display.println(units);
  display.display();
  delay(1);
}

void setup() {

    Serial.begin(115200);
   // Serial.setDebugOutput(true);

    Serial.println();
    Serial.println();
    Serial.println();

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 64x48)
    display.display();
    display.clearDisplay();

    for(uint8_t t = 4; t > 0; t--) {
        Serial.printf("[SETUP] WAIT %d...\n", t);
        Serial.flush();
        delay(1000);
    }

    // connect to wifi
    WiFi.begin(WIFI_AP, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("--------------------------");
}

void loop() {
    // wait for WiFi connection
    if((WiFi.status() == WL_CONNECTED)) {

        HTTPClient http;

        Serial.print("[HTTP] begin...\n");
        // GET to PHP script where data are being parsed and sent to D1 mini.
        // At the backend there is also default location specified.
        http.begin(SCRIPT_URL); //HTTP GET

        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                Serial.println(payload);

                char *p = (char*)payload.c_str();
                char *str;
                int i = 0;
                String temperature = "";
                while ((str = strtok_r(p, ";", &p)) != NULL) // delimiter is the semicolon
                {
                  String s = String(str);

                  switch (i) // switch index of displayed data
                  {
                    case 0:
                    temperature = String(str).substring(5);
                    showData("Actual", "temp", temperature, "deg. C");
                    delay(15000);
                    break;

                    case 1:
                    showData("Actual", "pressure", s, "HPa");
                    delay(5000);
                    break;

                    case 2:
                    s.replace(" ", "\n");
                    showDataSmall("Weather", "", s, "");
                    delay(5000);
                    break;

                    case 3:
                    showData("Tommorow", "temp", s, "deg. C");
                    delay(5000);
                    break;

                    case 4:
                    showData("Tommorow", "at night", s, "deg. C");
                    delay(5000);
                    break;

                    case 5:
                    s.replace(" ", "\n");
                    showDataSmall("Tommorow", "", s, "");
                    delay(5000);
                    break;

                    case 6:
                    showData("Day after", "temp", s, "deg. C");
                    delay(5000);
                    break;

                    case 7:
                    showData("Day after", "at night", s, "deg. C");
                    delay(5000);
                    break;

                    case 8:
                    s.replace(" ", "\n");
                    showDataSmall("Day after", "", s, "");
                    delay(5000);
                    break;

                    case 9:
                    showData("In 3 days", "temp", s, "deg. C");
                    delay(5000);
                    break;

                    case 10:
                    showData("In 3 days", "at night", s, "deg. C");
                    delay(5000);
                    break;

                    case 11:
                    s.replace(" ", "\n");
                    showDataSmall("In 3 days", "", s, "");
                    delay(5000);
                    break;
                  }
                  i++;
                }

                showData("Actual", "temp", temperature, "deg. C");
            }
        } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

    // Waits a minute so we don't overwhelm the data source's requests limit. Check API and PHP script.
    delay(60000);
}

#define BLYNK_TEMPLATE_ID "TMPL3UuwDnZ-c"
#define BLYNK_TEMPLATE_NAME "IGNITION"
#define BLYNK_DEVICE_NAME "IGNITION"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Replace with your Wi-Fi credentials
const char* ssid = "Y51";
const char* password = "12345678";

// Replace with your Blynk authentication token
char auth[] = "-GU2ipnGT4koa2B-zUv53oMZ983xFwtt";

// Define pin assignments
#define RELAY_PIN 13  // GPIO5 for the relay
#define BUZZER_PIN 4  // GPIO4 for the buzzer (D2 on most ESP8266 boards)

// Track relay state
bool relayState = false;

void setup() {
  // Start serial communication
  Serial.begin(115200);

  // Configure relay and buzzer pins
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Ensure relay is OFF initially
  digitalWrite(BUZZER_PIN, LOW); // Ensure buzzer is OFF initially

  // Connect to Wi-Fi and Blynk
  Blynk.begin(auth, ssid, password);
  Serial.println("Connecting to Wi-Fi and Blynk...");
}

void loop() {
  Blynk.run(); // Run Blynk service
}

// Virtual Pin V1 for toggle control
BLYNK_WRITE(V1) {
  relayState = param.asInt(); // Read button state (0 or 1)
  digitalWrite(RELAY_PIN, relayState ? HIGH : LOW);
  digitalWrite(BUZZER_PIN, relayState ? HIGH : LOW);

  // Print relay state to Serial Monitor
  Serial.println(relayState ? "Relay ON, Ignition successful!" : "Relay OFF");

  // Send a notification using logEvent
  if (relayState) {
    Blynk.logEvent("ignition_success", "Ignition successful!");
  }
}

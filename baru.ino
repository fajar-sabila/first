#include <DHT.h>

// Create an instance of the DHT sensor
#define DHTPIN 5
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Raindrop sensor pin
#define RAIN_SENSOR_PIN 13

// Rain intensity variable
int rainValue = 0;

void printMembershipDegree(const char* label, float value) {
  if (value > 0) {
    Serial.print(label);
    Serial.print(": ");
    Serial.println(value);
  }
}

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize the DHT sensor
  dht.begin();

  // Set the rain sensor pin as input
  pinMode(RAIN_SENSOR_PIN, INPUT);
}

void loop() {
  // Read the temperature and humidity from the DHT sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float rainIntensity = analogRead(RAIN_SENSOR_PIN);
  rainIntensity = map(rainIntensity, 0, 4095, 100, 0);

  // Determine the membership degree for temperature linguistic variables
  float coldDegree = 0.0;
  float medium_tDegree = 0.0;
  float warmDegree = 0.0;
  float hotDegree = 0.0;

   if (temperature == 0 ) {
    coldDegree = 1.0;
} else if (temperature > 0 && temperature < 15) {
    coldDegree = (15 - temperature) / (15 - 0);
    medium_tDegree = (temperature - 10) / (20 - 10);
  } else if (temperature == 20) {
    medium_tDegree = 1.0;
} else if (temperature > 15 && temperature < 20) {
medium_tDegree = (temperature - 10) / (20 - 10);
} else if (temperature > 20 && temperature < 30) {
medium_tDegree = (30 - temperature) / (30 - 20);
    warmDegree = (temperature - 25) / (35 - 25);
  } else if (temperature == 35) {
    warmDegree = 1.0;
} else if (temperature > 30 && temperature < 35) {
warmDegree = (temperature - 25) / (35 - 25);
    hotDegree = (temperature - 30) / (45 - 30);
} else if (temperature > 35 && temperature <= 45) {
warmDegree = (45 - temperature) / (45 - 35);
hotDegree = (temperature - 30) / (45 - 35);
}





  // Determine the membership degree for humidity linguistic variables
  float dryDegree = 0.0;
  float comfortableDegree = 0.0;
  float humidDegree = 0.0;
  float stickyDegree = 0.0;

if (humidity == 0) {
    dryDegree = 1.0;
  } else if (humidity > 0 && humidity < 30) {
    dryDegree = (30 - humidity) / (30 - 0);
    comfortableDegree = (humidity - 20) / (35 - 20);
  } else if (humidity == 35) {
    comfortableDegree = 1.0;
  } else if (humidity >= 30 && humidity <= 35) {
    comfortableDegree = (humidity - 20) / (35 - 20);
  } else if (humidity > 35 && humidity < 50) {
    comfortableDegree = (50 - humidity) / (50 - 35);
    humidDegree = (humidity - 40) / (55 - 40);
  } else if (humidity >= 50 && humidity <= 55) {
    humidDegree = (humidity - 40) / (55 - 40);
  } else if (humidity > 55 && humidity <= 70) {
    humidDegree = (70 - humidity) / (70 - 55);
    stickyDegree = (humidity - 60) / (100 - 60);
  } else if (humidity > 70 && humidity <= 100) {
    stickyDegree = (humidity - 60) / (100 - 60);
  } else if (humidity > 100) {
    stickyDegree = 1.0;
  }


  // Determine the membership degree for rain intensity linguistic variables
  float veryLowDegree = 0.0;
  float lowDegree = 0.0;
  float medium_rDegree = 0.0;
  float highDegree = 0.0;

  if (rainIntensity >= 0 && rainIntensity <= 15) {
    veryLowDegree = 1.0;
  } else if (rainIntensity > 10 && rainIntensity < 20) {
    veryLowDegree = (20 - rainIntensity) / (20 - 10);
    lowDegree = (rainIntensity - 10) / (20 - 10);
  } else if (rainIntensity >= 10 && rainIntensity <= 30) {
    lowDegree = 1.0;
  } else if (rainIntensity > 25 && rainIntensity < 35) {
    lowDegree = (35 - rainIntensity) / (35 - 25);
    medium_rDegree = (rainIntensity - 25) / (35 - 25);
  } else if (rainIntensity >= 25 && rainIntensity <= 45) {
    medium_rDegree = 1.0;
  } else if (rainIntensity > 30 && rainIntensity < 45) {
    medium_rDegree = (45 - rainIntensity) / (45 - 30);
    highDegree = (rainIntensity - 30) / (45 - 30);
  } else if (rainIntensity >= 30) {
    highDegree = 1.0;
  }

  // Print the temperature, humidity, rain intensity, and membership degrees
    Serial.println("--- Sensor Readings ---");
  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.print("Humidity: ");
  Serial.println(humidity);
  Serial.print("Rain Intensity: ");
  Serial.println(rainIntensity);
  Serial.println("--- Membership Degrees ---");
  Serial.println("Temperature:");
  printMembershipDegree("Cold", coldDegree);
  printMembershipDegree("Medium", medium_tDegree);
  printMembershipDegree("Warm", warmDegree);
  printMembershipDegree("Hot", hotDegree);
  Serial.println("Humidity:");
  printMembershipDegree("Dry", dryDegree);
  printMembershipDegree("Comfortable", comfortableDegree);
  printMembershipDegree("Humid", humidDegree);
  printMembershipDegree("Sticky", stickyDegree);
  Serial.println("Rain Intensity:");
  printMembershipDegree("Very Low", veryLowDegree);
  printMembershipDegree("Low", lowDegree);
  printMembershipDegree("Medium", medium_rDegree);
  printMembershipDegree("High", highDegree);
  delay(15000);
}
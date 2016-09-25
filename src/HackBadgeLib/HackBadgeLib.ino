#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "HackBadge.hpp"
#include "wifi_pass.h"

// #define USE_OTA

HackBadge badge;

const uint8_t  LED_PIN  = 2;
const char*    HOSTNAME = "badge000";
const uint16_t PORT     = 13337;

void setup() {
	uint8_t i;
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, HIGH);
	for (i = 0; i < 8; i++)
	{
		badge.writePixel(i,i,255);
	}
	#ifdef USE_OTA
	WiFi.mode(WIFI_AP);
	WiFi.begin(WIFI_SSID, WIFI_PASS);
	while (WiFi.waitForConnectResult() != WL_CONNECTED)
	{
		digitalWrite(LED_PIN, LOW);
		delay(500);
		digitalWrite(LED_PIN, HIGH);
		ESP.restart();
	}
	ArduinoOTA.setHostname(HOSTNAME);
	ArduinoOTA.setPort(PORT);
	ArduinoOTA.begin();
	#endif
}

void loop() {
	size_t i;
	for (i = 0; i < HackBadge::PIXELS_PER_ROW; i++)
	{
		size_t x = (HackBadge::PIXELS_PER_ROW - i) - 1;
		
		badge.clear();
		badge.writeText(x, "HackRPI!", 8);
		badge.drawFor(62);
	}
	ArduinoOTA.handle();
}

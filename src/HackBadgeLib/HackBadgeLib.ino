#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "HackBadge.hpp"
#include "wifi_pass.h"

// #define USE_OTA

HackBadge badge;

const uint8_t  LED_PIN      = 2;
const char*    HOSTNAME     = "badge000";
const uint16_t PORT         = 13337;
const char*    DISPLAY_TEXT = "HackRPI! ";

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
	size_t j;
	size_t width = badge.textWidth(DISPLAY_TEXT);
	for (i = 0; i < width + 1; i++)
	{		
		badge.clear();
		badge.writeText(0 - i, DISPLAY_TEXT);
		badge.writeText(width + 1 - i, DISPLAY_TEXT);
		badge.drawFor(200);
	}
	ArduinoOTA.handle();
}

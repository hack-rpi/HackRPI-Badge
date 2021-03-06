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
	Serial.begin(115200);
	#ifdef USE_OTA
	WiFi.mode(WIFI_STA);
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
	ArduinoOTA.setPassword(OTA_PASS);
	ArduinoOTA.onStart([]() {
		Serial.println("Start");
	});
	ArduinoOTA.onEnd([]() {
		Serial.println("\nEnd");
	});
	ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
		Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
	});
	ArduinoOTA.onError([](ota_error_t error) {
		Serial.printf("Error[%u]: ", error);
		if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
		else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
		else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
		else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
		else if (error == OTA_END_ERROR) Serial.println("End Failed");
	});
	ArduinoOTA.begin();
	#endif
}

void loop() {
	ArduinoOTA.handle();
	// Brightness test
	/*
	for (i = 0; i < 16; i++)
	{
		uint8_t j;
		for (j = 0; j < 8; j++)
		{
			badge.writePixel(i, j, i);
		}
	}
	badge.drawFor(200);
	*/
	// Scrolling text test
	/*
	size_t i;
	size_t j;
	size_t width = badge.textWidth(DISPLAY_TEXT);
	for (i = 0; i < width + 1; i++)
	{
		badge.clear();
		badge.writeText(0 - i, DISPLAY_TEXT, 255);
		badge.writeText(width + 1 - i, DISPLAY_TEXT, 255);
		badge.drawFor(200);
		ArduinoOTA.handle();
	}*/
	// Input test
	static size_t x = 0;
	static uint8_t prevButtons = 0;
	size_t width = badge.textWidth(DISPLAY_TEXT);
	uint8_t buttons = badge.readInputs();
	
	badge.clear();
	char characters[3];
	uint8_t i;
	uint8_t upper = (buttons >> 4) & 0x0F;
	uint8_t lower = buttons & 0x0F;
	if (upper >= 10)
	{
		characters[0] = 'A' + upper - 10;
	}
	else
	{
		characters[0] = '0' + upper;
	}
	if (lower >= 10)
	{
		characters[1] = 'A' + lower - 10;
	}
	else
	{
		characters[1] = '0' + lower;
	}
	characters[2] = '\0';
	badge.writeText(0, characters, 255);
	//badge.writeText(0 - x, DISPLAY_TEXT, 255);
	//badge.writeText(width + 1 - x, DISPLAY_TEXT, 255);
	
	if (buttons & 0b100)
	{
		x++;
	}
	/*if (buttons & 0b100 && !(prevButtons & 0b100))
	{
		uint32_t startTime = millis();
		uint8_t  buttonHeld = 1;
		while ((uint32_t)(millis() - startTime) <= 20)
		{
			buttons = badge.readInputs();
			if (!(buttons & 0b100))
			{
				buttonHeld = 0;
				break;
			}
			badge.drawFor(1);
		}
		if (buttonHeld)
		{
			x++;
		}
	}*/
	x %= (width + 1);
	prevButtons = buttons;
	badge.drawFor(100);	
}

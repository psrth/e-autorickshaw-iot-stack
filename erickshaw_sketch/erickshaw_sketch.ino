/* IoT Enabled Auto-Rickshaws 
 * NodeMCU ESP8266 AWS IoT
 * 
 * A program that reads sensor data and then transmits it to AWS IOT Core instance.
 * Uses the pubsubclient library to enable MQTT data transmission.
 * 
 * Author: Parth Sharma
 */


// A. BASIC SETUP
// -------------------------------------------------------------

// Library Imports
#include <time.h>
#include "sntp.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Connection to a WiFi Network
const char* ssid = "Rishit's OnePlus";
const char* password = "IMMA1234";

// AWS Connection Endpoint
const char* awsEndpoint = "a1bqj2b9wz8nh3-ats.iot.ap-south-1.amazonaws.com";

// -------------------------------------------------------------



// B. AWS CERTIFICATES
// -------------------------------------------------------------

// 1. xxxxxxxxxx-certificate.pem.crt
static const char certificatePemCrt[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUUt+DdQseqxcI/Gqo9YIy2EDdwn0wDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIyMTIwNTE2NDI1
MFoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALYHWlpPrNN0OL44mV03
Ap/5SwrDk/YBRogvdEOEV9hkMjMBVCCsdOaHmLLPUkM0KVlGXDrEDyOhA93fMWzx
jn+JB+5bTqc6bqNc1HRs15NwmmpPMnK/y3bjleonDsBGPi1bUisn52lVigkXvFU2
OSNjdLxIFMIK2da0cGQikg1D9avnyVamtVIqkgDBai/PVYhDT43xSnBCYz8DqbEx
una37NqiYMEd0Q8j7r+/+OPthMwJ7UYMmsEx5GbLJtZRRKPr/Q+Ak7vfR+F/1RXM
3Db3nmnih8uSgNguDn5Bf1QUqJ2dS/aVxQbI1eMIg2oxUTdgop0XiBM+yoeMFNA5
3lECAwEAAaNgMF4wHwYDVR0jBBgwFoAUK7Fxbgy4wruwYnwM7BrUvj8HRQAwHQYD
VR0OBBYEFBcS1h5tk9dUFjPadnYc8CPlmZ6tMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQAatoJnNTJXo9Ik09dbkV2hIzKk
KrzXR/sGn9gD7c/30unAE7eEqWIHnAb0P+cQoJvwwzFe28/UfAwhkiNxIHxf5nMs
oGRqNCzWnRVO3DZ3IvtsVZqBNju34bTKRZS4oOlT7HIuUODgS1t4GriGdghofy7r
3IHQIeMwDnUunnvmqMHHpf5AokzqblFPdyMoT/BVvYXFQ73mUsb46rJQkxKZoxz/
zBNF04fzeVBjNPexY/3AkTP6nZkB82b0BGp/OldN0P5F4ktr3jSWEb8oVPST8nEU
xFt8ZpGdsWe9DYTSbUzc4HHtB+REhu8FeJYrjgEB8U68aojxrU0uqccCScI1
-----END CERTIFICATE-----
)EOF";

// 2. xxxxxxxxxx-private.pem.key
static const char privatePemKey[] PROGMEM = R"EOF(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEAtgdaWk+s03Q4vjiZXTcCn/lLCsOT9gFGiC90Q4RX2GQyMwFU
IKx05oeYss9SQzQpWUZcOsQPI6ED3d8xbPGOf4kH7ltOpzpuo1zUdGzXk3Caak8y
cr/LduOV6icOwEY+LVtSKyfnaVWKCRe8VTY5I2N0vEgUwgrZ1rRwZCKSDUP1q+fJ
Vqa1UiqSAMFqL89ViENPjfFKcEJjPwOpsTG6drfs2qJgwR3RDyPuv7/44+2EzAnt
RgyawTHkZssm1lFEo+v9D4CTu99H4X/VFczcNveeaeKHy5KA2C4OfkF/VBSonZ1L
9pXFBsjV4wiDajFRN2CinReIEz7Kh4wU0DneUQIDAQABAoIBAAywvIrZTSo8ywvv
9Dk8cZFnluS8N9+JvToXXNqsKleqvJkzuYLBozDDOVEWBR0sUMmpjxqFuqx4OEXK
nq6CtLWNfyEN+pDMERSQjztCr1DXI9zPgqvfVTcHrNbzPCMJgqI04Kijko2Uahgy
MG4cZqVh9Kx/tfrFOOSwFbnVcys7eJKqmnY6s2a2HLUPWX7vft58FsPSLGWIe+B0
OuGT9EZjkApfJvl7FE5yQ1nmEqOlMjW8xkbQXBiN7zYaN1Ji1n+bJN6pWIfJhlYQ
Bg1oBMqIYaKi9K4fRJqouTb1JfIPKLqnRKrwWpqKHG4YmnIR/TTCASl10eCl9KZf
NWX06xUCgYEA3vQLAWPhFbVTpR4hajhvHp1Pk6M0DzsMfEQArklBbCovr9dsFmDw
5NyKLwkBkLIuCKkAI/f254cdrG3JljFeXz5+ig67Ecu9ICb6jWgKsEVWxFgegrzy
v9je4PHKwmZvBTfogbWum+kItcF1si1ywusT5qIpPthJkL+mZD1b57sCgYEA0QJt
nF3V8ufkA0mawgmWA5h6hxX/Y+bjPELkUKNW55PBTwB0sDPMAMmDStOhojNwJ6XQ
BNTpqm9ckPIlgynXrA2Jb/0BZIPTJXRZ6BFgG8bBgf1Wdry2IAcildaDzGGCvlut
UfIuEFtmMw6+4eV7Tf10PWIGzuQfAdhEDoa/M2MCgYAgWj12mC3DXqqinTqwFTxa
ru0rOVWGmET5i0yl/c9WiNCerZ3rqWmLbE1JAf+OJaz0aMGydnsHod22db/44XUW
URU/p1+R94ScM8vL1Tsn1QgAOeFDi3OWTzwYXD3V89NMaI5+tASAb1JqPYZ8soei
rUYYA5QEoJIcRRM6HIVHnQKBgAcvay899pX0LN2EEULsa3DSNBwiwHXhwRwYPJsd
EmbBqJqbrGdGUJQSWWYgImVeGVPzmlQgMaw/SdJd0LZSoOx0Rq5H511aPs8B0flt
Z31s9sgOOoO4dxZgyGqYRk2naIQ8yJeRmM3NJpVIw30mk3eZ5/4YOZ2xL/OzSJur
PDV7AoGBAMZ48eVV93dBPVyWMniIxovoQvtkk5oFWtlBoC+Wyi/TPO947wncHczq
8T/lJyhV5Y+Qq6ZTZwdE6TSNfpM5GOOcB8oiO/EmiF9bnLtjr3MuxFNIK0wwgCDG
xnAwRKFLyCAxMo71/mprwGkPbyB0S4k43+p2xwPkr8yMFrd/bamp
-----END RSA PRIVATE KEY-----
)EOF";

// 3. AWS IOT CA certificate
static const char caPemCrt[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Onboarding AWS Certificates to pubsubclient
BearSSL::X509List client_crt(certificatePemCrt);
BearSSL::PrivateKey client_key(privatePemKey);
BearSSL::X509List rootCert(caPemCrt);

WiFiClientSecure wiFiClient;
void msgReceived(char* topic, byte* payload, unsigned int len);
PubSubClient pubSubClient(awsEndpoint, 8883, msgReceived, wiFiClient); 

// -------------------------------------------------------------

// PRIMARY CODE
// -------------------------------------------------------------
void setup() {
  Serial.begin(115200); // setting baud rate to 115200
  Serial.println();
  Serial.println("IOT Enabled Auto Rickshaws");

  // WRITE CODE BELOW THIS


  Serial.print("Connecting to "); Serial.print(ssid);
  WiFi.begin(ssid, password);
  WiFi.waitForConnectResult();
  Serial.print(", WiFi connected, IP address: "); Serial.println(WiFi.localIP());

  // get current time, otherwise certificates are flagged as expired
  sntp_stop(); //speeds up the connection with UDP servers
  sntp_init(); // speeds up the connection with UDP servers
  setCurrentTime();

  wiFiClient.setClientRSACert(&client_crt, &client_key);
  wiFiClient.setTrustAnchors(&rootCert);
}

unsigned long lastPublish;
int msgCount;

void loop() {
  pubSubCheckConnect();
  // WRITE CODE HERE



  // JSON format parsing strings
  const char* speed1 = "{\"speed\": ";
  const char* pressure1 = ", \"pressure\": ";
  const char* gyro1 = ", \"gyro\": ";
  const char* close = "}";

  // values returned to the AWS Core
  char* speed = "34";
  char* pressure = "20";
  char* gyro = "250";

  // method to consolidate and publish data to AWS every 5 seconds
  if (millis() - lastPublish > 5000) {
    String msg = String(speed1) + String(speed) + String(pressure1) + String(pressure) + String(gyro1) + String(gyro) + String(close);
    pubSubClient.publish("outTopic", msg.c_str());
    Serial.print("Published: "); 
    Serial.println(msg);
    lastPublish = millis();
  }
}

// handler to acknowledge AWS handshake
void msgReceived(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received on "); Serial.print(topic); Serial.print(": ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

// handler to connect to AWS IOT Core Endpoint
void pubSubCheckConnect() {
  if ( ! pubSubClient.connected()) {
    Serial.print("PubSubClient connecting to: "); Serial.print(awsEndpoint);
    while ( ! pubSubClient.connected()) {
      Serial.print(".");
      pubSubClient.connect("ESPthing");
    }
    Serial.println(" connected");
    pubSubClient.subscribe("inTopic");
  }
  pubSubClient.loop();
}

// handler to set current time for certificate validation
void setCurrentTime() {
  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");

  Serial.print("Waiting for NTP time sync: ");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("");
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.print("Current time: "); Serial.print(asctime(&timeinfo));
}


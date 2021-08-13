#ifndef _EXAMPLE_KVS_WEBRTC_H_
#define _EXAMPLE_KVS_WEBRTC_H_

void example_kvs_webrtc(void);

/* Enter your AWS KVS key here */
#define KVS_WEBRTC_ACCESS_KEY   "xxxxxxxxxxxxxxxxxxxx"
#define KVS_WEBRTC_SECRET_KEY   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"

/* Setting your signaling channel name */
#define KVS_WEBRTC_CHANNEL_NAME "My_KVS_Signaling_Channel"

/* Cert path */
#define TEMP_CERT_PATH          "0://cert.pem"  // path to CA cert

/*
 * Testing Amazon KVS WebRTC with IAM user key is easy but it is not recommended.
 * With AWS IoT Thing credentials, it can be managed more securely.
 * (https://iotlabtpe.github.io/Amazon-KVS-WebRTC-WorkShop/lab/lab-4.html)
 */
#define ENABLE_KVS_WEBRTC_IOT_CREDENTIAL        0
#if ENABLE_KVS_WEBRTC_IOT_CREDENTIAL
#define KVS_WEBRTC_IOT_CREDENTIAL_ENDPOINT      "c22uhtun2z6h1u.credentials.iot.us-west-2.amazonaws.com"  // IoT credentials endpoint
#define KVS_WEBRTC_CERTIFICATE                  "0://certificate.pem.crt"   // path to iot certificate
#define KVS_WEBRTC_PRIVATE_KEY                  "0://private.pem.key"  // path to iot private key
#define KVS_WEBRTC_ROLE_ALIAS                   "KVSWebRTCIoTCredentialIAMRoleAlias"  // IoT role alias
#define KVS_WEBRTC_THING_NAME                   KVS_WEBRTC_CHANNEL_NAME  // iot thing name, recommended to be same as your channel name
#endif
   
/* log level */
#define KVS_WEBRTC_LOG_LEVEL    LOG_LEVEL_WARN  //LOG_LEVEL_VERBOSE

/* Video resolution setting */
#include "sensor.h"
#if SENSOR_USE == SENSOR_PS5270
    #define KVS_VIDEO_HEIGHT    VIDEO_1440SQR_HEIGHT
    #define KVS_VIDEO_WIDTH     VIDEO_1440SQR_WIDTH
#else
    #define KVS_VIDEO_HEIGHT    VIDEO_720P_HEIGHT   //VIDEO_1080P_HEIGHT
    #define KVS_VIDEO_WIDTH     VIDEO_720P_WIDTH    //VIDEO_1080P_WIDTH
#endif
#define KVS_VIDEO_OUTPUT_BUFFER_SIZE    KVS_VIDEO_HEIGHT*KVS_VIDEO_WIDTH/10

/* Audio format setting */
#define AUDIO_G711_MULAW        1
#define AUDIO_G711_ALAW         0
#define AUDIO_OPUS              0

/* Enable two-way audio communication (not support opus format now)*/
//#define ENABLE_AUDIO_SENDRECV

/* (Not Ready Now) Enable data channel */
//#define ENABLE_DATA_CHANNEL
   
/************************************************************************************************/
#define KVS_WEBRTC_IOT_CREDENTIAL_ENDPOINT      "c22uhtun2z6h1u.credentials.iot.us-west-2.amazonaws.com"  // IoT credentials endpoint
#define KVS_WEBRTC_ROLE_ALIAS                   "KVSWebRTCIoTCredentialIAMRoleAlias"  // IoT role alias
#define KVS_WEBRTC_THING_NAME                   KVS_WEBRTC_CHANNEL_NAME  // iot thing name, recommended to be same as your channel name
   
#define PRODUCER_ROOT_CA \
"-----BEGIN CERTIFICATE-----\n"\
"MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n"\
"ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n"\
"b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n"\
"MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n"\
"b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n"\
"ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n"\
"9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n"\
"IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n"\
"VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n"\
"93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n"\
"jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n"\
"AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n"\
"A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n"\
"U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n"\
"N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n"\
"o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n"\
"5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n"\
"rqXRfboQnoZsG4q5WTP468SQvvG5\n"\
"-----END CERTIFICATE-----"

#define PRODUCER_CERTIFICATE \
"-----BEGIN CERTIFICATE-----\n"\
"MIIDWTCCAkGgAwIBAgIUGXg4cKmy3tIG6i7em31hFAOjlFMwDQYJKoZIhvcNAQEL\n"\
"BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\n"\
"SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIxMDgxMzAyMDA1\n"\
"OVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\n"\
"ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAJrLV38Ci1k9e9r5q5vp\n"\
"OhK8LjaAxCOdhCE17M1qX4tA01uju2qnPB4pgoViDbgsMZ8W+2NPhD9he3aPbMEo\n"\
"usGpgzHWaLH/ohuObR7sgUCNo8pHuKgMTHeibtdgTH2mCcr60b1z/UQG82DzAgZd\n"\
"AGV4u9zcOHkUvtiCChBHcmqhndvOJ/yX1CWe6nstRqi2GqAO60rn89P1ls2cWldN\n"\
"6Knn+ANVp8XnMLcB021Xto6DQbdgHd2lXbw8yLfQYZ7fInkQiw/D/fPVZGEZlIom\n"\
"T1Nark7oKIrGSLchUrod/BqTReXMoSQGgt3Pabm03IKufLD4gum0scaTX6zSVUyK\n"\
"t90CAwEAAaNgMF4wHwYDVR0jBBgwFoAUK05LCny+LCz77jdaLsbuiaINd6MwHQYD\n"\
"VR0OBBYEFJLh+4zmDdsPRzxLdB47vA9/FMblMAwGA1UdEwEB/wQCMAAwDgYDVR0P\n"\
"AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQBUFJTvRVD4tRXXEuZLQwGsJfOg\n"\
"DZ+S2hlndcfZXIyTkiTe7ExofX96bDGU298pd43HSn4PrXvm3+xlAiViX2VOrirw\n"\
"i41CbyhGcBVEFuPi+TE4P8/GYaIYk6aoaUvBu2heIBPt/w88q5O4AbJ6AvXVJmWr\n"\
"wzpeKA7nUzI8AvABGp7Ax8otM2N4Ra3UO58kqmpowbsU6HRktMGhCR/O0I0DUquG\n"\
"Ykcxse8bogWNyPf1cw2aMJJFNCcSdPS+v+r5U28zVzS+oXP50txXAkxWlJHVW5oi\n"\
"lQUuxwMzcpRYF4nQ7JxPoAS+lqIstvlLMgd/pD+Y2BqnBzjHlEATVKU/D1nI\n"\
"-----END CERTIFICATE-----"

#define PRODUCER_PRIVATE_KEY \
"-----BEGIN RSA PRIVATE KEY-----\n"\
"-----END RSA PRIVATE KEY-----"


#endif /* _EXAMPLE_KVS_WEBRTC_H_ */


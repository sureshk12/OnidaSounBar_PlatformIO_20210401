/*
 * Copyright 2010-2015 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Additions Copyright 2016 Espressif Systems (Shanghai) PTE LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

/**
 * @file aws_iot_certifcates.c
 * @brief File to store the AWS certificates in the form of arrays
 */

#ifdef __cplusplus
extern "C"
{
#endif

    //eu-west-1
    const char rootCA[] = {"-----BEGIN CERTIFICATE-----\n\
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n\
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n\
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n\
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n\
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n\
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n\
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n\
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n\
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n\
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n\
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n\
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n\
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n\
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n\
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n\
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n\
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n\
rqXRfboQnoZsG4q5WTP468SQvvG5\n\
-----END CERTIFICATE-----\n"};

    const char certificate[] = {"-----BEGIN CERTIFICATE-----\n\
MIIDWjCCAkKgAwIBAgIVAPxmRMy1Z5+1w2/icoGuZhyNL1I4MA0GCSqGSIb3DQEB\n\
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n\
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMjAxMjIxMTIy\n\
MTZaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n\
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDE9D7DSNrm9KPyeqcN\n\
r+bJlzZVJAlAXs4MZ+sAeOps1hW3RS1frpYNU0l08XgdgnRkQOETIdWRTJWcj+z+\n\
evd6OsDDhYLujiC8R8Z3CLlYllN+lbK01a3imsesldZOz79KQb8Zq1jr+y3GcvZO\n\
Ya1qNi4YPZgitygjNOSNoEERhN4eDTuXUWpHxF/HN3wq14JL4jXa0w8aTy9JYwk8\n\
uA54tv6orpf/JQR0Vnnb+bmWGbJE5/Ts7LoeDTSD6X8vECbxuQ+YevBQ4snV7l2v\n\
RvifkZo5G5aky/oAfgRQVi2Gj6W3FNRxjbMDRgj2Yzfk9ommZlLNwHUmw8stIZii\n\
vMKPAgMBAAGjYDBeMB8GA1UdIwQYMBaAFAYTwCLT5+Pkqp5Z8+XRYNVadeA5MB0G\n\
A1UdDgQWBBQcZkMJZhhH9/y1kAIiBxuvCIvwhTAMBgNVHRMBAf8EAjAAMA4GA1Ud\n\
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAoO3EooRNnjx+ff32xvj7+6DE\n\
CkJaRburoqkVJkr3bgKI4ge/ioQgzwhCll9jZaXXPH2+8HJksL3KV5vC9XK27P9V\n\
raC8A4+jLQ9DKcc72ABEkz9Iik8NlVRzO8zWXr5ljbNVvU+gHUM31amzmpx+Oc4F\n\
GYTwUGaUKv5IPxR51Oyl4syjO6PfyXYcMV2/C6JmJgLqzcUaSJ6d4iD/mxievfNB\n\
2MVVa7r9347VKy0o4kINJv5+njILlaXXGTfYml6QPOmt5qwCU/oc5zdS1bvGTycC\n\
GVvYZkZhce5UfCIUd7vWfKey8zciw8Lb4y1OvNtA8kA19zsYDPGirkh7rxDEKw==\n\
-----END CERTIFICATE-----\n"};

    const char privateKey[] = {"-----BEGIN RSA PRIVATE KEY-----\n\
MIIEpAIBAAKCAQEAxPQ+w0ja5vSj8nqnDa/myZc2VSQJQF7ODGfrAHjqbNYVt0Ut\n\
X66WDVNJdPF4HYJ0ZEDhEyHVkUyVnI/s/nr3ejrAw4WC7o4gvEfGdwi5WJZTfpWy\n\
tNWt4prHrJXWTs+/SkG/GatY6/stxnL2TmGtajYuGD2YIrcoIzTkjaBBEYTeHg07\n\
l1FqR8Rfxzd8KteCS+I12tMPGk8vSWMJPLgOeLb+qK6X/yUEdFZ52/m5lhmyROf0\n\
7Oy6Hg00g+l/LxAm8bkPmHrwUOLJ1e5dr0b4n5GaORuWpMv6AH4EUFYtho+ltxTU\n\
cY2zA0YI9mM35PaJpmZSzcB1JsPLLSGYorzCjwIDAQABAoIBAHQBTIpneg+4nmwu\n\
1ABaz/uC5gyl6hERBhoGh0NC9Qjf2/CTfVMzGMyGdui7ZT00XmvCTw+eyRUI38JU\n\
f4mwUd2bh3hiRilOa3eaawoniEvmVw1jDNw4U2/6LIu5wX2wHYKWUQHEi96Kln6h\n\
rfOi0qqRePrsJJSl/q0l9Ux5zHmNGK9xKTMJNOZwjAAXufgoOWJ5BrmobrSPZnrQ\n\
8H/hvCcX6urY/IdQKZyfoXvYPdyBOQO4VFEcvqLXvGW5Gq8Q5DynfiEa/WN02qfC\n\
CAMXWwjF4jnFMijayXRGZIFwx0HIIzQuqssJw6q6d7SOGiHdoKulYj3B2/EGYeiz\n\
sSOz/RECgYEA8bHsdch8meOUa+14wTvXi0ZMuHtp6Yqr/KzDjFVDRRZ2kMSTDL11\n\
FwtkeNikuygJhO44dKpsbB4N6Yeu4jGT3BJ/BJx9dHCjBi3mGYl74EEDvfxIEumn\n\
vElcRRbbqfw1ZDukXSQj62TuC8xe1MTVr6P+CsidrDkclLdBvYivYWcCgYEA0Jxs\n\
RD6re++PvCNO99ebkRxQyAmNa8zWIX5JIZOiJiOxJwltHU9iXgCEWb0fEJVRMX2X\n\
yqJaNmE0t+Rj8N0EruXp3TGAqtITMmLSxIxNDdmoMG0H9eSjVyRQjob25Dei4DIp\n\
6lyyN0VUKM8RXIN/GD+bTTtZ9vfWc9vG67gElJkCgYEA5ya49TSXJj5ndokZEgV/\n\
cW38dftiIb9EGVXJd28b9Pk0z+OQl4CieTWmE4VulqgF4qJKUBmltAlSWOQxN5ce\n\
yDzQScK4oSIQaBqBlC7O0HydbZfX/m6EwyiOHG1uDDZvgbsgyQuFZt2SZKpCj87o\n\
ZyC6F+oiEdJVKU3Si8gro0UCgYBsnfV1Nxg8iIhTUiMMwpM6Y/7fmLGsvlODzugu\n\
9lqH9y+G/s50Y1/5R9Whj+n7zXMgDJ+bHxtPkx9K3Dz5LWsB0a4JwHuY9ZaPNos9\n\
UTvRiVGcHTj229v8RGk5PKaSPzGsABJ491jHlG50bRRCEil7q6ql9NAr2fEsE/On\n\
ygGAiQKBgQDTrmBqf9j3DjH2N59qXNE3zCVEUpF1712S2P75xDSiQl9iq0eesE5W\n\
UHJTiwsZUbfSjXKDXFQ9dXC/cQSE91FRCRYF3YpfdGiiXXdZEYeBet1fnClfch9H\n\
iwwtLSWO6xm9joWSsYrfYsL8u8md4CEYSinynfoE0p7tFdaDXyHKQA==\n\
-----END RSA PRIVATE KEY-----\n"};

#ifdef __cplusplus
}
#endif
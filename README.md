# E - Auto Rickshaw — IOT Tech Stack

## Setting up AWS IOT Core

---

![AWS Core Image](/resources/aws-core.png)

1. Created an IOT Thing on AWS Core `(ap-south-1)`
2. Generated root access policies `iot.*` and `*`
3. Applied policies to device certificate
4. Converted device certificates `(.key)` files to NodeMCU ESP8266 compatible `(.der)` files using **OpenSSL**.

```bash
> openssl x509 -in xxxxxxxxxx-certificate.pem.crt -out cert.der -outform DER
> openssl rsa -in xxxxxxxxxx-private.pem.key -out private.der -outform DER
> openssl x509 -in AmazonRootCA1.pem -out ca.der -outform DER
```

5. Installed **pubsubclient** for MQTT connectivity
6. Successfully connected to AWS IoT Core and subscribed to "outTopic" for data stream

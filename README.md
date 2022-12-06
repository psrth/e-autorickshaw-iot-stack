# E - Auto Rickshaw — IOT Tech Stack

## Overview

## Architecture

## Frontend

The client application for the IoT E-Auto Rickshaw is built using **[@vercel/next.js[(https://github.com/vercel/next.js/)**, a modern web-app framework built on top of **React.js**.

### Local Installation

1. Navigate to the client repository.

```
cd e-autorickshaw-iot-stack/erickshaw-client
```

2. Install Node dependencies using **NPM**.

```
npm install
```

3. Run the Development Server.

```
npm run dev
```

### Deployment

**Live Client Application**

- Client deploys live at [erickshaw-iot-stack](https://e-autorickshaw-iot-stack.vercel.app/).

**Setup and Settings**

- The client app deploys using **[Vercel](https://vercel.com).**
- Deploy configuration shown below:

![Vercel Config Image](/resources/vercel-config.png)

## Backend and DevOps (Data Management, AWS IoT Core, MQTT and API)

### Setting up AWS IOT Core

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

### Using a Flask Server as an API

- MQTT architecture sends data to an AWS IoT Core livestream
- Flask server (hosted on [ide.goorm.io](https://ide.goorm.io)) acts as a validated endpoint for AWS IoT Core to stream data from the outTopic topic
- AWS IOT Core uses the `POST` route to send data to the live Flask server
- server then uses `SQL` to store values in a database
- a `GET` request exists to return most recent value in the updated `SQL` database

**Instructions for running Flask Server**

1. Initialise SQL Database

```bash
> python3 init_db.py
```

2. Run Flask Application

```bash
> new run flask
```

**Finally, we get the resulting API endpoint:**

- [Flask Server — GET route](https://parth-iot-intro.run-ap-south1.goorm.io/aws_iot_get)
  ![Flask GET request Image](/resources/flask-get.png)

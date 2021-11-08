# esp8266 Now Range Test

ESP8266 sender and receiver using ESP NOW. Aim of this repo is to provide you with a simplies code to test range of ESP Now. You will need two ESP8266 boards. Build and upload receiver and sender to them. Sender send a message every 100ms.

Receiver flashs internal LED everytime it receives a message. This allows you to walk around and easily check whether internal LED on receiver is blinking and thus has a connection.

Sender also flash internal LED everytime has received a confirmation,

## Run

- Clone or download this repo and open it in VS Code with installed PlatformIO extension.
- Connect ESP8266 with USB cable.
- Select correct TTY port.
- Comment and uncomment _env_default_ line in _platformio.ini_ file.
- Build and upload it to ESP8266

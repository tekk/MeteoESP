# MeteoESP
## Weather Station for Wemos D1 mini with official 64x48 OLED shield

### Project is created in _PlatformIO IDE_
http://platformio.org/platformio-ide

There you can install libraries directly via console command in the IDE.
Find libs here http://platformio.org/lib and install for example: `> platformio lib install 13` to install _Adafruit GFX library_ (not needed...) Then you need some hosting space, for the server-side script which parses data for Wemos D1 mini. It's a tiny PHP script. If you don't have any hosting space, you can register for any of the free hosting services. You'll also need to fill in _Wunderground API_ key (free registration needed) and location ID in the PHP source file on the server. The PHP script is in directory `server-script`. Copy it to server for example with Filezilla client.

#### [Working example video here](https://youtu.be/ubzbj7ghyDk)

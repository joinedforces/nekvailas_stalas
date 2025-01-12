Main RPI hardware layer
=========

A simple combination of libraries for reading data from [rfid_reader](https://github.com/joinedforces/nekvailas_stalas/tree/master/rfid_reader) via I2C

------

Dependencies
-------
- This code is cardinally linked to [WiringPi library](http://wiringpi.com/)
- Binary also needs root access to work because of access to **/dev/mem**
- Using **libcurl** to submit event to remote server


### compile and install

#### getting dependencies

    sudo apt-get update
    sudo apt-get install git-core libcurl4-gnutls-dev
	git clone git://git.drogon.net/wiringPi /tmp/wiringPi
	cd /tmp/wiringPi
	./build
	cd -
	rm -r /tmp/wiringPi

#### compiling and test running

    make all
    sudo ./stalasd

#### installing and starting as daemon

    sudo make install
    sudo service stalasd start

**NOTE:** installed package should start on system boot

**NOTE:** In some cases service fails to install/uninstall due to: https://github.com/raspberrypi/linux/issues/530

    sudo apt-get remove wolfram-engine


## Outgoing data

**example data submitted to remote server**

    [
    {"time":{"sec":1398619851,"usec":844563},"type":"TableShake","data":{}},
    {"time":{"sec":1398619851,"usec":846044},"type":"AutoGoal","data":{"team":1}},
    {"time":{"sec":1398619851,"usec":847409},"type":"CardSwipe","data":{"team":0,"player":1,"card_id":123456789}}
    ]

**example remote server code**

    <?php
    $data = file_get_contents('php://input');
    do_magic($data);
	header('X-TableEventStored: 1');

**API should**

* return ***X-TableEventStored*** header with value 1 only if data
  was written successfully in a transaction manner. On failure header
  should be returned with negative value.
* handle empty json arrays ***[]*** by simply returning success header value
* handle empty event objects ***[{}]*** by ignoring them while processing
  non-empty objects in the same array as expected.


Raspberry Pi pinout
-------
### Inputs
- **P2** - 5V VCC (instead of micro usb)
- **P6** - GND
- **P7** - INT RFId Reader 0
- **P8** - INT MCU6050 Gyro
- **P10** - INT Photo transistor 0
- **P11** - INT RFId Reader 1
- **P12** - INT Photo transistor 1
- **P13** - INT RFId Reader 2
- **P15** - INT RFId Reader 3

### Outputs
- **P1** - 3.3VCC
- **P3** - SDA
- **P5** - SCL
- **P9** - GND (paired with 3.3V rail)
- **P20** - GND (paired with beeper)
- **P22** - Beeper

---
**Thanks to:**

- [@drogon](http://wiringpi.com/contact/) - WiringPi
- [Jeff Rowberg](https://github.com/jrowberg/i2cdevlib) - MPU6050/i2cdevlib
- [Richard Hirst](https://github.com/richardghirst/PiBits/tree/master/MPU6050-Pi-Demo) - For hacking i2cdevlib on PI :)

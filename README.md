

  
 Gnat-Stats is an open-source project that transforms a small OLED display into a real-time PC hardware performance monitor using Arduino-compatible microcontrollers. It visually presents metrics like CPU and GPU temperatures, loads, and system memory usage.([GitHub][1], [GitHub][2])
 
![](https://github.com/koogar/Gnat-Stats/blob/master/images/3620111625420060746.png)
---

## 🔧 Features

* **Real-Time Monitoring**: Displays CPU/GPU temperatures, loads, and system RAM usage.
* **Compact Design**: Utilizes SSD1306 or SH1106 OLED displays for a minimal footprint.
* **Customizable Layouts**: Offers multiple display styles and anti-burn features.
* **Hardware Compatibility**: Supports boards like Seeeduino XIAO, Adafruit QT Py, and ESP32.
* **Serial Communication**: Receives data from a Windows client via USB serial.([GitHub][3])

---

## 🛠️ Getting Started

1. **Hardware Setup**:

   * Connect an SSD1306 or SH1106 OLED display to your microcontroller.
   * Ensure proper I2C connections and address configuration.([GitHub][3])
   * For detailed setup guides and tutorials, refer to the [Gnat-Stats OLED Display Hook-Up Guide](https://runawaybrainz.blogspot.com/2021/03/phat-stats-ssd1306-oled-hook-up-guide.html).

2. **Software Installation**:

   * Install necessary Arduino libraries:

     * Adafruit NeoPixel
     * Adafruit SSD1306
     * Adafruit SH110X
     * Adafruit GFX
     * Adafruit BusIO
   * Configure your board using the appropriate Board Manager URLs:

     * For Seeeduino XIAO:

       ```
       https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json
       ```

3. **Firmware Upload**:

   * Open the desired `.ino` file (e.g., `GnatStats_V1.7.Base.ino`) in the Arduino IDE.
   * Select the correct board and port.
   * Upload the sketch to your microcontroller.([GitHub][3])

4. **Windows Client**:

   * Install the [HardwareSerialMonitor](https://github.com/koogar/HardwareSerialMonitor) on your Windows PC to relay performance data.
3. **Configuration**:

   * Adjust settings within the Gnat-Stats firmware and HardwareSerialMonitor to match your hardware setup and monitoring preferences.


---

## 📜 License

This project is licensed under the [GPL-2.0 License](https://github.com/koogar/Gnat-Stats/blob/master/LICENSE.txt).

Gnat-Stats, Phat-Stats & Hardware Serial Monitor 
Copyright (C) 2016  Colin Conway, Rupert Hirst and contributors
 
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; If not, see <http://www.gnu.org/licenses/>.

---

For more details, visit the [Gnat-Stats GitHub Repository](https://github.com/koogar/Gnat-Stats).

[1]: https://github.com/koogar/Gnat-Stats/releases?utm_source=chatgpt.com "Releases · koogar/Gnat-Stats - GitHub"
[2]: https://github.com/koogar/Gnat-Stats/blob/master/GnatStats_V1.7.Base/DisplayStats.ino?utm_source=chatgpt.com "Gnat-Stats/GnatStats_V1.7.Base/DisplayStats.ino at master - GitHub"
[3]: https://github.com/koogar/Gnat-Stats/blob/master/GnatStats_V1.7.Base/GnatStats_V1.7.Base.ino?utm_source=chatgpt.com "Gnat-Stats/GnatStats_V1.7.Base/GnatStats_V1.7.Base.ino at ... - GitHub"
[4]: https://github.com/koogar/Gnat-Stats?utm_source=chatgpt.com "GitHub - koogar/Gnat-Stats: GnatStats Tiny OLED Arduino PC Hardware ..."


# Sistema de Riego Automatizado con Arduino Nano

Prototipo de control y monitoreo de riego automatizado desarrollado en C++ utilizando PlatformIO, sensores de humedad y nivel de agua, y visualización en tiempo real mediante pantalla OLED.

---

### Hardware y Componentes
* **Microcontrolador:** Arduino Nano (ATmega328P)
* **Pantalla:** OLED I2C 128x64 (SSD1306)
* **Sensores:** Sensor de humedad de suelo y sensor ultrasónico HC-SR04 (nivel de depósito)
* **Actuadores e Interfaz:** Módulo relevador (bomba de agua) y botones físicos de control

---

### Diagrama de Conexiones (Pinout)

| Componente | Pin Arduino Nano | Tipo |
| :--- | :---: | :--- |
| **Sensor de Humedad** | `A3` | Entrada Analógica |
| **Ultrasónico (Trigger)** | `D8` | Salida Digital |
| **Ultrasónico (Echo)** | `D9` | Entrada Digital |
| **Módulo Relevador (Bomba)** | `D2` | Salida Digital |
| **Botón Ajuste Humedad** | `D3` | Entrada Digital |
| **Botón Control Agua** | `D4` | Entrada Digital |
| **Pantalla OLED (SDA / SCL)** | `A4 / A5` | Comunicación I2C |

---

### Compilación y Carga
1. Abre la carpeta del proyecto en **Visual Studio Code** con la extensión **PlatformIO IDE** instalada.
2. Conecta el Arduino Nano por USB.
3. Ejecuta **PlatformIO: Upload** para compilar y cargar el firmware.
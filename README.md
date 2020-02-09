# Telegram_ESP32
Telegram fué anunciada oficialmente en el 2013, está enfocada en la mensajería instantánea, el envío de varios archivos y la comunicación en masa, la aplicación se parece mucho a WhatsApp con algunas funciones extras. 
La idea es conectar ESP32 programado con el IDE de Arduino para que envíe mensajes de chat a Telegram, también se puede hacer lo mismo para WhatsApp sin embargo debido a las bibliotecas disponibles en este momento, es mas simple conectar con Telegram.
Para ensamblar el proyecto vamos a necesitar las bibliotecas ArduinoJson-5.x.x (Debe ser esta versión), Universal-Arduino-Telegram-Bot y Bibliotecas para programar ESP32.

NOTA:
Para agregar las bibliotecas necesarias para el manejo de ESP32 con Arduino vamos a Archivos > Preferencias > Gestor de URLs Adiciones de Tarjetas  y agregamos la siguiente línea:  https://dl.espressif.com/dl/package_esp32_index.json
# Como funciona?
Claro que necesitamos tener instalado Telegram en nuestro teléfono y su funcionamiento se basa en los Bot (Robots de software) de Telegram.
Lo primero que tenemos que hacer es crear un bot para conversar con ESP32, para esto en Telegram buscamos Botfather, un robot para crear robots, iniciamos conversación con el y escribimos /newbot donde nos preguntará el nombre del nuevo bot y el nombre de usuario, es importante que el nombre de usuario termine con la palabra bot por ejemplo prueba_bot.
Una vez que Botfather confirma la creación del nuevo bot asigna una identificación única a ese bot, este número o token será necesario para controlar el bot y debe ser privado ya que cualquiera que lo tenga controlara el robot.
En el programa para ESP32 el token declarado permite la conexión con el bot de telegram.
Mas info se puede consultar en www.firtec.com.ar

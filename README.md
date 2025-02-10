# Automatic Swing Barrier Gate

[Video Example](https://github.com/a-elmohamady/Automatic-Swing-Barrier-Gate/blob/main/example/example.mp4)

## وصف المشروع
هذا المشروع يهدف إلى تصميم وتنفيذ بوابة أتوماتيكية متأرجحة (Swing Barrier Gate) مخصصة للتحكم في دخول الأفراد. يمكن فتح البوابة باستخدام:
1. **نظام تحكم بالوصول (Access Control)**: مثل البطاقات الذكية أو القارئ البيومتري.
2. **QR Code**: يمكن للأفراد فتح البوابة عن طريق مسح رمز QR مخصص.
3. **زر تحكم يدوي**: للتحكم المباشر في فتح وإغلاق البوابة.

يتم استخدام المتحكم الدقيق **Arduino Nano** لقراءة الإشارات من المستشعرات أو أنظمة التحكم واتخاذ القرارات لفتح أو إغلاق البوابة تلقائيًا.

## المميزات
- **التحكم الأتوماتيكي**: يتم فتح البوابة تلقائيًا عند استخدام بطاقة وصول، قارئ بيومتري، أو مسح رمز QR.
- **التحكم اليدوي**: يمكن فتح البوابة يدويًا باستخدام زر تحكم.
- **الأمان**: يتم إغلاق البوابة تلقائيًا بعد مرور الفرد لمنع الدخول غير المصرح به- نظام انزار للدخول غير المسموح او الدخول عكس اتجاه الفتح
.
- **سهولة التركيب**: تم تصميم النظام ليكون سهل التركيب والصيانة.

## المكونات المستخدمة
- **المتحكم الدقيق**: Arduino Nano
- **مستشعر حركة الأفراد**: E18-D80NK (للكشف عن اقتراب الأفراد)
- **مستشعر تحديد مكان البوابة**: Infrared Obstacle Sensor (للتأكد من إغلاق البوابة بشكل صحيح)
- **نظام QR Code**: قارئ QR Code أو كاميرا لمسح الرمز
- **زر تحكم يدوي**: Push Button
- **محرك (Motor)**: لتحريك البوابة
- **وحدات تحكم**: Relay Module
- **مصدر طاقة**: Power Supply
- **أجزاء ميكانيكية**: Swing Barrier Gate



# Automatic Swing Barrier Gate

[Video Example](https://github.com/a-elmohamady/Automatic-Swing-Barrier-Gate/blob/main/example/example.mp4)
## Project Description
This project aims to design and implement an **Automatic Swing Barrier Gate** for controlling individual access. The gate can be opened using:
1. **Access Control System**: Such as smart cards or biometric readers.
2. **QR Code**: Individuals can open the gate by scanning a designated QR code.
3. **Manual Control Button**: Allows direct control to open and close the gate.

An **Arduino Nano** microcontroller is used to read signals from sensors or control systems and make decisions to automatically open or close the gate.

## Features
- **Automatic Control**: The gate opens automatically when an access card, biometric reader, or QR code is used.
- **Manual Control**: The gate can be manually opened using a control button.
- **Security**: The gate automatically closes after a person passes through to prevent unauthorized access. An alert system is included to detect unauthorized entry or entry in the opposite direction.
- **Easy Installation**: The system is designed to be easy to install and maintain.

## Components Used
- **Microcontroller**: Arduino Nano
- **Motion Sensor**: E18-D80NK (for detecting approaching individuals)
- **Gate Position Sensor**: Infrared Obstacle Sensor (to ensure the gate is properly closed)
- **QR Code System**: QR Code reader or camera for scanning
- **Manual Control Button**: Push Button
- **Motor**: To operate the gate
- **Control Modules**: Relay Module
- **Power Supply**: Power source for the system
- **Mechanical Parts**: Swing Barrier Gate


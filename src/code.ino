// تعريف المدخلات
const int motionRightPin = 2;    // حساس حركة جهة اليمين
const int motionLeftPin = 3;     // حساس حركة جهة اليسار
const int SENSOR_1 = 4;      // حساس 1
const int SENSOR_2 = 5;     //  حساس 2
const int SENSOR_3 = 6;       //  حساس 3
const int openRightSignalPin = A0; // إشارة فتح جهة اليمين
const int openLeftSignalPin = A1;  // إشارة فتح جهة اليسار
// تعريف المخرجات
const int motorRightPWM = 9;     // مخرج PWM لمحرك الفتح جهة اليمين
const int motorLeftPWM = 10;     // مخرج PWM لمحرك الفتح جهة اليسار
const int unlockPin = 11;        // مخرج فك قفل الحركة
const int alarmPin = 12;         // مخرج الإنذار
// المتغيرات العامة
const int MOTOR_SPEED = 60;        // سرعة المحرك (0-255)
const unsigned long WAIT_TIME = 5000; // وقت الانتظار (5 ثواني)
bool status = false;             // حالة الباب (مفتوح/مغلق)

bool SENSOR_is_Active = LOW ;
bool motion_is_Active = LOW ;
bool open_Signa_is_Active = LOW ;


void setup() {
    // تهيئة المدخلات
  pinMode(motionRightPin, INPUT_PULLUP);
  pinMode(motionLeftPin, INPUT_PULLUP);
  pinMode(SENSOR_1, INPUT_PULLUP);
  pinMode(SENSOR_2, INPUT_PULLUP);
  pinMode(SENSOR_3, INPUT_PULLUP);
  pinMode(openRightSignalPin, INPUT_PULLUP);
  pinMode(openLeftSignalPin, INPUT_PULLUP);
  // تهيئة المخرجات
  pinMode(motorRightPWM, OUTPUT);
  pinMode(motorLeftPWM, OUTPUT);
  pinMode(unlockPin, OUTPUT);
  pinMode(alarmPin, OUTPUT);
  // التأكد من أن من إيقاف المحركات في البداية
  analogWrite(motorRightPWM, 0);
  analogWrite(motorLeftPWM, 0);
  // التأكد من أن القفل مغلق في البداية
  digitalWrite(unlockPin, LOW);
  // بدء الاتصال التسلسلي لعرض الرسائل (لأغراض التصحيح)
  Serial.begin(9600);
  Serial.println("Start");
}
void loop() {

  //  Serial.println("Start11");
  //  Serial.println(digitalRead(SENSOR_1) );
  // //  Serial.print(digitalRead(" ----- ") );
  //  Serial.println(digitalRead(SENSOR_2) );
  // //  Serial.print(digitalRead(" ------- ") );
  //     Serial.println(digitalRead(SENSOR_3) );


while ((digitalRead(SENSOR_1) == digitalRead(SENSOR_2)) && 
       (digitalRead(SENSOR_2) == digitalRead(SENSOR_3))) { 
        Serial.println("SENSOR_error");
    // حالة غير متوقعة، يمكن تشغيل إنذار
    triggerAlarm();
    
}

   // السيناريو 1: فتح الباب جهة اليمين
  if (digitalRead(openRightSignalPin) == open_Signa_is_Active && digitalRead(openLeftSignalPin) != open_Signa_is_Active) {
    status = true; // تحديث حالة الباب إلى "مفتوح"
    executeRightOpenScenario();
  }
  // السيناريو 2: فتح الباب جهة اليسار
  if (digitalRead(openLeftSignalPin) == open_Signa_is_Active &&  digitalRead(openRightSignalPin) != open_Signa_is_Active) {
    status = true; // تحديث حالة الباب إلى "مفتوح"
    executeLeftOpenScenario();
  }

  if(digitalRead(openLeftSignalPin)   == digitalRead(openLeftSignalPin)){ closeDoor();}
    // التحقق من الحركة غير المصرح بها
    checkUnauthorizedMovement() ;
}
// دالة تنفيذ سيناريو الفتح يمينًا
void executeRightOpenScenario() {
  Serial.println("executeRightOpenScenario");
  // فك قفل الحركة
  unlock();
  int sofOpen_SPEED =  MOTOR_SPEED /6 ; // سرعة بداية الحركة (تسريع تدريجي)
  analogWrite(motorLeftPWM, 0);  // التاكد من ايقاف المحرك الأيسر
  while (digitalRead(SENSOR_3) != SENSOR_is_Active || ( digitalRead(SENSOR_3) != SENSOR_is_Active  &&  digitalRead(SENSOR_1) != SENSOR_is_Active  &&  digitalRead(SENSOR_2) != SENSOR_is_Active   )) {
   analogWrite(motorRightPWM, sofOpen_SPEED ); // تشغيل المحرك الأيمن بسرعة متزايدة
    if(sofOpen_SPEED < MOTOR_SPEED){
      sofOpen_SPEED += 1; // زيادة السرعة تدريجيًا
    }else{
      sofOpen_SPEED = MOTOR_SPEED; // الوصول إلى السرعة القصوى
      }
  }
    analogWrite(motorRightPWM, 0); // إيقاف المحرك الأيمن
      // الانتظار 5 ثواني أو حتى يتم تفعيل حساس الحركة اليسار ثم اليمين
    int motionStatus = waitForMotionSequence(motionLeftPin, motionRightPin, WAIT_TIME);
    if (motionStatus == -1) {
    // تم تفعيل الحساس الثاني قبل الأول (اليمين قبل اليسار)
    triggerAlarm(); // تفعيل الإنذار
  }
  // في جميع الحالات (تسلسل صحيح، مهلة انتهت، أو إنذار)، يتم إغلاق الباب
  closeDoor();
}
// دالة تنفيذ سيناريو الفتح يسارًا
void executeLeftOpenScenario() {
  Serial.println("executeLeftOpenScenario");
  // فك قفل الحركة
  unlock();
  int sofOpen_SPEED =  MOTOR_SPEED /6; // سرعة بداية الحركة (تسريع تدريجي)
  analogWrite(motorRightPWM, 0);// التاكد من ايقاف المحرك الأيمن
  while (digitalRead(SENSOR_3) != SENSOR_is_Active   || ( digitalRead(SENSOR_3) != SENSOR_is_Active  &&  digitalRead(SENSOR_1) != SENSOR_is_Active  &&  digitalRead(SENSOR_2) != SENSOR_is_Active   )  ) {
  // تشغيل المحرك جهة اليسار حتى يصل الباب إلى حساس اليسار
    analogWrite(motorLeftPWM, sofOpen_SPEED ); // تشغيل المحرك الأيسر بسرعة متزايدة
    if(sofOpen_SPEED < MOTOR_SPEED){
      sofOpen_SPEED += 1;; // زيادة السرعة تدريجيًا
    }else{
      sofOpen_SPEED = MOTOR_SPEED;// الوصول إلى السرعة القصوى
      }
  }
  analogWrite(motorLeftPWM, 0); // إيقاف المحرك الأيسر
  // الانتظار 5 ثواني أو حتى يتم تفعيل حساس الحركة اليمين ثم اليسار
  int motionStatus = waitForMotionSequence(motionRightPin, motionLeftPin, WAIT_TIME);
  if (motionStatus == -1) {
    // تم تفعيل الحساس الثاني قبل الأول (اليسار قبل اليمين)
    triggerAlarm();  // تفعيل الإنذار
  }
  // في جميع الحالات (تسلسل صحيح، مهلة انتهت، أو إنذار)، يتم إغلاق الباب
  closeDoor();
}
// دالة فك قفل الحركة
void unlock(){
   Serial.println("unlock");
   digitalWrite(unlockPin, HIGH); // تفعيل فك القفل
   delay(90);  // انتظار 90 مللي ثانية لضمان تفعيل القفل
}
// دالة إغلاق الباب
void closeDoor() {
  Serial.println("closeDoor");
  if ( digitalRead(SENSOR_1) == SENSOR_is_Active  &&  digitalRead(SENSOR_2) == SENSOR_is_Active ) {
    Serial.println("Door is close");
     // حالة القفل (الباب مغلق تمامًا)
    analogWrite(motorLeftPWM, 0); // إيقاف المحرك الأيسر
    analogWrite(motorRightPWM, 0); // إيقاف المحرك الأيمن
    Serial.println("Lock door");
    digitalWrite(unlockPin, LOW); // إعادة قفل الحركة
    status = false; // تحديث حالة الباب إلى "مغلق"
  } else {
    // تحريك الباب للوصول لحالة القفل
  unlock(); // فك القفل
  // if (status){
  int sofClose_SPEED =  MOTOR_SPEED ; // سرعة الإغلاق
  while (digitalRead(SENSOR_1) != SENSOR_is_Active && digitalRead(SENSOR_2) == SENSOR_is_Active){
            Serial.println("goRight");

            analogWrite(motorRightPWM, sofClose_SPEED);
            analogWrite(motorLeftPWM, 0);
            if(sofClose_SPEED > MOTOR_SPEED /2  ){sofClose_SPEED = sofClose_SPEED - 10;}
            else{sofClose_SPEED = MOTOR_SPEED / 2 ;}
            
    }
      // تحريك الباب جهة اليمين حتى يتم تفعيل حساس 1
  while (digitalRead(SENSOR_2) != SENSOR_is_Active && digitalRead(SENSOR_1) == SENSOR_is_Active) {
    
      Serial.println("goLeft");

      analogWrite(motorLeftPWM, sofClose_SPEED);  // تشغيل المحرك الأيمن
      analogWrite(motorRightPWM, 0);  // إيقاف المحرك الأيسر
       if(sofClose_SPEED > MOTOR_SPEED / 2 ){
        sofClose_SPEED -= 10;  // تقليل السرعة تدريجيًا
        }
       else{
        sofClose_SPEED = MOTOR_SPEED / 2 ; // الوصول إلى السرعة الدنيا
       }
    }
  //  }else{
  // int sofClose_SPEED =  MOTOR_SPEED / 4 ;  // سرعة بداية الإغلاق
  //     // تحريك الباب جهة اليمين حتى يتم تفعيل حساس 1
  // while (digitalRead(SENSOR_1) != SENSOR_is_Active  &&  digitalRead(SENSOR_2) == SENSOR_is_Active){
  //   Serial.println("goRight ------------ ");
  //           analogWrite(motorRightPWM, sofClose_SPEED); // تشغيل المحرك الأيمن
  //           analogWrite(motorLeftPWM, 0);// إيقاف المحرك الأيسر
  //           if(sofClose_SPEED < MOTOR_SPEED){
  //             sofClose_SPEED += 10; // زيادة السرعة تدريجيًا
  //             }else{
  //               sofClose_SPEED = MOTOR_SPEED; // الوصول إلى السرعة القصوى
  //               }    
  //   }
  //     // تحريك الباب جهة اليسار حتى يتم تفعيل حساس 2
  // while (digitalRead(SENSOR_2) != SENSOR_is_Active && digitalRead(SENSOR_1) == SENSOR_is_Active ) {
  //       Serial.println("goLeft ------------");

  //     analogWrite(motorLeftPWM, sofClose_SPEED);// تشغيل المحرك الأيسر
  //     analogWrite(motorRightPWM, 0);  // إيقاف المحرك الأيمن
  //      if(sofClose_SPEED < MOTOR_SPEED){
  //       sofClose_SPEED += 10; // زيادة السرعة تدريجيًا
  //       }
  //      else{
  //       sofClose_SPEED = MOTOR_SPEED ;  // الوصول إلى السرعة القصوى
  //       }
  //   }
  //  }
  }
}
// دالة التحقق من الحركة غير المصرح بها
void checkUnauthorizedMovement() {
        

  
    if ((digitalRead(motionRightPin) == motion_is_Active && digitalRead(openLeftSignalPin) != open_Signa_is_Active) ||  (digitalRead(motionLeftPin) == motion_is_Active && digitalRead(openRightSignalPin) != open_Signa_is_Active) ) {
      Serial.println("UnauthorizedMovement");
      unsigned long startTime = millis(); // حفظ وقت بدء الإنذار
      while ((millis() - startTime < 1000 )  && digitalRead(openLeftSignalPin) != open_Signa_is_Active &&  digitalRead(openRightSignalPin) != open_Signa_is_Active ) {
        digitalWrite(alarmPin, HIGH); // تفعيل الإنذار
      }
      digitalWrite(alarmPin, LOW);// إيقاف الإنذار
    }
}
// دالة تفعيل الإنذار
void triggerAlarm() {
  digitalWrite(alarmPin, HIGH); // تفعيل الإنذار
  delay(1000); // الإنذار يعمل لمدة ثانية
  digitalWrite(alarmPin, LOW);// إيقاف الإنذار
}
// دالة الانتظار مع التحقق من تسلسل الحساسات
int waitForMotionSequence(int firstSensor, int secondSensor, unsigned long waitTime) {
  unsigned long startTime = millis(); // حفظ وقت بدء الانتظار
  bool firstSensorTriggered = false; // حالة تفعيل الحساس الأول
  while (millis() - startTime < waitTime) {
    if (digitalRead(firstSensor) == motion_is_Active) {
      firstSensorTriggered = true; // تم تفعيل الحساس الأول
    }
    if (firstSensorTriggered && digitalRead(secondSensor) == motion_is_Active) {
      return 1; // تم تفعيل التسلسل الصحيح
    }
    if (digitalRead(secondSensor) == motion_is_Active && !firstSensorTriggered) {
      return -1; // تم تفعيل الحساس الثاني قبل الأول
    }
  }
  return 0; // انتهت المهلة دون تفعيل التسلسل الصحيح
}
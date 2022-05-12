# Car Reverse Sensor (Demo)

Website: [http://compro.pongphun.com](http://compro.pongphun.com)\
Tinkercad demo link (without wifi): [https://www.tinkercad.com/things/3QwPCx9ffWl](https://www.tinkercad.com/things/3QwPCx9ffWl)\
Wokwi demo link (with wifi): [https://wokwi.com/projects/330841959706919507](https://wokwi.com/projects/330841959706919507)

![Demo car reverse sensor](/images/demo.png "car reverse sensor")

## Abstract
โปรเจคนี้ มีวัตถุประสงค์เพื่อสร้าง Car Reverse Sensor (เซนเซอร์วัดระยะห่างของรถยนต์) ด้วย Microcontroller ทั้งนี้เพื่อ
เป็นการศึกษาระบบการทำงานของ Microcontroller และ ใช้ในการตรวจเช็คระยะห่างของรถยนต์ในจุดที่ไม่สามารถมองเห็นได้ด้วยตา ส่งผลให้รับรู้ระยะห่างที่ไม่สามารถมองเห็นได้ โดยทั่วไปจะใช้ในการถอยรถยนต์เพื่อเข้าจอด เพื่อให้รับรู้ได้ถึงสิ่งที่จะมากระทบต่อรถยนต์ ขณะกำลังถอยรถยนต์
โดยการทำงานของ Microcontroller จะสามารถรับคำสั่งได้ด้วยการเขียนโค้ดคำสั่งใน Wokwi.com ส่วนของอุปกรณ์ประกอบไปด้วย HC-SR04 (ultrasonic distance sensor), Buzzer, ESP-32 และมีการ Connect WiFi เพื่อส่งสัญญาณเตือนผ่านหน้า Website เมื่อรถชนขณะกำลังถอยหลัง เพื่อแจ้งเตือนในการชนอีกด้วย

![Poster](/Poster/ComPro-Project.jpg "Poster")

## Project Detail
Car Reverse Sensor หรือ เซนเซอร์วัดระยะห่างของรถยนต์ สร้างขึ้นมาเพื่อใช้ในการถอยรถยนต์เพื่อเข้าจอด โดยใช้ ultrasonic distance sensor ซึ่งเป็นเซ็นเซอร์ที่ใช้สำหรับตรวจจับวัดถุต่างๆ โดยอาศัยหลักการสะท้อนของคลื่นความถี่เสียง คำนวณหาค่าระยะทางได้จากการเดินทางของคลื่นและนำมาเทียบกับเวลา ด้วยกลไกดังกล่าวทำให้สามารถนำมาประยุกต์ใช้งานในรูปแบบต่าง ๆ ได้อย่างมากมาย มาเป็นตัวควบคุมการทำงานของระบบ  โดยหากรถยนต์ได้ถอยมากระทบกับวัตถุบางอย่าง จะใช้สัญญาณ WiFi เพื่อส่งสัญญานเตือนผ่านหน้า Website เพื่อแจ้งเตือนให้ผู้ใช้งานได้ทราบ

## Usage Example Video
Youtube: [https://www.youtube.com/embed/UqZsu2JbV_I](https://www.youtube.com/embed/UqZsu2JbV_I)

[![Youtube VDO](https://cdn.discordapp.com/attachments/880736678954811413/974280048871878676/unknown.png "car reverse sensor")](https://www.youtube.com/embed/UqZsu2JbV_I)

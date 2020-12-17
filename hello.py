from flask import Flask,render_template,redirect,url_for,request
from picamera import PiCamera
import time
from time import sleep
import serial

arduino = serial.Serial("/dev/ttyACM1",115200)
app = Flask(__name__)

@app.route('/')                     # 기본('/') 웹주소로 요청이 오면                     
def home():                        #hello 함수 실행
    return render_template('index.html')


@app.route('/',methods=['POST'])
def sending():
    #LCD part
    try :
        value_LCD=request.form['LCD']
    except :
        value_LCD="no input"
    msg_LCD="LCD"+str(value_LCD)
    print("LCD sending message: "+ str(msg_LCD))
    msg_LCD=msg_LCD.encode('utf-8')
    arduino.write(msg_LCD)
    time.sleep(1)
    #seg 7 part
    try :
        value_seg7=request.form['seg7']
        msg_seg7="seg7"+str(value_seg7)
        print("seg7 sending message: "+ str(msg_seg7))
        msg_seg7=msg_seg7.encode('utf-8')
        arduino.write(msg_seg7)
    except:
        print("no input for 7seg")
    return redirect(url_for('home'))


@app.route('/picture')
def taking_picture():
    camera = PiCamera()
    camera.capture('/home/pi/webapp/static/image/picture.jpg')
    sleep(2)
    camera.close()
    mode="picture"
    mode=mode.encode('utf-8')
    arduino.write(mode)
    return redirect(url_for('aftershot'))

@app.route('/aftershot')
def aftershot():
    return render_template('aftershot.html')


if __name__ == '__main__':          # 현재 파일 실행시 개발용 웹서버 구동
    app.run(debug=True, port=8080, host='0.0.0.0')  

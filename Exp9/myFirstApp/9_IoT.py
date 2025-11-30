import RPi.GPIO as GPIO
from flask import Flask, render_template, request

app = Flask(__name__)

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

ledRed = 13
ledYellow = 19
ledGreen = 26

GPIO.setup(ledRed, GPIO.OUT)
GPIO.setup(ledYellow, GPIO.OUT)
GPIO.setup(ledGreen, GPIO.OUT)

GPIO.output(ledRed, GPIO.LOW)
GPIO.output(ledYellow, GPIO.LOW)
GPIO.output(ledGreen, GPIO.LOW)

@app.route("/")
def index():
    ledRedSts = GPIO.input(ledRed)
    ledYellowSts = GPIO.input(ledYellow)
    ledGreenSts = GPIO.input(ledGreen)

    templateData = {
        'ledRed': ledRedSts,
        'ledYellow': ledYellowSts,
        'ledGreen': ledGreenSts
    }
    return render_template('index.html', **templateData)

@app.route("/<deviceName>/<action>")
def action(deviceName, action):
    if deviceName == "ledRed":
        actuator = ledRed
    elif deviceName == "ledYellow":
        actuator = ledYellow
    elif deviceName == "ledGreen":
        actuator = ledGreen

    if action == "on":
        GPIO.output(actuator, GPIO.HIGH)
    elif action == "off":
        GPIO.output(actuator, GPIO.LOW)

    ledRedSts = GPIO.input(ledRed)
    ledYellowSts = GPIO.input(ledYellow)
    ledGreenSts = GPIO.input(ledGreen)

    templateData = {
        'ledRed': ledRedSts,
        'ledYellow': ledYellowSts,
        'ledGreen': ledGreenSts
    }
    return render_template('index.html', **templateData)

if __name__ == "__main__":
    app.run(host="0.0.0.0", debug=True)

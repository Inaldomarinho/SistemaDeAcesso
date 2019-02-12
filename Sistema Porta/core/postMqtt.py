import paho.mqtt.client as mqttClient
import time


def on_connect(client, userdata, flags, rc):
    if rc == 0:

        print("Connected to broker")

        global Connected  # Use global variable
        Connected = True  # Signal connection

    else:

        print("Connection failed")


def postMQTT(msg):
    Connected = False  # global variable for the state of the connection

    broker_address = "m16.cloudmqtt.com"
    port = 17990
    user = "zzzzrxve"
    password = "eUo0gAhjtyPe"

    client = mqttClient.Client("Python")  # create new instance
    client.username_pw_set(user, password=password)  # set username and password
    client.on_connect = on_connect  # attach function to callback
    client.connect(broker_address, port=port)  # connect to broker

    client.loop_start()  # start the loop

    client.publish("python/test", msg)

    client.loop_stop()

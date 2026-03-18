from machine import Pin
import time

click_count = 0
# Підключаємо вбудований зелений світлодіод на Pico
led = Pin("LED", Pin.OUT) 

def count_pulse(pin):
    global click_count
    click_count += 1
    led.toggle() # Плата блиматиме при кожному кліку

geiger_pin = Pin(8, Pin.IN) 
# Ловимо і падіння напруги
geiger_pin.irq(trigger=Pin.IRQ_FALLING , handler=count_pulse)

print("...")

while True:
    time.sleep(10)
    print(f"Частинок за останні 10 сек: {click_count}")
    click_count = 0